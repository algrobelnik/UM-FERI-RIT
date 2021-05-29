#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>
//#include <cmath>

void bubbleSortASC(std::vector<int> vec, int number) {
  for (int step = 0; step < number - 1; ++step) {
    for (int i = 0; i < number - step - 1; ++i) {
      if (vec[i] > vec[i + 1]) {
        std::swap(vec[i], vec[i + 1]);
      }
    }
  }
}

int randGen(int min, int max) {
  int range = max - min++;
  return rand() % range + min;
}

void generateVecRand(std::vector<int>& vec, int num1){
	vec.clear();
	for(int i = 0; i < num1; i++)
		vec.push_back(randGen(1, 150));
}

bool check(std::vector<int>& vec)
{
	for (int i = 1; i < vec.size(); i++){
		if(vec[i-1] > vec[i]) return false;
	}
	return true;
}

int split(std::vector<int>& vec, int a, int b)
{
	int pivot = vec[a];
	int li = a;
	int ri = b;
	while (li < ri){
		while(vec[li] <= pivot && li < b)li++;
		while(vec[ri] >= pivot && ri > a)ri--;
		if(li < ri) std::swap(vec[li], vec[ri]); 
	}
	std::swap(vec[a], vec[ri]);
	return ri;
}

int split_desc(std::vector<int>& vec, int a, int b)
{
	int pivot = vec[a];
	int li = a;
	int ri = b;
	while (li < ri){
		while(vec[li] >= pivot && li < b)li++;
		while(vec[ri] <= pivot && ri > a)ri--;
		if(li < ri) std::swap(vec[li], vec[ri]); 
	}
	std::swap(vec[a], vec[ri]);
	return ri;
}

int split_median(std::vector<int>& vec, int a, int b)
{
	int median = (b+a)/2;
	std::swap(vec[a], vec[median]);
	int pivot = vec[a];
	int li = a;
	int ri = b;
	while (li < ri){
		while(vec[li] <= pivot && li < b)li++;
		while(vec[ri] >= pivot && ri > a)ri--;
		if(li < ri) std::swap(vec[li], vec[ri]); 
	}
	std::swap(vec[a], vec[ri]);
	return ri;
}

void quickSort(std::vector<int>& vec, int a, int b, int sort)
{
	
	/* std::vector<int> tmp;
	generateVecRand(tmp, 10000);
	quickSort(tmp, 0, tmp.size(),1); */
	if (a < b){
		int tmp;
		//if(sort == 1)tmp = split(vec, a, b);
		switch(sort){
			case 0: tmp = split_desc(vec, a, b); break;
			case 1: tmp = split(vec, a, b); break;
			case 2: tmp = split_median(vec, a, b); break;
			default: tmp = split(vec, a, b); break;
		}
		quickSort(vec, a, tmp-1, sort);
		quickSort(vec, tmp+1, b, sort);
	}
}

void menu() {
  std::cout << "======================================" << std::endl;
  std::cout << "================ MENU ================" << std::endl;
  std::cout << "======================================" << std::endl;
  std::cout << "1) Generate random sequence" << std::endl;
  std::cout << "2) Generate ascending sequence" << std::endl;
  std::cout << "3) Generate descending sequence" << std::endl;
  std::cout << "4) Print sequence" << std::endl;
  std::cout << "5) Check if sequence is sorted" << std::endl;
  std::cout << "6) Quicksort without median" << std::endl;
  std::cout << "7) Quicksort with median" << std::endl;
  std::cout << "8) Other sorting alorithm" << std::endl;
  std::cout << "0) End" << std::endl;
  std::cout << "======================================" << std::endl;
  std::cout << "Select: ";
}

int main() {
	srand(time(nullptr));
	std::chrono::time_point<std::chrono::system_clock> start, end;
  bool running = true;
  int selection, num1;/*, num2;
  std::string str1; */
	std::vector<int> vec;
  do {
    menu();
    std::cin >> selection;
    switch (selection) {
    case 1:{
			std::cout << "Size: ";
			std::cin >> num1;
			generateVecRand(vec, num1);
      break;
		}
    case 2:{
			std::cout << "Size: ";
			std::cin >> num1;
			generateVecRand(vec, num1);
			quickSort(vec,0,vec.size()-1, 1);
      break;
		}
    case 3:{
			std::cout << "Size: ";
			std::cin >> num1;
			generateVecRand(vec, num1);
			quickSort(vec,0,vec.size()-1, 0);
      break;
		}
    case 4: {
      for(int i = 0; i < vec.size(); i++){
				std::cout << vec[i] << " ";
			}
			std::cout << std::endl;
      break;
    }
    case 5: {
      if(check(vec)) std::cout << "Sequence is sorted";
			else std::cout << "Sequence is not sorted";
      break;
    }
    case 6: {
			start = std::chrono::system_clock::now();
			quickSort(vec,0,vec.size()-1, 1);
			end = std::chrono::system_clock::now();
			std::cout << "Elapsed time[µs]: " << std::chrono::duration_cast<std::chrono::microseconds> (end - start).count() << std::endl;
      break;
    }
    case 7: {
			start = std::chrono::system_clock::now();
			quickSort(vec,0,vec.size()-1,2);
			end = std::chrono::system_clock::now();
			std::cout << "Elapsed time[µs]: " << std::chrono::duration_cast<std::chrono::microseconds> (end - start).count() << std::endl;
      break;
    }
    case 8: {
			start = std::chrono::system_clock::now();
			bubbleSortASC(vec,vec.size());
			end = std::chrono::system_clock::now();
			std::cout << "Elapsed time[µs]: " << std::chrono::duration_cast<std::chrono::microseconds> (end - start).count() << std::endl;
      break;
    }
    case 0:
      running = false;
      break;
    default:
      std::cout << "Wrong selection!" << std::endl;
      break;
    }
    std::cout << std::endl;
  } while (running);
  return 0;
}