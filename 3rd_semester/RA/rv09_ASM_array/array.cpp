#include <cstring>
#include <iostream>

using namespace std;

void f(const char *ptr1, char *&ptr2, int size) {
  char *rev = new char[size];
  strcpy(rev, ptr1);
  for (int i = 0, j = size - 1; i < j; i++, j--)
    swap(rev[i], rev[j]);
  memcpy(&ptr2, &rev, 5);
}

int main() {
  const char *str1 = "ABCDE";
  char *str2 = "";
  f(str1, str2, 5);
  cout << "str1: " << str1 << endl;
  cout << "str2: " << str2 << endl;
  return 0;
}

