#ifndef TASK0501_BOARD_H
#define TASK0501_BOARD_H

#include "Category.h"
#include "DateTime.h"
#include <iostream>
#include <vector>

class Board {
private:
  std::string name;
  std::vector<Category> categories;

public:
  Board(std::string name);
  //~Board();
  void addCategory(const Category &category);
  bool addTask(const std::string &categoryName, Task* task);
	std::vector<Task *> agenda(const DateTime &dt) const;
	std::vector<Task *> beforeDate(const DateTime &dt) const;
	std::vector<Task *> afterDate(const DateTime &dt) const;
	Board removeAllWithTaskName(const std::string &taskName) const;
  std::string toString() const;
};

#endif
