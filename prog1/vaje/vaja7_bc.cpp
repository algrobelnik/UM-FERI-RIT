#include <algorithm>
#include <chrono>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;
using namespace chrono;

string guessList[100];
string scenariji[11];


struct players_s {
  int ID;
  string name;
  string password;
  vector<char> gLetters;
  int eTime;
	players_s *next;
} players[10];

class linked_list{
private: players_s *head,*tail;
public: linked_list(){
        head = NULL;
        tail = NULL;
    }

    void add_node(int i, string n, int number){
        node *tmp = new players_s;
        tmp->ID = i;
        tmp->name = n;
				bool status;
				string pass;
				for (int j = 0; j < 200; j++) {
					status = true;
					pass = guessList[randGen(0, 99)];
					if (pass.length() == number) {
						tmp->password = pass;
						status = false;
						break;
					}
				}
				if (status) {
					tmp->password = guessList[randGen(0, 99)];
					cout << "Cannot find any passwords with that length. You got a random word."
									"from password list."
							 << endl;
				}
        tmp->eTime = 0;
        tmp->next = NULL;

        if(head == NULL)
        {
            head = tmp;
            tail = tmp;
        }
        else
        {
            tail->next = tmp;
            tail = tail->next;
        }
    }
		
		void display() {
		  struct players_s* ptr;
		  ptr = head;
		  while (ptr != NULL) {
				cout<< ptr->data << endl;
				ptr = ptr->next;
		  }
		}
};

int randGen(int min, int max) {
  int range = max - min++;
  return rand() % range + min;
}

void swap(int index) {
  int a;
  string b;
  vector<char> c;

  a = players[index].ID;
  players[index].ID = players[index - 1].ID;
  players[index - 1].ID = a;

  b = players[index].name;
  players[index].name = players[index - 1].name;
  players[index - 1].name = b;

  b = players[index].password;
  players[index].password = players[index - 1].password;
  players[index - 1].password = b;

  c = players[index].gLetters;
  players[index].gLetters = players[index - 1].gLetters;
  players[index - 1].gLetters = c;

  a = players[index].eTime;
  players[index].eTime = players[index - 1].eTime;
  players[index - 1].eTime = a;
}

void sortASC(const int number) {
  int st, j;
  for (int i = 1; i < number; i++) {
    st = players[i].gLetters.size();
    j = i;
    for (; j > 0 && players[j - 1].gLetters.size() > st; j--) {
      swap(j);
    }
  }
}

void game(int num) {
  cout << "———————————————————————————————— " << players[num].ID << ":"
       << players[num].name << " ————————————————————————————————" << endl;
  cout << "Try to guess this hidden word: ";
  auto start = steady_clock::now();

  for (int i = 0; i < players[num].password.length(); i++) {
    cout << "_ ";
  }
  char guess;
  bool cGss;
  int cnt = 0;
  int count = 0;
  int rep = 0;
  int ls;
  for (int i = 0; i < 11 + count + rep; i++) {
    cGss = false;
    ls = 0;
    cout << endl << i + 1 - rep << ". guess: ";
    cin >> guess;
    if (find(players[num].gLetters.begin(), players[num].gLetters.end(),
             guess) != players[num].gLetters.end()) {
      cout << "This character was already guessed." << endl;
      rep++;
      continue;
    } else {
      players[num].gLetters.push_back(guess);
    }
    if (find(players[num].password.begin(), players[num].password.end(),
             guess) != players[num].password.end()) {
      cGss = true;
      count++;
    }

    for (int j = 0; j < players[num].password.length(); j++) {
      if (find(players[num].gLetters.begin(), players[num].gLetters.end(),
               players[num].password[j]) != players[num].gLetters.end()) {
        cout << players[num].password[j] << " ";
      } else {
        cout << "_ ";
        ls++;
      }
    }
    if (!cGss) {
      cout << endl << endl << scenariji[cnt];
      cnt++;
    }
    if (ls == 0) {
      break;
    }
    cout << endl;
  }

  // players[num]gLetters.clear();
  if (ls > 0)
    cout << "Hidden word was " << players[num].password << ".";
  cout << endl;
  auto end = steady_clock::now();
  players[num].eTime += duration_cast<seconds>(end - start).count();
  cout << "Last game lasted " << duration_cast<seconds>(end - start).count()
       << " seconds." << endl;
}

int main() {
  srand(time(0));

  ifstream ifsw("vaja7_words.i");
  for (int i = 0; i < 100; i++) {
    ifsw >> guessList[i];
  }
  ifsw.close();

  int num_lines = 0;
  ifstream ifss("vaja7_pictures.i");

  string line;
  getline(ifss, line);
  cout << line;

  for (int i = 0; i < 11; i++) {
    string scenarij = "";
    for (int j = 0; getline(ifss, line) && j < 9; j++) {
      scenarij += line + "\n";
      // cout << line;
    }
    scenariji[i] = scenarij;
  }
  ifss.close();

  /* for(int i = 0; i < 11; i++){
          cout << scenariji[i] << endl;
  } */

  for (int i = 0; i < 10; i++) {
		players_s players;
		string name;
		int number;
		int wLen;
    cout << i+1 << "| Name: ";
    cin >> name;
    cout << i+1 << "| Word length: ";
    cin >> number;
  }

  for (int i = 0; i < 10; i++) {
    game(i);
  }

  sortASC(10);

  ofstream file;
  file.open("vaja7.o");

  for (int i = 0; i < 5; i++) {
    file << "————————————————————————————————————————————————————————————————"
         << endl;
    file << "ID: " << players[i].ID << endl;
    file << "Name: " << players[i].name << endl;
    file << "Name: " << players[i].password << endl;
    file << "Guessed letters were: ";
    for (int j = 0; j < players[i].gLetters.size(); j++) {
      file << players[i].gLetters[j] << " ";
    }
    file << endl;
    file << "Total time: " << players[i].eTime << endl;
  }
  file.close();

  ofstream myfile;
  myfile.open("vaja7.html");
  myfile << "<html>\
<head>\
<meta http-equiv='Content-Type' content='text/html; charset=utf-8'>\n\
<title>Naloga N6: Vislice</title>\
<style>\
.a {background-color:#ffbbbb; width:550px;}\
.b {background-color:#e0ffff; width:550px;}\
.c {background-color:#aaaaff; width:550px;}\
</style>\
</head>\
<body>\
<div class='c'>\
<span style='width:50px;display:table-cell;'>ID</span>\
<span style='width:200px;display:table-cell;'>Tekmovalec</span>\
<span style='width:200px;display:table-cell;'>Geslo</span>\
<span style='width:100px;display:table-cell;'>Število ugibanj</span>\
<span style='width:50px;display:table-cell;'>Čas</span>\
</div>\
<div class='a'>\
<span style='width:50px;display:table-cell;'>"
         << players[0].ID << "</span>\
<span style='width:200px;display:table-cell;'>"
         << players[0].name << "</span>\
<span style='width:200px;display:table-cell;'>'"
         << players[0].password << "'</span>\
<span style='width:100px;display:table-cell;'>"
         << players[0].gLetters.size() << "</span>\
<span style='width:50px;display:table-cell;'>"
         << players[0].eTime << "</span>\
</div>\
<div class='b'>\
<span style='width:50px;display:table-cell;'>"
         << players[1].ID << "</span>\
<span style='width:200px;display:table-cell;'>"
         << players[1].name << "</span>\
<span style='width:200px;display:table-cell;'>'"
         << players[1].password << "'</span>\
<span style='width:100px;display:table-cell;'>"
         << players[1].gLetters.size() << "</span>\
<span style='width:50px;display:table-cell;'>"
         << players[1].eTime << "</span>\
</div>\
<div class='a'>\
<span style='width:50px;display:table-cell;'>"
         << players[2].ID << "</span>\
<span style='width:200px;display:table-cell;'>"
         << players[2].name << "</span>\
<span style='width:200px;display:table-cell;'>'"
         << players[2].password << "'</span>\
<span style='width:100px;display:table-cell;'>"
         << players[2].gLetters.size() << "</span>\
<span style='width:50px;display:table-cell;'>"
         << players[2].eTime << "</span>\
</div>\
<div class='b'>\
<span style='width:50px;display:table-cell;'>"
         << players[3].ID << "</span>\
<span style='width:200px;display:table-cell;'>"
         << players[3].name << "</span>\
<span style='width:200px;display:table-cell;'>'"
         << players[3].password << "'</span>\
<span style='width:100px;display:table-cell;'>"
         << players[3].gLetters.size() << "</span>\
<span style='width:50px;display:table-cell;'>"
         << players[3].eTime << "</span>\
</div>\
<div class='a'>\
<span style='width:50px;display:table-cell;'>"
         << players[4].ID << "</span>\
<span style='width:200px;display:table-cell;'>"
         << players[4].name << "</span>\
<span style='width:200px;display:table-cell;'>'"
         << players[4].password << "'</span>\
<span style='width:100px;display:table-cell;'>"
         << players[4].gLetters.size() << "</span>\
<span style='width:50px;display:table-cell;'>"
         << players[4].eTime << "</span>\
</div>\
</html>";
  myfile.close();
  return 0;
}
