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

void izpis_arr(const int *polje, int len) {
  for (int i = 0; i < len; ++i) {
    out << polje[i] << ' ';
  }
  out << endl;
}
void izpis_vec(vector<int> vec, int len) {
  for (int i = 0; i < len; ++i) {
    out << vec[i] << ' ';
  }
  out << endl;
}
void BCH(const string &text, const string &vzorec) {
  long unsigned int indexes[] = {vzorec.size(), text.size()};
  vector<int> BCH(256, indexes[0] + 1);
  vector<int> hits;

  for (int i = 0; i < indexes[0]; i++) {
    BCH[vzorec[i]] = indexes[0] - i;
  }
  for (int i, j = 0; i < indexes[0]; i++) {
    if (j >= indexes[1] - indexes[0]) {
      // izpis_vec(BCH, BCH.size());
      izpis_vec(hits, hits.size());
      return;
    }
    if (vzorec[i] != text[j + i]) {
      j += BCH[text[j + indexes[0] - i]];
      i = -1;
    }
    if (i == indexes[0] - 1) {
      hits.push_back(j);
      j += indexes[0];
      i = -1;
    }
  }
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

  BCH(text, vzorec);
  return 0;
}