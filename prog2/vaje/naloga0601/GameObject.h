#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

using namespace std;

class GameObject {
protected:
  float x, y, width, height;

public:
  GameObject(float x, float y, float width, float height)
      : x(x), y(y), width(width), height(height){};
  virtual ~GameObject() = default;
  virtual void draw() const = 0;
  virtual void update() = 0;
};

#endif // GAMEOBJECT_H