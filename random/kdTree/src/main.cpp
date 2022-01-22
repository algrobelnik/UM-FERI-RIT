#include <cmath>
#include <iostream>

using namespace std;

double distance(double *a, double *b) {
  return sqrt(pow(a[0] - b[0], 2) + pow(a[1] - b[1], 2));
}

int main() {
  double val[2];
  cout << "coordinates: ";
  cin >> val[0] >> val[1];
  double arr[7][2] = {{1, 2}, {3, 2}, {4, 6}, {6, 4}, {7, 8}, {9, 9}, {5.4, 8.4},};
  double *res = arr[0];
  double dist = distance(res, val);
  for (int i = 1; i < 6; i++) {
    if (distance(res, val) > distance(arr[i], val)) {
      res = arr[i];
      dist = distance(arr[i], val);
    }
  }
  cout << "Closes element to (" << val[0] << "," << val[1] << ") is (" << res[0]
       << "," << res[1] << ")[" << dist << "]" << endl;
  return 0;
}
