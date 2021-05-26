#include "Color.h"

Color Color::red = Color(255,0,0);
Color Color::green = Color(0,255,0);
Color Color::blue = Color(0,0,255);

Color::Color(unsigned int c, unsigned int m, unsigned int y, unsigned int k){
	r = 255 * (1-c/100)*(1-k/100);
	g = 255 * (1-m/100)*(1-k/100);
	b = 255 * (1-y/100)*(1-k/100);
}

unsigned int Color::getRed(){return r;}
unsigned int Color::getGreen(){return g;}
unsigned int Color::getBlue(){return b;}

string Color::toString() const{
	stringstream ss;
	ss << "Color(" << r << "," << g << "," << b << ")";
	return ss.str();
}

Color Color::generateRandomColor(){
	return Color(rand()% 256,rand()% 256,rand()% 256);
}
