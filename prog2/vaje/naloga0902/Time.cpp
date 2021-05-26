#include "Time.h"
#include <sstream>

Time::Time(unsigned int hour, unsigned int minute, unsigned int second)
    : hour(hour), minute(minute), second(second) {}

std::string Time::exportJSON() const {
  std::stringstream ss;
  ss << "{ h: " << ((hour < 10) ? "0" : "") << hour << ", m: " << ((minute < 10) ? "0" : "")
	<< minute << ", s: " << ((second < 10) ? "0" : "") << second << "}";
  return ss.str();
}

std::string Time::toString() const {
  std::stringstream ss;
  ss << ((hour < 10) ? "0" : "") << hour << ":" << ((minute < 10) ? "0" : "")
	<< minute << ":" << ((second < 10) ? "0" : "") << second;
  return ss.str();
}