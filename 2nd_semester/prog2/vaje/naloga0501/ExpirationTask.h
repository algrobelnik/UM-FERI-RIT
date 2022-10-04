#ifndef TASK0501_EXPIRATIONTASK_H
#define TASK0501_EXPIRATIONTASK_H

#include "Task.h"
#include <iostream>

class ExpirationTask : public Task {
private:
  std::string assignee, state;
  DateTime &deadline;

public:
  ExpirationTask(std::string assignee, std::string state, DateTime &deadline,
                 std::string name, std::string description, DateTime &added);

  std::string toString() const override;
};

#endif
