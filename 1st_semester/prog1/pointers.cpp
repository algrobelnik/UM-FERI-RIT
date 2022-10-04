#include <iostream>
#include <cstring>
using namespace std;

char *mystrcpyDVA(char *dest, const char *src) { // const src (vsebine src ne želimo spreminjati (konstantna))
    char *tmp = dest; // kopiramo
    while (*tmp++ = *src++){} // nato izvor in cilj kopiranja oboje premaknemo za 1 naprej
    return dest;
}

char *mystrcpy(char *dest, const char *src) { // dest ni const, ker ravno v njegovo vsebino pišemo
    char *tmp = dest;
    while (*tmp = *src)
    {
        tmp++; // eanko kot zgoraj samo ta del zapisan na malo drugačen način
        src++; // vsako polje premakemo tu posebej s svojim ukazom
    }
    return dest;
}

void ZamenjajPrviINZadnji(Seznam *& ZACETEK){
  Seznam *prva;
  Seznam *druga;
  Seznam *predzadnja;
  druga = ZACETEK->knext;
  prva = ZACETEK;
  predzadnja = ZACETEK;
  while (predzadnja->knext->knext != NULL){
    predzadnja=predzadnja->knext;
  }
cout<< "to je predzadnji" <<predzadnja->ime ;
 
  ZACETEK=predzadnja->knext;
  predzadnja->knext = prva;
  ZACETEK->knext=druga;
  prva->knext=NULL;

}

void vnstavi_sortirano(igralec** igralci, igralec* podatki) {
    podatki->naslednji = nullptr;

    if(*igralci == nullptr) {
        *igralci = podatki;
        return;
    }
    if(podatki->napake < (*igralci)->napake || (podatki->napake == (*igralci)->napake && podatki->cas < (*igralci)->cas)) {
        igralec* staro = *igralci;
        podatki->naslednji = staro;
        *igralci = podatki;
        return;
    }

    igralec* prejsni = *igralci;
    igralec* trenutni = (*igralci)->naslednji;
    while(trenutni != nullptr) {
        if(podatki->napake < trenutni->napake || (podatki->napake == trenutni->napake && podatki->cas < trenutni->cas)) {
            igralec* staro = trenutni;
            prejsni->naslednji = podatki;
            podatki->naslednji = staro;
            return;
        }

        prejsni = trenutni;
        trenutni = trenutni->naslednji;
    }

    prejsni->naslednji = podatki;
}


int main() {
	int a = 5;
	int b = 7;
	int* pa = &a;
	int* pb = &b;
	int nb = *(pb);
	nb += 2;
	cout << *pa << endl;
	cout << nb << endl;
	
	char pz[30] = {'a','b','c','d'};
	char* kpz = pz; // kazalec kaže na začetek polja znakov
	for (int i = 0; i < strlen(pz); i++) //* izpiše do \0, vsakič začne eno mesto naprej (pomikanje kazalca)
	{
			cout << kpz << endl;
			kpz++;
	}
	
	kpz = pz;
	//while (*kpz != '\0') { //* daljša oblika (isto kot spodaj) [polje znakov se konča z '\0']
	while (*kpz)
	{
			cout << kpz << endl;
			kpz++;
	}
	cin.ignore();
	char vrstica[10];
	cin.getline(vrstica, 10, '\n');
	
	return 0;
}