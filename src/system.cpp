#include <unistd.h>
#include <cstddef>
#include <set>
#include <string>
#include <vector>
#include <iostream>

#include "process.h"
#include "processor.h"
#include "system.h"

#include "linux_parser.h"

using std::set;
using std::size_t;
using std::string;
using std::vector;
using namespace std;

// TODO: Return the system's CPU
Processor& System::Cpu() { 
    Processor cpu_;
    cpu_.Utilization();
    return cpu_; 
}

// TODO: Return a container composed of the system's processes
vector<Process>& System::Processes() {

    
  //vector<Process> locprocesses_;
  processes_.clear();
  vector<int> pids = LinuxParser::Pids();
  long int in = pids.size();
  
  for(long int i=0;i < in;i++){
      Process prc(pids[i]);
      processes_.emplace_back(prc);
  }
  //processes_ = processes_ ;
  return processes_;
  
}




// TODO: Return the system's kernel identifier (string)
std::string System::Kernel() { 
    
    std::string SKernel = LinuxParser::Kernel();
    return SKernel; 
}

// TODO: Return the system's memory utilization
float System::MemoryUtilization() { 
    
    float memUtil = LinuxParser::MemoryUtilization();
    return memUtil; 
    
    }

// TODO: Return the operating system name
std::string System::OperatingSystem() { 

    std::string SOperatingSystem = LinuxParser::OperatingSystem();
    
    return SOperatingSystem; 
    
}

// TODO: Return the number of processes actively running on the system
int System::RunningProcesses() { 

    int RunProc = LinuxParser::RunningProcesses();
    return RunProc; 

 }

// TODO: Return the total number of processes on the system
int System::TotalProcesses() { 

    int TotProc = LinuxParser::TotalProcesses();
    return TotProc; 
    
}

// TODO: Return the number of seconds since the system started running
long int System::UpTime() { 

    long int upt = LinuxParser::UpTime();
    return upt; 
    
 }