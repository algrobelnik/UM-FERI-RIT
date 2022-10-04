#include "Date.h"
#include "ReferenceCounter.h"
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
  std::cout << "reference equal count: "
            << ReferenceCounter::NoOfEqualExpressions << std::endl;

  SmartPointer<Date> a(new Date(2, 2, 2020));
  SmartPointer<Date> b(new Date(17, 12, 2019));
  a = b;
  return 0;
}