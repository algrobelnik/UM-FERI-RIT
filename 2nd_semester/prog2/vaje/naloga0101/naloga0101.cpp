#include <iostream>
#include <math.h>

using namespace std;

void order3(int &a, int &b, int &c){
	if (a < c) 
		swap(a, c);

	if (a < b)
		swap(a, b);

	if (b < c)
		swap(b, c);
}

void swap(int &a, int &b){
	int temp = a;
	a = b;
	b = temp;
}

bool primeNum(int num) {
  if (num < 2)
    return false;
  else {
    for (int i = 0; i + 2 <= (sqrt(num)); i++) {
      if (num % (i + 2) == 0) {
        return false;
      }
    }
    return true;
  }
}

void primeOutput(int num) {
  if (num < 3) {
    cout << "The number is to small." << endl;
    return;
  }
  int count = 0;
  for (int i = 2; i < num; i++) {
    if (primeNum(i)) {
      if (count) {
        cout << ", " << i;
      } else {
        cout << i;
      }
      count++;
    }
  }
  if (!count) {
    cout << "No numbers were found.";
  }
  cout << endl;
}

int primeSum(int num) {
  int count = 0;
  int sum = 0;
  for (int i = 1; i < num; i++) {
    if (num % i == 0) {
      sum += i;
    }
  }
  return sum;
}

bool deficient(int num) { return primeSum(num) <= num; }

void printDeficientBetween(int lBound, int rBound){
	for(int i = lBound; i < rBound; i++){
		if(deficient(i)) cout << i << " ";
	}
	cout << endl;
}

int main() {
	int a=5;
  int b=10;
  int c=2;
	order3(a,b,c); //po referenci
  cout << a << " " << b << " " << c << endl; //10 5 2
	
	
	printDeficientBetween(10, 22);

  int number;
  do {
    cout << "Vnesite stevilo: ";
    cin >> number;
    cout << "Prastevila, ki so manjsa ali enaka stevilu " << number << ": ";
    primeOutput(number);
  } while (deficient(number));
  cout << "Stevilo " << number
       << " ni nezadostno stevilo. Zato se je program zakljucil." << endl;
  return 0;
}