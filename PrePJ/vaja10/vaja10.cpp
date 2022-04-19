#include <bits/stdc++.h>
#include <iostream>
#include <memory>
#include <vector>

using namespace std;

template <typename T> T myMax(T x, T y) { return (x > y) ? x : y; }

constexpr long int fib(int n) { return (n <= 1) ? n : fib(n - 1) + fib(n - 2); }

int main() {
  // auto
  auto first = myMax(0.23, 242.321);
  auto second = myMax("da", "lpo");
  cout << first << endl;
  cout << second << endl;
  // shared_ptr
  auto ptr = make_shared<int>(10);
  cout << *ptr << endl;
  // nullptr
  int ptr2 = NULL; // only warning
  cout << ptr2 << endl;
  auto ptr3 = nullptr; // error int ptr3 = nullptr;
  // lambda izraz
  vector<int> vec{3, 34, 123, 4, 21, 0, 23, -23, -1};
  for_each(vec.begin(), vec.end(), [](int i) { cout << i << " "; });
  cout << endl;
  // constexpr
  const long int res = fib(10);
  cout << res << endl;
  //  uniform initialization and initializer lists,
  int nums[] = {1, 2, 3, 4, 5};
  // range-based for loop
  for (int i : nums) {
    cout << i << " ";
  }
  cout << endl;
  string foo = "foo-string";
  string bar = "bar-string";
  vector<string> myvector;

  myvector.push_back(foo);       // copies
  myvector.push_back(move(bar)); // moves

  cout << "myvector contains:";
  for (string &x : myvector) {
    cout << ' ' << x;
  }
  cout << endl;
  cout << foo << " " << bar << endl;
  return 0;
}
