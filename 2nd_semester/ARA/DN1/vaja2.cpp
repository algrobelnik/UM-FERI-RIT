#include <bitset>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

vector<unsigned char> countingSort(vector<unsigned char> A, int k) {
  vector<unsigned char> B(A.size());
  vector<int> C(2, 0);
  for (int i = 0; i < A.size(); i++)
    C[(A[i] >> k) & 1]++;
  C[1] += C[0];
  for (int i = A.size() - 1; i >= 0; i--)
    B[--C[(A[i] >> k) & 1]] = A[i];
  swap(A, B);
  return A;
}

vector<unsigned char> radixSort(vector<unsigned char> A) {
  for (int bit = 0; bit < 8; bit++)
    A = countingSort(A, bit);
  return A;
}

bool Branje_Stevil(vector<unsigned char> &vec, const char s[]) {
  ifstream input(s);
  int st;

  if (!input.is_open()) {
    return false;
  }

  while (!input.eof()) {
    input >> st;
    bitset<8> b(st);
    unsigned char c = static_cast<unsigned char>(b.to_ulong());
    vec.push_back(c);
    while (isspace(input.peek()))
      input.get();
  }
  input.close();
  return true;
}

void Izpis_Stevil(vector<unsigned char> &vec, unsigned int velikost) {
  ofstream output("out.txt");
  for (int i = 0; i < velikost; i++) {
    output << static_cast<int>(vec[i]) << " ";
  }
}

int main(int argc, const char *argv[]) {
  vector<unsigned char> A;

  if (argc < 2)
    return 0;
  if (!Branje_Stevil(A, argv[1]))
    return 0;

  A = radixSort(A);

  Izpis_Stevil(A, A.size());

  return 0;
}
