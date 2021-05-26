#include "Competitor.h"
#include <iostream>
#include <sstream>

using namespace std;

Competitor::Competitor(unsigned int startNumber, Result res): startNumber(startNumber), result(res), Athlete() {}
Competitor::Competitor(unsigned int startNumber, string firstName,
                       string lastName, string country, int height, int weight,
                       int id, Result res)
    : startNumber(startNumber), result(res),
      Athlete(firstName, lastName, country, height, weight, id) {}

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
  ss << firstName << " " << lastName;
  return ss.str();
}

bool Competitor::isSame(Athlete &a) {
  return firstName == a.getFirstName() && lastName == a.getLastName() &&
         country == a.getCountry() && height == a.getHeight() && weight == a.getWeight();
}
void Competitor::print() {
  cout << "Athlete[" << id << "] " << firstName << " " << lastName << " is "
       << (float)height / 100 << "m tall and weights " << (float)weight / 100
       << "kg.";
}

string Competitor::toString() {
  stringstream ss;
  vector<double> vec = result.getResult();
  ss << "(" << startNumber << ")" << "Athlete[" << id << "] " << firstName << " " << lastName << " is "
     << (float)height / 100 << "m tall and weights " << (float)weight / 100
     << "kg." << " Result was ("
     << result.toString() << ")" << endl;
  return ss.str();
}

/* int getHeight() { return height; }
int getWeight() { return weight; }
string getFirstName() { return firstName; }
string getLastName() { return lastName; }
string getCountry() { return country; }
int getId() { return id; } */
