#ifndef LAYOUT_H
#define LAYOUT_H

#include "View.h"
#include <iostream>
#include <vector>
#include <memory>

class Layout {
private:
  std::vector<std::shared_ptr<View>> views;

public:
  Layout() {}
  void addView(std::shared_ptr<View> view);
  std::shared_ptr<View> getView(int position);
  void draw();
  void print();
};
#endif