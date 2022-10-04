#include <iostream>
#ifndef ATHLETE_H
#define ATHLETE_H

using namespace std;

class Athlete {
private:
  int height, weight, id;
  string firstName, lastName, country;

public:
  Athlete();
  Athlete(const Athlete *a);
  Athlete(string firstName, string lastName, string country, int height,
          int weight, int id);
  int getHeight();
  int getWeight();
  string getFirstName();
  string getLastName();
  string getCountry();
  int getId();
  void setHeight(int height);
  void setWeight(int weight);
  void setFirstName(string firstName);
  void setLastName(string lastName);
  void setCountry(string country);
  void setId(int country);
  void print();
  bool isSame(Athlete &a);
  string toString();
};

#endif
