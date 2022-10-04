#include <iostream>
using namespace std;
const int number = 3;
void kvad(int polje1[number][number], int polje2[number][number], int polje3[number][number]) {
  for (int i = 0; i< number; i++){
		for (int j = 0; j< number; j++){
			polje3[i][j] = 0;
		}
	}
	for	(int i = 0; i < number; i++){
		for	(int j = 0; j < number; j++){
			for	(int k = 0; k < number; k++){
				polje3[i][j] += polje1[i][k] * polje2[k][j];
			}
		}
	}
}

int main() {
	int polje[number][number] = {{1, 2, 3}, {1, 1, 0}, {0, -1, 1}};
	int polje2[number][number] = {{1, 2, 3}, {1, 1, 0}, {0, -1, 1}};
	int returnPolje[number][number];
	kvad(polje, polje2, returnPolje);
	for	(int i = 0; i < number; i++){
		for	(int j = 0; j < number; j++){
			cout << returnPolje[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
	return 0;
}