#include "Button.h"
#include "ImageButton.h"
#include "ImageView.h"
#include "Layout.h"
#include "TextInput.h"
#include "TextView.h"
#include <iostream>
#include <memory>

using namespace std;

int main() {
  Layout *ly1 = new Layout();
  Position p1(10, 10), p2(20, 20), p3(30, 30), p4(40, 40), p5(50, 50),
      p6(60, 60), p7(70, 70), p8(80, 80), p9(90, 90), p10(100, 100);
  Size s1(10, 10, Unit::mm), s2(20, 20, Unit::mm), s3(30, 30, Unit::mm),
      s4(40, 40, Unit::mm), s5(50, 50, Unit::mm), s6(60, 60, Unit::px),
      s7(70, 70, Unit::px), s8(80, 80, Unit::px), s9(90, 70, Unit::px),
      s10(100, 100, Unit::px);
  std::shared_ptr<TextView> tw1 = std::make_shared<TextView>(p1, s1, "TEXT1");
  std::shared_ptr<TextView> tw2 = std::make_shared<TextView>(p2, s2, "TEXT2");
  std::shared_ptr<Button> bt1 = std::make_shared<Button>(p3, s3, "BUTTON1");
  std::shared_ptr<Button> bt2 = std::make_shared<Button>(p4, s4, "BUTTON2");
  std::shared_ptr<ImageView> iv1 =
      std::make_shared<ImageView>(p5, s5, "C:\\documents\\krneka.txt");
  std::shared_ptr<ImageButton> ib1 = std::make_shared<ImageButton>(
      p6, s6, "IMAGEBUTTON1", "C:\\documents\\notVirus.exe");
  ly1->addView(make_shared<TextView>(p1, s1, "TEXT1"));
  ly1->addView(make_shared<TextView>(p2, s2, "TEXT2"));
  ly1->addView(make_shared<Button>(p3, s3, "BUTTON1"));
  ly1->addView(make_shared<Button>(p4, s4, "BUTTON2"));
  ly1->addView(make_shared<ImageView>(p5, s5, "C:\\documents\\krneka.txt"));
  ly1->addView(static_cast<shared_ptr<Button>>(
      make_shared<ImageButton>(Position(0, 4), Size(10, 2, Unit::mm), "Potrdi",
                               "/../images/confirm.png")));
  ly1->draw();
  cout << "-----------------------------------------------------------" << endl;
  Layout *ly2 = new Layout();
  std::shared_ptr<TextInput> ti1 = std::make_shared<TextInput>(p6, s6, "Ime", 10, "Privzeto");
  std::shared_ptr<TextInput> ti2 = std::make_shared<TextInput>(p7, s7, "Priimek", 10, "Privzeto");
  std::shared_ptr<TextInput> ti3 = std::make_shared<TextInput>(p8, s8, "Leto", 10, "Privzeto");
  std::shared_ptr<Button> bt3 = std::make_shared<Button>(p9, s9, "OK");
  std::shared_ptr<Button> bt4 = std::make_shared<Button>(p10, s9, "CANCEL");
  ti1->draw();
  ti1->setInputText("0123456789AB");
  ti1->draw();
  ly2->addView(ti1);
  ly2->addView(ti2);
  ly2->addView(ti3);
  ly2->addView(bt3);
  ly2->addView(bt4);
  ly2->print();
  return 0;
}