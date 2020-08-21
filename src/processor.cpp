#include "processor.h"
#include "linux_parser.h"

#include <sstream>
#include <string>
#include <vector>

using std::string;
using std::vector;

double Processor::Utilization() {
  string line;
  std::ifstream ActJiffie(LinuxParser::kProcDirectory + LinuxParser::kStatFilename);

  if (ActJiffie.is_open()) {
    while (std::getline(ActJiffie, line)) {
      std::istringstream linestr(line);
      std::vector<std::string> values;
      for (std::string jiffie; linestr >> jiffie;) {
        values.push_back(jiffie);
      }

      double user = atol(values[0].c_str());
      double nice = atol(values[1].c_str());
      double system = atol(values[2].c_str());
      double idle = atol(values[3].c_str());
      double iowait = atol(values[4].c_str());
      double irq = atol(values[5].c_str());
      double softirq = atol(values[6].c_str()); 
      double steal = atol(values[7].c_str());

      double PrevIdle = previdle + previowait;
      double Idle = idle + iowait;

      double PrevNonIdle =
          prevuser + prevnice + prevsystem + previrq + prevsoftirq + prevsteal;
      double NonIdle = user + nice + system + irq + softirq + steal;

      double PrevTotal = PrevIdle + PrevNonIdle;
      double Total = Idle + NonIdle;

      double totald = Total - PrevTotal;

      double idled = Idle - PrevIdle;

      double CPU_Percentage = (totald - idled) / totald;

      int prevUser = user;
      int prevnice = nice;
      int prevsystem = system;
      int previdle = idle;
      int previowait = iowait;
      int previrq = irq;
      int prevsoftirq = softirq;
      int prevsteal = steal;    

      return CPU_Percentage;
    }
  }
}



  /*
  #include "linux_parser.h"
  #include "processor.h"

  // TODO: Return the aggregate CPU utilization
  float Processor::Utilization() {

    //  long jiff = LinuxParser::Jiffies();
     // long idle = LinuxParser::IdleJiffies();

      float Util = (LinuxParser::ActiveJiffies() - LinuxParser::IdleJiffies())/
  LinuxParser::ActiveJiffies();

      return Util;

  }
  */
