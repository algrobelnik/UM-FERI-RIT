#ifndef C_h
#define C_h
#include <iostream>
#include <string>
#include <vector>
#include "../naloga0701/Color.h"
#include "../naloga0502/Date.h"
#include "Triangle.h"

using namespace std;

template <typename T>
class C{
  public:
    T const& largest(T const& a, T const& b, T const& c) { 
      if (a > b && a > c)
        return a;
      else if(b > c && b > a)
        return b;
      else
        return c;
    }
    
};

template <>
class C<string>{
  public:
    string const& largest(string &a, string &b, string &c) {
      /* std::cout << "a:" << a.length() << std::endl;
      std::cout << "a:" << b.length() << std::endl;
      std::cout << "a:" << c.length() << std::endl; */
      if (a.length() >= b.length() && a.length() >= c.length())
        return a;
      else if(b.length() >= c.length() && b.length() >= a.length())
        return b;
      else
        return c;
    }
};

template <>
class C<Color>{
  public:
    Color const& largest(Color &a, Color &b, Color &c) {
      /* std::cout << "a:" << a.length() << std::endl;
      std::cout << "a:" << b.length() << std::endl;
      std::cout << "a:" << c.length() << std::endl; */
      unsigned int aT = a.getRed() + a.getGreen() + a.getBlue();
      unsigned int bT = b.getRed() + b.getGreen() + b.getBlue();
      unsigned int cT = c.getRed() + c.getGreen() + c.getBlue();
      if (aT >= bT && aT >= cT)
        return a;
      else if(bT >= cT && bT >= aT)
        return b;
      else
        return c;
    }
};

template <>
class C<Date>{
  public:
    Date const& largest(Date &a, Date &b, Date &c) {
      /* std::cout << "a:" << a.length() << std::endl;
      std::cout << "a:" << b.length() << std::endl;
      std::cout << "a:" << c.length() << std::endl; */
      if (a.getYear() == b.getYear() && a.getYear() == c.getYear()){
        if (a.getMonth() == b.getMonth() && a.getMonth() == c.getMonth()){
          if (a.getDay() == b.getDay() && a.getDay() == c.getDay()){
            return a;
          }else{
            if (a.getDay() >= b.getDay() && a.getDay() >= c.getDay())
              return a;
            else if(b.getDay() >= c.getDay() && b.getDay() >= a.getDay())
              return b;
            else
              return c;
          }
        }else{
          if (a.getMonth() >= b.getMonth() && a.getMonth() >= c.getMonth())
            return a;
          else if(b.getMonth() >= c.getMonth() && b.getMonth() >= a.getMonth())
            return b;
          else
            return c;
        }
      } else{
        if (a.getYear() >= b.getYear() && a.getYear() >= c.getYear())
          return a;
        else if(b.getYear() >= c.getYear() && b.getYear() >= a.getYear())
          return b;
        else
          return c;
      }
    }
};

template <>
class C<Triangle>{
  public:
    Triangle const& largest(Triangle &a, Triangle &b, Triangle &c, bool t) {
      double aP, aA, bP, bA, cP, cA;
      aP = a.getPerimeter();
      aA = a.getArea();
      bP = b.getPerimeter();
      bA = b.getArea();
      cP = c.getPerimeter();
      cA = c.getArea();
      if(t){
        if (aP >= bP && aP >= cP)
          return a;
        else if(bP >= cP && bP >= aP)
          return b;
        else
          return c;
      }else{
        if (aA >= bA && aA >= cA)
          return a;
        else if(bA >= cA && bA >= aA)
          return b;
        else
          return c;
      }
    }
};


#endif