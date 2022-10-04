#include "Category.h"
#include <sstream>

Category::Category(std::string name) : name(name) {}
/* Category::~Category(){
	for (int i = 0; i < tasks.size(); i++) {
    delete tasks[i];
  }
	tasks.clear();
} */

void Category::addTask(Task* task) { tasks.push_back(task); }

std::vector<Task *> Category::getTasks() const{return tasks;}

std::string Category::getName() const { return name; }

std::string Category::toString() const {
  std::stringstream ss;
  ss << "CATEGORY: " << name << std::endl;
  for (int i = 0; i < tasks.size(); i++) {
    ss << tasks[i]->toString() << std::endl;
  }
  return ss.str();
}