#include <iostream>

using namespace std;

int f(int n) {
  if (n == 0) return 12;
  if (n == 1) return 22;
  if (n == 2) return 45;
  return 1 + f(n - 3) + f(n - 2);
}

int main() {
  cout << "Insert value for n: ";
  int num;
  cin >> num;
  for (int i = 2; i < num; i++){
    cout << "Recursion result: " << f(i) << endl;
  }
  return 0;
}

