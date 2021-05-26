#ifndef COMPETITION_H
#define COMPETITION_H
#include "Athlete.h"
#include "Competitor.h"
#include "DateTime.h"
#include "Result.h"
#include <iostream>
#include <vector>

using namespace std;

class Competition {
private:
  string name;
  DateTime startDate, endDate;
  vector<Competitor *> competitors;
  int counter;

public:
  Competition(string name, DateTime startDate, DateTime endDate);
  ~Competition();
  DateTime getStartDate();
  DateTime getEndDate();
  void addCompetitor(string firstName, string lastName, string country, int height, int weight, int id);
  void addResult(unsigned int startNumber, vector<double> &res);
  void printCompetitors();
  void printPlayOff();
  vector<Competitor *> getQualifiedCompetitors(double limit) const;
  static vector<Competition *>
  getCompetitionsBetween(const std::vector<Competition *> competitions,
                         const DateTime &from, const DateTime &to);
  string toString();
};

#endif
