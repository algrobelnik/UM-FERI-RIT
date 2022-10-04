#include "Board.h"
#include <sstream>

Board::Board(std::string name) : name(name) {}
//Board::~Board() { categories.clear(); }

void Board::addCategory(const Category &category) { categories.push_back(category); }

bool Board::addTask(const std::string &categoryName, Task* task) { 
	for(int i = 0; i < categories.size(); i++){
		if(categories[i].getName() == categoryName){
			categories[i].addTask(task);
			return true;
		}
	}
	return false;
}

std::vector<Task *> Board::agenda(const DateTime &dt) const{
	std::vector<Task *> out;
	for(int i = 0; i < categories.size(); i++){
		for(int j = 0; j < categories[i].getTasks().size(); j++){
			if(categories[i].getTasks()[j]->getAdded().isEqual(dt))
				out.push_back(categories[i].getTasks()[j]);
		}
	}
	return out;
}

std::vector<Task *> Board::beforeDate(const DateTime &dt) const{
	std::vector<Task *> out;
	for(int i = 0; i < categories.size(); i++){
		for(int j = 0; j < categories[i].getTasks().size(); j++){
			if(categories[i].getTasks()[j]->getAdded().isBefore(dt))
				out.push_back(categories[i].getTasks()[j]);
		}
	}
	return out;
}

std::vector<Task *> Board::afterDate(const DateTime &dt) const{
	std::vector<Task *> out;
	for(int i = 0; i < categories.size(); i++){
		for(int j = 0; j < categories[i].getTasks().size(); j++){
			if(categories[i].getTasks()[j]->getAdded().isAfter(dt))
				out.push_back(categories[i].getTasks()[j]);
		}
	}
	return out;
}

Board Board::removeAllWithTaskName(const std::string &taskName) const{
	Board cpy(*this);
	for(int i = 0; i < categories.size(); i++){
		for(int j = 0; j < categories[i].getTasks().size(); j++){
			if(categories[i].getTasks()[j]->getName() != taskName){
				cpy.addTask(categories[i].getName(), categories[i].getTasks()[j]);
			}
		}
	}
	return cpy;
}

std::string Board::toString() const {
  std::stringstream ss;
  ss << "BOARD: " << name << std::endl;
  for (int i = 0; i < categories.size(); i++) {
    ss << categories[i].toString() << std::endl;
  }
  return ss.str();
}