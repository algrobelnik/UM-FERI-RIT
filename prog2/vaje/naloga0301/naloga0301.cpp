#include "Trapez.h"
#include "Circle.h"
#include "Math.h"
#include <iostream>
#include <vector>

using namespace std;

int main() {
  srand(time(NULL));
  Circle::printCounter();
  int num1;
  cout << "Vnesi velikost vektorja: ";
  cin >> num1;
  vector<Circle *> b = Circle::generateCircles(num1);
  Circle::printCircles(b);
  Circle *aptr = Math::maxCircle(b[1], b[0]);
  cout << aptr->toString();
  Circle::printCounter();
	for (int i = 0; i < b.size(); i++){
		delete b[i];
	}
	b.clear();
	vector<Trapez *> c = Trapez::generateTrapez(num1);
  Trapez::printTrapez(c);
  Trapez *cptr = Math::maxTrapez(c[1], c[0]);
  cout << cptr->toString();
  Trapez::printCounter();
	for (int i = 0; i < c.size(); i++){
		delete c[i];
	}
	c.clear();
	Trapez::printCounter();
  return 0;
}