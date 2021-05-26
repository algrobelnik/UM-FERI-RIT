#ifndef PLAYER_H
#define PLAYER_H

#include "GameObject.h"
#include <iostream>

using namespace std;

class Player : public GameObject {
private:
  string name;

public:
  Player(float x, float y, float width, float height, string name)
      : name(name), GameObject(x, y, width, height){};
  void draw() const {
    cout << "(" << x << "," << y << ")"
         << "[" << width << "-" << height << "] " << name;
  };
  void update() { x++; }
};

#endif // PLAYER_H