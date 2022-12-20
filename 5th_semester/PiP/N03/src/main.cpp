#include "sync_queue.h"
#include <algorithm>
#include <array>
#include <climits>
#include <cmath>
#include <condition_variable>
#include <functional>
#include <iostream>
#include <mutex>
#include <queue>
#include <random>
#include <sstream>
#include <thread>
#include <vector>

struct Seq {
  static unsigned int seq_index;
  unsigned int index;
  int *sequence;
  Seq() {}
  Seq(int *sequence) {
    this->sequence = sequence;
    // std::cout << seq_index << std::endl;
    this->index = seq_index;
    seq_index++;
  }
};
unsigned int Seq::seq_index = -1;

/*struct Result {
  Seq parent;
  unsigned int psl;
  double mf;
  Result() {}
  Result(Seq *parent, unsigned int psl, double mf)
      : parent(*parent), psl(psl), mf(mf) {}
};*/

const int count_threads = 128; // number of threads
unsigned int nfes = 0;
SyncQueue<Seq> queue;
std::mutex mtx;
std::vector<unsigned int> psls;
std::vector<double> mfs;

void printWrongUsage() {
  std::cout
      << "Usage: main.x -L=<unsign int> -type=[PSL|MF] -seed=<unsigned int> "
         "-nfesLmt=<unsigned int>"
      << std::endl;
}

int *generateSequence(unsigned int size, unsigned int seed) {
  int *arr = new int[size];
  int values[2] = {-1, 1};
  std::mt19937 mt(seed);
  std::uniform_int_distribution<int> dist(0,
                                          (sizeof(values) / sizeof(int)) - 1);
  for (unsigned int i = 0; i < size; i++) {
    arr[i] = values[dist(mt)];
  }
  return arr;
}

std::string convertBinaryToHexadecimal(int *arr, unsigned int size) {
  // std::cout << "HERE" << std::endl;
  int n = ceil((size - 1) / 4) + 1;
  // std::cout << size << std::endl;
  std::string res = "0x";
  for (unsigned int i = n; i > 0; i--) {
    // std::cout << size - i * 4 << std::endl;
    int sum = (*(arr + size - i * 4 + 3) != 1 ? 0 : 1) +
              (*(arr + size - i * 4 + 2) != 1 ? 0 : 1) * 2 +
              (*(arr + size - i * 4 + 1) != 1 ? 0 : 1) * 4 +
              (*(arr + size - i * 4) != 1 ? 0 : 1) * 8;
    res += (sum > 9 ? (char)(sum + 65 - 10) : std::to_string(sum)[0]);
    // std::cout << *(arr + i * 4) << " ";
    // std::cout << *(arr + i * 4 + 1) << " ";
    // std::cout << *(arr + i * 4 + 2) << " ";
    // std::cout << *(arr + i * 4 + 3) << " " << std::endl;
  }
  return res;
}

int C(int *sequence, unsigned int k, unsigned int L) {
  int sum = 0;
  for (unsigned int i = 0; i <= L - k - 1; i++) {
    sum += sequence[i] * sequence[i + k];
  }
  return sum;
}

unsigned int PSL(int *sequence, unsigned int L, unsigned int nfesLmt) {
  int mVal = INT_MIN;
  for (unsigned int k = 1; k < L; k++) {
    if (nfes > nfesLmt) {
      return INT_MIN;
    }
    mVal = std::max(std::abs(C(sequence, k, L)), mVal);
    mtx.lock();
    nfes++;
    mtx.unlock();
  }
  return mVal;
}

double MF(int *sequence, unsigned int L, unsigned int nfesLmt) {
  int energy = 0;
  for (unsigned int k = 1; k < L; k++) {
    if (nfes > nfesLmt) {
      return 0;
    }
    int ck = C(sequence, k, L);
    energy += ck * ck;
    mtx.lock();
    nfes++;
    mtx.unlock();
  }
  return (L * L) / (2.0 * energy);
}

void producer(Seq sequence, unsigned int L) {
  int *seq = new int[L];
  for (unsigned int i = 0; i < L; i++) {
    seq[i] = sequence.sequence[i];
  }
  queue.insert(Seq(seq));
  for (unsigned int i = 0; i < L; i++) {
    int *seq = new int[L];
    for (unsigned int i = 0; i < L; i++) {
      seq[i] = sequence.sequence[i];
    }
    seq[i] *= -1;
    queue.insert(Seq(seq));
  }
  queue.switchFinished();
}

void consumer(unsigned int L, std::string type, unsigned int nfesLmt) {
  while (!queue.queue.empty()) {
    Seq parent = queue.read();
    int *seq = parent.sequence;
    if (type == "PSL") {
      int psl = PSL(seq, L, nfesLmt);
      psls[parent.index] = psl;
    } else if (type == "MF") {
      double mf = MF(seq, L, nfesLmt);
      mfs[parent.index] = mf;
    }
  }
}

int main(int argc, char **argv) {
  if (argc == 1) {
    std::cout << "Wrong number of given arguments" << std::endl;
    printWrongUsage();
    return 1;
  }
  unsigned int seed = 0;
  unsigned int L = 0;
  std::string type = "";
  unsigned int nfesLmt = 0;
  for (int i = 1; i < argc; i++) {
    std::string arg(argv[i]);
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
    std::cout << (seed != 0 ? "FOUND: seed" : "NOT FOUND: seed") << std::endl
              << (L != 0 ? "FOUND: L" : "NOT FOUND: L") << std::endl
              << ((type == "MF" || type == "PSL") ? "FOUND: type"
                                                  : "NOT FOUND: type")
              << std::endl
              << (nfesLmt != 0 ? "FOUND: nfesLmt" : "NOT FOUND: nfesLmt")
              << std::endl;
    printWrongUsage();
    return -1;
  }
  std::chrono::time_point<std::chrono::system_clock> start, end;
  int *sequence = generateSequence(L, seed);
  psls.resize(L + 1);
  mfs.resize(L + 1);
  // create a producer thread
  start = std::chrono::system_clock::now();
  std::thread prod(std::bind(producer, Seq(sequence), L));
  prod.join();                        // wait for the producer thread to finish
  std::vector<std::thread> consumers; // create a consumers vector
  for (int i = 0; i < count_threads; i++) {
    consumers.emplace_back(
        std::bind(consumer, L, type, nfesLmt)); // create a consumer thread
  }
  // wait for the consumer threads to finish
  for (auto &consumer : consumers) {
    consumer.join();
  }
  end = std::chrono::system_clock::now();
  std::chrono::duration<double> elapsed_seconds;
  elapsed_seconds = end - start;
  unsigned int index;
  /*while (!results.queue.empty()) {
    Result res = results.read();
    if (res.psl == 0 && res.mf == 0) {
      continue;
    }
    // std::cout << res.psl << " " << res.mf << " " << res.parent.index
    //           << std::endl;
    psls_vec[res.parent.index] = res.psl;
    mfs_vec[res.parent.index] = res.mf;
  }*/

  /*for (auto el : psls) {
    std::cout << el << std::endl;
  }*/

  if (type == "MF") {
    /*for (auto el : psls_vec) {
      if (el < psls[index]) index = std::cout << el << std::endl;
    }*/
    index = std::distance(std::begin(mfs),
                          std::min_element(std::begin(mfs), std::end(mfs)));
  } else {
    index = std::distance(std::begin(psls),
                          std::min_element(std::begin(psls), std::end(psls)));
  }
  //std::cout << index << std::endl;
  sequence[index] *= -1;
  //std::cout << convertBinaryToHexadecimal(sequence, L) << std::endl;
  std::cout << "L: " << L << std::endl
            << "nfesLmt: " << nfesLmt << std::endl
            << "seed: " << seed << std::endl
            << "nfes: " << nfes << std::endl
            << "runtime: " << elapsed_seconds.count() * 1000 * 1000 << "qs"
            << std::endl
            << "speed: " << nfes / elapsed_seconds.count() * 1000 * 1000
            << std::endl
            << "sequence: " << convertBinaryToHexadecimal(sequence, L)
            << std::endl
            << "MF: " << mfs[index] << std::endl
            << "PSL: " << psls[index] << std::endl;
  return 0;
}
