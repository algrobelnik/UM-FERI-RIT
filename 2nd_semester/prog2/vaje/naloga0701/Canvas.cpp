#include "Canvas.h"

Canvas::~Canvas(){
	int size=shapes.size();
	for(int i = size -1 ; i > -1; i--)
		delete shapes[i];
	shapes.clear();
}
bool Canvas::addShape(Shape2D* shape){
	if(shape->InBounds(width, height)){
		shapes.push_back(shape);
		return true;
	}
	return false;
}
void Canvas::resize(float width, float height){
	this->width = width;
	this->height = height;
	for(int i = 0; i < shapes.size(); i++){
		if(!shapes[i]->InBounds(width, height))
			shapes.erase(shapes.begin() + i);
	}
}
void Canvas::draw() const{
	cout << "================================" << endl;
	for(int i = 0; i < shapes.size(); i++){
		shapes[i]->draw();
	}
	cout << "================================" << endl;
}
void Canvas::undo(){
	shapes.pop_back();
}
