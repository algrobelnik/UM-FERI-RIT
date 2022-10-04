#include "Board.h"
#include "DateTime.h"
#include "ExpirationTask.h"
#include "Task.h"
#include "Category.h"
#include <ctime>
#include <iostream>
#include <vector>

using namespace std;

int main() {
  string desc[] = {
      "Lorem ipsum dolor sit amet, consectetur",
      "adipiscing elit. Curabitur rutrum",
      "ante non turpis hendrerit finibus. Sed erat risus",
      "efficitur consequat arcu non, cursus",
      "placerat mauris. Nam vitae dolor sed nisi pretium congue a eu felis.",
      "Donec mattis urna ipsum, et sollicitudin velit volutpat sit amet.",
      "Ut vel nibh sit amet sapien tincidunt",
      "gravida nec vel arcu. Aliquam eget lacus rhoncus, euismod enim "
      "tincidunt",
      "aliquam massa. Nam id odio sit amet orci sodales interdum ac sed dolor.",
      "Seconsequat odio ut faucibus vehicula. Nam quam ipsum, posuere et "
      "sapien in",
      "aliquet venenatis odio. Fusce varius feugiat arcu ac congue. Proin "
      "lacinia nibh id lorem ",
      "Mauris dignissim gravida libero id eleifend"};
  string names[] = {"Janez",  "Tomaž",  "Sebastjan",
                         "Rafael", "Daniel", "Aleksander"};
  string state[] = {"TODO", "DOING", "DONE"};
  Board board("Januar");
	Category categ("Financing");
	Category marke("Marketing");
	board.addCategory(categ);
	board.addCategory(marke);
  ExpirationTask **e;
  e = new ExpirationTask *[16];
  DateTime datesS[16];
  DateTime datesE[16];
  for (int i = 0; i < 16; i++) {
    datesS[i] = DateTime(Date((int)1 + i * 0.5, 11 + i * 2, 2018 + i),
                         Time(i, i * 2, i * i));
    if (i > 4) {
      datesE[i] = DateTime(Date(15 + i, (int)4 + i * 1.5, 2019 + i),
                           Time(i * 2, i * i, (int)i / 2));
      e[i] = new ExpirationTask(names[i % 6], state[i % 3], datesE[i],
                                "Dynamicly alocated " + to_string(i), desc[i % 10],
                                datesS[i]);
    } else {
      datesE[i] = DateTime();
      e[i] = new ExpirationTask("", "", datesE[i],
                                "Dynamicly alocated " + to_string(i), desc[i % 10],
                                datesS[i]);
    }
    if(i < 9) board.addTask("Financing", e[i]);
    else board.addTask("Marketing", e[i]);
		
  }
  cout << board.toString();
	vector<Task *> a = board.agenda(datesS[6]);
	vector<Task *> b = board.beforeDate(datesS[6]);
	vector<Task *> c = board.afterDate(datesS[6]);
	//cout << "-------------------------------------------------------------------";
	cout << endl;
	for(int i = 0; i < a.size(); i++){
		cout << a[i]->toString();
	}
	cout << "-------------------------------------------------------------------";
	cout << endl;
	for(int i = 0; i < b.size(); i++){
		cout << b[i]->toString();
	}
	cout << "-------------------------------------------------------------------";
	cout << endl;
	for(int i = 0; i < c.size(); i++){
		cout << c[i]->toString();
	}
	Board newBoard = board.removeAllWithTaskName("Janez");
	cout << newBoard.toString();
  return 0;
}