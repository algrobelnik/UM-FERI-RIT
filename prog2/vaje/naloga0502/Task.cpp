#include "Task.h"

Task::Task(std::string name, std::string description, DateTime &added)
    : name(name), description(description), added(added) {}
