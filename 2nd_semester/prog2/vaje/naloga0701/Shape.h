#ifndef SHAPE2D_H
#define SHAPE2D_H
#include <iostream>
#include <vector>
#include "Color.h"

using namespace std;

enum class Visibility{VISIBLE, INVISIBLE};

class Shape2D{
	protected:
		Color color;
		Visibility visibility;
	public:
		Shape2D(Color color, Visibility visibility): color(color){visibility = Visibility::VISIBLE;};
		~Shape2D() = default;
		void setVisibility(Visibility visibility): visibility(visibility){};
		virtual bool InBounds(float canvasWidth, float canvasHeight) = 0;
		virtual void draw() const = 0;
};

#endif