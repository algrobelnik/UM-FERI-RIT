#ifndef RECTANGLE_H
#define RECTANGLE_H
#include <iostream>
#include "Shape2D.h"
#include "Color.h"

using namespace std;

class Rectangle: public Shape2D{
	private:
		float x, y, width, height;
	public:
		Rectangle(const Color &color, float x, float y, float width, float height): x(x), y(y), width(width), height(height), Shape2D(color){};
		bool InBounds(float canvasWidth, float canvasHeight);
		void draw() const;
};

#endif