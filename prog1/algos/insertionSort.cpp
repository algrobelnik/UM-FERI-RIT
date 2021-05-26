#include <iostream>
using namespace std;

void swap(int &a, int &b) {
  int tmp = a;
  a = b;
  b = tmp;
}

void sortASC(int polje[], const int number) {
  int st, j;
  for (int i = 1; i < number; i++) {
    st = polje[i];
    j = i;
    for (; j > 0 && polje[j - 1] > st; j--) {
      swap(polje[j], polje[j - 1]);
    }
  }
}

void sortDESC(int polje[], const int number) {
  int st, j;
  for (int i = 1; i < number; i++) {
    st = polje[i];
    j = i;
    for (; j > 0 && polje[j - 1] < st; j--) {
      swap(polje[j], polje[j - 1]);
    }
  }
}

int main() {
  int polje[9] = {9, 2, 3, 6, 5, 1, 4, 8, 7};

  sortDESC(polje, 9);

  cout << "DESC: ";
  for (int a : polje) {
    cout << a;
  }
  cout << endl;
  return 0;
}