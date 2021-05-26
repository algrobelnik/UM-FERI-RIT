#include "ExpirationTask.h"
#include <sstream>

ExpirationTask::ExpirationTask(std::string assignee, std::string state,
                               DateTime &deadline, std::string name,
                               std::string description, DateTime &added)
    : assignee(assignee), state(state), deadline(deadline),
      Task(name, description, added) {}

std::string ExpirationTask::toString() const {
  std::stringstream ss;
  ss << Task::toString() << " ";
  if (assignee != "")
    ss << "(" << assignee << ")";
  ss << deadline.toString() << " " << state << std::endl;
  return ss.str();
}