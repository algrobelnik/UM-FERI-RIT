#include "BinReader.h"
#include "BinWriter.h"
#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <string>
#include <vector>
using namespace std;

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

void shannon_fano(map<char, string> &out, vector<char> v, vector<int> vec) {
  vector<int> left;
  vector<char> leftName;
  vector<int> right;
  vector<char> rightName;
  vector<int> res;
  int size = vec.size();
  for (int i = 1; i < size - 1; i++) {
    left.push_back(sum(vec, 0, i));
    right.push_back(sum(vec, i, vec.size()));
  }
  for (int i = 0; i < size - 2; i++) {
    res.push_back(abs(left[i] - right[i]));
  }
  int min = 0;
  for (int i = 1; i < size - 2; i++) {
    if (res[min] >= res[i])
      min = i;
  }
  left.clear();
  right.clear();
  for (int i = 0; i < size; i++) {
    if (out.find(v[i]) == out.end()) {
      out[v[i]] = to_string(i > min);
    } else {
      out[v[i]] += to_string(i > min);
    }
    if (i <= min) {
      leftName.push_back(v[i]);
      left.push_back(vec[i]);
    } else {
      rightName.push_back(v[i]);
      right.push_back(vec[i]);
    }
  }
  if (left.size() > 1) {
    shannon_fano(out, leftName, left);
  }
  if (right.size() > 1) {
    shannon_fano(out, rightName, right);
  }
}

int split(vector<char> &v, vector<int> &vec, int a, int b) {
  int pivot = vec[a];
  int li = a;
  int ri = b;
  while (li < ri) {
    while (vec[li] >= pivot && li < b)
      li++;
    while (vec[ri] <= pivot && ri > a)
      ri--;
    if (li < ri) {
      swap(vec[li], vec[ri]);
      swap(v[li], v[ri]);
    }
  }
  swap(vec[a], vec[ri]);
  swap(v[a], v[ri]);
  return ri;
}

void quickSort(vector<char> &v, vector<int> &vec, int a, int b) {
  if (a < b) {
    int tmp;
    tmp = split(v, vec, a, b);
    quickSort(v, vec, a, tmp - 1);
    quickSort(v, vec, tmp + 1, b);
  }
}

int main(int argc, char **argv) {
  if (argc != 3) {
    cout << "Error: arguments are not OK" << endl;
    return -1;
  }
  if (argv[1][0] != 'c' && argv[1][0] != 'd') {
    cout << "argv[1] is not c or d" << endl;
    return -2;
  }
  BinReader br(argv[2]);
  std::vector<char> fileBytes;
  map<char, int> temp;
  vector<char> freqName;
  vector<int> freq;
  map<char, string> values;

  if (argv[1][0] == 'c') {
    while (!br.f.eof()) {
      fileBytes.push_back(br.readByte());
    }

    for (int i = 0; i < fileBytes.size(); i++) {
      if (temp.find(fileBytes[i]) == temp.end()) {
        temp[fileBytes[i]] = 1;
      } else {
        temp[fileBytes[i]]++;
      }
    }

    for (pair<char, int> f : temp) {
      freqName.push_back(f.first);
      freq.push_back(f.second);
    }
    // vector<char> test1 = {65, 66 , 67, 68, 69};
    // vector<int> test2 = {5, 2, 2 , 1, 1};

    quickSort(freqName, freq, 0, freqName.size() - 1);

    shannon_fano(values, freqName, freq);
    BinWriter bw("out.bin");
    bw.writeInt(values.size());
    for (int i = 0; i < freqName.size(); i++) {
      bw.writeByte(freqName[i]);
      bw.writeInt(freq[i]);
    }
    BinReader read(argv[2]);
    // br.f.seekg(0, br.f.beg);
    //BinReader read("lorem_ipsum.txt");
    while (!read.f.eof()) {
      char val = read.readByte();
      for (int i = 0; i < values[val].size(); i++) {
        bw.writeBit(values[val][i] == '1');
      }
    }
    bw.writeByte(bw.x);
    int sum = 0;
    for (int i = 0; i < freq.size(); i++) {
      sum += freq[i];
    }
    cout << sum * 8 << endl;
    cout << bw.b << endl;
    float ratio = (sum * 8 / (float)bw.b);
    cout << "Ratio: " << ratio << endl;
  } else {
    // BinReader read(argv[2]);
    BinReader read("out.bin");
    BinWriter write("out_d.bin");
    int sValue = read.readInt();
    for (int i = 0; i < sValue; i++) {
      char c = read.readByte();
      int f = read.readInt();
      std::vector<char>::iterator it =
          find(freqName.begin(), freqName.end(), c);
      if (it != freqName.end()) {
        int index = distance(freqName.begin(), it);
        freq[index] = f;
      } else {
        freqName.push_back(c);
        freq.push_back(f);
      }
    }
    shannon_fano(values, freqName, freq);
    freqName.clear();
    vector<string> freqValues;
    for (pair<char, string> f : values) {
      freqName.push_back(f.first);
      freqValues.push_back(f.second);
    }

    // BinReader read2(argv[2]);
    read.readByte();
    string val = to_string(read.readBit());
    std::vector<string>::iterator it;
    while (!read.f.eof()) {
      it = find(freqValues.begin(), freqValues.end(), val);
      if (it != freqValues.end()) {
        int index = distance(freqValues.begin(), it);
        write.writeByte(freqName[index]);
        val = "";
      }
      val += to_string(read.readBit());
    }
    cout << "DONE!" << endl;
  }

  return 0;
}