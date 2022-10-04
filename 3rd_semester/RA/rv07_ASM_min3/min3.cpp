#include <iostream>

using namespace std;

bool minVal(int min, int u, int v) {
  if (min < u) {
    if (min < v) {
      return true
    }
  }
  // return min < u && min < v;
}

int main() {
  cout << "Insert value for x1: ";
  int x1;
  cin >> x1;
  cout << "Insert value for x2: ";
  int x2;
  cin >> x2;
  cout << "Insert value for x3: ";
  int x3;
  cin >> x3;
  int res = x1;
  if (minVal(x1, x2, x3))
    res = x1;
  if (minVal(x2, x1, x3))
    res = x2;
  if (minVal(x3, x1, x2))
    res = x3;
  cout << "Lowest number: " << res << endl;
  return 0;
}

