#include "Board.h"
#include <sstream>

float randGen(int min, int max) {
  int range = max - min++;
  return rand() % range + min;
}

bool exists(std::map<std::string, Task*> tasks, std::string name){
  for (std::pair<std::string, Task *> task : tasks) {
    if(task.first == name) return true;
  }
  return false;
}

Board::Board(std::string name) : name(name) {}
Board::~Board(){
	for (std::pair<std::string, Task *> task : tasks) {
    delete task.second;
  }
	tasks.clear();
}

std::map<std::string, Task*> Board::getTasks(){
  return tasks;
}

bool Board::addTask(Task *task) {
  bool check = exists(tasks, task->getName());
  if(!check){
    tasks[task->getName()] = task;
    std::vector<std::string> tags = task->getTags();
    for(int i = 0; i<tags.size(); i++)
      byTag[tags[i]].push_back(task);
  }
  return !check;
}

Task* Board::findTask(const std::string key){
  bool check = exists(tasks, key);
  if(!check){
    return tasks[key];
  }
  return NULL;
}

void Board::deleteTask(const std::string key){
  bool check = exists(tasks, key);
  if(!check){
    for (std::map<std::string, Task *>::iterator it = tasks.begin(); it != tasks.end(); it++) {
      if(it->first == key)tasks.erase(it);
    }
  }
}

unsigned int Board::numberOfTasks() const{
  unsigned int numb = 0;
  for (std::pair<std::string, Task *> task : tasks) {
    numb++;
  }
  return numb;
}

std::vector<Task *> Board::toVector(Board board){
  std::vector<Task *> out;
  for (std::pair<std::string, Task *> task : board.getTasks()) {
    out.push_back(task.second);
  }
  return out;
}

void Board::reverse(){
  std::map<std::string, Task*> out;
  for (std::map<std::string, Task *>::iterator it = tasks.end(); it != tasks.begin(); it--) {
    out[it->first] = it->second;
  }
  tasks = out;
};

void Board::changeEveryKey(std::string k){
  for (std::pair<std::string, Task *> task : tasks) {
    tasks[task.first+k] = task.second;
  }
};

void Board::deleteRandomElements(){
  for (std::map<std::string, Task *>::iterator it = tasks.begin(); it != tasks.end(); it++) {
    if(randGen(-1,1))tasks.erase(it);
  }
};

std::vector<Task *> Board::findTaskByTag(const std::string tag){
  if(byTag.find(tag) != byTag.end())
    return byTag.at(tag);
  return {};
};

std::string Board::exportJSON() const {
  std::stringstream ss;
  ss << "BOARD: {" << name;
  for (std::pair<std::string, Task *> task : tasks) {
    ss << "{(" << task.first << ") " << task.second->exportJSON() << "}" << std::endl;
  }
	ss << "}";
  return ss.str();
}

std::string Board::toString() const {
  std::stringstream ss;
  ss << "BOARD: "<< name;
  for (std::pair<std::string, Task *> task : tasks) {
    ss << "(" << task.first << ") " << task.second->toString() << std::endl;
  }
  return ss.str();
}