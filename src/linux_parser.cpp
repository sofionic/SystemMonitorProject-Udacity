#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>

#include "linux_parser.h"

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

// TODO: Read and return the system memory utilization

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

// TODO: Read and return the system uptime
long LinuxParser::UpTime() { 
  string line, totalUpTime;
  float tUpTime{0};
  std::ifstream stream(kProcDirectory+kUptimeFilename);
  if (stream.is_open()){
    std::getline(stream, line);
    std::istringstream stream(line);
    if(stream>>totalUpTime)
    tUpTime=stof(totalUpTime);
  }

  return tUpTime; }

// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { 
  return UpTime()*sysconf(_SC_CLK_TCK); }

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid[[maybe_unused]]) {
   return 0; }

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { 
  long activeJiffies;
  vector<CPUStates> activeStates{kUser_,kNice_,kSystem_,kIRQ_,kSoftIRQ_,kSteal_};
  vector<string> utilization=CpuUtilization();
  for (auto state: activeStates){ activeJiffies+=stol(utilization[state]);}
  return activeJiffies;
}

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { 
  long idleJiffies;
  vector<CPUStates> idleStates {kIdle_,kIOwait_}
  ;
   vector<string> utilization=CpuUtilization();
  for (auto state: idleStates){ idleJiffies+=stol(utilization[state]);}
  return idleJiffies;
}

// TODO: Read and return CPU utilization
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

// TODO: Read and return the total number of processes
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

// TODO: Read and return the number of running processes
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

// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid) { 
  string line;
  std::ifstream filestream(kProcDirectory+to_string(pid)+kCmdlineFilename);
  if(filestream.is_open()){
    std::getline(filestream,line);
  }
  return line; }

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid) { 
  string line, key, value, VmSize;
  int ram=0;
  std::ifstream filestream (kProcDirectory+to_string(pid)+kStatusFilename);
  if(filestream.is_open()){
    while(std::getline(filestream,line)){
      std::replace(line.begin(), line.end(),':', ' ');
      std::istringstream stream(line);
      while(stream>>key>>value){
        if (key=="VmSize"){ ram=std::stoi(value)/1000;break;}
      }
    }    
  }
  return to_string(ram); }

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid) { 
  string line, key, value,UID;
  std::ifstream fileStream (kProcDirectory+to_string(pid)+kStatFilename);
  if(fileStream.is_open()){
    while(std::getline(fileStream,line)){
      std::replace(line.begin(), line.end(),':',' ');
      std::istringstream lineStream(line);
      while(lineStream>>key>>value){
        if(key=="Uid:"){UID=value;break;}        
      }
    }
  }
  return UID;}

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid) { 
  string uid = LinuxParser::Uid(pid);
  string line, key, user,userName, uidValue;
  std::ifstream fileStream (kPasswordPath);
  if(fileStream.is_open()){
    while(std::getline(fileStream,line)){
      std::replace(line.begin(), line.end(),':',' ');
      std::istringstream lineStream(line);
      while(lineStream>>user>>key>>uidValue){
        if(uidValue==uid){userName=user;break;}         
      }
    }
  }
  return userName; }

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid) { 
  string file_name{kProcDirectory+to_string(pid)+kStatFilename}, timeValue;;
  std::ifstream file {file_name};
  if(file.is_open()){
    string line, value;
    while(std::getline(file,line)){
      std::istringstream linestream(line);
      for(int i=0; i<21; i++, linestream>>value);
      timeValue=value;
      //return stoi(value);
    }
}
//return 0; 
return stoi(timeValue);}