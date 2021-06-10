#ifndef IMAGEVIEW_H
#define IMAGEVIEW_H

#include "View.h"
#include <iostream>

class ImageView : public View {
private:
  std::string imgPath;

public:
  ImageView(Position position, Size size, std::string imgPath)
      : View(position, size), imgPath(imgPath) {}
  std::string getImgPath();
  void setImgPath(std::string imgPath);
  void draw();
  void print();
};
#endif