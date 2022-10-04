// basic file operations
#include <fstream>
#include <iostream>
#include <iterator>
#include <map>
#include <regex>
#include <string>
#include <vector>
using namespace std;

void displayIP(vector<int> arr, string text, int index) {
  cout << text;
  for (int i = 0; i < 4; i++) {
    cout << (i != 0 ? "." : "") << arr[i + index * 4];
  }
  cout << endl;
}

void checkMask(vector<int> arr, char const *text, int index) {
  int nonFull = 0;
  for (int i = 0; i < 4; i++) {
    if (arr[i + index * 4] > 255) {
      throw text;
    }
    if (arr[i + index * 4] != 0 && nonFull != 0) {
      throw text;
    }
    if (arr[i + index * 4] != 255) {
      nonFull = i;
    }
  }
}

void checkIP(vector<int> arr, char const *text, int index) {
  for (int i = 0; i < 4; i++) {
    if (arr[i + index * 4] > 254)
      throw text;
    if (arr[i + index * 4] == 0)
      throw text;
  }
}

void displayMap(map<string, int> arr) {
  for (map<string, int>::iterator itr = arr.begin(); itr != arr.end(); ++itr) {
    cout << itr->first << '\t' << itr->second << endl;
  }
}

int main(int argc, char **argv) {
  if (argc != 3) {
    cout << "File should be called with 2 arguments: ./executable_file "
            "log_file_name mask";
    return 1;
  }
  vector<int> masks;
  vector<int> octets;
  string s;
  ifstream file;
  map<string, int> ips;
  map<string, int> wrongAuth;
  file.open(argv[1]);
  if (!file.is_open()) {
    cout << "Unable to open file";
    return 1;
  }
  stringstream ss(argv[2]);
  string tmp;
  while (getline(ss, tmp, '.')) {
    masks.push_back(stoi(tmp));
  }
  while (getline(file, s)) {
    regex exp("\\d+\\.\\d+\\.\\d+\\.\\d+");
    smatch m;
    string::const_iterator searchStart(s.cbegin());
    while (regex_search(searchStart, s.cend(), m, exp)) {
      searchStart = m.suffix().first;
      if (ips.find(m[0]) != ips.end()) {
        ips[m[0]]++;
      } else {
        ips.insert(pair<string, int>(m[0], 1));
      }
      stringstream ss2(m[0]);
      while (getline(ss2, tmp, '.')) {
        octets.push_back(stoi(tmp));
      }
      if (octets.size() <= 4) {
        continue;
      }
      try {
        displayIP(masks, "Mask: ", 0);
        displayIP(octets, "First IP: ", 0);
        displayIP(octets, "Second IP: ", 1);
        checkMask(masks, "Mask error", 0);
        checkIP(octets, "First IP error", 0);
        checkIP(octets, "Second IP error", 1);
        for (int i = 0; i < 4; i++) {
          if (masks[i] == 255) {
            if (octets[i] != octets[i + 4]) {
              throw "Not in same subnetwork";
            }
          } else if (masks[i] != 0) {
            int diff = 256 - masks[i];
            int magic = octets[i] / diff;
            int bc = magic * diff + diff - 1;
            cout << magic * diff << " < " << octets[i + 4] << " < " << bc
                 << endl;
            if (!(magic * diff > octets[i + 4] || octets[i + 4] > bc))
              cout << "IP's are in same subnetwork for given mask" << endl;
          }
        }
      } catch (char const *err) {
        cout << err << endl;
      }
      cout << endl;
    }
    octets.clear();
    smatch sm;
    regex expr("r\\s([\\w\\.]*)\\sfrom\\s([\\w\\.]*)\\sport\\s([\\w\\.]*)");
    string::const_iterator sStart(s.cbegin());
    while (regex_search(sStart, s.cend(), sm, expr)) {
      sStart = sm.suffix().first;
      cout << "User: " << sm[1] << ", IP: " << sm[2] << ", port: " << sm[3]
           << endl;
      string ins = sm[1].str() + " " + sm[2].str() + " " + sm[3].str();
      if (wrongAuth.find(ins) != wrongAuth.end()) {
        wrongAuth[ins]++;
      } else {
        wrongAuth.insert(pair<string, int>(ins, 1));
      }
    }
  }
  cout << endl;
  file.close();
  displayMap(ips);
  cout << "------------------------------------" << endl;
  displayMap(wrongAuth);
  return 0;
}
