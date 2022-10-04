#include "View.h"

Position View::getPosition() { return position; }
void View::setPosition(Position position) { this->position = position; }
Size View::getSize() { return size; }
void View::setSize(Size size) { this->size = size; }
bool View::isVisible() { return visible; }
void View::setVisible(bool visible) { this->visible = visible; }
void View::draw() {
  std::cout << position.toString() << std::endl;
  std::cout << size.toString() << std::endl;
  std::cout << "[View]: " << visible << std::endl;
}
void View::print() {
  std::cout << position.toString() << std::endl;
  std::cout << size.toString() << std::endl;
  std::cout << "[View]: " << visible << std::endl;
}