#include "Layout.h"

void Layout::addView(std::shared_ptr<View> view) { views.push_back(view); }
std::shared_ptr<View> Layout::getView(int position) { return views[position]; }
void Layout::draw() {
  for(std::shared_ptr<View> v: views){
    v->draw();
  }
}
void Layout::print() {
  for(std::shared_ptr<View> v: views){
    v->print();
  }
}