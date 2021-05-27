#include "Date.h"
#include "SmartPointer.h"
#include <iostream>
#include <memory>

using namespace std;

int main() {
  SmartPointer<Date> date1(new Date(6, 5, 2020));
  {
    SmartPointer<Date> date2(new Date(31, 12, 2020));
    (*date2)++;
    cout << *date2 << endl;
  }
  //cout << *date2 << endl;
  cout << date1->toString() << endl;

  auto ob1 = shared_ptr<Date>(new Date(1, 2, 2021));
  shared_ptr<Date> ob2(new Date(1, 1, 1900));
  ob2->setDay(10);
  ob2->setMonth(3);
  ob2->setYear(2021);
  ob1 = ob2;
  cout << (ob1.get() == ob2.get()) << endl;
  return 0;
}