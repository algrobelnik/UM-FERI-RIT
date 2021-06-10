#ifndef SIZE_H
#define SIZE_H

#include "Unit.h"
#include <iostream>
#include <string>
#include <sstream>

class Size {
private:
  float width, height;
  Unit unit;

public:
  Size(float width, float height, Unit unit)
      : width(width), height(height), unit(unit) {}
  float getWidth();
  void setWidth(float width);
  float getHeight();
  void setHeight(float height);
  Unit getUnit();
  void setUnit(Unit unit);
  std::string getUnitInString();
  std::string toString() const;
};
#endif