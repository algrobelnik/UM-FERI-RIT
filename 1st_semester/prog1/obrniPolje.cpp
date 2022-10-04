#include <iostream>
using namespace std;
const int number = 5;
void obrni(double polje[]) {
	double novoPolje[number];
	for(int i = 0; i < number; i++){
		novoPolje[number-i-1] = polje[i];
	}
  for (int i = 0; i < number; i++) {
	polje[i] = novoPolje[i];
  }
}

int main() {
	double polje[] = {2, 3, 7, 5.5, 1};
	obrni(polje);
	for (double a : polje) {
    cout << a << " ";
  }
	cout << endl;
	return 0;
}
