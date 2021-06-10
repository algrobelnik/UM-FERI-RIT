#include "TextInput.h"

void TextInput::setInputText(std::string val){
  if(val.size() > len){
    setText(val.substr(0,10));
  }else{
    setText(val);
  }
}
void TextInput::draw() {
  View::draw();
  std::cout << "[TextView]: " << getText() << std::endl;
}
void TextInput::print() {
  std::cout << name << ": " << getText() << std::endl;
}