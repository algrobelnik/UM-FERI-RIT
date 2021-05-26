#include "Circle.h"
#include "Trapez.h"
#include <iostream>
#ifndef MATH_H
#define MATH_H

using namespace std;

class Math {
private:
  Math();

public:
  static constexpr float PI = 3.14159265358979323846;
  static int square(int a) { return a * a; };
  static Circle *maxCircle(Circle *a, Circle *b) {
    if (Circle::getDiameter(a) > Circle::getDiameter(b)) {
      return a;
    }
    return b;
  }
	static Trapez *maxTrapez(Trapez *a, Trapez *b) {
    if (Trapez::getArea(a) > Trapez::getArea(b)) {
      return a;
    }
    return b;
  }
	static int randGen(int min, int max){
		int range = max - min++;
		return rand() % range + min;
	}
};

#endif
