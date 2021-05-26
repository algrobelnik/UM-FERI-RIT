#include "Result.h"
#include <iostream>
#include <sstream>

Result::Result(std::vector<double> &vec) : vec(vec) {}

std::vector<double> Result::getResult() { return vec; }

std::string Result::toString() const {
  std::stringstream ss;
  for (int i = 0; i < vec.size(); i++) {
    ss << (i == 0 ? "" : ", ") << vec[i];
  }
  return ss.str();
}
