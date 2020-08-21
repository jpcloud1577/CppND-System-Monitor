#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <string>
#include <vector>

using std::string;
using std::vector;

class Processor {
 private:
  int previdle;
  int previowait;
  int prevuser;
  int prevnice;
  int prevsystem;
  int previrq;
  int prevsoftirq;
  int prevsteal;

  void AssignPrevValues(std::vector<string>);

 public:
  double Utilization();
};

#endif