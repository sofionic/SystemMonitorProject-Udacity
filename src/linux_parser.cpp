#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>

#include "linux_parser.h"
//using namespace std;
 

using std::stof;
using std::string;
using std::to_string;
using std::vector;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, kernel, version;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >>version >>kernel;
  }
  return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

//  Read and return the system memory utilization

float LinuxParser::MemoryUtilization() {
float totalmemory{0.0}, buffer{0.0},memoryfree{0.0},value{0.0};
string line, key;
std::ifstream filestream(kProcDirectory + kMeminfoFilename);
if(filestream.is_open()){
  while(std::getline(filestream, line)){
  std::istringstream linestream(line);
    while (linestream >> key >> value){
      if (key == "MemTotal:"){
      totalmemory = value;     
      }
      else if(key == "MemFree:"){
      memoryfree = value;      
      }
      else  if(key == "Buffers:"){
      buffer = value;    
      } 
    }
  }
}
return 1.0 -(memoryfree/(totalmemory - buffer));} 

//  Read and return the system uptime
long LinuxParser::UpTime() { 
  string line, totalUpTime;
  long tUpTime{0};
  std::ifstream stream(kProcDirectory+kUptimeFilename);
  if (stream.is_open()){
    std::getline(stream, line);
    std::istringstream stream(line);
    if(stream>>totalUpTime)
    tUpTime=stof(totalUpTime);
  }

  return tUpTime; }


//  Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { 

  return ActiveJiffies()+IdleJiffies();}

//  Read and return the number of active jiffies for a PID
 
long LinuxParser::ActiveJiffies(int pid) {
  	vector<string> pid_stats = CpuUtilization(pid);
  	return std::stol(pid_stats[13]) + std::stol(pid_stats[14]) + 
    std::stol(pid_stats[15]) + std::stol(pid_stats[16]);
    }
vector<string> LinuxParser::CpuUtilization(int pid) {
	std::ifstream pidFile(kProcDirectory + std::to_string(pid) + kStatFilename);
  	if (pidFile) {
      string pidLine;
      getline(pidFile, pidLine);
      pidFile.close();
      
      std::istringstream pidStream(pidLine);
      std::vector<string> pidTokens;
      string pidToken;
      
      while(pidStream >> pidToken) {
      	pidTokens.push_back(pidToken);
      }
      return pidTokens;
    }
  	return {};
}

// Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { 
  long activeJiffies;
  vector<CPUStates> activeStates{kUser_,kNice_,kSystem_,kIRQ_,kSoftIRQ_,kSteal_};
  vector<string> utilization=CpuUtilization();
  for (auto state: activeStates){ activeJiffies+=stol(utilization[state]);}
  return activeJiffies;
}

// Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { 
  long idleJiffies;
  vector<CPUStates> idleStates {kIdle_,kIOwait_}
  ;
   vector<string> utilization=CpuUtilization();
  for (auto state: idleStates){ idleJiffies+=stol(utilization[state]);}
  return idleJiffies;
}

//  Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() {
   string line, value;
   vector<string> utilizationData{};
   std::ifstream stream(kProcDirectory+kStatFilename);
   if(stream.is_open()){
     std::getline(stream, line);
     std::istringstream linestream(line);
     while(linestream>>value){
       if(value!="cpu"){utilizationData.emplace_back(value);}
     };
   }   
return utilizationData; }

//  Read and return the total number of processes
int LinuxParser::TotalProcesses() { 
  string line, key;
  int processes, value;
  std::ifstream filestream (kProcDirectory+kStatFilename);
  if(filestream.is_open()){
    while(std::getline(filestream,line)){
      std::istringstream stream(line);
      while(stream>>key>>value){
        if (key=="processes"){ processes=value;}
      }
    }
  }  
return processes; }

//  Read and return the number of running processes
int LinuxParser::RunningProcesses() { 
  string line, key;
  int runningProcesses, value;
  std::ifstream filestream (kProcDirectory+kStatFilename);
  if(filestream.is_open()){
    while(std::getline(filestream,line)){
      std::istringstream stream(line);
      while(stream>>key>>value){
        if (key=="procs_running"){runningProcesses=value;}
      }
    }
  }  
return runningProcesses; }

//  Read and return the command associated with a process
 
string LinuxParser::Command(int pid) { 
  string line;
  std::ifstream filestream(kProcDirectory+to_string(pid)+kCmdlineFilename);
  if(filestream.is_open()){
    std::getline(filestream,line);
  }
  return line; }

//  Read and return the memory used by a process
 
string LinuxParser::Ram(int pid) { 
  string line, key, value, VmSize;
  int ram=0;
  std::ifstream filestream (kProcDirectory+to_string(pid)+kStatusFilename);
  if(filestream.is_open()){
    while(std::getline(filestream,line)){
      std::replace(line.begin(), line.end(),':', ' ');
      std::istringstream stream(line);
      while(stream>>key>>value){
        if (key=="VmSize"){ ram=std::stoi(value)/1024;return to_string(ram);}
      }
    }    
  }
  return to_string(ram); }

//  Read and return the user ID associated with a process
 
  string LinuxParser::Uid(int pid) {
  std::ifstream userFile(kProcDirectory + std::to_string(pid) + kStatusFilename);
  string uid;
  if (userFile) {
    while(userFile.is_open()) {
      string userLine;
      getline(userFile, userLine);
      std::istringstream userStream(userLine);
      
      string key, value;
      userStream >> key >> value;
      if (key == "Uid:") {
        uid = value;
        userFile.close();
      }
    }
  }
  return uid;
}

  string LinuxParser::User(int pid) {
  string uid = Uid(pid);
  std::ifstream etc_password(kPasswordPath);
  if (etc_password) {
    while(etc_password.is_open()) {
      string line;
      getline(etc_password, line);

      std::istringstream line_stream(line);
      string user, mode, matching_uid;
      getline(line_stream, user, ':');
      getline(line_stream, mode, ':');
      getline(line_stream, matching_uid, ':');

      if (matching_uid == uid) {
      	etc_password.close();
        return user;
      }
    }
    etc_password.close();
  }
  return string();
}

//  Read and return the uptime of a process
 
long LinuxParser::UpTime(int pid) { 
 	std::vector<std::string> pidStatuses = CpuUtilization(pid);
 	//return UpTime() - (std::stol(pidStatuses[21]) / sysconf(_SC_CLK_TCK)) ;
  return (std::stol(pidStatuses[21]) / sysconf(_SC_CLK_TCK)) ;
}
