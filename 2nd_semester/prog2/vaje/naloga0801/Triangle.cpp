#include "Triangle.h"

double Triangle::getA() { return a; }

double Triangle::getB() { return b; }

double Triangle::getC() { return c; }

double Triangle::getArea() { area = (a + b + c) / 2; return (a + b + c) / 2; }

double Triangle::getPerimeter() { perimeter = a + b + c; return a + b + c; }

std::string Triangle::toString() const {
  std::stringstream ss;
  ss << "Triangle: (" << a << ", " << b << ", " << c << "), perimeter: " << perimeter << ", area: " << area;
  return ss.str();
}