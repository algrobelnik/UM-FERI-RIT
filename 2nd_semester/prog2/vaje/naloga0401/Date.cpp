#include "Date.h"
#include <iostream>
#include <sstream>

Date::Date(unsigned int day, unsigned int month, unsigned int year)
    : day(day), month(month), year(year) {}

std::string Date::toString() const {
  std::stringstream ss;
  ss << ((day < 10) ? "0" : "") << day << "." << ((month < 10) ? "0" : "")
     << month << "." << year;
  return ss.str();
}
