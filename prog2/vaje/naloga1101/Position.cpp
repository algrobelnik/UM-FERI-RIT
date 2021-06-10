#include "Position.h"

float Position::getX() { return x; }
float Position::getY() { return y; }
std::string Position::toString() const {
  std::stringstream ss;
  ss << "X: " << x << ", Y: " << y;
  return ss.str();
}