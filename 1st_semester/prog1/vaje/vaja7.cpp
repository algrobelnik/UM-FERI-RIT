#include <algorithm>
#include <chrono>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;
using namespace chrono;

string guessList[100];
string scenariji[11];

int randGen(int min, int max) {
    int range = max - min++;
    return rand() % range + min;
}

struct players_s {
    int ID;
    string name;
    string password;
    vector<char> gLetters;
    int eTime;
    players_s* next;
};

struct players_s* players = NULL;

void push(struct players_s** head_ref, int id, string name, int wLength) {
    struct players_s* tmp = new players_s();

    tmp->ID = id;
    tmp->name = name;
    bool status = true;
    string pass;
    for (int j = 0; j < 200; j++) {
        pass = guessList[randGen(0, 99)];
        if (pass.length() == wLength) {
            tmp->password = pass;
            status = false;
            break;
        }
    }
    if (status) {
        tmp->password = guessList[randGen(0, 99)];
        cout << "Cannot find any passwords with that length. You got a random word from password list."
            << endl;
    }
    tmp->eTime = 0;
		sortASC(5);
    tmp->next = (*head_ref);
    (*head_ref) = tmp;
}

void sortASC(const int number) {
    int st, j, st2;
    for (int i = 1; i < number; i++) {
        players_s* nxt = players[0].next;
        players_s* prev = players;
        for (int k = 0; k < (i - 1); k++) {
            nxt = nxt->next;
            prev = prev->next;
        }
        st = nxt->gLetters.size();
        st2 = prev->gLetters.size();
        j = i;
        for (; j > 0 && st2 > st; j--) {
            players_s* temp = prev;
            prev = nxt;
            nxt = temp;
        }
    }
}

void game(int num) {
    players_s* play = players;
    for (int i = 0; i < num; i++)
    {
        play = play->next;
    }
    cout << "———————————————————————————————— " << play[0].ID << ":"
        << play[0].name << " ————————————————————————————————" << endl;
    cout << "Try to guess this hidden word: ";
    auto start = steady_clock::now();

    for (int i = 0; i < players[0].password.length(); i++) {
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
        if (find(play[0].gLetters.begin(), play[0].gLetters.end(),
            guess) != play[0].gLetters.end()) {
            cout << "This character was already guessed." << endl;
            rep++;
            continue;
        }
        else {
            play[0].gLetters.push_back(guess);
        }
        if (find(play[0].password.begin(), play[0].password.end(),
            guess) != play[0].password.end()) {
            cGss = true;
            count++;
        }

        for (int j = 0; j < play[0].password.length(); j++) {
            if (find(play[0].gLetters.begin(), play[0].gLetters.end(),
                play[0].password[j]) != play[0].gLetters.end()) {
                cout << play[0].password[j] << " ";
            }
            else {
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

    // play[0]gLetters.clear();
    if (ls > 0)
        cout << "Hidden word was " << play[0].password << ".";
    cout << endl;
    auto end = steady_clock::now();
    play[0].eTime += duration_cast<seconds>(end - start).count();
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
        string name;
        int number;
        cout << i + 1 << "| Name: ";
        cin >> name;
        cout << i + 1 << "| Word length: ";
        cin >> number;
        push(&players, i + 1, name, number);
    }

    for (int i = 0; i < 10; i++) {
        game(i);
    }
		sortASC(10);

    ofstream file;
    file.open("vaja7.o");

    for (int i = 0; i < 5; i++) {

        players_s* play = players;
        for (int k = 0; k < i; k++)
        {
            play = play->next;
        }
        file << "————————————————————————————————————————————————————————————————"
            << endl;
        file << "ID: " << play[0].ID << endl;
        file << "Name: " << play[0].name << endl;
        file << "Name: " << play[0].password << endl;
        file << "Guessed letters were: ";
        for (int j = 0; j < play[0].gLetters.size(); j++) {
            file << play[0].gLetters[j] << " ";
        }
        file << endl;
        file << "Total time: " << play[0].eTime << endl;
    }
    file.close();

    ofstream myfile;
    myfile.open("vaja7.html");
    myfile << "<html>\
<head>\
<meta http-equiv='Content-Type' content='text/html; charset=utf-8'>\n\
<title>Naloga N7: Vislice</title>\
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
</div>";
    for (int i = 0; i < 5; i++)
    {
        players_s* play = players;
        for (int k = 0; k < i; k++)
        {
            play = play->next;
        }
        if (i % 2) {
            myfile << "<div class='a'>\
            <span style='width:50px;display:table-cell;'>"
                    << play[0].ID << "</span>\
            <span style='width:200px;display:table-cell;'>"
                    << play[0].name << "</span>\
            <span style='width:200px;display:table-cell;'>'"
                    << play[0].password << "'</span>\
            <span style='width:100px;display:table-cell;'>"
                    << play[0].gLetters.size() << "</span>\
            <span style='width:50px;display:table-cell;'>"
                    << play[0].eTime << "</span>\
            </div>\
            </html>";
        }
        else {
            myfile << "<div class='b'>\
            <span style='width:50px;display:table-cell;'>"
                << play[0].ID << "</span>\
            <span style='width:200px;display:table-cell;'>"
                << play[0].name << "</span>\
            <span style='width:200px;display:table-cell;'>'"
                << play[0].password << "'</span>\
            <span style='width:100px;display:table-cell;'>"
                << play[0].gLetters.size() << "</span>\
            <span style='width:50px;display:table-cell;'>"
                << play[0].eTime << "</span>\
            </div>\
            </html>";
        }
    }

    myfile.close();
    return 0;
}
