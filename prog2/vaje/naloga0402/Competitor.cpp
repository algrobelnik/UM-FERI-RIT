#include "Competitor.h"
#include <iostream>
#include <sstream>

using namespace std;

Competitor::Competitor(unsigned int startNumber, Athlete *athlete, Result res)
    : startNumber(startNumber), athlete(athlete), result(res) {}

unsigned int Competitor::getStartNumber() { return startNumber; }

void Competitor::setResult(Result result) { this->result = result; }

bool Competitor::calculateAverageResult(double limit) {
  double vsota = 0;
  vector<double> vec = result.getResult();
  for (int i = 0; i < vec.size(); i++) {
    vsota += vec[i];
  }
  return (vsota / vec.size()) > limit;
}

string Competitor::nameAndLastName() {
  stringstream ss;
  ss << athlete->getFirstName() << " " << athlete->getLastName();
  return ss.str();
}

string Competitor::toString() {
  stringstream ss;
  vector<double> vec = result.getResult();
  ss << "(" << startNumber << ")" << athlete->toString() << " Result was ("
     << result.toString() << ")" << endl;
  return ss.str();
}