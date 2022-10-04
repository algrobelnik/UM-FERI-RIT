#include <cstring>
#include <fcntl.h>
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
    map<char, int>::iterator it;
    if (type == "read") {
      int fd, ret;
      char buf[bSize];
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
      }
    } else if (type == "fread") {
      int ret;
      char buf[bSize];
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
      }
    } else if (type == "mmap") {
      int fd;
      char *addr;
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
          munmap(addr, st.st_size);
          offset += st.st_size;
        }
        close(fd);
      }
    } else {
      cout << "WRONG USAGE. Type histChar --help for additional inforamtions."
           << endl;
      return 1;
    }
    for (it = hist.begin(); it != hist.end(); ++it) {
      cout << it->first << " " << it->second << " | ";
    }
  } catch (const char *err) {
    cout << err << endl;
  }
  return 0;
}
