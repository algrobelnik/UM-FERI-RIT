#ifndef COMPETITOR_H
#define COMPETITOR_H
#include "Athlete.h"
#include <iostream>

using namespace std;

class Competitor {
private:
  unsigned int startNumber;
  Athlete *athlete;
  double result;

public:
  Competitor(unsigned int startNumber, Athlete *athlete, double result);
  unsigned int getStartNumber();
  void setResult(double result);
	double getResult();
  string toString();
};

#endif
