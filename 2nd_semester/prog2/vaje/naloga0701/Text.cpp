#include "Text.h"

bool Text::InBounds(float canvasWidth, float canvasHeight){
	return (fontSize * text.size()) < canvasWidth && (fontSize * text.size()) < canvasHeight;
}
void Text::draw() const{
	if(visibility == Visibility::VISIBLE){
		cout << "[Text] Position(" << x << "," << y << ") " << text << endl;
	}
}
