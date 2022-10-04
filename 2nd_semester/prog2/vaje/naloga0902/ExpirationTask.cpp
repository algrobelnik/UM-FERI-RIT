#include "ExpirationTask.h"
#include <sstream>

ExpirationTask::ExpirationTask(std::string assignee, std::string state,
                               DateTime &deadline, std::string name,
                               std::string description, DateTime &added, std::vector<std::string> tags)
    : assignee(assignee), state(state), deadline(deadline),
      Task(name, description, added, tags) {}

std::string ExpirationTask::toString() const {
  std::stringstream ss;
  ss << Task::toString() << " ";
  if (assignee != "")
    ss << "(" << assignee << ")";
  ss << deadline.toString() << " " << state << std::endl;
  return ss.str();
}