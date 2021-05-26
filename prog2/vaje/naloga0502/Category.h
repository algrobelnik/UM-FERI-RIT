#ifndef TASK0501_CATEGORY_H
#define TASK0501_CATEGORY_H

#include "Task.h"
#include <iostream>
#include <vector>

class Category {
private:
  std::string name;
  std::vector<Task *> tasks;

public:
  Category(std::string name);
  //~Category();
  void addTask(Task *task);
  std::vector<Task *> getTasks() const;
  std::string getName() const;
  std::string toString() const;
};

#endif
