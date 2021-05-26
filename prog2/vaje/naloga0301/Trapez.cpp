#include "Trapez.h"
#include "Math.h"
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

int Trapez::counter = 0;

Trapez::Trapez() : a(1.0), b(1.0), c(1.0), d(1.0), h(1.0) { counter++; }
Trapez::Trapez(const Trapez *t) : a(t->a), b(t->b), c(t->c), d(t->d), h(t->h) { counter++; }
Trapez::Trapez(double a, double b, double c, double d, double h) : a(a), b(b), c(c), d(d), h(h) { counter++; }
Trapez::~Trapez() { counter--; }
string Trapez::toString() const {
  stringstream ss;
  ss << "Trapez[" << counter << "] has a: " << a << ", b: " << b << ", c: " << c << ", d: " << d << " and height: " << h << "." << endl;
  if(area != 0 && diameter != 0) ss << "Diameter: " << diameter << ", Area: " << area << endl;
  return ss.str();
}
void Trapez::printCounter() { cout << "Counter: " << counter << endl; }
void Trapez::calculateDiameter(Trapez *t) {
	t->diameter = t->a + t->b + t->c + t->d;
}
void Trapez::calculateArea(Trapez *t) {
	t->area = (t->a+t->c)/2 * t->h;
}
double Trapez::getDiameter(Trapez *t) {
	return t->diameter;
}
double Trapez::getArea(Trapez *t) {
	return t->area;
}
vector<Trapez *> Trapez::generateTrapez(int length) {
  if (length < 2)
    length = 2;
  vector<Trapez *> vec;
  for (int i = 0; i < length; i++) {
    if (i != 0){
      vec.push_back(new Trapez(Math::randGen(0, 10), Math::randGen(0, 10), Math::randGen(0, 10), Math::randGen(0, 10), Math::randGen(0, 10)));
			calculateDiameter(vec[i]);
			calculateArea(vec[i]);
		}
    else
		{
      vec.push_back(new Trapez());
			calculateDiameter(vec[i]);
			calculateArea(vec[i]);
		}
    Trapez::printCounter();
  }
  return vec;
}

void Trapez::printTrapez(vector<Trapez *> vec) {
  for (int i = 0; i < vec.size(); i++)
    cout << vec[i]->toString();
}