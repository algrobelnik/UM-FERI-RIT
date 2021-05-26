#include <iostream>
#ifndef ATHLETE_H
#define ATHLETE_H

using namespace std;

class Athlete {
protected:
  int height, weight, id;
  string firstName, lastName, country;

public:
  Athlete();
  Athlete(const Athlete *a);
  Athlete(string firstName, string lastName, string country, int height,
          int weight, int id);
  virtual ~Athlete() = default;
	int getHeight() const;
  int getWeight() const;
  string getFirstName() const;
  string getLastName() const;
  string getCountry() const;
  /*int getId() = 0;*/
  virtual bool isSame(Athlete &a) = 0;
  virtual void print() = 0;
  virtual string toString() = 0;
};

#endif
