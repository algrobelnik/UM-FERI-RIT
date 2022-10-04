#include <iostream>
#include <chrono>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;
using namespace std::chrono;

const char *scenarij0 = 
  "       *  * * * *     \n"
  "       * *      *     \n"
  "       **             \n"
  "       *              \n"
  "       *              \n"
  "       *              \n"
  "       *              \n"
  "      * *             \n"
  "     *   *            \n";

  const char *scenarij1 = 
  "       *  * * * *     \n"
  "       * *      *     \n"
  "       **      -O-    \n"
  "       *              \n"
  "       *              \n"
  "       *              \n"
  "       *              \n"
  "      * *             \n"
  "     *   *            \n";


  const char *scenarij2 = 
  "       *  * * * *     \n"
  "       * *      *     \n"
  "       **      -O-    \n"
  "       *        |     \n"
  "       *        |     \n"
  "       *              \n"
  "       *              \n"
  "      * *             \n"
  "     *   *            \n";

  const char *scenarij3 = 
  "       *  * * * *     \n"
  "       * *      *     \n"
  "       **      -O-    \n"
  "       *        |     \n"
  "       *        |     \n"
  "       *       /      \n"
  "       *              \n"
  "      * *             \n"
  "     *   *            \n";

  const char *scenarij4 = 
  "       *  * * * *     \n"
  "       * *      *     \n"
  "       **      -O-    \n"
  "       *        |     \n"
  "       *        |     \n"
  "       *       / \\    \n"
  "       *              \n"
  "      * *             \n"
  "     *   *            \n";
  const char *scenarij5 = 
  "       *  * * * *     \n"
  "       * *      *     \n"
  "       **      -O-    \n"
  "       *        |     \n"
  "       *        |     \n"
  "       *      _/ \\    \n"
  "       *              \n"
  "      * *             \n"
  "     *   *            \n";
  const char *scenarij6 = 
  "       *  * * * *     \n"
  "       * *      *     \n"
  "       **      -O-    \n"
  "       *        |     \n"
  "       *        |     \n"
  "       *      _/ \\_   \n"
  "       *              \n"
  "      * *             \n"
  "     *   *            \n";
  const char *scenarij7 = 
  "       *  * * * *     \n"
  "       * *      *     \n"
  "       **      -O-    \n"
  "       *       =|     \n"
  "       *        |     \n"
  "       *      _/ \\_   \n"
  "       *              \n"
  "      * *             \n"
  "     *   *            \n";
 
  const char *scenarij8 = 
  "       *  * * * *     \n"
  "       * *      *     \n"
  "       **      -O-    \n"
  "       *       =|=    \n"
  "       *        |     \n"
  "       *      _/ \\_   \n"
  "       *              \n"
  "      * *             \n"
  "     *   *            \n";
 
  const char *scenarij9 = 
  "       *  * * * *     \n"
  "       * *      *     \n"
  "       **      -O-    \n"
  "       *     --=|=    \n"
  "       *        |     \n"
  "       *      _/ \\_   \n"
  "       *              \n"
  "      * *             \n"
  "     *   *            \n";
 
	const char *scenarij10 = 
  "       *  * * * *     \n"
  "       * *      *     \n"
  "       **      -O-    \n"
  "       *     --=|=--  \n"
  "       *        |     \n"
  "       *      _/ \\_   \n"
  "       *              \n"
  "      * *  GAME OVER! \n"
  "     *   *            \n";

const char *scenariji[] = {scenarij0, scenarij1, scenarij2, scenarij3, scenarij4, scenarij5, scenarij6, scenarij7, scenarij8, scenarij9, scenarij10};
const char *guessList[] = {"jog","cycle","muddled","unit","lyrical","left","legs","cent","bright","vase","shaggy","fanatical","gate","star","fireman",
"old","representative","enchanted","alluring","hydrant","whine","tramp","anxious","deer","rambunctious","buzz","yawn","unfasten","ready","judicious",
"calculating","adorable","carpenter","eatable","grate","jeans","pan","auspicious","milky","oval","delicate","drawer","toothsome","chief","clip","unkempt",
"shallow","fearless","grain","creator","receipt","ugly","peace","switch","strip","few","forgetful","oranges","loving","desk","tow","song","stove","mindless",
"night","radiate","yoke","neighborly","bewildered","separate","agreement","month","impartial","meddle","somber","cough","worry","view","bit","beginner","ruddy",
"injure","apathetic","wholesale","legal","increase","trap","uptight","possessive","admit","embarrass","behavior","hideous","worried","follow","telephone","abashed",
"premium","rake","pack"};

struct players_s {
		int ID;
		string name;
		string password;
		vector<char> gLetters;
		int eTime;
	} players [5];

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

void game(int num){
	cout << "———————————————————————————————— " << players[num].ID << ":" << players[num].name << " ————————————————————————————————" << endl;
	cout << "Try to guess this hidden word: ";
	auto start = steady_clock::now();
	
	
	for(int i = 0; i < players[num].password.length(); i++){
		cout <<  "_ ";
	}
	char guess;
	bool cGss;
	int cnt = 0;
	int count = 0;
	int rep = 0;
	int ls;
	for(int i = 0; i < 11 + count + rep; i++){
		cGss = false;
		ls = 0;
		cout << endl << i+1-rep << ". guess: ";
		cin >> guess;
		if(find(players[num].gLetters.begin(), players[num].gLetters.end(), guess) != players[num].gLetters.end()){
			cout << "This character was already guessed." << endl;
			rep++;
			continue;
		}else{
			players[num].gLetters.push_back(guess);
		}
		if(find(players[num].password.begin(), players[num].password.end(), guess) != players[num].password.end()){
			cGss = true;
			count++;
		}
		
		for(int j = 0; j < players[num].password.length(); j++){
			if(find(players[num].gLetters.begin(), players[num].gLetters.end(), players[num].password[j]) != players[num].gLetters.end()){
				cout << players[num].password[j] << " ";
			}else{
				cout << "_ ";
				ls ++;
			}
		}
		if(!cGss){
			cout << endl << endl << scenariji[cnt];
			cnt ++;
		}
		if(ls == 0){
			break;
		}
		cout << endl;
	}
	
	//players[num]gLetters.clear();
	if(ls > 0)cout << "Hidden word was "<< players[num].password << ".";
	cout << endl;
	auto end = steady_clock::now();
	players[num].eTime += duration_cast<seconds>(end - start).count();
	cout << "Last game lasted " << duration_cast<seconds>(end - start).count() << " seconds." << endl;
}

int main() {
	srand(time(0));	
	
	for (int i = 0; i<5; i++){		
		players[i].ID = i+1;
		cout << "Name: ";
		cin >> players[i].name;
		players[i].password = guessList[randGen(0,99)];
		players[i].eTime = 0;
	}
	for (int i = 0; i<5; i++){
		game(i);
	}
	
	sortASC(5);
	
	for (int i = 0; i<5; i++){
		cout << "————————————————————————————————————————————————————————————————" << endl;
		cout << "ID: " << players[i].ID << endl;
		cout << "Name: " << players[i].name << endl;
		cout << "Pass: " << players[i].password << endl;
		cout << "Guessed letters were: ";
		for (int j=0; j<players[i].gLetters.size(); j++)
		{
			cout << players[i].gLetters[j] << " ";
		}
		cout << endl;	
		cout << "Total time: " << players[i].eTime << endl;
	}
	
	ofstream myfile;
  myfile.open ("output.html");
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
<span style='width:50px;display:table-cell;'>" << players[0].ID << "</span>\
<span style='width:200px;display:table-cell;'>" << players[0].name << "</span>\
<span style='width:200px;display:table-cell;'>'" << players[0].password << "'</span>\
<span style='width:100px;display:table-cell;'>" << players[0].gLetters.size() << "</span>\
<span style='width:50px;display:table-cell;'>" << players[0].eTime << "</span>\
</div>\
<div class='b'>\
<span style='width:50px;display:table-cell;'>" << players[1].ID << "</span>\
<span style='width:200px;display:table-cell;'>" << players[1].name << "</span>\
<span style='width:200px;display:table-cell;'>'" << players[1].password << "'</span>\
<span style='width:100px;display:table-cell;'>" << players[1].gLetters.size() << "</span>\
<span style='width:50px;display:table-cell;'>" << players[1].eTime << "</span>\
</div>\
<div class='a'>\
<span style='width:50px;display:table-cell;'>" << players[2].ID << "</span>\
<span style='width:200px;display:table-cell;'>" <<  players[2].name << "</span>\
<span style='width:200px;display:table-cell;'>'" << players[2].password << "'</span>\
<span style='width:100px;display:table-cell;'>" << players[2].gLetters.size() << "</span>\
<span style='width:50px;display:table-cell;'>" << players[2].eTime << "</span>\
</div>\
<div class='b'>\
<span style='width:50px;display:table-cell;'>" << players[3].ID << "</span>\
<span style='width:200px;display:table-cell;'>" << players[3].name << "</span>\
<span style='width:200px;display:table-cell;'>'" << players[3].password << "'</span>\
<span style='width:100px;display:table-cell;'>" << players[3].gLetters.size() << "</span>\
<span style='width:50px;display:table-cell;'>" << players[3].eTime << "</span>\
</div>\
<div class='a'>\
<span style='width:50px;display:table-cell;'>" << players[4].ID << "</span>\
<span style='width:200px;display:table-cell;'>" << players[4].name << "</span>\
<span style='width:200px;display:table-cell;'>'" << players[4].password << "'</span>\
<span style='width:100px;display:table-cell;'>" << players[4].gLetters.size() << "</span>\
<span style='width:50px;display:table-cell;'>" << players[4].eTime << "</span>\
</div>\
</html>";
  myfile.close();
  return 0;
}

















