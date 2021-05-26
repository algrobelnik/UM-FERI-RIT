#include "DateTime.h"
#include <sstream>

DateTime::DateTime() : date(Date(0, 0, 0)), time(Time(0, 0, 0)) {}
DateTime::DateTime(Date date, Time time) : date(date), time(time) {}

std::string DateTime::exportJSON() const {
  std::stringstream ss;
  ss << "{ date: " << date.exportJSON() << ", time: " << time.exportJSON() << "}";
  return ss.str();
}

std::string DateTime::toString() const {
  std::stringstream ss;
  ss << "[" << date.toString() << " " << time.toString() << "]";
  return ss.str();
}
