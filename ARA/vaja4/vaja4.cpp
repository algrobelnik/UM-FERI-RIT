#include "BinReader.h"
#include "BinWriter.h"
#include <algorithm>
#include <bitset>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

string getBitsFromInt(int num, int b_len) {
  string out = "";
  int prev = num;
  for (int i = 0; i < ceil(log2(num + 1)); i++) {
    out += to_string(prev % 2 == 1);
    prev /= 2;
  }
  if(b_len - ceil(log2(num + 1)) > 0){
    for (int i = 0; i < b_len - ceil(log2(num + 1)); i++) {
      out += to_string(0);
    }
  }else{
    std::string tmp = out.substr(ceil(log2(num + 1))-b_len,b_len);
  }
  reverse(out.begin(), out.end());
  return out;
}

int sum(vector<int> vec, int min, int max) {
  if (min == max)
    return 0;
  if (min > max)
    swap(min, max);
  int a = 0;
  for (; min < max; min++) {
    a += vec[min];
  }
  return a;
}

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
  // int len = 1024;
  const int b_len = ceil(log2(len + 1));
  vector<string> S(256);
  // vector<string> S(26);
  for (int i = 0; i < 256; i++) {
    // for (int i = 0; i < 26; i++) {
    char tmp = i;
    // char tmp = i + 65;
    S[i] = tmp;
  }
  vector<string> out;

  if (argv[1][0] == 'c') {
    // if (1) {
    BinReader br(argv[3]);
    // BinReader br("lorem_ipsum.txt");
    BinWriter bw("out.bin");
    string T = "";
    int index = S.size() - 1;
    string hldr;
    while (br.f.peek() != EOF) {
      if (index == 2605)
        cout << "Here";
      char val = br.readByte();
      if (find(S.begin(), S.end(), T + val) != S.end()) {
        T += val;
      } else {
        auto it = find(S.begin(), S.end(), T);
        if (it == S.end()) {
          hldr = getBitsFromInt(index, b_len);
        } else {
          hldr = getBitsFromInt(distance(S.begin(), it), b_len);
        }
        for (int i = 0; i < b_len; i++) {
          bool res = hldr[i] == '1';
          bw.writeBit(res);
        }
        out.push_back(hldr);
        S.push_back(T + val);
        index++;
        T = val;
      }
    }
    auto it = find(S.begin(), S.end(), T);
    hldr = getBitsFromInt(distance(S.begin(), it), b_len);
    string tmp = "";
    for (int i = 0; i < b_len; i++) {
      bool res = hldr[i] == '1';
      bw.writeBit(res);
      tmp += to_string(res);
    }
    // cout << endl;
    out.push_back(tmp);
  } else {
    BinReader br(argv[3]);
    // BinReader br("out.bin");
    BinWriter bw("out_d.bin");
    string tmp = "";
    string val = "";
    string T = "";
    br.readByte();
    while (br.f.peek() != EOF) {
      for (int i = 0; i < b_len; i++) {
        tmp += to_string(br.readBit());
      }
      int ind = stoi(tmp, 0, 2);
      tmp = "";
      if (S.size() <= ind) {
        break;
      }
      val = S[ind];
      // cout << ind << "-" << val << "-" << T[0] << endl;
      // cout << "[" << val+T[0] << "]" << endl;
      for (int i = 0; i < val.length(); i++) {
        bw.writeByte(val[i]);
      }
      string checkString;
      if (T == "") {
        checkString = val;
      } else {
        checkString = T + val[0];
      }
      if (find(S.begin(), S.end(), checkString) != S.end()) {
        T += val;
      } else {
        S.push_back(T + val[0]);
        T = val;
      }
    }
    T += T[0];
    S.push_back(T);
    for (int i = 0; i < T.length(); i++) {
      bw.writeByte(T[i]);
    }
  }
  return 0;
}