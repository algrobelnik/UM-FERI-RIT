#include <iostream>
using namespace std;

struct RojstniDatum{
	int d;
	int m;
	int l;
};

struct Oseba{
	char ime[30];
  string priimek;
	char spol;
	string emso;
	RojstniDatum rDatum; 
};

int main() {
	Oseba Miha;
	Miha.ime=strcpy("Miha");
	cin>>Miha.ime;
	Miha.spol='M';
	cout << Miha.ime;
	cout << endl;
	return 0;
}