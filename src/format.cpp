#include <string>

#include "format.h"
#define SEC_IN_MIN (60)
#define MIN_IN_HR (60)
#define SEC_IN_HR (SEC_IN_MIN)*(MIN_IN_HR)

using std::string;

// github test
// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) { 
    
    long hours, minutes;
    hours=seconds/SEC_IN_HR;
    seconds=seconds%SEC_IN_HR;
    minutes=seconds/SEC_IN_MIN;
    seconds=seconds%SEC_IN_MIN;
    return (std::to_string(hours)+ ":"+
    std::to_string(minutes)+":"+std::to_string(seconds)); }
