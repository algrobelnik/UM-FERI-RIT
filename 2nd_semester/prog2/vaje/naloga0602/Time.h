#ifndef TIME_H
#define TIME_H

#include <iostream>

class Time {
private:
  unsigned int hour, minute, second;

public:
  Time(unsigned int hour, unsigned int minute, unsigned int second);
  unsigned int getHour();
  unsigned int getMinute();
  unsigned int getSecond();

  std::string toString() const;
};

#endif
