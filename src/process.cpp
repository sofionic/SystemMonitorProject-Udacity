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

//Process::Process(int pid):pid_(pid), user_(LinuxParser::User(pid)), command_(LinuxParser::Command(pid)){
//Process::Ram();Process::UpTime();Process::CpuUtilization();}
Process::Process(int pid):pid_(pid){}
 
// TODO: Return this process's ID
int Process::Pid() { //return LinuxParser::Pids(); }
//int pid_{0};
return pid_; } 

 

// TODO: Return this process's CPU utilization
    float Process::CpuUtilization() {
   /* string key, line, tokenUtil;
    vector<string> values;
    int uTime=0;
    int sTime=0;
    int cuTime=0;
    int csTime=0;
    int pid_=0;
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

  
    
	/*long jiffies = LinuxParser::ActiveJiffies(Pid());
	long activeTime = jiffies / sysconf(_SC_CLK_TCK);
  	return float(activeTime) / float(UpTime());
*/
   
    unsigned long int activeJiffies = LinuxParser::ActiveJiffies(Pid());
    unsigned long int processUptime = LinuxParser::UpTime(Pid());
    unsigned long int systemUptime = LinuxParser::UpTime();
    auto seconds = systemUptime - processUptime;
    if(seconds <= 0) return 0.0;
    return (float) (1.0*(activeJiffies/sysconf(_SC_CLK_TCK)) / seconds);

   
}

// TODO: Return the command that generated this process
string Process::Command() {  return LinuxParser::Command( Pid()); }

// TODO: Return this process's memory utilization
string Process::Ram() {
    return  LinuxParser::Ram(Pid());}

// TODO: Return the user (name) that generated this process
string Process::User() { return LinuxParser::User(Pid()); }

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() { return LinuxParser::UpTime(Pid()) ; }

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
//bool Process::operator<(Process const& a[[maybe_unused]]) const { return true; }
/*bool Process::operator<(Process& a)  {
	return (this->CpuUtilization() > a.CpuUtilization());
}*/
bool Process::operator<(Process const& a) const {
	return cpuUtilization_>a.cpuUtilization_;
}