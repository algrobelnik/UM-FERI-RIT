#ifndef IMAGEBUTTON_H
#define IMAGEBUTTON_H

#include "Button.h"
#include "ImageView.h"
#include <iostream>

class ImageButton : public Button, public ImageView {
  private:
  public:
    ImageButton(Position position, Size size, std::string text, std::string imgPath): Button(position, size, text), ImageView(position, size, imgPath){};
};
#endif