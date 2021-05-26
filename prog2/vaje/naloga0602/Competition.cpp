#include "Competition.h"
#include <iostream>
#include <sstream>

using namespace std;

Competition::Competition(string name, DateTime startDate, DateTime endDate)
    : name(name), startDate(startDate), endDate(endDate), counter(0) {}
Competition::~Competition() {}
DateTime Competition::getStartDate() { return startDate; }
DateTime Competition::getEndDate() { return endDate; }
void Competition::addCompetitor(string firstName, string lastName, string country, int height, int weight, int id) {
  counter++;
  vector<double> vec;
  competitors.push_back(new Competitor(counter, firstName, lastName, country, height, weight, id, Result(vec)));
}
void Competition::addResult(unsigned int startNumber, vector<double> &res) {
  for (int i = 0; i < competitors.size(); i++) {
    if (competitors[i]->getStartNumber() == startNumber) {
      competitors[i]->setResult(Result(res));
      return;
    }
  }
}
void Competition::printCompetitors() {
  for (int i = 0; i < competitors.size(); i++) {
    cout << "[" << counter << "]" << competitors[i]->toString();
  }
}
void Competition::printPlayOff() {
  if (competitors.size() < 8) {
    cout << "We need at least 8 competitors.";
    return;
  }
  if (competitors.size() % 2 != 0) {
    cout << "We need number of competitors devisable by 2.";
    return;
  }
  for (int i = 0; i < competitors.size()/2; i++) {
    cout << "Match " << i+1 << ": ["<< competitors[i]->nameAndLastName() << " vs " << competitors[competitors.size()-1-i]->nameAndLastName() << "]" << endl;
  }
}
vector<Competitor *> Competition::getQualifiedCompetitors(double limit) const {
  vector<Competitor *> tmp;
  for (int i = 0; i < competitors.size(); i++) {
    if (competitors[i]->calculateAverageResult(limit)) {
      tmp.push_back(competitors[i]);
    }
  }
  return tmp;
}

vector<Competition *> Competition::getCompetitionsBetween(
    const std::vector<Competition *> competitions, const DateTime &from,
    const DateTime &to) {
  vector<Competition *> vec;
  for (int i = 0; i < competitions.size(); i++) {
    if (competitions[i]->getStartDate().isAfter(from) &&
        competitions[i]->getEndDate().isBefore(to)) {
      vec.push_back(competitions[i]);
    }
  }
  return vec;
}

string Competition::toString() {
  stringstream ss;
  ss << "[" << startDate.toString() << " - " << endDate.toString() << "] "
     << name << endl;
  return ss.str();
}