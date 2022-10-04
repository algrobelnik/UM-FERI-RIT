#ifndef TASK0501_BOARD_H
#define TASK0501_BOARD_H

#include "Task.h"
#include <iostream>
#include <vector>

class Board {
private:
  std::string name;
  std::vector<Task *> tasks;

public:
  Board(std::string name);
  ~Board();
  void addTask(Task *task);
  std::string exportJSON() const;
  std::string toString() const;
};

#endif
