#include "Competition.h"
#include <iostream>
#include <sstream>

using namespace std;

Competition::Competition(string name, Date startDate)
    : name(name), startDate(startDate), counter(0) {}
Competition::~Competition() {}
void Competition::addCompetitor(Athlete *athlete) {
  counter++;
  competitors.push_back(new Competitor(counter, athlete, 0));
}
void Competition::addResult(unsigned int startNumber, double result) {
  for (int i = 0; i < competitors.size(); i++) {
    if (competitors[i]->getStartNumber() == startNumber) {
      competitors[i]->setResult(result);
      return;
    }
  }
}
void Competition::removeResult0() {
  for (int i = 0; i < competitors.size(); i++) {
    if (competitors[i]->getResult() <= 0) {
      competitors.erase(competitors.begin() + i);
    }
  }
}
void Competition::printCompetitors() {
  for (int i = 0; i < competitors.size(); i++) {
    cout << "[" << counter << "]" << competitors[i]->toString();
  }
};
vector<Competitor *> Competition::getQualifiedCompetitors(double limit) const {
  vector<Competitor *> tmp;
  for (int i = 0; i < competitors.size(); i++) {
    if (competitors[i]->getResult() > limit) {
      tmp.push_back(competitors[i]);
    }
  }
  return tmp;
}

string Competition::toString() {
  stringstream ss;
  ss << "[" << startDate.toString() << "] " << name << endl;
  return ss.str();
}