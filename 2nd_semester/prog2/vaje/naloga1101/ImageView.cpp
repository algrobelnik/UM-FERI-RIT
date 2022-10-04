#include "ImageView.h"

std::string ImageView::getImgPath() { return imgPath; }
void ImageView::setImgPath(std::string imgPath) { this->imgPath = imgPath; }
void ImageView::draw() {
  View::draw();
  std::cout << "[ImageView]: " << imgPath << std::endl;
}
void ImageView::print() {
  std::cout << "[ImageView]: " << imgPath << std::endl;
}