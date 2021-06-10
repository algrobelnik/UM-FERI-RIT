#include "Size.h"

float Size::getWidth() { return width; }
void Size::setWidth(float width) { this->width = width; }
float Size::getHeight() { return height; }
void Size::setHeight(float height) { this->height = height; }
Unit Size::getUnit() { return unit; }
void Size::setUnit(Unit unit) { this->unit = unit; }
std::string Size::getUnitInString() {
  switch (unit) {
  case Unit::m:
    return "m";
  case Unit::mm:
    return "mm";
  case Unit::cm:
    return "cm";
  case Unit::dm:
    return "dm";
  case Unit::km:
    return "km";
  case Unit::in:
    return "in";
  case Unit::ft:
    return "ft";
  case Unit::yd:
    return "yd";
  case Unit::mi:
    return "mi";
  case Unit::cl:
    return "cl";
  case Unit::dl:
    return "dl";
  case Unit::g:
    return "g";
  case Unit::kg:
    return "kg";
  case Unit::ton:
    return "ton";
  default:
    return "ERROR";
  }
}
std::string Size::toString() const {
  std::stringstream ss;
  ss << "W: " << width << ", H: " << height;
  return ss.str();
}