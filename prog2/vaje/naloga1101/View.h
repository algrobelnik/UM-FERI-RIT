#ifndef VIEW_H
#define VIEW_H

#include "Position.h"
#include "Size.h"
#include <iostream>

class View {
protected:
  Position position;
  Size size;
  bool visible;

public:
  View(Position position, Size size) : position(position), size(size), visible(true) {}
  Position getPosition();
  void setPosition(Position position);
  Size getSize();
  void setSize(Size size);
  bool isVisible();
  void setVisible(bool visible);
  virtual void draw();
  virtual void print();
};
#endif