#ifndef COMPETITION_H
#define COMPETITION_H
#include "Athlete.h"
#include "Competitor.h"
#include "Date.h"
#include <iostream>
#include <vector>

using namespace std;

class Competition {
private:
  string name;
  Date startDate;
  vector<Competitor *> competitors;
  int counter;

public:
  Competition(string name, Date startDate);
  ~Competition();
  void addCompetitor(Athlete *athlete);
  void addResult(unsigned int startNumber, double result);
  void removeResult0();
  void printCompetitors();
  vector<Competitor *> getQualifiedCompetitors(double limit) const;
  string toString();
};

#endif
