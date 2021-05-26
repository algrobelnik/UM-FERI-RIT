#ifndef DATETIME_H
#define DATETIME_H

#include "Date.h"
#include "Time.h"
#include <iostream>

class DateTime {
private:
  Date date;
  Time time;

public:
  DateTime(Date date, Time time);
  bool isEqual(const DateTime &second);
  bool isBefore(const DateTime &second);
  bool isAfter(const DateTime &second);
  Date getDate() const;
  Time getTime() const;

  std::string toString() const;
};

#endif
