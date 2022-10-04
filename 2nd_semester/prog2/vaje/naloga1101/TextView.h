#ifndef TEXTVIEW_H
#define TEXTVIEW_H

#include "View.h"
#include <iostream>

class TextView : public View {
private:
  std::string text;

public:
  TextView(Position position, Size size, std::string text)
      : View(position, size), text(text) {}
  std::string getText();
  void setText(std::string text);
  void draw() override;
  void print() override;
};
#endif