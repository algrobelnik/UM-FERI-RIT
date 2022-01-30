#include <cstring>
#include <fcntl.h>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <iterator>
#include <map>
#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

using namespace std;

void printHelp() {
  cout << "histChar version: histChar/0.0.1" << endl
       << "Command for counting ascii characters in file" << endl
       << endl
       << "Usage: histChar [options] input_file" << endl
       << "Options:" << endl
       << "\t-?,-h,--help   : show this help" << endl
       << "\t-t <type>      : supported types are read, fread, mmap" << endl
       << "\t-b <number>    : size of buffer in bytes" << endl
       << endl;
}

int main(int argc, char **argv) {
  try {
    namespace fs = filesystem;
    string type;
    int bSize;
    map<char, int> hist;
    for (int i = 1; i < argc - 1; i++) {
      if (strcmp(argv[i], "--help") == 0 || strcmp(argv[i], "-h") == 0 ||
          strcmp(argv[i], "-?") == 0) {
        printHelp();
        break;
      }
      if (i + 1 != argc && strcmp(argv[i + 1], "") != 0 &&
          argv[i + 1][0] != '-') {
        if (strcmp(argv[i], "-t") == 0) {
          type = argv[i + 1];
          i++;
        }
        if (strcmp(argv[i], "-b") == 0) {
          bSize = atoi(argv[i + 1]);
          i++;
        }
      } else {
        cout << "WRONG USAGE. Type histChar --help for additional inforamtions."
             << endl;
        return 1;
      }
    }
    if (type == "read") {
      int fd, ret;
      char buf[bSize];
      map<char, int>::iterator it;
      if ((fd = open(argv[argc - 1], O_RDONLY)) < 0) {
        cout << "WRONG FILE. Type histChar --help for additional inforamtions.";
        return 1;
      } else {
        while ((ret = read(fd, buf, bSize)) > 0) {
          buf[ret] = 0x00;
          for (int i = 0; i < ret; i++) {
            it = hist.find(buf[i]);
            if (it == hist.end()) {
              hist.insert(pair<char, int>(buf[i], 1));
            } else {
              it->second++;
            }
          }
        }
        close(fd);
        for (it = hist.begin(); it != hist.end(); ++it) {
          cout << it->first << " " << it->second << endl;
        }
      }
    } else if (type == "fread") {
      int ret;
      char buf[bSize];
      map<char, int>::iterator it;
      ifstream file;
      file.open(argv[argc - 1]);
      if (!file.is_open()) {
        cout << "FILE ERROR. Type histChar --help for additional inforamtions.";
        return 1;
      } else {
        while (file.read(buf, bSize)) {
          buf[file.gcount()] = 0x00;
          for (int i = 0; i < file.gcount(); i++) {
            it = hist.find(buf[i]);
            if (it == hist.end()) {
              hist.insert(pair<char, int>(buf[i], 1));
            } else {
              it->second++;
            }
          }
        }
        for (int i = 0; i < file.gcount(); i++) {
          it = hist.find(buf[i]);
          if (it == hist.end()) {
            hist.insert(pair<char, int>(buf[i], 1));
          } else {
            it->second++;
          }
        }
        file.close();
        for (it = hist.begin(); it != hist.end(); ++it) {
          cout << it->first << " " << it->second << endl;
        }
      }
    } else if (type == "mmap") {
      int fd;
      char *addr;
      map<char, int>::iterator it;
      if ((fd = open(argv[argc - 1], O_RDONLY)) < 0) {
        cout << "FILE ERROR. Type histChar --help for additional inforamtions.";
        return 1;
      } else {
        int offset = 0;
        struct stat st;
        stat(argv[argc - 1], &st);
        while ((addr = (char *)mmap(0, st.st_size, PROT_READ, MAP_PRIVATE, fd,
                                    offset)) != MAP_FAILED) {
          for (int i = 0; i < st.st_size; i++) {
            it = hist.find(addr[i]);
            if (it == hist.end()) {
              hist.insert(pair<char, int>(addr[i], 1));
            } else {
              it->second++;
            }
          }
          munmap(addr, bSize);
          offset += bSize;
        }
        close(fd);
        for (it = hist.begin(); it != hist.end(); ++it) {
          cout << it->first << " " << it->second << endl;
        }
      }
    } else {
      cout << "WRONG USAGE. Type histChar --help for additional inforamtions."
           << endl;
      return 1;
    }
  } catch (const char *err) {
    cout << err << endl;
  }
  /*ifstream input;
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
  }*/
  return 0;
}
