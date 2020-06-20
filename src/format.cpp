#include <string>

#include "format.h"
#include "iostream"
#include <iomanip>
#define SEC_IN_MIN (60)
#define MIN_IN_HR (60)
#define SEC_IN_HR (SEC_IN_MIN)*(MIN_IN_HR)

using std::string;
using std::cout;
using std::ostringstream;

    /*long hours, minutes;
    hours=seconds/SEC_IN_HR;
    seconds=seconds%SEC_IN_HR;
    minutes=seconds/SEC_IN_MIN;
    seconds=seconds%SEC_IN_MIN;*/
// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
 string Format::ElapsedTime(long seconds) { 
    int  hours,minutes;
    ostringstream stream;
    hours=seconds/3600;
    seconds=seconds%3600;
    minutes=seconds/60;
    seconds=seconds%60;
    //seconds.insert(0,2-seconds.length(), '0');
    stream<<std::setw(2)<<std::setfill('0')<<hours<<":"<<std::setw(2)<<std::setfill('0')<<minutes<<":"
    <<std::setw(2)<<std::setfill('0')<<seconds;
    return stream.str();}  

 

