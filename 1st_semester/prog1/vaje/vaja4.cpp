#include <iostream>
#include <math.h>
using namespace std;

/* N4: praštevila / N4: prime numbers
Napišite funkcijo, ki za podano celo število vrne logično vrednost, ali je
število praštevilo (testirajte delitelje). Pazite na to, da negativna števila, 0
in število 1 niso praštevila.

Napišite še funkcijo, ki izračuna in vrne, koliko praštevil je v razponu od
vključno -217 do vključno 9001.

Napišite še funkcijo, ki ima dva parametra, prvi je polje velikosti 20, drugi je
celo število. Funkcija v to podano polje shrani prvih 20 praštevil, ki so enaka
ali večja od podanega števila v drugem parametru. Nato v tej funkciji
izračunajte še povprečno vrednost teh praštevil in jo vrnite kot rezultat s
stavkom return.

Pred definicijo teh treh funkcij deklarirajte njihov predpis (prototip
funkcije). Ne uporabljajte globalnih spremenljivk. Te tri zahtevane funkcije naj
ne berejo in pišejo na zaslon, ampak to opravite v glavnem programu.

V glavnem programu uporabnik nato vnese neko novo število in po klicu tretje
funkcije izpišite najmanjše praštevilo iz podanega polja, ki je najbližje korenu
tega števila.

KRITERIJ OCENJEVANJA (za dosego nekega števila točk je potrebno rešiti vse, kar
je zahtevano tudi za manj točk):
1 točka - funkcija 1: praštevila
2 točki - funkcija 2: štetje praštevil
3 točke - funkcija 3: polnjenje polja s praštevili in izračun povprečja
4 točke - vnos/izpis v glavnem programu, razumevanje prenosa polja po referenci
5 točk - iskanje najbližjega praštevila; program brez globalnih spremenljivk */

bool primeNum1(int number) {
  if (number < 2)
    return false;
  else {
    for (int i = 0; i + 2 <= (sqrt(number)); i++) {
      if (number % (i + 2) == 0) {
        return false;
      }
    }
    return true;
  }
}

int primeNum2() {
  int count = 0;
  for (int i = -217; i <= 9002; i++) {
    if (primeNum1(i))
      count++;
  }
  return count;
}

double primeNum3(int polje[], int st) {
  int count = 0;
  for (; count < 20; st++) {
    if (primeNum1(st)) {
      polje[count] = st;
      count++;
    }
  }
  count -= 20;
  for (int i = 0; i < 20; i++) {
    count += polje[i];
  }
  return (float)count / 20;
}

int findClosestPrimeNum(int polje[], double number) {
  int close = polje[0];
  for (int i = 1; i < 20; i++) {
    if (abs(polje[i] - number) < abs(close - number))
      close = polje[i];
  }
  return close;
}

int main() {
  int num, num2, num3;
  cout << "Vpiši število 1: ";
  cin >> num;
  cout << "Vpiši število 2: ";
  cin >> num2;
  if (primeNum1(num))
    cout << "Število " << num << " je praštevilo" << endl;
  else
    cout << "Število " << num << " ni praštevilo" << endl;
  cout << "Število praštevil med -217 in 9002 je " << primeNum2() << endl;
  int polje[20];
  cout << "Povprečje je " << primeNum3(polje, num2) << endl;
  cout << "Vpiši število 3: ";
  cin >> num3;
  cout << "Najmanjše število, ki je najbližje " << sqrt(num3) << "(√" << num3
       << ") iz tega polja je " << findClosestPrimeNum(polje, sqrt(num3))
       << endl;
  return 0;
}