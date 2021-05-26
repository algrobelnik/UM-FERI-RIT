#include <string>
#include <vector>
#include "BinWriter.h"
#include "BinReader.h"
using namespace std;

int main() {
  BinWriter bw("test.bin");
	bw.writeBit(1);
	bw.writeBit(0);
	bw.writeBit(0);
	bw.writeBit(0);
	bw.writeBit(0);
	bw.writeBit(0);
	bw.writeBit(1);
	bw.writeBit(0); 
	bw.writeByte(bw.x);
	bw.f.close();

	BinReader br("test.bin");
	br.readByte();
	for (int i = 0; i < 8; ++i)
		std::cout << (int)br.readBit() << "\n";
	br.f.close();
  return 0;
}