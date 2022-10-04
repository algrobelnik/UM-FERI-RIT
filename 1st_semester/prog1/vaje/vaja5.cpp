#include <iostream>
#include <math.h>
using namespace std;
const int st_studentov = 166;

bool is_number(const string &s) {
  string::const_iterator it = s.begin();
  while (it != s.end() && isdigit(*it))
    ++it;
  return !s.empty() && it == s.end();
}

int randGen(int min, int max) {
  int range = max - min++;
  return rand() % range + min;
}

void swap(int polje[5][st_studentov], int index,
          string array[2][st_studentov]) {
	for (int i = 0; i < 5; i++) {
		int temp = polje[i][index];
		polje[i][index] = polje[i][index - 1];
		polje[i][index - 1] = temp;
	}
	for (int i = 0; i < 2; i++) {
		string temp = array[i][index];
		array[i][index] = array[i][index - 1];
		array[i][index - 1] = temp;
	}
}


void calculate(int polje[5][st_studentov]) {
  for (int i = 0; i < st_studentov; i++) {
    polje[4][i] = ceil(((polje[3][i] + polje[2][i] + polje[1][i]) / 3) / 10);
  }
}

void sorting(int polje[5][st_studentov], string array[2][st_studentov]) {
  int st, j;
  for (int i = 1; i < st_studentov; i++) {
    st = polje[4][i];
    j = i;
    for (; j > 0 && polje[4][j - 1] < st; j--) {
      swap(polje, j, array);
    }
  }
}

void printTable(int polje[5][st_studentov],
                string imenaPriimki[2][st_studentov], string names[30],
                string lnames[20]) {
									 cout << endl << "--------------------------------------------------------------"
           << endl
           << "| Zaporedna številka	| Ime in priimek | KV | RV | VI | OC |"
           << endl
           << "--------------------------------------------------------------"
           << endl;
  for (int i = 0; i < st_studentov; i++) {


      cout << "| " << to_string(polje[0][i]) << " | ";
      if (is_number(imenaPriimki[0][i]) && is_number(imenaPriimki[1][i])) {
        int a = stoi(imenaPriimki[0][i]);
        int b = stoi(imenaPriimki[1][i]);
        cout << names[a] << " " << lnames[b];
      } else if (is_number(imenaPriimki[0][i]) &&
                 !is_number(imenaPriimki[1][i])) {
        int a = stoi(imenaPriimki[0][i]);
        cout << names[a] << " " << imenaPriimki[1][i];
      } else if (!is_number(imenaPriimki[0][i]) &&
                 is_number(imenaPriimki[1][i])) {
        int b = stoi(imenaPriimki[1][i]);
        cout << imenaPriimki[0][i] << " " << lnames[b];
      } else if (!is_number(imenaPriimki[0][i]) &&
                 !is_number(imenaPriimki[1][i])) {
        cout << imenaPriimki[0][i] << " " << imenaPriimki[1][i];
      }
      cout << " | " << to_string(polje[1][i]) << " | " << to_string(polje[2][i]) <<
                  " | " << to_string(polje[3][i]) << " | " <<
                  to_string(polje[4][i]) << " | "
           << endl;
    
  }
}

int main() {
  srand(time(0));
  int redovalnica[5][st_studentov];
  for (int i = 0; i < st_studentov; i++) {
    redovalnica[0][i] = i + 1;
    cout << redovalnica[0][i] << " ";
  }
  cout << endl;
  for (int i = 1; i < 4; i++) {
    for (int j = 0; j < st_studentov; j++) {
      redovalnica[i][j] = randGen(0, 100);
      cout << redovalnica[i][j] << " ";
    }
    cout << endl;
  }
  string imena[30] = {"Cletus",    "Korey",   "Marva",    "Lauri",   "Delta",
                      "Tula",      "Sulema",  "Felice",   "Hye",     "Kathey",
                      "Audrie",    "Danae",   "Sheilah",  "Alex",    "Norah",
                      "Jeff",      "Mao",     "Chanelle", "Melita",  "Tammi",
                      "Anastacia", "Palmer",  "Howard",   "Florrie", "Dottie",
                      "April",     "Chester", "Sterling", "Anthony", "Crysta"};
  string priimki[20] = {"Griffin",  "Carter", "Morrow",  "House",  "King",
                        "Gamble",   "Dixon",  "Navarro", "Morton", "Charles",
                        "Wells",    "Li",     "Torres",  "Maddox", "Mullins",
                        "Townsend", "Mccall", "Arnold",  "Norris", "Callahan"};
  string imenaPriimki[2][st_studentov];
  for (int i = 0; i < st_studentov; i++) {
    int st = randGen(0, 5);
    if (st == 1) {
      imenaPriimki[0][i] = imena[randGen(0, 29)] + " " + imena[randGen(0, 29)];
    } else {
      imenaPriimki[0][i] = to_string(randGen(0, 29));
    }
    if (st == 1 || st == 2) {
      imenaPriimki[1][i] =
          priimki[randGen(0, 19)] + " " + priimki[randGen(0, 19)];
    } else {
      imenaPriimki[1][i] = to_string(randGen(0, 19));
    }
  }
  for (int j = 0; j < st_studentov; j++) {
    cout << imenaPriimki[0][j] << " ";
  }

  calculate(redovalnica);
  sorting(redovalnica, imenaPriimki);
  printTable(redovalnica, imenaPriimki, imena, priimki);

  /* for (int j = 0; j < st_studentov; j++) {
          cout << redovalnica[4][j] << " ";
  } */
  cout << endl;
  return 0;
}
