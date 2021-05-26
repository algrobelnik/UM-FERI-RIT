#include "Athlete.h"
#include <iostream>
#include <sstream>

using namespace std;

Athlete::Athlete() {
  this->height = 180;
  this->weight = 6220;
  this->firstName = "Suzan";
  this->lastName = "Cuphock";
  this->country = "United Kingdom";
  this->id = 0;
}
Athlete::Athlete(const Athlete *a) {
  height = a->height;
  weight = a->weight;
  firstName = a->firstName;
  lastName = a->lastName;
  country = a->country;
  id = a->id;
}
Athlete::Athlete(string firstName, string lastName, string country, int height,
                 int weight, int id) {
  if (height < 50) {
    cout << "Data error";
    height = 50;
  }
  this->firstName = firstName;
  this->lastName = lastName;
  this->country = country;
  this->height = height;
  this->weight = weight;
  this->id = id;
}
int Athlete::getHeight() const { return height; }
int Athlete::getWeight() const { return weight; }
string Athlete::getFirstName() const { return firstName; }
string Athlete::getLastName() const { return lastName; }
string Athlete::getCountry() const { return country; }
