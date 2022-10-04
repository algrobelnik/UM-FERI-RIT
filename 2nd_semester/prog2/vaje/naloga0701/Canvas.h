#ifndef CANVAS_H
#define CANVAS_H
#include <iostream>
#include <vector>
#include "Shape2D.h"

using namespace std;

class Canvas{
	private:
		float width, height;
		vector<Shape2D*> shapes;
	public:
		Canvas(float width, float height): width(width), height(height){};
		Canvas(float widthHeight): width(widthHeight), height(widthHeight){};
		~Canvas();
		bool addShape(Shape2D* shape);
		void resize(float width, float height);
		void draw() const;
		void undo();
};

#endif