#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <iostream>
#include <sstream>

class Triangle {
private:
  double a, b, c, area, perimeter;

public:
  Triangle(double a, double b, double c) : a(a), b(b), c(c) {}
  double getA();
  double getB();
  double getC();
  double getArea();
  double getPerimeter();
  std::string toString() const;
};

#endif
