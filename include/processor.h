#ifndef PROCESSOR_H
#define PROCESSOR_H
# include <linux_parser.h>
#include <unordered_map>

class Processor {
 public:
  float Utilization();  // TODO: See src/processor.cpp
  void user(const unsigned long int);
  void nice(const unsigned long int);
  void system(const unsigned long int);
  void idle(const unsigned long int);
  void iowait(const unsigned long int);
  void irq(const unsigned long int);
  void softirq(const unsigned long int);
  void steal(const unsigned long int);
  void guest(const unsigned long int);
  void guestNice(const unsigned long int);


  // TODO: Declare any necessary private members
 private:
 long anteriorTotal{0};
 long anteriorActive{0};
 unsigned long int previousIdle{0};
 unsigned long int previousNonIdle{0};
 std::unordered_map<LinuxParser::CPUStates, unsigned long int> cpuStates {};
 void update_cpu_state(const LinuxParser::CPUStates, const unsigned long int);
};

#endif