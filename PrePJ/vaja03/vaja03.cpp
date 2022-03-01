#include <fstream>
#include <iostream>
#include <regex>
#include <string>
using namespace std;

int main(int argc, char **argv) {
  if (argc != 2 && argc != 3) {
    cout << "File should be called with 1 or 2 argument: ./executable_file "
            "<file_name> [<outfile_name>]"
         << endl;
    return 1;
  }
  string s;
  ifstream fileI;
  ofstream fileO;
  fileI.open(argv[1]);
  if (!fileI.is_open()) {
    cout << "Unable to open file";
    return 1;
  }
  if (argc == 2) {
    string tmp;
    while (getline(fileI, s)) {
      smatch m;
      regex expr("(SI\\d\\d-)(\\d+-\\d+-\\d+)(-\\d+)");
      cout << regex_replace(s, expr, "$1XXX-XXX-XXX$3") << endl;
    }
  } else {
    fileO.open(argv[2]);
    if (!fileO.is_open()) {
      cout << "Unable to open file";
      return 1;
    }
    string tmp;
    while (getline(fileI, s)) {
      smatch m;
      regex expr("(SI\\d\\d-)(\\d+-\\d+-\\d+)(-\\d+)");
      fileO << regex_replace(s, expr, "$1XXX-XXX-XXX$3") << endl;
    }
    fileO.close();
  }
  fileI.close();
  return 0;
}
