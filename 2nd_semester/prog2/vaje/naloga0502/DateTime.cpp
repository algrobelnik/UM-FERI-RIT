#include "DateTime.h"
#include <iostream>
#include <sstream>

DateTime::DateTime() : date(Date(0, 0, 0)), time(Time(0, 0, 0)) {}
DateTime::DateTime(Date date, Time time) : date(date), time(time) {}

bool DateTime::isEqual(const DateTime &second) { return this == &second; }
bool DateTime::isBefore(const DateTime &second) {
  if (getDate().getYear() >= second.getDate().getYear()) {
    return true;
  }
  if (getDate().getMonth() >= second.getDate().getMonth()) {
    return true;
  }
  if (getDate().getDay() >= second.getDate().getDay()) {
    return true;
  }
  if (getTime().getHour() >= second.getTime().getHour()) {
    return true;
  }
  if (getTime().getMinute() >= second.getTime().getMinute()) {
    return true;
  }
  if (getTime().getSecond() >= second.getTime().getSecond()) {
    return true;
  }
  return false;
}
bool DateTime::isAfter(const DateTime &second) {
  if (getDate().getYear() >= second.getDate().getYear()) {
    return true;
  }
  if (getDate().getMonth() >= second.getDate().getMonth()) {
    return true;
  }
  if (getDate().getDay() >= second.getDate().getDay()) {
    return true;
  }
  if (getTime().getHour() >= second.getTime().getHour()) {
    return true;
  }
  if (getTime().getMinute() >= second.getTime().getMinute()) {
    return true;
  }
  if (getTime().getSecond() >= second.getTime().getSecond()) {
    return true;
  }
  return false;
}

Date DateTime::getDate() const { return date; }
Time DateTime::getTime() const { return time; }

std::string DateTime::toString() const {
  std::stringstream ss;
  ss << date.toString() << " " << time.toString();
  return ss.str();
}
