#include "process.h"

#include <unistd.h>

#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "linux_parser.h"

using std::string;
using std::to_string;
using std::vector;

Process::Process(int pid)
    : pid_(pid),
      user_(LinuxParser::User(pid)),
      command_(LinuxParser::Command(pid)),
      cpuUtilization_(LinuxParser::CpuUtilization(pid)),
      ram_(LinuxParser::Ram(pid)),
      uptime_(LinuxParser::UpTime(pid)),
      actjiff_(LinuxParser::ActiveJiffies(pid)){};

// TODO: Return this process's ID
int Process::Pid() { return pid_; }

long Process::ActiveJiffies() { return actjiff_; }

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() const { return cpuUtilization_; }

// TODO: Return the command that generated this process
string Process::Command() { return command_; }

void Process::update() {
  user_ = LinuxParser::User(pid_);
  command_ = LinuxParser::Command(pid_);
  cpuUtilization_ = LinuxParser::CpuUtilization(pid_);
  ram_ = LinuxParser::Ram(pid_);
  uptime_ = LinuxParser::UpTime(pid_);
  actjiff_ = LinuxParser::ActiveJiffies(pid_);
}

// TODO: Return this process's memory utilization
string Process::Ram() { return ram_; }

// TODO: Return the user (name) that generated this process
string Process::User() { return user_; }

// TODO: Return the age of this process (in seconds)
long Process::UpTime() { return uptime_; }

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a) const {
  string y = ram_;
  string x = a.ram_;
  float f, g;

  f = (x.empty()) ? 0 : stof(x);
  g = (y.empty()) ? 0 : stof(y);

  return (f < g);

  /*
    bool flag = a.cpuUtilization_ < this->cpuUtilization_;

    return flag; */
}
