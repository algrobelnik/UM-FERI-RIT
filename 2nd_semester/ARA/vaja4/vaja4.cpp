#include "BinReader.h"
#include "BinWriter.h"
#include <algorithm>
#include <bitset>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main(int argc, char **argv) {
  if (argc != 4) {
    cout << "Error: arguments are not OK" << endl;
    return -1;
  }
  if (argv[1][0] != 'c' && argv[1][0] != 'd') {
    cout << "argv[1] is not c or d" << endl;
    return -2;
  }
  int len = atoi(argv[2]);
  const int b_len = ceil(log2(len + 1));
  vector<string> S;
  for (int i = 0; i < 256; i++)
    S.push_back(std::string(1, i));
  unsigned int b_sum = 0;
  if (argv[1][0] == 'c') {
    BinReader br(argv[3]);
    BinWriter bw("out.bin");
    string T = "";
    while (br.f.peek() != EOF) {
      b_sum++;
      char val = br.readByte();
      auto itTmp = find(S.begin(), S.end(), T + val);
      if (itTmp != S.end()) {
        T = T + val;
      } else {
        auto it = find(S.begin(), S.end(), T);
        int tmp = distance(S.begin(), it);
        for (int i = b_len - 1; i >= 0; i--)
          bw.writeBit((tmp >> i) & 1);
        S.push_back(T + val);
        if (S.size() >= len) {
          S.clear();
          for (int i = 0; i < 256; i++)
            S.push_back(std::string(1, i));
        }
        T = val;
      }
    }
    auto it = find(S.begin(), S.end(), T);
    int tmp = distance(S.begin(), it);
    for (int i = b_len - 1; i >= 0; i--)
      bw.writeBit((tmp >> i) & 1);
    cout << b_sum * 8 << endl;
    cout << bw.b << endl;
    float ratio = (b_sum * 8 / (float)bw.b);
    cout << "Ratio: " << ratio << endl;
  } else {
    BinReader br(argv[3]);
    BinWriter bw("out_d.bin");
    string T = "";
    string tmp = "";
    br.readByte();
    while (br.f.peek() != EOF) {
      string b = "";
      for (int i = 0; i < b_len; i++)
        b += to_string(br.readBit());
      int ind = stoi(b, 0, 2);
      tmp = "";
      if (S.size() <= ind) {
        tmp = T + T[0];
        S.push_back(tmp);
      } else
        tmp = S[ind];
      for (int i = 0; i < tmp.length(); i++)
        bw.writeByte(tmp[i]);
      if (!tmp.empty()) {
        char val = tmp[0];
        if (find(S.begin(), S.end(), T + val) == S.end()) {
          S.push_back(T + val);
          if (S.size() >= len) {
            S.clear();
            for (int i = 0; i < 256; i++)
              S.push_back(std::string(1, i));
          }
        }
      }
      T = tmp;
    }
  }
  return 0;
}