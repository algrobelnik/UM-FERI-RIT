#include <iostream>
using namespace std;
const int number1 = 3;
const int number2 = 3;
void trans(int polje[number1][number2], int retPolje[number1][number2]) {
	for	(int i = 0; i < number1; i++){
		for	(int j = 0; j < number2; j++){
			retPolje[i][j] = polje[j][i];
		}
	}
}

int main() {
	int polje[number1][number2] = {{1, 2, 0}, {1, 1, -1}, {0, -1, 2}};
	int returnPolje[number1][number2];
	trans(polje, returnPolje);
	for	(int i = 0; i < number1; i++){
		for	(int j = 0; j < number2; j++){
			cout << returnPolje[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
	return 0;
}