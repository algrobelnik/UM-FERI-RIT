#ifndef RAINDROP_H
#define RAINDROP_H

#include "GameObject.h"
#include "Game.h"
#include <iostream>

using namespace std;

class RainDrop : public GameObject {
private:
  float speedX, speedY;

public:
  RainDrop(float x, float y, float width, float height, float speedX, float speedY): speedX(speedX), speedY(speedY), GameObject(x, y, width, height){};
  void draw() const {
    cout << "(" << x << "," << y << ")"
         << "[" << width << "-" << height << "] " << "{" << speedX << ", " << speedX << "}";
		//Game::display->writeXY("*", x, y);
  };
  void update() { x += speedX; y += speedY; }
};

#endif // PLAYER_H