#ifndef RESULT_H
#define RESULT_H

#include <iostream>
#include <vector>

class Result {
private:
  std::vector<double> vec;

public:
  Result(std::vector<double> &vec);
  std::vector<double> getResult();

  std::string toString() const;
};

#endif
