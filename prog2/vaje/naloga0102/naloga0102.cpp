#include <ctime>
#include <iostream>

using namespace std;

int randGen(int min, int max) {
  int range = max - min++;
  return rand() % range + min;
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
  cout << "0 ... EXIT" << endl;
  cout << "======================================" << endl;
  cout << "Select: ";
}

void fillArray(unsigned int *array, int days) {
  for (int i = 0; i < days; i++) {
    array[i] = randGen(1000, 5000);
  }
}

void printArray(const unsigned int *array, const unsigned int size) {
  for (unsigned int i = 0; i < size; i++) {
    cout << ((i > 0) ? ", " : "") << array[i];
  }
  cout << "." << endl;
}

void averageCases(const unsigned int *array, const unsigned int size) {
  double avg = 0;
  for (int i = 0; i < size; i++) {
    avg += array[i];
  }
  cout << avg / size << endl;
}

void averageDays(const unsigned int *array, const unsigned int size) {
  double avg = 0;
  int count = 0;
  for (int i = 0; i < size; i++) {
    avg += array[i];
  }
  avg = avg / size;
  for (int i = 0; i < size; i++) {
    if (array[i] > avg)
      count++;
  }
  cout << count << endl;
}

void averagePercentageDays(const unsigned int *array, const unsigned int size) {
  double avg = 0;
  double count = 0;
  for (int i = 0; i < size; i++) {
    avg += array[i];
  }
  avg = avg / size;
  for (int i = 0; i < size; i++) {
    if (array[i] > avg) {
      count += (double)100 / size;
    }
  }
  double value = (int)(count * 100 + .5);
  cout << (double)value / 100 << "%" << endl;
}

void groupCases(const unsigned int *array, const unsigned int size) {
  int arr[4];
  for (int i = 0; i < 4; i++) {
    arr[i] = 0;
  }
  for (int i = 0; i < size; i++) {
    arr[(array[i] / 1000) - 1]++;
  }
  cout << "=========================================" << endl;
  cout << "|1000-1999|2000-2999|3000-3999|4000-5000|" << endl;
  cout << "|—————————|—————————|—————————|—————————|" << endl;
  cout << "|" << display(arr[0]) << "|" << display(arr[1]) << "|"
       << display(arr[2]) << "|" << display(arr[3]) << "|" << endl;
  cout << "=========================================" << endl;
}

void printMax5days(const unsigned int *array, const unsigned int size) {
  int max = array[0];
  for (int i = 1; i < size; i++) {
    if ((i + 1) % 5 == 0) {
      cout << max << " ";
      max = 0;
    }
    if (max < array[i])
      max = array[i];
  }
  if (size % 5 != 0) {
    int number = size % 5;
    cout << "Do naslednjega izračuna je potrebnih še " << (5 - number) << "dni";
  }
  cout << endl;
}

void printNumberOfCasesBelowNumber(const unsigned int *array,
                                   const unsigned int size, int number) {
  int count = 0;
  for (int i = 0; i < size; i++) {
    if (array[i] < number)
      count++;
  }
  cout << count << endl;
}

int main() {
  const unsigned int days = 31;
  unsigned int *activeCases = new unsigned int[days];

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
      fillArray(activeCases, days);
      break;
    case 2:
      printArray(activeCases, days);
      break;
    case 3:
      averageCases(activeCases, days);
      break;
    case 4:
      averageDays(activeCases, days);
      break;
    case 5:
      averagePercentageDays(activeCases, days);
      break;
    case 6:
      groupCases(activeCases, days);
      break;
    case 7:
      printMax5days(activeCases, days);
      break;
    case 8:
      printNumberOfCasesBelowNumber(activeCases, days, 1500);
      break;
    case 0:
      running = false;
      break;
    default:
      cout << "Wrong selection!" << endl;
      break;
    }
    cout << endl;
  } while (running);

  delete[] activeCases;

  return 0;
}