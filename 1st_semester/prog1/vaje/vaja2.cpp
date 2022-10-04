#include <iostream>
using namespace std;

int main()
{
	double hitrost, trajanje, dolzinaPoti;
	cout << "Insert hitrost: ";
	cin >> hitrost;
	cout << "Insert trajanje: ";
	cin >> trajanje;
	cout << "Insert dolzinaPoti: ";
	cin >> dolzinaPoti;
	cout << hitrost << "m/s " << trajanje << "s " << dolzinaPoti << "m" << endl;
	cout << "Račun: dolzinaPoti - hitrost * trajanje" << endl;
	double manjkPot = dolzinaPoti - hitrost * trajanje;
	cout << "Rezultat: " << manjkPot << "m" <<endl;
	if(manjkPot > 0){
		cout << "Kolesar še ni mimo cilja" << endl;
	}else{
		cout << "Kolesar je že mimo cilja" << endl;
	}
	return 0;
}