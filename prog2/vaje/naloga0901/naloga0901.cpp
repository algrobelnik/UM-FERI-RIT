#include <iostream>
#include <string>
#include "MyStack.h"
#include "Point.h"
#include "../naloga0502/Date.h"

int main () {
  srand(time(0));
  MyStack<double> o1("test double");
  o1.push(1923.12);
  o1.push(17);
  o1.push(312.2);
  o1.push(78.32);
  if(!o1.empty()){
    if(o1.pop()){
      std::cout << o1.top() << std::endl << o1.size() << std::endl; 
    }
  }
  MyStack<std::string> o2("test string");
  o2.push("J");
  o2.push("A");
  o2.push("N");
  o2.push("E");
  o2.push("Z");
  
  o2.popX(3);
  std::cout << o2.size() << std::endl;
  std::vector<std::string> out = o2.backX(2);
  o2.pushX(out);
  std::cout << "HERE";
  std::cout << o1.toString() << std::endl;
  std::cout << o2.toString() << std::endl;
  o2.addXToAll("A");
  o2.reverse();
  o2.deleteRandomElements();
  std::cout << o2.toString() << std::endl;
  
  
  MyStack<Date> o3("test datumi");
  Date d1(15, 10, 2001);
  Date d2(31, 1, 1996);
  Date d3(1, 2, 2002);
  Date d4(3, 1, 2002);
  Date d5(2, 1, 2002);
  Date d6(1, 1, 2002);
  o3.push(d1);
  o3.push(d2);
  o3.push(d3);
  o3.push(d4);
  o3.push(d5);
  o3.push(d6);
  std::cout << o3.toString() << std::endl;

  Point<float> o4;
  o4.move(2, 0.5);
  Point<float> o5;
  o5.move(4, 0.4).move(-2,0.1);
  std::cout << o4.toString() << std::endl;
  std::cout << o5.toString() << std::endl;
  std::cout << o4.equal(o5) << std::endl;

  return 0;
}