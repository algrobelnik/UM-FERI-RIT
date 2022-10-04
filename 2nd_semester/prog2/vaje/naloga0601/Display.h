#ifndef DISPLAY_H
#define DISPLAY_H

#include <iostream>
#include <vector>

using namespace std;

/*Naloga 0602
Popravi nalogo tako da demonstriraš uporabo.
 - Game ima razredno spremenljivko display
 - vse draw metode namesto na ekran pišejo na display 
 - while zanko ki kliče display clear, update in render, ter display draw vsakič ko pritisneš presledek.*/

class Display {
private:
  float width, height;
	vector<string> lines;

public:
  Display(float width, float height) : width(width), height(height){};
  void clear() {
		for(int i = 0; i < height; i++){
			for(int j = 0; j < width; j++){
				lines[i].insert(j, " ");
			}
		}
  };
  void writeXY(string str, float x, float y) {
		if (x < width && y < height) {
			lines[y].insert(x, str);
		}
	};
	void draw() {
		for(int i = 0; i < width; i++){
			for(int j = 0; j < height; j++){
				cout << lines[i][j];
			}
		}
	};
};

#endif // DISPLAY_H