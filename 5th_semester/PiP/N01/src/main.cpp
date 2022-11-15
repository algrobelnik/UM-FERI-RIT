#include <array>
#include <chrono>
#include <iostream>
#include <thread>
#include <vector>

using namespace std;
using namespace std::chrono;

typedef vector<double> dm1;
typedef vector<dm1> dm2;
// typedef vector<dm2> dm3;

const int count_threads = 12;

dm2 mat;
dm1 vec;
dm2 out_mat;
dm1 out_vec;

int rand_gen(int min, int max) {
  int range = max - min++;
  return rand() % range + min;
}

void fill_matrix(int size) {
  for (int j = 0; j < size; j++) {
    dm1 vec1;
    for (int k = 0; k < size; k++) {
      vec1.push_back(rand_gen(0, 10));
    }
    mat.push_back(vec1);
  }
}

void fill_vector(int size) {
  for (int i = 0; i < size; i++) {
    vec.push_back(rand_gen(0, 10));
  }
}

void fill_vector_zeros(int size) {
  for (int i = 0; i < size; i++) {
    out_vec.push_back(0);
  }
}

void fill_matrix_zeros(int size) {
  for (int i = 0; i < size; i++) {
    dm1 vec1;
    for (int j = 0; j < size; j++) {
      vec1.push_back(0);
    }
    out_mat.push_back(vec1);
  }
}

void print_matrix() {
  for (int i = 0; i < mat.size(); i++) {
    for (int j = 0; j < mat[i].size(); j++) {
      cout << mat[i][j] << " ";
    }
    cout << endl;
  }
  cout << endl;
}

void print_matrix_out() {
  for (int i = 0; i < out_mat.size(); i++) {
    for (int j = 0; j < out_mat[i].size(); j++) {
      cout << out_mat[i][j] << " ";
    }
    cout << endl;
  }
  cout << endl;
}

void print_vector() {
  for (int i = 0; i < vec.size(); i++) {
    cout << vec[i] << " ";
  }
  cout << endl;
}

void print_vector_out() {
  for (int i = 0; i < out_vec.size(); i++) {
    cout << out_vec[i] << " ";
  }
  cout << endl;
}

void add_vector(int s, int e) {
  for (int j = 0; j < 100; j++) {
    for (int i = s; i < e; i++) {
      out_vec[i] = vec[i] + vec[i];
    }
  }
}

void dot_product_vector(int s, int e) {
  for (int i = s; i < e; i++) {
    out_vec[i] = vec[i] * vec[i];
  }
}

void product_matrix(int s, int e) {
  for (int i = s; i < e; i++) {
    for (int j = 0; j < mat[i].size(); j++) {
      for (int k = 0; k < mat.size(); k++) {
        out_mat[i][j] += mat[i][k] * mat[k][j];
      }
    }
  }
}

int split(int a, int b) {
  int pivot = vec[a];
  int li = a;
  int ri = b;
  while (li < ri) {
    while (vec[li] <= pivot && li < b) {
      li++;
    }
    while (vec[ri] >= pivot && ri > a) {
      ri--;
    }
    if (li < ri) {
      swap(vec[li], vec[ri]);
    }
  }
  swap(vec[a], vec[ri]);
  return ri;
}

void quicksort(int a, int b) {
  if (a < b) {
    int splitter = split(a, b);
    quicksort(a, splitter - 1);
    quicksort(splitter + 1, b);
  }
}

int main(int argc, char **argv) {
  if (argc != 4) {
    cout << "Wrong number of given arguments" << endl;
    return 1;
  }
  auto size = stoi(argv[1]);
  auto seed = stoi(argv[2]);
  auto method = stoi(argv[3]);
  srand(seed);
  time_point<system_clock> start, end;

  cout << "computing program.." << endl;
  switch (method) {
  case 0: {
    fill_vector(size);
    fill_vector_zeros(size);
    array<thread, count_threads> threads;
    int offset = size / count_threads;
    int thread_size = sizeof(threads) / sizeof(thread);
    start = system_clock::now();
    for (int i = 0; i < thread_size; i++) {
      if (i == 0) {
        threads[i] = thread(add_vector, 0, offset);
      } else if (i == thread_size - 1) {
        threads[i] = thread(add_vector, i * offset + 1, size);
      } else {
        threads[i] = thread(add_vector, i * offset + 1, (i + 1) * offset);
      }
      // threads[i].join();
    }
    for (auto &t : threads) {
      t.join();
    }
    break;
  }
  case 1: {
    fill_vector(size);
    fill_vector_zeros(size);
    array<thread, count_threads> threads;
    int offset = size / count_threads;
    int thread_size = sizeof(threads) / sizeof(thread);
    start = system_clock::now();
    for (int i = 0; i < thread_size; i++) {
      if (i == 0) {
        threads[i] = thread(dot_product_vector, 0, offset);
      } else if (i == thread_size - 1) {
        threads[i] = thread(dot_product_vector, i * offset + 1, size);
      } else {
        threads[i] =
            thread(dot_product_vector, i * offset + 1, (i + 1) * offset);
      }
      //threads[i].join();
    }
    for (auto &t : threads) {
      t.join();
    }
    break;
  }
  case 2: {
    fill_matrix(size);
    fill_matrix_zeros(size);
    array<thread, count_threads> threads;
    int offset = size / count_threads;
    int thread_size = sizeof(threads) / sizeof(thread);
    start = system_clock::now();
    for (int i = 0; i < thread_size; i++) {
      if (i == 0) {
        threads[i] = thread(product_matrix, 0, offset);
      } else if (i == thread_size - 1) {
        threads[i] = thread(product_matrix, i * offset + 1, size);
      } else {
        threads[i] = thread(product_matrix, i * offset + 1, (i + 1) * offset);
      }
      //threads[i].join();
    }
    for (auto &t : threads) {
      t.join();
    }
    break;
  }
  case 3: {
    fill_vector(size);
    array<thread, count_threads> threads;
    int offset = size / count_threads;
    int thread_size = sizeof(threads) / sizeof(thread);
    start = system_clock::now();
    for (int i = 0; i < thread_size; i++) {
      if (i == 0) {
        threads[i] = thread(quicksort, 0, offset);
      } else if (i == thread_size - 1) {
        threads[i] = thread(quicksort, i * offset + 1, size);
      } else {
        threads[i] = thread(quicksort, i * offset + 1, (i + 1) * offset);
      }
      //threads[i].join();
    }
    for (auto &t : threads) {
      t.join();
    }
    quicksort(0, vec.size() - 1);
    break;
  }
  }
  end = system_clock::now();
  //print_vector();
  print_vector_out();
  // print_vector(ret_dm2);
  //print_matrix();
  //print_matrix_out();
  cout << "method used: "
       << (method == 0   ? "add"
           : method == 1 ? "dot"
           : method == 2 ? "mat"
                         : "sort")
       << endl;

  duration<double> elapsed_seconds;
  elapsed_seconds = end - start;
  cout << "Elapsed time: " << elapsed_seconds.count() * 1000 * 1000 << "μs"
       << endl;
  cout << "Operations per second: "
       << size * (method != 2 ? 1 : size) / elapsed_seconds.count() << endl;
  cout << "Number of operations: " << size * (method != 2 ? 1 : size) << endl;
  return 0;
}
