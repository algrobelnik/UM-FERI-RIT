#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

ofstream out;

string inputText(const string &pot) {
  ifstream input(pot);
  stringstream sstream;

  if (!input.is_open()) {
    return string();
  }

  sstream << input.rdbuf();
  return sstream.str();
}

void izpis_arr_KMPnext(const int *polje, int len) {
  for (int i = 0; i < len; ++i) {
    out << polje[i] << ' ';
  }
  out << endl;
}
void izpis_vec_KMPnext(vector<int> vec, int len) {
  for (int i = 0; i < len; ++i) {
    out << vec[i] << ' ';
  }
  out << endl;
}

void KMPinit(const string &text, const string &vzorec, int kmpNext[],
             int indexes[]) {
  for (int i = 0; i < 2; i++) {
    kmpNext[i] = i - 1;
  }
  while (indexes[0] < vzorec.size()) {
    while (indexes[1] >= 0 && vzorec[indexes[0]] != vzorec[indexes[1]]) {
      indexes[1] = kmpNext[indexes[1]];
    }
    for (int i = 0; i < 2; i++) {
      indexes[i]++;
    }
    kmpNext[indexes[0]] = indexes[1];
  }
  for (int i = 0; i < 2; i++) {
    indexes[i] = 0;
  }
}

void KMP(const string &text, const string &vzorec) {
  int kmpNext[text.size() + 1];
  int indexes[] = {1, 0};
  vector<int> hits;

  KMPinit(text, vzorec, kmpNext, indexes);
  while (indexes[0] < text.size()) {
    while (indexes[1] >= 0 && text[indexes[0]] != vzorec[indexes[1]]) {
      indexes[1] = kmpNext[indexes[1]];
    }
    for (int i = 0; i < 2; i++) {
      indexes[i]++;
    }
    if (indexes[1] == vzorec.size()) {
      hits.push_back(indexes[0] - indexes[1]);
    }
  }
  izpis_arr_KMPnext(kmpNext, vzorec.size());
  izpis_vec_KMPnext(hits, hits.size());
}

int main(int argc, const char *const argv[]) {
  if (argc != 3) {
    cout << "Error: arguments are not OK" << endl;
    return -1;
  }

  string text = inputText(argv[2]);
  string vzorec = argv[1];
  out.open("out.txt");

  if (!out) {
    return -2;
  }

  KMP(text, vzorec);
  return 0;
}