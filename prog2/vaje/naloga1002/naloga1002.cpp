#include "Date.h"
#include "SmartPointer.h"
#include <iostream>
#include <memory>

using namespace std;

int main() {
  SmartPointer<Date> date1(new Date(6, 5, 2020));
  SmartPointer<Date> date2(new Date(1, 1, 2019));

  date2 = date1 = date1 = date1 = date1 = date1;
  date2 = date2;
  date2 = date2;

  std::cout << "reference count: " << date2.useCount() << std::endl;
  return 0;
}