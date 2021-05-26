#ifndef COMPETITOR_H
#define COMPETITOR_H
#include "Athlete.h"
#include "Result.h"
#include <iostream>
#include <vector>

using namespace std;

class Competitor {
private:
  unsigned int startNumber;
  Athlete *athlete;
  Result result;

public:
  Competitor(unsigned int startNumber, Athlete *athlete, Result result);
  unsigned int getStartNumber();
  void setResult(Result result);
  bool calculateAverageResult(double limit);
  string nameAndLastName();
  string toString();
};

#endif
