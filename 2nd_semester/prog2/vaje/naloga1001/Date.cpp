#include "Date.h"
#include <sstream>

Date::Date(unsigned int day, unsigned int month, unsigned int year)
    : day(day), month(month), year(year) {}

unsigned int Date::getDay() const{
  return day;
}

unsigned int Date::getMonth() const{
  return month;
}

unsigned int Date::getYear() const{
  return year;
}

void Date::setDay(unsigned int d){day = d;}

void Date::setMonth(unsigned int m){month = m;}

void Date::setYear(unsigned int y){year = y;}

bool Date::operator==(const Date& other){
  return day == other.getDay() && month == other.getMonth() && year == other.getYear();
}

Date& Date::operator++(){
  int months[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  if(months[month-1] <= day){
    if(month >= 12 && day == 31){
      year++;
      month = 0;
    }
    month++;
    day = 1;
  }else{
    day++;
  }
  return *this;
}

Date Date::operator++(int dummy){
  int months[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  if(months[month-1] <= day){
    if(month >= 12 && day == 31){
      ++year;
      month = 0;
    }
    ++month;
    day = 1;
  }else{
    ++day;
  }
  return *this;
}

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
