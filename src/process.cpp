#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>
#include <linux_parser.h>

#include "process.h"
#include "processor.h"

using std::string;
using std::to_string;
using std::vector;

//Process::Process(int pid) : pid_(pid), user_(LinuxParser::User(pid)), command_(LinuxParser::Command(pid)){
//Process::Ram();Process::UpTime();Process::CpuUtilization();}
// TODO: Return this process's ID
int Process::Pid() { //return LinuxParser::Pids(); }
int pid_{0};
return pid_; }

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() {
   /* string key, line, tokenUtil;
    vector<string> values;
    int uTime=0;
    int sTime=0;
    int cuTime=0;
    int csTime=0;
    float startTime=0.0;
    std::ifstream fileStream (LinuxParser::kProcDirectory+to_string(pid_)+LinuxParser::kStatFilename);
    if (fileStream.is_open()){
        std::getline(fileStream,line);
        std::istringstream lineStream(line);
        while(lineStream>>tokenUtil){
            values.push_back(tokenUtil);}
    }
    uTime=std::stoi(values[13]);
    sTime=std::stoi(values[14]);
    cuTime=std::stoi(values[15]);
    csTime=std::stoi(values[16]);
    startTime=std::stof(values[21]);
    float totalTime=float(uTime+sTime+cuTime+csTime);
    float seconds=float(LinuxParser::UpTime()-(startTime/sysconf(_SC_CLK_TCK)));
    cpuUtilization_=(totalTime/sysconf(_SC_CLK_TCK))/seconds;

    return cpuUtilization_ ;*/
    int pid_{0};
    //float cpuUtilization=LinuxParser::CpuUtilization(pid_);
    float cpuUtilization =5.5;
    return cpuUtilization;
    }

// TODO: Return the command that generated this process
string Process::Command() { int pid_ {0};
    return LinuxParser::Command( Process::Pid()); }

// TODO: Return this process's memory utilization
string Process::Ram() {
    int pid_{0};
    return  LinuxParser::Ram(Process::Pid());}

// TODO: Return the user (name) that generated this process
string Process::User() { return LinuxParser::User(Process::Pid()); }

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() { return LinuxParser::UpTime() ; }

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a[[maybe_unused]]) const { return true; }