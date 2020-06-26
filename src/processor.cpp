#include "processor.h"
#include "linux_parser.h"
#include "unistd.h"

// Return the aggregate CPU utilization
double Processor::Utilization() { 

  double smallJiffie;
  long activeJiffies = LinuxParser::ActiveJiffies();
  long totalJiffies = LinuxParser::Jiffies();

  smallJiffie = double(activeJiffies - anteriorActive) / double(totalJiffies - anteriorTotal);
  anteriorActive = activeJiffies;
  anteriorTotal = totalJiffies;

  return smallJiffie;
    
    }