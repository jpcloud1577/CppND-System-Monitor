#include "linux_parser.h"

#include <dirent.h>
#include <unistd.h>

#include <filesystem>
#include <iostream>
#include <string>
#include <vector>

using std::cout;
using std::stof;
using std::string;
using std::to_string;
using std::vector;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, kernel, version;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >> kernel;
  }
  return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

// TODO: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() {
  std::ifstream memostream(kProcDirectory + kMeminfoFilename);

  string line, key, value;
  float totalMemory, freeMemory, floatValue, memUtil;

  if (memostream.is_open()) {
    while (std::getline(memostream, line)) {
      std::replace(line.begin(), line.end(), '=', ' ');
      std::istringstream linestream(line);
      linestream >> key >> value;
      std::stringstream intValue(value);
      intValue >> floatValue;

      if (key == "MemTotal:") {
        totalMemory = floatValue;
      }

      else if (key == "MemFree:") {
        freeMemory = floatValue;
        break;
      }
    }
    float MemUtil = 1 - (totalMemory - freeMemory) / totalMemory;
    return MemUtil;
  }
}

// TODO: Read and return the system uptime
long LinuxParser::UpTime() {
  std::ifstream Uptim(kProcDirectory + kUptimeFilename);
  string line, key, value;
  long IntValue;

  if (Uptim.is_open()) {
    std::getline(Uptim, line);
    std::istringstream linestr(line);
    linestr >> key;
    std::stringstream intValue(key);
    intValue >> IntValue;
  }

  return IntValue;
}

// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() {
  std::ifstream Jiffie(kProcDirectory + kStatFilename);
  string line, key, value1, value2, value3, value4, value5, value6, value7,
      value8, value9, value10;
  long IntValue, IntValue1, IntValue2, IntValue3, IntValue4, IntValue5,
      IntValue6, IntValue7, IntValue8, IntValue9, IntValue10;

  if (Jiffie.is_open()) {
    while (std::getline(Jiffie, line)) {
      std::istringstream linestr(line);
      linestr >> key;
      if (key == "cpu") {
        linestr >> key >> value1 >> value2 >> value3 >> value4 >> value5 >>
            value6 >> value7 >> value8 >> value9 >> value10;

        std::stringstream intValue1(value1), intValue2(value2),
            intValue3(value3), intValue4(value4), intValue5(value5),
            intValue6(value6), intValue7(value7), intValue8(value8),
            intValue9(value9), intValue10(value10);
        intValue1 >> IntValue1;
        intValue2 >> IntValue2;
        intValue3 >> IntValue3;
        intValue4 >> IntValue4;
        intValue5 >> IntValue5;
        intValue6 >> IntValue6;
        intValue7 >> IntValue7;
        intValue8 >> IntValue8;
        intValue9 >> IntValue9;
        intValue10 >> IntValue10;
        IntValue = IntValue1 + IntValue2 + IntValue3 + IntValue4 + IntValue5 +
                   IntValue6 + IntValue7 + IntValue8 + IntValue9 + IntValue10;
        break;
      }
    }
  }
  return IntValue;
}

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid [[maybe_unused]]) { return 0; }

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() {
  std::ifstream ActJiffie(kProcDirectory + kStatFilename);
  string line, key, value1, value2, value3, value4, value5, value6, value7,
      value8, value9, value10;
  long IntValue, IntValue1, IntValue2, IntValue3, IntValue4, IntValue5,
      IntValue6, IntValue7, IntValue8, IntValue9, IntValue10;

  if (ActJiffie.is_open()) {
    while (std::getline(ActJiffie, line)) {
      std::istringstream linestr(line);
      linestr >> key;
      if (key == "cpu") {
        linestr >> key >> value1 >> value2 >> value3 >> value4 >> value5 >>
            value6 >> value7 >> value8 >> value9 >> value10;

        std::stringstream intValue1(value1), intValue2(value2),
            intValue3(value3), intValue6(value6), intValue7(value7),
            intValue8(value8);

        intValue1 >> IntValue1;
        intValue2 >> IntValue2;
        intValue3 >> IntValue3;
        intValue6 >> IntValue6;
        intValue7 >> IntValue7;
        intValue8 >> IntValue8;
        IntValue = IntValue1 + IntValue2 + IntValue3 + IntValue6 + IntValue7 +
                   IntValue8;
        break;
      }
    }
  }

  long ActJiff = IntValue - LinuxParser::IdleJiffies();

  return ActJiff;
}

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() {
  std::ifstream Jiffie(kProcDirectory + kStatFilename);
  string line, key, value1, value2, value3, value4, value5;
  long IntValue, IntValue1, IntValue2, IntValue3, IntValue4, IntValue5;

  if (Jiffie.is_open()) {
    while (std::getline(Jiffie, line)) {
      std::istringstream linestr(line);
      linestr >> key;
      if (key == "cpu") {
        linestr >> key >> value1 >> value2 >> value3 >> value4 >> value5;

        std::stringstream intValue4(value4), intValue5(value5);
        intValue4 >> IntValue4;
        intValue5 >> IntValue5;
        break;
      }
    }
  }
  return IntValue4 + IntValue5;
}

// TODO: Read and return CPU utilization
float LinuxParser::CpuUtilization(int pid) {
  string token;
  std::string fileName{kProcDirectory + std::to_string(pid) + kStatFilename};

  std::ifstream fileStream(fileName);
  std::vector<std::string> tokens;
  const char delimiter = ' ';
  if (fileStream.is_open()) {
    while (std::getline(fileStream, token, delimiter)) {
      tokens.push_back(token);
    }
  }

  // Reference from
  // https://stackoverflow.com/questions/16726779/how-do-i-get-the-total-cpu-usage-of-an-application-from-proc-pid-stat/16736599#16736599

  long total_time = atol(tokens[14].c_str()) + atol(tokens[15].c_str()) +
                    atol(tokens[16].c_str()) + atol(tokens[17].c_str());

  long hertz = static_cast<long int>(sysconf(_SC_CLK_TCK));

  long elapsedTime = LinuxParser::UpTime() - (atol(tokens[14].c_str())/hertz);

  float cpuutil = 100 * (total_time/hertz) / elapsedTime;

  return cpuutil;
}

// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses() {
  std::ifstream TotProc(kProcDirectory + kStatFilename);
  string line, key, value;
  int IntValue;

  if (TotProc.is_open()) {
    while (std::getline(TotProc, line)) {
      std::istringstream linestr(line);
      linestr >> key >> value;
      if (key == "processes") {
        std::stringstream intValue(value);
        intValue >> IntValue;
        break;
      }
    }
  }
  return IntValue;
}

// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses() {
  std::ifstream RunProc(kProcDirectory + kStatFilename);
  string line, key, value;
  int IntValue;

  if (RunProc.is_open()) {
    while (std::getline(RunProc, line)) {
      std::istringstream linestr(line);
      linestr >> key >> value;
      if (key == "procs_running") {
        std::stringstream intValue(value);
        intValue >> IntValue;
        break;
      }
    }
  }
  return IntValue;
}

// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid) {
  std::ifstream ProcCmd(kProcDirectory + to_string(pid) + kCmdlineFilename);
  string line, cmd;
  if (ProcCmd.is_open()) {
    std::getline(ProcCmd, line);
    std::istringstream linestr(line);
    linestr >> cmd;
  }
  return cmd;
}

std::string LinuxParser::Ram(int pid) {
  string key, value;
  string lineBuffer;
  std::string fileName{kProcDirectory + std::to_string(pid) + kStatusFilename};
  std::ifstream filestream(fileName);
  if (filestream.is_open()) {
    while (std::getline(filestream, lineBuffer)) {
      std::istringstream linestream(lineBuffer);
      while (linestream >> key >> value) {
        if (key == "VmSize:") {
          // convert from kilobytes to megabytes
          return std::to_string(atol(value.c_str()) / 1000);
        }
      }
    }
  }
  return string();
}

// This can eventually be made private
std::string LinuxParser::Uid(int pid) {
  string key, value;
  string lineBuffer;
  std::string fileName{kProcDirectory + std::to_string(pid) + kStatusFilename};
  std::ifstream filestream(fileName);
  if (filestream.is_open()) {
    while (std::getline(filestream, lineBuffer)) {
      std::istringstream linestream(lineBuffer);
      while (linestream >> key >> value) {
        if (key == "Uid:") {
          return value;
        }
      }
    }
  }
  return string();
}

std::string LinuxParser::User(int pid) {
  string token;
  std::string fileName{kPasswordPath};
  std::ifstream filestream(fileName);
  string uid = Uid(pid);
  std::vector<string> tokens;
  const char delimiter = ':';
  if (filestream.is_open()) {
    while (std::getline(filestream, token, delimiter)) {
      tokens.push_back(token);
    }
    if (tokens[2] == uid) {
      return tokens[0];
    }
  }

  return string();
}

// UpTime in seconds
long int LinuxParser::UpTime(int pid) {
  string token;
  std::string fileName{kProcDirectory + std::to_string(pid) + kStatFilename};

  std::ifstream fileStream(fileName);
  std::vector<std::string> tokens;
  const char delimiter = ' ';
  if (fileStream.is_open()) {
    while (std::getline(fileStream, token, delimiter)) {
      tokens.push_back(token);
    }
  }

  long upTime =
      atol(tokens[22].c_str()) / static_cast<long int>(sysconf(_SC_CLK_TCK));
  return upTime;
}
