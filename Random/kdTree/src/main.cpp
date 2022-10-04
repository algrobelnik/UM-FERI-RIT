#include <cmath>
#include <iostream>

using namespace std;
//const int len1 = 1000000;
const int len1 = 100;
const int len2 = 2;

double distance(double *arr, double *val, int offset) {
  //cout << "OFFSET: " << offset << " ";
  double sum = 0;
  for (int i = 0; i < len2; i++) {
    //cout << arr[i + offset] << " ";
    sum += pow(arr[i + offset] - val[i + offset], 2);
  }
  //cout << "SUM: " << sum << " | " << sqrt(sum) << endl;
  return sqrt(sum);
}

double randGen(int min, int max) {
  int range = max - min++;
  return rand() % range + min;
}

void fillArr(double *arr) {
  for (int i = 0; i < len1; i++) {
    for (int j = 0; j < len2; j++) {
      arr[i * len2 + j] = randGen(-10, 10);
    }
  }
}

int main() {
  srand(time(nullptr));
  double val[len2];
  cout << "coordinates(" << len2 << "): ";
  for (int i = 0; i < len2; i++) {
    cin >> val[i];
  }
  double *arr = new double[len1 * len2];
  fillArr(arr);
  int offset = 0;
  double dist = distance(arr, val, 0);
  for (int i = len2; i < len1; i += len2) {
    double tmp = distance(arr, val, i);
    if (dist > tmp) {
      offset = i;
      dist = tmp;
    }
  }
  cout << "Closes element to (";
  for (int i = 0; i < len2; i++) {
    cout << (i != 0 ? "," : "") << val[i];
  }
  cout << ") is (";
  for (int i = 0; i < len2; i++) {
    cout << (i != 0 ? "," : "") << arr[offset + i];
  }
  cout << ")[" << dist << "]" << endl;
  delete[] arr;
  return 0;
}
