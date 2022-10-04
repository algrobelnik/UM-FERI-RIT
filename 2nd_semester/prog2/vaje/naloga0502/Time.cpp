#include "Time.h"
#include <iostream>
#include <sstream>

Time::Time(unsigned int hour, unsigned int minute, unsigned int second)
    : hour(hour), minute(minute), second(second) {}

unsigned int Time::getHour() { return hour; }
unsigned int Time::getMinute() { return minute; }
unsigned int Time::getSecond() { return second; }

std::string Time::toString() const {
  std::stringstream ss;
  ss << hour << ":" << minute << ":" << second;
  return ss.str();
}
