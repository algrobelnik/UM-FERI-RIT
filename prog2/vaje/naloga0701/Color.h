#ifndef COLOR_H
#define COLOR_H
#include <iostream>
#include <sstream>

using namespace std;

class Color{
	private:
		unsigned int r, g ,b;
	public:
		static Color red, green, blue;
		Color(unsigned int r, unsigned int g, unsigned int b): r(r), b(b), g(g){};
		Color(unsigned int c, unsigned int m, unsigned int y, unsigned int k);
		unsigned int getRed();
		unsigned int getGreen();
		unsigned int getBlue();
		string toString() const;
		static Color generateRandomColor();
};

#endif