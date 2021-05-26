#ifndef COMPETITOR_H
#define COMPETITOR_H
#include "Athlete.h"
#include "Result.h"
#include <iostream>
#include <vector>

using namespace std;

class Competitor : public Athlete{
private:
  unsigned int startNumber;
  Result result;

public:
  Competitor(unsigned int startNumber, Result result);
	Competitor(unsigned int startNumber, string firstName, string lastName, string country, int height,
          int weight, int id, Result result);
  unsigned int getStartNumber();
  void setResult(Result result);
  bool calculateAverageResult(double limit);
  string nameAndLastName();
/* 	int getHeight();
  int getWeight();
  string getFirstName();
  string getLastName();
  string getCountry();
  int getId();*/
  bool isSame(Athlete &a);
  void print();
  string toString();
};

#endif
