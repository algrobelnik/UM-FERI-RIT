#include "Board.h"
#include "DateTime.h"
#include "ExpirationTask.h"
#include "Task.h"
#include <ctime>
#include <iostream>
#include <vector>

using namespace std;

int main() {
  std::string desc[] = {
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
  std::string names[] = {"Janez",  "Tomaž",  "Sebastjan",
                         "Rafael", "Daniel", "Aleksander"};
  std::string state[] = {"TODO", "DOING", "DONE"};
  Board board("Januar");
  ExpirationTask **e;
  e = new ExpirationTask *[8];
  DateTime datesS[8];
  DateTime datesE[8];
  std::vector<std::string> vec;
  vec.push_back("Domača naloga");
  vec.push_back("Tag1");
  vec.push_back("Tag2");
  for (int i = 0; i < 8; i++) {
    datesS[i] = DateTime(Date((int)1 + i * 0.5, 11 + i * 2, 2018 + i),
                         Time(i, i * 2, i * i));
    if (i > 4) {
      datesE[i] = DateTime(Date(15 + i, (int)4 + i * 1.5, 2019 + i),
                           Time(i * 2, i * i, (int)i / 2));
      e[i] = new ExpirationTask(names[i % 6], state[i % 3], datesE[i],
                                "Dynamicly alocated " + to_string(i), desc[i] /* "Random text to check" */,
                                datesS[i], vec);
    } else {
      datesE[i] = DateTime();
      e[i] = new ExpirationTask("", "", datesE[i],
                                "Dynamicly alocated " + to_string(i), desc[i] /* "Random text to check" */,
                                datesS[i], vec);
    }
    board.addTask(e[i]);
  }
  //cout << board.toString();
  cout << board.exportJSON();
  return 0;
}