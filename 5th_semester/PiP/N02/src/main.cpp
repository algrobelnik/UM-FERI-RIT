#include <chrono>
#include <cmath>
#include <iostream>
#include <random>
#include <thread>

using namespace std;
using namespace std::chrono;

const int count_threads = 12;

void printWrongUsage() {
  cout << "Usage: main.x -L=<unsign int> -type=[PSL|MF] -seed=<unsigned int> "
          "-nfesLmt=<unsigned int>"
       << endl;
}

int random_number(unsigned int seed) {
  random_device r;
  default_random_engine eng{r()};
  uniform_real_distribution<double> dist(-1, 1);
  return (dist(eng) < 0 ? -1 : 1);
}

int *generateSequence(unsigned int size, unsigned int seed) {
  int *arr = new int[size];
  for (unsigned int i = 0; i < size; i++) {
    arr[i] = random_number(seed);
  }
  return arr;
}

char *convertDecimalToHexadecimal(int *arr, unsigned int size) {
  int n = ceil(size / 4);
  char *res = new char[n];
  for (unsigned int i = size-1; i >= 0; i--) {
    cout << *(arr + i) << endl;
  }
  return res;
}

int main(int argc, char **argv) {
  if (argc == 1) {
    cout << "Wrong number of given arguments" << endl;
    printWrongUsage();
    return 1;
  }
  unsigned int seed = 0;
  unsigned int L = 0;
  string type = "";
  unsigned int nfesLmt = 0;
  for (int i = 1; i < argc; i++) {
    string arg(argv[i]);
    int pos = arg.find("=");
    if (pos == -1 || arg == "-h" || arg == "-?") {
      printWrongUsage();
      return 1;
    }
    if (arg.substr(0, pos) == "-L" || arg.substr(0, pos) == "L") {
      L = stoi(arg.substr(pos + 1));
    } else if (arg.substr(0, pos) == "-type" || arg.substr(0, pos) == "type") {
      type = arg.substr(pos + 1);
    } else if (arg.substr(0, pos) == "-seed" || arg.substr(0, pos) == "seed") {
      seed = stoi(arg.substr(pos + 1));
    } else if (arg.substr(0, pos) == "-nfesLmt" ||
               arg.substr(0, pos) == "nfesLmt") {
      nfesLmt = stoi(arg.substr(pos + 1));
    }
  }
  if (seed == 0 || L == 0 || type == "" || nfesLmt == 0) {
    cout << (seed != 0 ? "FOUND: seed" : "NOT FOUND: seed") << endl;
    cout << (L != 0 ? "FOUND: L" : "NOT FOUND: L") << endl;
    cout << (type != "" ? "FOUND: type" : "NOT FOUND: type") << endl;
    cout << (nfesLmt != 0 ? "FOUND: nfesLmt" : "NOT FOUND: nfesLmt") << endl;
    printWrongUsage();
    return -1;
  }
  srand(seed);
  time_point<system_clock> start, end;

  // cout << "computing program..." << endl;
  start = system_clock::now();
  int *sequence = generateSequence(L, seed);
  char *hexadecimal = convertDecimalToHexadecimal(sequence, L);
  cout << hexadecimal << endl;
  end = system_clock::now();
  duration<double> elapsed_seconds;
  elapsed_seconds = end - start;
  cout << "Elapsed time: " << elapsed_seconds.count() * 1000 * 1000 << "μs"
       << endl;
  /*cout << "Operations per second: "
       << size * (method != 2 ? 1 : size) / elapsed_seconds.count() << endl;
  cout << "Number of operations: " << size * (method != 2 ? 1 : size) <<
  endl;*/
  delete[] sequence;
  delete[] hexadecimal;
  return 0;
}
