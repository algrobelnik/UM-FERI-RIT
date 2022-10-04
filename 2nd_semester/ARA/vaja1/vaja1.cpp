#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

bool Branje_Stevil(vector<int> &vec, const char s[]) {
  ifstream input(s);
  int st;

  if (!input.is_open()) {
    return false;
  }

  while (!input.eof()) {
    input >> st;
    vec.push_back(st);
    while (isspace(input.peek()))
      input.get();
  }
  input.close();
  return true;
}

void removeNegNumbers(vector<int> &vec, int &number, unsigned int size) {
  number = vec[0];
  for (int i = 1; i < size; i++) {
    if (number > vec[i])
      number = vec[i];
  }
  for (int i = 0; i < size; i++) {
    vec[i] -= number;
  }
}

void addNegNumbers(vector<int> &vec, int number, unsigned int size) {
  for (int i = 0; i < size; i++) {
    vec[i] += number;
  }
}

void DeclareVector(vector<int> &vec, vector<int> &vecEnd, unsigned int size) {
  int max = vec[0];
  for (int i = 1; i < size; i++) {
    if (max < vec[i])
      max = vec[i];
  }
  for (int i = 0; i < max + 1; i++) {
    vecEnd.push_back(0);
  }
}

void Izpis_Stevil(int *polje, unsigned int velikost) {
  ofstream output("out.txt");

  for (int i = 0; i < velikost; i++)
    output << polje[i] << ' ';
}

int main(int argc, const char *argv[]) {
  vector<int> A;
  vector<int> B;
  vector<int> C;

  if (argc < 3)
    return 0;
  if (!Branje_Stevil(A, argv[2]))
    return 0;

  int varNumber;
  removeNegNumbers(A, varNumber, A.size());
  DeclareVector(A, C, A.size());
  for (int i = 0; i < A.size(); i++)
    C[A[i]] = C[A[i]] + 1;
  for (int i = 0; i < A.size(); i++)
    B.push_back(0);

  if (argv[1][0] == '0') {
    for (int i = 1; i < C.size(); i++)
      C[i] = C[i] + C[i - 1];

    for (int i = 0; i < A.size(); i++) {
      B[C[A[i]] - 1] = A[i];
      C[A[i]] = C[A[i]] - 1;
    }
  } else {
    int count = 0;
    for (int i = 0; i < C.size(); i++) {
      if (C[i] != 0) {
        for (int j = 0; j < C[i]; j++) {
          B[count] = i;
          count++;
        }
      }
    }
  }

  addNegNumbers(B, varNumber, B.size());
  Izpis_Stevil(&B[0], B.size());

  return 0;
}
