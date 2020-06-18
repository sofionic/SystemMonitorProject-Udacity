#include "processor.h"
#include "linux_parser.h"
#include "unistd.h"

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() { 
    float utilization{0.0};
    long activetime=LinuxParser::ActiveJiffies();
    long uptime=LinuxParser::UpTime();
    utilization=(float)(activetime/sysconf(_SC_CLK_TCK)/uptime);

    return utilization; }