#include <iostream>

using namespace std;

int main() {
  cout << "Insert value for N: ";
  long unsigned int N;
  cin >> N;
  for (long unsigned int i = 1; i < N; i++) {
    cout << i << endl;
  }
  return 0;
}

