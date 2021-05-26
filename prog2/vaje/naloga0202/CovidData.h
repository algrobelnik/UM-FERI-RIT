#include <iostream>
#ifndef COVIDDATA_H
#define COVIDDATA_H

using namespace std;

class CovidData {
private:
  unsigned int day, month, year, activeCases;

public:
  CovidData();
  CovidData(const CovidData &a);
  CovidData(unsigned int day, unsigned int month, unsigned int year, unsigned int activeCases);
	~CovidData();
  unsigned int getDay();
  unsigned int getMonth();
  unsigned int getYear();
  unsigned int getActiveCases();
  void setActiveCases(unsigned int activeCases);
  string toString();
};

#endif
