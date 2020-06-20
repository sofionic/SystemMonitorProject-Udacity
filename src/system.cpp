#include <unistd.h>
#include <cstddef>
#include <set>
#include <string>
#include <vector>

#include "process.h"
#include "processor.h"
#include "system.h"
#include "linux_parser.h"

using std::set;
using std::size_t;
using std::string;
using std::vector;
System::System() {
	for(int pid: LinuxParser::Pids()) {
    	allProcesses_.push_back(Process(pid));
    }
}

// TODO: Return the system's CPU
Processor& System::Cpu() { 
    std::vector<string> utilizations = LinuxParser::CpuUtilization();
    /*stoi(cpu_.user(utilizations[0]));
    cpu_.nice(utilizations[1]);
    cpu_.system(utilizations[2]);
    cpu_.idle(utilizations[3]);
    cpu_.iowait(utilizations[4]);
    cpu_.irq(utilizations[5]);
    cpu_.softirq(utilizations[6]);
    cpu_.steal(utilizations[7]);
    cpu_.guest(utilizations[8]);
    cpu_.guestNice(utilizations[9]);*/

    utilizations.clear();


    
    return cpu_;
     //return Processor::Utilization();
     }

// TODO: Return a container composed of the system's processes
vector<Process>& System::Processes() { 
    sort(allProcesses_.begin(), allProcesses_.end());
    return allProcesses_; }

// TODO: Return the system's kernel identifier (string)
std::string System::Kernel() { return LinuxParser::Kernel(); }

// TODO: Return the system's memory utilization
float System::MemoryUtilization() { return LinuxParser::MemoryUtilization(); }

// TODO: Return the operating system name
std::string System::OperatingSystem() { return LinuxParser::OperatingSystem(); }

// TODO: Return the number of processes actively running on the system
int System::RunningProcesses() { return LinuxParser::RunningProcesses(); }

// TODO: Return the total number of processes on the system
//int System::TotalProcesses() { return LinuxParser::TotalProcesses(); }
int System::TotalProcesses() { return allProcesses_.size(); }

// TODO: Return the number of seconds since the system started running
long int System::UpTime() { return LinuxParser::UpTime(); }