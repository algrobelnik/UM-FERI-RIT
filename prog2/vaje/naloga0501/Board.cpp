#include "Board.h"
#include <sstream>

Board::Board(std::string name) : name(name) {}
Board::~Board(){
	for (int i = 0; i < tasks.size(); i++) {
    delete tasks[i];
  }
	tasks.clear();
}

void Board::addTask(Task *task) { tasks.push_back(task); }

std::string Board::exportJSON() const {
  std::stringstream ss;
  ss << "BOARD: {" << name;
  for (int i = 0; i < tasks.size(); i++) {
    ss << "{" << tasks[i]->exportJSON() << "}" << std::endl;
  }
	ss << "}";
  return ss.str();
}

std::string Board::toString() const {
  std::stringstream ss;
  ss << "BOARD: "<< name;
  for (int i = 0; i < tasks.size(); i++) {
    ss << tasks[i]->toString() << std::endl;
  }
  return ss.str();
}