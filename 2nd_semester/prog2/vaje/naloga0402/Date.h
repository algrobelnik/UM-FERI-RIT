#ifndef DATE_H
#define DATE_H

#include <iostream>

class Date {
private:
  unsigned int day, month, year;

public:
  Date(unsigned int day, unsigned int month, unsigned int year);
  unsigned int getDay() const;
  unsigned int getMonth() const;
  unsigned int getYear() const;

  std::string toString() const;
};

#endif
