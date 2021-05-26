#include <iostream>
using namespace std;

void swap(int &a, int &b) {
  int tmp = a;
  a = b;
  b = tmp;
}

void sortASC(int polje[], int number) {
  for (int step = 0; step < number - 1; ++step) {
    for (int i = 0; i < number - step - 1; ++i) {
      if (polje[i] > polje[i + 1]) {
        swap(polje[i], polje[i + 1]);
      }
    }
  }
}

void sortDESC(int polje[], int number) {
  for (int step = 0; step < number - 1; ++step) {
    for (int i = 0; i < number - step - 1; ++i) {
      if (polje[i] < polje[i + 1]) {
        swap(polje[i], polje[i + 1]);
      }
    }
  }
}

int main() {
  int polje[9] = {9, 2, 3, 6, 5, 1, 4, 8, 7};

  sortASC(polje, 9);

  cout << "ASC: ";
  for (int a : polje) {
    cout << a;
  }
  cout << endl;

  sortDESC(polje, 9);

  cout << "DESC: ";
  for (int a : polje) {
    cout << a;
  }
  cout << endl;
  return 0;
}