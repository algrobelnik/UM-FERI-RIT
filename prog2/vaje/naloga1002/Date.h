#ifndef DATE_H
#define DATE_H

#include <iostream>

class Date {
private:
  unsigned int day;
  unsigned int month;
  unsigned int year;

public:
  friend std::ostream &operator<<(std::ostream &out, const Date &date) {
    out << "(" << date.getDay() << ", " << date.getMonth() << ", "
        << date.getYear() << ")";
    return out;
  }
  Date(unsigned int day, unsigned int month, unsigned int year);
  unsigned int getDay() const;
  unsigned int getMonth() const;
  unsigned int getYear() const;
  void setDay(unsigned int d);
  void setMonth(unsigned int d);
  void setYear(unsigned int d);
  bool operator==(const Date &other);
  Date &operator++();
  Date operator++(int dummy);
  std::string exportJSON() const;
  std::string toString() const;
};

#endif
