#include "processor.h"
#include "linux_parser.h"

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() { 

  //  long jiff = LinuxParser::Jiffies();
   // long idle = LinuxParser::IdleJiffies();
    
    float Util = (LinuxParser::ActiveJiffies() - LinuxParser::IdleJiffies())/ LinuxParser::ActiveJiffies();

    return Util; 
    
}

