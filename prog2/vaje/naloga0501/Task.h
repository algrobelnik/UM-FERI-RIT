#ifndef TASK0501_TASK_H
#define TASK0501_TASK_H

#include "DateTime.h"
#include <iostream>

class Task {
private:
  std::string name, description;
  DateTime &added;

public:
  Task(std::string name, std::string description, DateTime &added);
	std::string exportJSON() const;
  virtual std::string toString() const;
};

#endif
