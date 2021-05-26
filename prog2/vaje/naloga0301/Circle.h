#ifndef CIRCLE_H
#define CIRCLE_H

#include <iostream>
#include <vector>

using namespace std;

class Circle {
private:
  double radius, area, diameter;
  static int counter;

public:
  Circle();
  Circle(const Circle *a);
  Circle(double radius);
  ~Circle();
  string toString() const;
  static void printCounter();
  static void calculateDiameter(Circle *a);
  static void calculateArea(Circle *a);
  static double getDiameter(Circle *a);
  static double getArea(Circle *a);
	static vector<Circle *> generateCircles(int length);
	static void printCircles(vector<Circle *> vec);
	static int randGen(int min, int max);

};

#endif
