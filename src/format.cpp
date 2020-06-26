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

 
 string Format::ElapsedTime(long seconds) { 
    int  hours,minutes;
    ostringstream stream;
    hours=seconds/3600;
    seconds=seconds%3600;
    minutes=seconds/60;
    seconds=seconds%60;
    stream<<std::setw(2)<<std::setfill('0')<<hours<<":"
          <<std::setw(2)<<std::setfill('0')<<minutes<<":"
          <<std::setw(2)<<std::setfill('0')<<seconds;
    return stream.str();}  
 
