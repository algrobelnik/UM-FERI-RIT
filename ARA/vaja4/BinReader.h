#ifndef BINREADER_H
#define BINREADER_H

#include <iostream>
#include <fstream>
#include <vector>

class BinReader {
  public:
    int k;
    std::ifstream f;
    char x;
    BinReader(std::string path): k(0){
      f.open(path, std::ios::binary);
    };

    bool readBit(){
      if (k == 8) {
        readByte();
        k = 0;
      }
      bool b = (x >> k) & 1;
      k++;
      return b;
    };

    char readByte(){
      f.read((char*)&x, 1);
      return x;
    };

    int readInt(){
      int x = 0;
      f.read(reinterpret_cast<char*>(&x), 4);
      return x;
    };

    float readFloat(){
      float x = 0;
      f.read(reinterpret_cast<char*>(&x), 4);
      return x;
    };

    ~BinReader(){
      f.close();
    };
};

#endif
