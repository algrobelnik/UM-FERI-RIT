#include "CovidData.h"
#include <ctime>
#include <iostream>
#include <vector>

using namespace std;

int randGen(int min, int max) {
  int range = max - min++;
  return rand() % range + (rand() % range / 10 + min);
}

string display(int num) {
  string value = "";
  for (int i = 0; i < 9 - to_string(num).length(); i++) {
    value += " ";
  }
  return value += to_string(num);
}

void menu() {
  cout << "======================================" << endl;
  cout << "================ MENU ================" << endl;
  cout << "======================================" << endl;
  cout << "1 ... GENERATE ACTIVE CASES" << endl;
  cout << "2 ... PRINT ACTIVE CASES" << endl;
  cout << "3 ... AVERAGE ACTIVE CASES" << endl;
  cout << "4 ... NUMBER OF DAYS ABOVE AVERAGE" << endl;
  cout << "5 ... PERCENTAGE OF DAYS ABOVE AVERAGE" << endl;
  cout << "6 ... GROUP ACTIVE CASES" << endl;
  cout << "7 ... PRINT MAX 5 DAYS" << endl;
  cout << "8 ... NUMBER OF DAYS 1000 CASES" << endl;
  cout << "9 ... ADD DATA" << endl;
  cout << "10 ... FILTER DATA" << endl;
  cout << "0 ... EXIT" << endl;
  cout << "======================================" << endl;
  cout << "Select: ";
}

void fillVector(vector<CovidData *> &vec, int days) {
  time_t t = time(0);
  tm *now = localtime(&t);
  for (int i = 0; i < days; i++)
    vec.push_back(new CovidData(i + 1, now->tm_mon + 1, now->tm_year + 1900,
                                randGen(1000, 4500)));
}

void printVector(const vector<CovidData *> &vec) {
  for (unsigned int i = 0; i < vec.size(); i++) {
    cout << vec[i]->toString() << ((i < vec.size() - 1) ? ", " : ".");
    if (i == vec.size() - 1) {
      cout << std::endl;
    }
  }
}

void averageCases(const vector<CovidData *> &vec) {
  double avg = 0;
  for (int i = 0; i < vec.size(); i++) {
    avg += vec[i]->getActiveCases();
  }
  cout << avg / vec.size() << endl;
}

void averageDays(const vector<CovidData *> &vec) {
  double avg = 0;
  int count = 0;
  for (int i = 0; i < vec.size(); i++) {
    avg += vec[i]->getActiveCases();
  }
  avg = avg / vec.size();
  for (int i = 0; i < vec.size(); i++) {
    if (vec[i]->getActiveCases() > avg)
      count++;
  }
  cout << count << endl;
}

void averagePercentageDays(const vector<CovidData *> &vec) {
  double avg = 0;
  double count = 0;
  for (int i = 0; i < vec.size(); i++) {
    avg += vec[i]->getActiveCases();
  }
  avg = avg / vec.size();
  for (int i = 0; i < vec.size(); i++) {
    if (vec[i]->getActiveCases() > avg) {
      count += (double)100 / vec.size();
    }
  }
  double value = (int)(count * 100 + .5);
  cout << (double)value / 100 << "%" << endl;
}

void groupCases(const vector<CovidData *> &vec) {
  int arr[4];
  for (int i = 0; i < 4; i++) {
    arr[i] = 0;
  }
  for (int i = 0; i < vec.size(); i++) {
    arr[(vec[i]->getActiveCases() / 1000) - 1]++;
  }
  cout << "=========================================" << endl;
  cout << "|1000-1999|2000-2999|3000-3999|4000-5000|" << endl;
  cout << "|—————————|—————————|—————————|—————————|" << endl;
  cout << "|" << display(arr[0]) << "|" << display(arr[1]) << "|"
       << display(arr[2]) << "|" << display(arr[3]) << "|" << endl;
  cout << "=========================================" << endl;
}

void printMax5days(const vector<CovidData *> &vec) {
  int max = vec[0]->getActiveCases();
  for (int i = 1; i < vec.size(); i++) {
    if ((i + 1) % 5 == 0) {
      cout << max << " ";
      max = 0;
    }
    if (max < vec[i]->getActiveCases())
      max = vec[i]->getActiveCases();
  }
  if (vec.size() % 5 != 0) {
    int number = vec.size() % 5;
    cout << "Do naslednjega izračuna je potrebnih še " << (5 - number) << "dni";
  }
  cout << endl;
}

void printNumberOfCasesBelowNumber(const vector<CovidData *> &vec, int number) {
  int count = 0;
  for (int i = 0; i < vec.size(); i++) {
    if (vec[i]->getActiveCases() < number)
      count++;
  }
  cout << count << endl;
}

vector<CovidData *> filterData(const vector<CovidData *> vec, int number) {
  vector<CovidData *> tmp;
  int count = 0;
  for (int i = 0; i < vec.size(); i++) {
    if (vec[i]->getActiveCases() > number)
      tmp.push_back(vec[i]);
  }
  return tmp;
}

void addData(vector<CovidData *> &vec) {
  time_t t = time(0);
  tm *now = localtime(&t);
  vec.push_back(new CovidData(31, now->tm_mon + 1, now->tm_year + 1900,
                              randGen(1000, 4500)));
	cout << "Data was added";
}

int main() {
  const unsigned int days = 30;
  vector<CovidData *> covidStats;
  // vector<unsigned int> activeCases;
  CovidData **objCovid;
  objCovid = new CovidData *[days];

  srand(time(NULL));

  bool running = true;
  int selection;

  do {
    menu();
    cin >> selection;
    if (selection != 1)
      cout << endl;
    switch (selection) {
    case 1:
      fillVector(covidStats, days);
      break;
    case 2:
      printVector(covidStats);
      break;
    case 3:
      averageCases(covidStats);
      break;
    case 4:
      averageDays(covidStats);
      break;
    case 5:
      averagePercentageDays(covidStats);
      break;
    case 6:
      groupCases(covidStats);
      break;
    case 7:
      printMax5days(covidStats);
      break;
    case 8:
      printNumberOfCasesBelowNumber(covidStats, 1500);
      break;
    case 9:
      addData(covidStats);
      break;
    case 10: {
      vector<CovidData *> tmp = filterData(covidStats, 4000);
      for (int i = 0; i < tmp.size(); i++) {
        cout << tmp[i]->toString() << endl;
      }
      break;
    }
    case 0:
      running = false;
      break;
    default:
      cout << "Wrong selection!" << endl;
      break;
    }
    cout << endl;
  } while (running);
  for (int i = 0; i < covidStats.size(); i++) {
    delete covidStats[i];
  }
  covidStats.clear();
  return 0;
}