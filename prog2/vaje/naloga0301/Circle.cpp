#include "Circle.h"
#include "Math.h"
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

int Circle::counter = 0;

Circle::Circle() : radius(1.0) { counter++; }
Circle::Circle(const Circle *a) : radius(a->radius) { counter++; }
Circle::Circle(double radius) : radius(radius) { counter++; }
Circle::~Circle() { counter--; }
string Circle::toString() const {
  stringstream ss;
  ss << "Circle[" << counter << "] has radius: " << radius << endl;
  if(area != 0 && diameter != 0) ss << "Diameter: " << diameter << ", Area: " << area << endl;
  return ss.str();
}
void Circle::printCounter() { cout << "Counter: " << counter << endl; }
void Circle::calculateDiameter(Circle *a) {
	a->diameter = 2 * Math::PI * a->radius;
}
void Circle::calculateArea(Circle *a) {
	a->area = Math::PI * Math::square(a->radius);
}
double Circle::getDiameter(Circle *a) {
	return a->diameter;
}
double Circle::getArea(Circle *a) {
	return a->area;
}
vector<Circle *> Circle::generateCircles(int length) {
  if (length < 2)
    length = 2;
  vector<Circle *> vec;
  for (int i = 0; i < length; i++) {
    if (i != 0){
      vec.push_back(new Circle(Math::randGen(0, 10)));
			calculateDiameter(vec[i]);
			calculateArea(vec[i]);
		}
    else{
      vec.push_back(new Circle());
			calculateDiameter(vec[i]);
			calculateArea(vec[i]);
		}
    Circle::printCounter();
  }
  return vec;
}

void Circle::printCircles(vector<Circle *> vec) {
  for (int i = 0; i < vec.size(); i++)
    cout << vec[i]->toString();
}