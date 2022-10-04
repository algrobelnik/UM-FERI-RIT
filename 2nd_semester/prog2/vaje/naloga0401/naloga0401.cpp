#include "Athlete.h"
#include "Competition.h"
#include "Competitor.h"
#include "Date.h"
#include <ctime>
#include <iostream>
#include <vector>

using namespace std;

int main() {
  Athlete **e;
  e = new Athlete *[6];
  for (int i = 0; i < 2; i++)
    e[i] = new Athlete("Dynamicly", "alocated", "Slovenia", i * 15 + 160, 7302,
                       3 + i);
  e[2] =
      new Athlete("John", "Johnson", "United States of America", 184, 7531, 1);
  e[3] = new Athlete("Ana", "Lenistov", "Russian Federation", 161, 5228, 2);
  e[4] = new Athlete();
  e[5] = new Athlete(e[2]);

  time_t t = time(0);
  tm *now = localtime(&t);
  Competition archery("Archery",
                      Date(now->tm_mday, now->tm_mon + 1, now->tm_year + 1900));
  cout << archery.toString();
  for (int i = 0; i < 6; i++) {
    archery.addCompetitor(e[i]);
    archery.addResult(i + 1, (i % 2 == 0 ? i * 25 + 160 : i * -25 + 290));
  }
  archery.addCompetitor(e[3]);
  archery.addCompetitor(e[4]);
  archery.addResult(7, 0);
  archery.addResult(8, 1);
  archery.removeResult0();
  archery.printCompetitors();
  cout << endl;
  cout << "Qualified Archers:" << endl;
  vector<Competitor *> vec = archery.getQualifiedCompetitors(212);
  for (int i = 0; i < vec.size(); i++) {
    cout << vec[i]->toString();
  }
  for (int i = 0; i < 6; i++) {
    delete e[i];
  }
  vec.clear();
  return 0;
}