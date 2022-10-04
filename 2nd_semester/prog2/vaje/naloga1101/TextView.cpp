#include "TextView.h"

std::string TextView::getText() { return text; }
void TextView::setText(std::string text) { this->text = text; }
void TextView::draw() {
  View::draw();
  std::cout << "[TextView]: " << text << std::endl;
}
void TextView::print() {
  std::cout << "[TextView]: " << text << std::endl;
}