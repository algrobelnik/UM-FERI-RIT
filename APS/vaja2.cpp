#include <iostream>

using namespace std;

struct Sklad {
  int *S;
  int vrh;
  int max;
};

void pushSklad(Sklad &s, int x) {
  if (s.vrh + 1 == s.max) {
    cout << "napaka: polno" << endl;
  } else {
    s.vrh++;
    s.S[s.vrh] = x;
  }
}

int popSklad(Sklad &s) {
  if (s.vrh + 1 == 0) {
    cout << "Napaka: prazno." << endl;
    return -1;
  }
  s.vrh--;
  return s.S[s.vrh + 1];
}

void izpis(int a, Sklad &b) {
  cout << "Stolp " << a << ": ";
  for (int i = 0; i < b.vrh + 1; i++) {
    cout << b.S[i] << " ";
  }
  cout << endl;
}

void getLast(int &a, Sklad &b) {
  a = b.max + 1;
  for (int i = 0; i < b.vrh + 1; i++) {
    a = b.S[i];
  }
}

int main() {
  int stPloscic = 0;
  Sklad s[3];
  cout << "Število ploščic: ";
  cin >> stPloscic;
  for (int i = 0; i < 3; i++)
    s[i].max = stPloscic;
  if (s[0].max == 0) {
    for (int i = 0; i < 3; i++)
      s[i].max = 9;
  }
  for (int i = 0; i < 3; i++) {
    s[i].S = new int[s[i].max];
    s[i].vrh = -1;
  }

  for (int i = s[0].max; i > -1; i--)
    pushSklad(s[0], i);
  int num[2];
  int last[3];
  cout << "Za premik iz stolpca 1 v stolpec 2, napišite 1 in nato 2. Če želite "
          "zaključiti igro napišite 0. "
       << endl;
  do {
    for (int i = 0; i < 3; i++) {
      izpis(i + 1, s[i]);
    }
    cout << "Premik iz: ";
    cin >> num[0];
    cout << "Premik v: ";
    cin >> num[1];
    if (num[0] == 0 || num[1] == 0)
      break;
    if (num[0] > 3 || num[1] > 3) {
      cout << "Napaka pri vnosu." << endl;
      continue;
    }
    if (num[0] == num[1]) {
      cout << "Premik ploščice v samega sebe ni dovoljeno." << endl;
      continue;
    }
    for (int i = 0; i < 3; i++){
      getLast(last[i], s[i]);
		}
    if (last[num[0] - 1] < last[num[1] - 1]) {
      int tmp = popSklad(s[num[0] - 1]);
      if (tmp != -1){
        pushSklad(s[num[1] - 1], tmp);
			}
    } else {
      cout << "Napaka večje na manjše ne gre ali pa je celica prazna." << endl;
    }
  } while (1);
  return 0;
}