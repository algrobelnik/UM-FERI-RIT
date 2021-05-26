#include "ExpirationTask.h"
#include <sstream>

ExpirationTask::ExpirationTask(std::string assignee, std::string state,
                               DateTime &deadline, std::string name,
                               std::string description, DateTime &added)
    : assignee(assignee), state(state), deadline(deadline),
      Task(name, description, added) {}

DateTime ExpirationTask::getAdded() const{
	return added;
}

std::string ExpirationTask::getName() const{
	return name;
}

std::string ExpirationTask::toString() const {
  std::stringstream ss;
  if (name != "")
    ss << "(" << name << ")";
  ss << added.toString() << description << std::endl << " ";
  if (assignee != "")
    ss << "(" << assignee << ")";
  ss << deadline.toString() << " " << state << std::endl;
  return ss.str();
}