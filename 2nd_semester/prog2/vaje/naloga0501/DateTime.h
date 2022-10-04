#ifndef TASK0501_DATETIME_H
#define TASK0501_DATETIME_H

#include "Date.h"
#include "Time.h"

class DateTime {
private:
  Date date;
  Time time;

public:
  DateTime();
  DateTime(Date date, Time time);

  std::string exportJSON() const;
  std::string toString() const;
};

#endif // TASK0501_DATETIME_H
