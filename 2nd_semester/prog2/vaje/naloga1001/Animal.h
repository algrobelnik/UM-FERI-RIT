#ifndef ANIMAL_H
#define ANIMAL_H

#include <iostream>
#include <ostream>

class Animal {
  friend std::ostream &operator<<(std::ostream &out, const Animal &a) {
    out << a.weight << " kg.";
    return out;
  }

private:
  double weight;

public:
  Animal(double weight) : weight(weight) {}
  Animal operator++(int dummy) {
    Animal *temp = new Animal(weight);
    weight += weight * 0.01;
    return *temp;
  }
  Animal operator++() {
    weight += weight * 0.01;
    return *this;
  }
};
#endif