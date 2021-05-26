#include "Task.h"
#include <sstream>

Task::Task(std::string name, std::string description, DateTime &added)
    : name(name), description(description), added(added) {}

std::string Task::exportJSON() const {
  std::stringstream ss;
	ss << "{name:\"" << name << "\", description: \"" << description << "\", added: " << added.exportJSON() << "}";
  return ss.str();
}

std::string Task::toString() const {
  std::stringstream ss;
  if (name != "")
    ss << "(" << name << ")";
  ss << added.toString() << description << std::endl;
  return ss.str();
}