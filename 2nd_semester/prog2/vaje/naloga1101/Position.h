#ifndef POSITION_H
#define POSITION_H

#include <iostream>
#include <sstream>

class Position {
private:
  float x, y;

public:
  Position(float x, float y) : x(x), y(y) {}
  float getX();
  float getY();
  std::string toString() const;
};
#endif