#ifndef TASK0501_BOARD_H
#define TASK0501_BOARD_H

#include "Task.h"
#include <iostream>
#include <vector>
#include <map>

class Board {
private:
  std::string name;
  std::map<std::string, Task *> tasks;
  std::map<std::string, std::vector<Task *>> byTag;

public:
  Board(std::string name);
  ~Board();
  std::map<std::string, Task*> getTasks();
  bool addTask(Task *task);
  Task* findTask(const std::string key);
  void deleteTask(const std::string key);
  unsigned int numberOfTasks() const;
  static std::vector<Task*> toVector(Board board);
  void reverse();
  void changeEveryKey(std::string k);
  void deleteRandomElements();
  std::vector<Task *> findTaskByTag(const std::string tag);
  std::string exportJSON() const;
  std::string toString() const;
};

#endif
