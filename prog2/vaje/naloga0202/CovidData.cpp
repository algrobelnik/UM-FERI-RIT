#include "CovidData.h"
#include <ctime>
#include <iostream>
#include <sstream>

using namespace std;

CovidData::CovidData() {
  time_t t = time(0);
  tm *now = localtime(&t);
  this->day = now->tm_mday;
  this->month = (now->tm_mon + 1);
  this->year = (now->tm_year + 1900);
  this->activeCases = 0;
}
CovidData::CovidData(const CovidData &a) {
  day = a.day;
  month = a.month;
  year = a.year;
  activeCases = a.activeCases;
}
CovidData::CovidData(unsigned int day, unsigned int month, unsigned int year,
                     unsigned int activeCases) {
  this->day = day;
  this->month = month;
  this->year = year;
  this->activeCases = activeCases;
}
CovidData::~CovidData(){
	cout << "Object was destroyed using destructor" << endl;
}
unsigned int CovidData::getDay() { return day; }
unsigned int CovidData::getMonth() { return month; }
unsigned int CovidData::getYear() { return year; }
unsigned int CovidData::getActiveCases() { return activeCases; }
void CovidData::setActiveCases(unsigned int activeCases) {
  this->activeCases = activeCases;
}
string CovidData::toString() {
  stringstream ss;
  ss << "(" << day << "." << month << "." << year << "): " << activeCases;
  return ss.str();
}