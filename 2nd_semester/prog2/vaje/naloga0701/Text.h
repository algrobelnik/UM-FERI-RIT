#ifndef TEXT_H
#define TEXT_H
#include <iostream>
#include "Shape2D.h"
#include "Color.h"

using namespace std;

class Text: public Shape2D{
	private:
		float x, y;
		unsigned int fontSize;
		string text;
	public:
		Text(const Color &color, float x, float y, unsigned int fontSize, string text): x(x), y(y), fontSize(fontSize), text(text), Shape2D(color){};
		bool InBounds(float canvasWidth, float canvasHeight);
		void draw() const;
};

#endif