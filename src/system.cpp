#include "system.h"

#include <unistd.h>

#include <cstddef>
#include <iostream>
#include <set>
#include <string>
#include <vector>

#include "linux_parser.h"
#include "process.h"
#include "processor.h"

using std::set;
using std::size_t;
using std::string;
using std::vector;
using namespace std;

System::System() : cpu_(Processor()) {}

// TODO: Return the system's CPU
Processor& System::Cpu() { return cpu_; }

// TODO: Return a container composed of the system's processes
vector<Process>& System::Processes() {
  // vector<Process> locprocesses_;
  // processes_.clear();
  vector<int> pids = LinuxParser::Pids();
  long int in = pids.size();

  std::vector<int> current_pids;

  for (auto process : processes_) {
    current_pids.push_back(process.Pid());
  }

  for (long int i = 0; i < in; i++) {
    Process prc(pids[i]);
    if (!(std::find(current_pids.begin(), current_pids.end(), pids[i]) !=
          current_pids.end())) {
      prc.update();
      processes_.emplace_back(prc);
    }
  }
  std::sort(processes_.begin(), processes_.end());

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