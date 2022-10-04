#include <iostream>
#include "Canvas.h"
#include "Rectangle.h"
#include "Text.h"

using namespace std;

int main() {
    srand(time(nullptr));

    Canvas canvas(500, 500);
    Color c1(0,0,0);
    Color c2(50,19,219);
    Color c3(50,181,48);
    Text *t1 = new Text(c1, 0, 0, 14, "Programiranje II Bonus naloga");
    Rectangle *r1 = new Rectangle(Color::red, 0, 10, 100, 50);
    Rectangle *r2 = new Rectangle(Color::green, 0, 80, 1000, 50);
    Rectangle *r3 = new Rectangle(c2, 0, 80, 100, 50);
    Rectangle *r4 = new Rectangle(c3, 0, 80, 100, 50);
		canvas.addShape(t1);
		canvas.addShape(r1);
		canvas.addShape(r2);
		canvas.addShape(r3);
		canvas.addShape(r4);
    canvas.draw();
    canvas.undo();
    canvas.draw();
    canvas.resize(100, 100);
    canvas.draw();

    return 0;
}
