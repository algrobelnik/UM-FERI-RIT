// Simple C++ program to 
// find n'th node from end 
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void DodajPovp(DEPS *& abc){
	float povp = IzracunajPovp(DEPS *& abc);
	cout << "Povp cena je: " << povp << endl;
	 while (abc != NULL) {
			vsota = abc->cena + povp;
			abc = abc->kn;
	}
}

float IzracunajPovp(DEPS *& abc){
		float vsota = 0;
    while (abc != NULL) {
			vsota = abc->cena;
			abc = abc->kn;
    }
		return vsota;
}

int main() 
{ 
	struct DEPS {
			 DEPS * kn;
			 float cena;    
			 char * opis;
			 string * em;
	}
	
	struct DEPS *xyz = NULL;
	
	DodajPovp(xyz);
}

struct Student {
    string ime;
    string priimek;
    int posSt;               // poštna številka, npr.   2101
    string kraj;
    char * opis;
};

/*Napišite funkcijo, ki polje, v katerem so študenti, uredi naraščajoče po poštni številki. Če sta dve poštni številki enaki, funkcija naj pri urejanju upošteva še priimek (od A do Ž).
Funkcija naj vrne število različnih poštnih številk v polju.*/


string uredi(Student poljeStudentov[], int n){ //uporaba knjižnic <vector> in <algorithm>
	vector<string> ret;
	for (int i = 0; i < n; i++)
	{
		if(poljeStudentov[i].posSt>poljeStudentov[i+1].posSt){
			swap(poljeStudentov[i], poljeStudentov[i+1]);
		}
		else if(poljeStudentov[i].posSt==poljeStudentov[i+1].posSt){
			if(poljeStudentov[i].priimek > poljeStudentov[i+1].priimek){
				swap(poljeStudentov[i], poljeStudentov[i+1]);
			}
		}
	}
	
	for(int i = 0; i < n; i++){
		if(find(ret.begin(), ret.end(), poljeStudentov[i].posSt) != ret.end())){
			//nič saj je že v polju
		}else{
			ret.push_back(poljeStudentov[i].posSt);
		}
	}
	return ret.size();
}

void swap(Student* &a, Student* &b) {
	Student* temp = a;
	a = b;
	b = temp;
}











