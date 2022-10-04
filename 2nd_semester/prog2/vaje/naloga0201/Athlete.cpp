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
Athlete::Athlete(const Athlete &a) {
  height = a.height;
  weight = a.weight;
  firstName = a.firstName;
  lastName = a.lastName;
  country = a.country;
  id = a.id;
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
int Athlete::getHeight() { return height; }
int Athlete::getWeight() { return weight; }
string Athlete::getFirstName() { return firstName; }
string Athlete::getLastName() { return lastName; }
string Athlete::getCountry() { return country; }
int Athlete::getId() { return id; }
void Athlete::setHeight(int height) { 
	if (height < 50) {
    cout << "Data error";
    height = 50;
  }
	this->height = height;
}
void Athlete::setWeight(int weight) { this->weight = weight; }
void Athlete::setFirstName(string firstName) { this->firstName = firstName; }
void Athlete::setLastName(string lastName) { this->lastName = lastName; }
void Athlete::setCountry(string country) { this->country = country; }
void Athlete::setId(int id) { this->id = id; }
bool Athlete::isSame(Athlete &a) {
	return firstName == a.firstName && lastName == a.lastName && country == a.country && height == a.height && weight == a.weight; 
}
void Athlete::print() {
  cout << "Athlete[" << id << "] " << firstName << " " << lastName << " is "
       << (float)height / 100 << "m tall and weights " << (float)weight / 100
       << "kg." << endl;
}
string Athlete::toString() {
  stringstream ss;
  ss << "Athlete[" << id << "] " << firstName << " " << lastName << " is "
     << (float)height / 100 << "m tall and weights " << (float)weight / 100
     << "kg." << endl;
  return ss.str();
}