#include "Athlete.h"
#include <iostream>

using namespace std;

// Poglejte primer Point na prosojnicah iz predavanj in po enakem vzoru napišite
// razred Athlete (zapišite Athlete.h in Athlete.cpp). Vse metode (tudi krajše)
// implementirajte v datoteki Athlete.cpp.

// Razred Athlete mora imeti naslednje instančne spremenljivke:
// firstName,
// lastName,
// country,
// height in
// weight.
// Razred Athlete mora imeti še:
// privzeti konstruktor in
// konstruktor s 5 parametri.
// Napišite javne metode: get (vrne podatek) za vsako lastnost posebej.
// Napišite javne metode: set (nastavi podatek) pri izbranih lastnostih, kjer je
// smiselno. Napišite javno metodo print(), ki izpiše vse podatke. Napišite
// metodo toString(), ki vrne string, ki vsebuje vse podatke o atletu. V glavnem
// programu demonstrirajte uporabo konstruktorjev in metod iz razreda Athlete.
// Ustvarite vsaj 5 objektov, kjer demonstrirate: statično in dinamično
// alokacijo objektov (razreda Athlete), uporabo vseh metod iz razreda Athlete.

int main() {
  Athlete a("John", "Johnson", "United States of America", 184, 7531, 1);
  Athlete b("Ana", "Lenistov", "Russian Federation", 161, 5228, 2);
  Athlete c;
  Athlete d(a);
  Athlete **e;
  cout << c.toString();
  /* d.height = 180; //std::string Athlete::height’ is private within this
  context d.weight = 6220; //std::string Athlete::weight’ is private within this
  context d.firstName = "Suzan"; //std::string Athlete::firstName’ is private
  within this context d.lastName = "Cuphock"; //std::string Athlete::lastName’
  is private within this context d.country = "United Kingdom"; //std::string
  Athlete::country’ is private within this context */
  cout << d.toString();
  e = new Athlete *[2];
  for (int i = 0; i < 2; i++)
    e[i] = new Athlete("Dynamicly", "alocated", "Slovenia", i * 25 + 160, 7302, 3 + i);
  e[0]->print();
  e[1]->print();
  cout << a.getHeight() << endl;
  cout << a.getWeight() << endl;
  cout << a.getFirstName() << endl;
  cout << a.getLastName() << endl;
  cout << a.getCountry() << endl;
  cout << b.getHeight() << endl;
  cout << b.getWeight() << endl;
  cout << b.getFirstName() << endl;
  cout << b.getLastName() << endl;
  cout << b.getCountry() << endl;
  a.print();
  cout << b.toString();
	if(a.isSame(d)) cout << "Same athlete" << endl;
	else cout << "Not same athlete" << endl;
	if(a.isSame(b)) cout << "Same athlete" << endl;
	else cout << "Not same athlete" << endl;
  delete e;
  // e[0]->print(); //Segmentation fault (core dumped)
  return 0;
}