#include <iostream>
#include <omp.h>
// Predpostavimo , da je velikost vrstice predpomnilnika L1 64 bajtov
#define PAD 8
#define NUM_THREADS 2

int main() {
  const int num_steps = 100000;
  // Vsaka vsota se nahaja v svoji vrstici predponilnika
  double pi = 0.0;
  double sum[NUM_THREADS][PAD];
  double step = 1.0 / num_steps;
  omp_set_num_threads(NUM_THREADS);
#pragma omp parallel
  {
    int id = omp_get_thread_num();
    double x;
    sum[id][0] = 0.0;
    for (int i = id; i < num_steps; i = i + NUM_THREADS) {
      x = (i + 0.5) * step;
      sum[id][0] += 4.0 / (1.0 + x * x);
    }
  }
  for (int i = 0; i < NUM_THREADS; i++) {
    pi += sum[i][0] * step;
  }
  std::cout << "PI:" << pi << std::endl;
  return 0;
}
