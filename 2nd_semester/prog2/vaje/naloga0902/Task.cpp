#include "Task.h"
#include <sstream>

Task::Task(std::string name, std::string description, DateTime &added, std::vector<std::string> tags)
    : name(name), description(description), added(added), tags(tags) {}

std::string Task::exportJSON() const {
  std::stringstream ss;
	ss << "{name:\"" << name << "\", description: \"" << description << "\", added: " << added.exportJSON() << "}";
  return ss.str();
}

std::string Task::getName() const {
  return name;
}

std::vector<std::string> Task::getTags() const {
  return tags;
}

std::string Task::toString() const {
  std::stringstream ss;
  ss << added.toString() << description << std::endl;
  return ss.str();
}