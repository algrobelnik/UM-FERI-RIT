#include <iostream>
using namespace std;

void obrni(int &a, int &b) {
	int temp = a;
	a = b;
	b = temp;
}

int main() {
	int a = 13;
	int b = 7;
	cout << "a="<< a << ", b=" << b << endl;
	obrni(a, b);
	cout << "a="<< a << ", b=" << b << endl;	
	return 0;
}