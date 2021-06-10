#include "Button.h"

bool Button::getEnabled() { return enabled; }
void Button::setEnabled(bool enabled) { this->enabled = enabled; }
void Button::onClick() {
  if (enabled)
    std::cout << "BUTTON CLICKED!" << std::endl;
}
void Button::draw() {
  TextView::draw();
  std::cout << "[Button]: " << enabled << std::endl;
}
void Button::print() {
  std::cout << "[" << getText() << "]" << std::endl;
}
