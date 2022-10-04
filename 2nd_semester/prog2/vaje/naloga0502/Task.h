#ifndef TASK0501_TASK_H
#define TASK0501_TASK_H

#include "DateTime.h"
#include <iostream>

class Task {
protected:
  std::string name, description;
  DateTime &added;

public:
  Task(std::string name, std::string description, DateTime &added);
  virtual ~Task() = default;
  virtual DateTime getAdded() const = 0;
  virtual std::string getName() const = 0;
  virtual std::string toString() const = 0;
};

#endif
