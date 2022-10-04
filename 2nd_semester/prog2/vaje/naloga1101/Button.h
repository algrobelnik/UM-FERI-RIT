#ifndef BUTTON_H
#define BUTTON_H

#include "TextView.h"
#include <iostream>

class Button : public TextView {
private:
  bool enabled;

public:
  Button(Position position, Size size, std::string text)
      : TextView(position, size, text), enabled(true) {}
  bool getEnabled();
  void setEnabled(bool enabled);
  void onClick();
  void draw() override;
  void print() override;
};
#endif