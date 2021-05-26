#include "Competitor.h"
#include <iostream>
#include <sstream>

using namespace std;

Competitor::Competitor(unsigned int startNumber, Athlete *athlete,
                       double result)
    : startNumber(startNumber), athlete(athlete), result(result) {}

unsigned int Competitor::getStartNumber() { return startNumber; }

void Competitor::setResult(double result) { this->result = result; }
double Competitor::getResult() { return result; }

string Competitor::toString() {
  stringstream ss;
  ss << "(" << startNumber << ")" << athlete->toString() << " Result was "
     << result << endl;
  return ss.str();
}