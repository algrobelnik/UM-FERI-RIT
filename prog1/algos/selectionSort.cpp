#include <iostream>
using namespace std;

void swap(int &a, int &b) {
  int tmp = a;
  a = b;
  b = tmp;
}

int indMaxEl(polje[], const int n){
	double m = P[0];
	int ind = 0;
	for(int i = 1; i<n; i++){
		if(m<P[i]){
			m=P[i];
			ind= i;
		}
	}
	return ind;
}

void sortDESC(int polje[], int number) {
  for (int i = number - 1; i > 0; i--) {
    int ind = indMaxEl(polje, i);
    if (polje[ind] < polje[i]) {
      swap(polje[ind], polje[i]);
    }
  }
}

int main() {
  int polje[9] = {9, 2, 3, 6, 5, 1, 4, 8, 7};
  sortDESC(polje, 9);

  cout << "DESC: ";
  for (int a : polje) {
    cout << a;
  }
  cout << endl;
  return 0;
}