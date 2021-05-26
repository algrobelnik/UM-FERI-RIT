#ifndef DATE_H
#define DATE_H

#include <iostream>

class Date {
private:
  unsigned int day;
  unsigned int month;
  unsigned int year;

public:
  Date(unsigned int day, unsigned int month, unsigned int year);

  std::string toString() const;
};

#endif
