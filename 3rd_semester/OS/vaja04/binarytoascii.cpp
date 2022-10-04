#include <cstring>
#include <fstream>
#include <iostream>
#include <unistd.h>

using namespace std;

void printHelp() {
  cout << "binarytoascii version: binarytoascii/0.0.1" << endl
       << "Command for converting binary data to ascii signs" << endl
       << endl
       << "Usage: binarytoascii [options]" << endl
       << "Options:" << endl
       << "\t-?,-h,--help   : show this help" << endl
       << "\t-i <file>      : binary input from specified file" << endl
       << "\t-o <file>      : binary output to specified file" << endl
       << "\t-I <number>     : binary input from specified file descriptor "
          "number"
       << endl
       << "\t-O <number>     : binary output to specified file descriptor "
          "number"
       << endl;
}

int main(int argc, char **argv) {
  try {
    bool ocheck = false;
    bool icheck = false;
    int fdO = 1;
    int fdI = 0;
    string file_input = "unknown####";
    string file_output = "unknown####";
    for (int i = 1; i < argc; i++) {
      if (strcmp(argv[i], "--help") == 0 || strcmp(argv[i], "-h") == 0 ||
          strcmp(argv[i], "-?") == 0) {
        printHelp();
        break;
      }
      bool arr[5] = {strcmp(argv[i + 1], "") != 0, strcmp(argv[i], "-o") == 0,
                     strcmp(argv[i], "-O") == 0, strcmp(argv[i], "-i") == 0,
                     strcmp(argv[i], "-I") == 0};
      if (i + 1 != argc && arr[0] && argv[i + 1][0] != '-') {
        if (!ocheck && (arr[1] || arr[2])) {
          if (arr[1]) {
            file_output = argv[i + 1];
          } else {
            fdO = atoi(argv[i + 1]);
          }
          ocheck = true;
          i++;
        }
        if (!icheck && (arr[3] || arr[4])) {
          if (arr[3]) {
            file_input = argv[i + 1];
          } else {
            fdI = atoi(argv[i + 1]);
          }
          icheck = true;
          i++;
        }
      } else {
        cout << "WRONG USAGE. Type binarytoascii --help for additional "
                "inforamtions."
             << endl;
        break;
      }
    }
    ifstream input;
    ofstream output;
    char c;
    if (file_input != "unknown####" && file_output != "unknown####") {
      input.open(file_input);
      output.open(file_output, fstream::in | fstream::out | fstream::app);
      if (input.is_open() && output.is_open()) {
        while (input) {
          c = input.get();
          if ((int)c != -1) {
            output << (int)c << " ";
          }
        }
        input.close();
        output.close();
      } else {
        cout << "Input: " << (input.is_open() ? "open" : "error")
             << " Output: " << (output.is_open() ? "open" : "error");
      }
      cout << endl;
    } else if (file_output != "unknown####") {
      output.open(file_output, fstream::in | fstream::out | fstream::app);
      if (output.is_open()) {
        while (read(fdI, &c, 1)) {
          output << (int)c << " ";
        }
      } else {
        cout << " Output: " << (output.is_open() ? "open" : "error");
      }
    } else if (file_input != "unknown####") {
      input.open(file_input);
      if (input.is_open()) {
        string str = "";
        while (input) {
          c = input.get();
          int num = (int)c;
          if (num != -1) {
            str += to_string(num) + " ";
          }
        }
        write(fdO, str.c_str(), str.size());
        input.close();
      } else {
        cout << "Input: " << (input.is_open() ? "open" : "error");
      }
    } else {
      string str = "";
      while (read(fdI, &c, 1)) {
        int num = (int)c;
        str += to_string(num) + " ";
      }
      write(fdO, str.c_str(), str.size());
    }
  } catch (const char *err) {
    cout << err << endl;
  }
  return 0;
}
