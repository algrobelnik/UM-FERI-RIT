#include "Rectangle.h"

bool Rectangle::InBounds(float canvasWidth, float canvasHeight){
	return width <= canvasWidth && height < canvasHeight;
}
void Rectangle::draw() const{
	if(visibility == Visibility::VISIBLE){
		cout << "[Rectangle] " << color.toString() << " Position(" << x << "," << y << ") width = " << width << ", height = " << height << endl;
	}
}
