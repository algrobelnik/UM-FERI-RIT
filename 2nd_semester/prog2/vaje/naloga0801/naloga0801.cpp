#include <iostream>
#include <string>
#include "C.h"
#include "../naloga0701/Color.h"
#include "../naloga0502/Date.h"
#include "Triangle.h"

using namespace std;

template <typename M>
vector<M> toVector2X(M a, M b, int c) {
  vector<M> out;
  for(int i = 0; i < c; i++){
    out.push_back(a);
    out.push_back(b);
  }
  return out;
}

template <typename N>
long long vectorSize(vector<N> a) {
  return sizeof(N)*a.size();
}

int main () {
  C<double> o1;
  C<string> o2;
  double a = 1., b = 2., c = 3.;
  cout << "The largest number between " << a << " and " << b << " and " << c << " is " << o1.largest(a, b, c) << "." << endl;
  string s1 = "Hello", s2 = "World", s3 = "da";
  cout << o2.largest(s1, s2, s3) << "." << endl;
  C<Color> o3;
  Color c1(101, 100, 100);
  Color c2(100, 0, 0);
  Color c3(100, 122, 100);
  C<Date> o4;
  Date d1(15, 10, 2001);
  Date d2(31, 1, 1996);
  Date d3(1, 2, 2002);
  Date d4(3, 1, 2002);
  Date d5(2, 1, 2002);
  Date d6(1, 1, 2002);
  C<Triangle> o5;
  Triangle t1(10.5, 23.2, 12.21);
  Triangle t2(3, 11.11111, 33);
  Triangle t3(7.7, 7.7, 7.7);
  /* cout << c1.toString();
  cout << c2.toString();
  cout << c3.toString(); */
  
  cout << o3.largest(c1, c2, c3).toString() << "." << endl;
  cout << o4.largest(d1, d2, d3).toString() << "." << endl;
  cout << o4.largest(d4, d5, d6).toString() << "." << endl;
  cout << o5.largest(t1, t2, t3, 1).toString() << "." << endl;
  cout << o5.largest(t1, t2, t3, 0).toString() << "." << endl;
  cout << o5.largest(t1, t2, t3, 0).toString() << "." << endl;
  vector<const char *> out = toVector2X("hi", "you", 7);
  cout << "[";
  for (int i = 0; i < out.size(); i++)
    cout << (i > 0?", ":"") << out[i];
  cout << "]" << endl;
  vector<Color> classOut = toVector2X(c1, c2, 2);
  cout << "[";
  for (int i = 0; i < classOut.size(); i++)
    cout << (i > 0?", ":"") << classOut[i].toString();
  cout << "]" << endl;
  vector<int> testVec(2,12312);
  cout << "Size 1: " << vectorSize(out) << endl;
  cout << "Size 2: " << vectorSize(classOut) << endl;
  cout << "Size 3: " << vectorSize(testVec) << endl;
  
  return 0;
}