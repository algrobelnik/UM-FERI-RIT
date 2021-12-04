#include <iostream>
#include <string>

using namespace std;

void hexToBin(string &text) {
  string out = "";
  for (long unsigned int i = 0; i < text.size(); i++) {
    char c = text[i];
    if ((c < '0' || c > '9') && (c < 'A' || c > 'F')) {
      cerr << "Character " << c << " was out of valid range";
      exit(EXIT_FAILURE);
    }
    if (c >= 'A') {
      c -= 'A' - 10;
    } else {
      c -= '0';
    }
    out += c & 0x8 ? "1" : "0";
    out += c & 0x4 ? "1" : "0";
    out += c & 0x2 ? "1" : "0";
    out += c & 0x1 ? "1" : "0";
  }
  text = out;
}

void binToHex(string &text) {
  string out = "";
  int total = 0;
  // if (text.size() % 4 != 0){
  //  cerr << "Number of binary character error";
  //  exit(EXIT_FAILURE);
  //}
  for (long unsigned int i = 0; i < text.size(); i += 4) {
    total += text[i] == '1' ? 8 : 0;
    total += text[i + 1] == '1' ? 4 : 0;
    total += text[i + 2] == '1' ? 2 : 0;
    total += text[i + 3] == '1' ? 1 : 0;
    char c = '7';
    if (total < 10) {
      c = '0';
    }
    out += (char)(total + c);
    total = 0;
  }
  text = out;
}

void minBinaryLen(string &text, int step) {
  int cuts = 0;
  if (step == 1) {
    for (long unsigned int i = 0; i < text.size() + cuts; i++) {
      if (text[i - cuts] == '0') {
        text.erase(0, 1);
        cuts++;
      } else {
        return;
      }
    }
  } else {
    text.insert(0, string("0000", 4 - text.size() % 4));
    for (long unsigned int i = 0; i < text.size() + cuts; i += step) {
      string compare = "";
      for (int j = 0; j < step; j++) {
        if (text[(i - cuts) * 4 + j] != '0')
          compare += text[i + j];
      }
      if (compare == "") {
        text.erase(0, step);
        cuts++;
      } else {
        return;
      }
    }
  }
}

string encodeUTF8(string text) {
  hexToBin(text);
  minBinaryLen(text, 1);
  if (text.size() < 8) {
    text.insert(0, string("000000000000000000000000000000", 8 - text.size()));
  } else if (text.size() < 12) {
    text.insert(0, string("000000000000000000000000000000", 11 - text.size()));
    text.insert(0, "110");
    text.insert(8, "10");
  } else if (text.size() < 17) {
    text.insert(0, string("000000000000000000000000000000", 16 - text.size()));
    text.insert(0, "1110");
    text.insert(8, "10");
    text.insert(16, "10");
  } else if (text.size() < 22) {
    text.insert(0, string("000000000000000000000000000000", 21 - text.size()));
    text.insert(0, "11110");
    text.insert(8, "10");
    text.insert(16, "10");
    text.insert(24, "10");
  } else {
    cerr << "Couldn't encode character";
    exit(EXIT_FAILURE);
  }
  binToHex(text);
  return text;
}

string decodeUTF8(string text) {
  if (text == "FE" || text == "FF") {
    cerr << "Couldn't decode character";
    exit(EXIT_FAILURE);
  }
  hexToBin(text);
  if (text.size() > 7 && text.size() < 17) {
    text.erase(8, 2);
    text.erase(0, 3);
    if (text.substr(0, 5) == "00000" || text.substr(5, 6) == "000000") {
      cerr << "Couldn't decode character";
      exit(EXIT_FAILURE);
    }
    minBinaryLen(text, 4);
  } else if (text.size() < 25) {
    text.erase(16, 2);
    text.erase(8, 2);
    text.erase(0, 4);
    if (text.substr(0, 4) == "0000" || text.substr(4, 6) == "000000" ||
        text.substr(11, 6) == "000000") {
      cerr << "Couldn't decode character";
      exit(EXIT_FAILURE);
    }
    minBinaryLen(text, 4);
  } else if (text.size() < 33) {
    text.erase(24, 2);
    text.erase(16, 2);
    text.erase(8, 2);
    text.erase(0, 5);
    if (text.substr(0, 3) == "000" || text.substr(3, 6) == "000000" ||
        text.substr(10, 6) == "000000" || text.substr(17, 6) == "000000") {
      cerr << "Couldn't decode character";
      exit(EXIT_FAILURE);
    }
    minBinaryLen(text, 4);
  } else {
    cerr << "Couldn't decode character";
    exit(EXIT_FAILURE);
  }
  binToHex(text);
  return text;
}

int main() {
  string inputStr, resStr;
  cout << "Insert number for encoding: ";
  cin >> inputStr;
  resStr = encodeUTF8(inputStr);
  cout << "Result of encoding: " << resStr;
  cout << endl;
  cout << "Insert number for decoding: ";
  cin >> inputStr;
  resStr = decodeUTF8(inputStr);
  cout << "Result of decoding: " << resStr << endl;
  return 0;
}
