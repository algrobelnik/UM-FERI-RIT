#ifndef TASK0501_TASK_H
#define TASK0501_TASK_H

#include "DateTime.h"
#include <iostream>
#include <vector>

class Task {
private:
  std::string name, description;
  DateTime &added;
  std::vector<std::string> tags;

public:
  Task(std::string name, std::string description, DateTime &added, std::vector<std::string> tags);
	std::string getName() const;
  std::vector<std::string> getTags() const;
	std::string exportJSON() const;
  virtual std::string toString() const;
};

#endif
