#include "Date.h"
#include <sstream>

Date::Date(unsigned int day, unsigned int month, unsigned int year)
    : day(day), month(month), year(year) {}

std::string Date::exportJSON() const {
  std::stringstream ss;
	ss << "{ day: " << ((day < 10) ? "0" : "") << day << ", month: " << ((month < 10) ? "0" : "")
	<< month << ", year: " << year << "}";
  return ss.str();
}

std::string Date::toString() const {
  std::stringstream ss;
  ss << ((day < 10) ? "0" : "") << day << "." << ((month < 10) ? "0" : "")
     << month << "." << year;
  return ss.str();
}
