#ifndef TRAPEZ_H
#define TRAPEZ_H

#include <iostream>
#include <vector>

using namespace std;

class Trapez {
private:
  double a, b, c, d, h;
  double area, diameter;
  static int counter;

public:
  Trapez();
  Trapez(const Trapez *t);
  Trapez(double a, double b, double c, double d, double h);
  ~Trapez();
  string toString() const;
  static void printCounter();
  static void calculateDiameter(Trapez *t);
  static void calculateArea(Trapez *t);
  static double getDiameter(Trapez *t);
  static double getArea(Trapez *t);
	static vector<Trapez *> generateTrapez(int length);
	static void printTrapez(vector<Trapez *> vec);

};

#endif
