#ifndef BINWRITER_H
#define BINWRITER_H

#include <iostream>
#include <fstream>
#include <vector>

class BinWriter {
  public:
    int k;
    std::ofstream f;
    char x;
    BinWriter(std::string path) : k(0) {
      f.open(path, std::ios::binary);
    };

    void writeBit(bool b) {
      if (k == 8) {
        writeByte(x);
        k = 0;
      }
      x ^= (-b ^ x) & (1 << k);
      k++;
    };

    void writeByte(char x) {
      f.write((char*)&x, 1);
    };

    void writeInt(int y) {
      f.write((char*)&y, 4);
    };

    void writeFloat(int y) {
      f.write((char*)&y, 4);
    };

    ~BinWriter() {
      if (k > 0) writeByte(x);
      f.close();
    };
};

#endif