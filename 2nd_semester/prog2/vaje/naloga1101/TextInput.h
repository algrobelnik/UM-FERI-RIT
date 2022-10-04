#ifndef TEXTINPUT_H
#define TEXTINPUT_H

#include "TextView.h"
#include <iostream>

class TextInput : public TextView {
private:
  std::string name;
  int len;

public:
  TextInput(Position position, Size size, std::string name, int len, std::string text )
      : TextView(position, size, text), name(name), len(len) {}
  void setInputText(std::string val);
  void draw() override;
  void print() override;
};
#endif