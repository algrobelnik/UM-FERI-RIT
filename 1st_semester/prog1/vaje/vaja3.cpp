#include <iostream>
#include <math.h>
using namespace std;

void vpis(int pon, double arH[], double arT[], double arD[]) {
  for (int i = 0; i < pon; i++) {
    cout << "Insert hitrost za tekmovalca " << i + 1 << ": ";
    cin >> arH[i];
    cout << "Insert trajanje za tekmovalca " << i + 1 << ": ";
    cin >> arT[i];
    cout << "Insert dolzinaPoti za tekmovalca " << i + 1 << ": ";
    cin >> arD[i];
  }
}

double *izracun(double arH[], double arT[], double arD[]) {
  static double r[5];
  for (int i = 0; i < 5; i++) {
    cout << arH[i] << "m/s " << arT[i] << "s " << arD[i] << "m" << endl;
    r[i] = arD[i] - arH[i] * arT[i];
    cout << "Rezultat: " << r[i] << "m" << endl;
  }
  return r;
}

void izpis(double arr[], int N) {
  for (int i = 0; i < 5; i++) {
    cout << "Tekmovalec " << i + 1 << " (" << arr[i] << "%)" << endl;
    for (int j = 0; j < N; j++) {
      for (int k = 0; k < 101; k++) {
        if (arr[i] < k)
          cout << ".";
        else
          cout << "*";
      }
      cout << endl;
    }
    cout << endl;
  }
}

int main() {
  int pon;
  cout << "Insert št. vrstic: ";
  cin >> pon;
  double hitrost[5];
  double trajanje[5];
  double dolzinaPoti[5];
  vpis(5, hitrost, trajanje, dolzinaPoti);
  cout << "Račun: dolzinaPoti - hitrost * trajanje" << endl;
  double *p;
  p = izracun(hitrost, trajanje, dolzinaPoti);
  double manjkPotProcent[5];
  for (int i = 0; i < 5; i++) {
    if (*(p + i) < 0)
      manjkPotProcent[i] = 100;
    else
      manjkPotProcent[i] = ceil(*(p + i) / dolzinaPoti[i] * 100);
  }
  izpis(manjkPotProcent, pon);
  return 0;
}