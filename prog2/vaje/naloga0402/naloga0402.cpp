#include "Athlete.h"
#include "Competition.h"
#include "Competitor.h"
#include "DateTime.h"
#include "Result.h"
#include <ctime>
#include <iostream>
#include <vector>

using namespace std;

int main() {
  Athlete **e;
  e = new Athlete *[8];
  for (int i = 0; i < 2; i++)
    e[i] = new Athlete("Dynamicly", "alocated", "Slovenia", i * 15 + 160, 7302,
                       3 + i);
  e[2] =
      new Athlete("John", "Johnson", "United States of America", 184, 7531, 1);
  e[3] = new Athlete("Ana", "Lenistov", "Russian Federation", 161, 5228, 2);
  e[4] = new Athlete();
  e[5] = new Athlete("Fant", "Fare", "Slovenia", 184, 7531, 5);
  e[6] = new Athlete(e[2]);
  e[7] = new Athlete("Janez", "Sosedov", "Slovenia", 192, 10019, 6);

  time_t t = time(0);
  tm *now = localtime(&t);
  Competition archery("Archery", DateTime(Date(1, 11, 2019), Time(0, 0, 0)),
                      DateTime(Date(20, 3, 2021), Time(0, 0, 0)));
  Competition swimming("Swimming",
                       DateTime(Date(1, 12, 2020), Time(20, 10, 10)),
                       DateTime(Date(23, 3, 2021), Time(0, 0, 0)));
  cout << archery.toString();
  cout << swimming.toString();
  vector<double> res;
  for (int i = 0; i < 8; i++) {
    archery.addCompetitor(e[i]);
    for (int j = 0; j < 3; j++)
      res.push_back((j % 2 == 0 ? i * 25.12 + j * 50.7 + 160
                                : i * -25.4 + j * 10.2 + 290));
    archery.addResult(i + 1, res);
    res.clear();
  }
  archery.printCompetitors();
  cout << endl;
  cout << "Qualified Archers:" << endl;
  vector<Competitor *> vec = archery.getQualifiedCompetitors(250);
  for (int i = 0; i < vec.size(); i++) {
    cout << vec[i]->toString();
  }
  cout << endl;
  vector<Competition *> vec2;
  vector<Competition *> out;

  vec2.push_back(&archery);
  vec2.push_back(&swimming);

  out = Competition::getCompetitionsBetween(
      vec2, DateTime(Date(1, 12, 2020), Time(10, 0, 0)),
      DateTime(Date(1, 12, 2021), Time(23, 59, 59)));
  for (int i = 0; i < out.size(); i++) {
    cout << out[i]->toString();
  }

  archery.printPlayOff();

  for (int i = 0; i < 6; i++) {
    delete e[i];
  }
  vec.clear();
  return 0;
}