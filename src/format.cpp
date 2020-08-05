#include <string>

#include "format.h"

using std::string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) { 
   
    long hours = seconds / (60 * 60);
    seconds = seconds % (60 * 60);
    long minutes = seconds / 60;
    seconds = seconds % 60;

    std::string HH = std::to_string(hours);
    std::string MM = std::to_string(minutes);
    std::string SS = std::to_string(seconds);

    std::string output = HH+":"+MM+":"+SS;

    return HH+":"+MM+":"+SS; 

    }