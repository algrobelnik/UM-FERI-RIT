#ifndef POINT_H
#define POINT_H

#include <iostream>
#include <sstream>
#include <string>
#include <cmath>
#include <iomanip>

template <typename T>
class Point {
private:
  T x, y;

public:
  Point() : x(0), y(0) {}
  Point(T x, T y) : x(x), y(y) {}
  Point &move(T x1, T y1){
    x += x1;
    y += y1;
    return this;
  }
  bool equal(const Point &t) const{
    return this == t;
  };
  std::string toString() const{
    std::stringstream ss;
    ss << "X: " << x << ", Y: " << y;
    return ss.str();
  };
};

template <>
class Point<float> {
private:
  float x, y;

public:
  Point() : x(0), y(0) {}
  Point(float x, float y) : x(x), y(y) {}
  Point &move(float x1, float y1){
    x += x1;
    y += y1;
    return *this;
  }
  bool equal(const Point &t) const{
    return std::abs(t.x - x) < 0.0001 && std::abs(t.y - y) < 0.0001;
  };
  std::string toString() const{
    std::stringstream ss;
    ss << "X: " << std::setprecision(10) << x << ", Y: " << std::setprecision(10) << y;
    return ss.str();
  };
};

#endif
