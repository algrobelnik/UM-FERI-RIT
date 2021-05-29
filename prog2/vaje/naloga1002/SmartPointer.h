#ifndef SMARTPOINTER_H
#define SMARTPOINTER_H

#include "ReferenceCounter.h"
#include <iostream>

template <typename T> class SmartPointer {
private:
  T *pData;
  ReferenceCounter *refCounter;

public:
  SmartPointer(T *d) {
    refCounter = new ReferenceCounter();
    (*refCounter)++;
    pData = d;
  }
  SmartPointer(const SmartPointer &other)
      : pData(other.data), refCounter(other.refCounter) {
    (*refCounter)++;
  }
  T &operator*() { return *pData; }
  T *operator->() { return pData; }
  SmartPointer &operator=(const SmartPointer &s) {
    if (this->pData == s.pData) {
      ReferenceCounter::NoOfEqualExpressions++;
      return *this;
    }
    if (refCounter->count == 1) {
      std::cout << "Deleting: " << pData << std::endl;
      delete pData;
    }
    pData = s.pData;
    // std::cout << s.refCounter->count << std::endl;
    (*s.refCounter)++;
    // std::cout << s.refCounter->count << std::endl;
    refCounter = s.refCounter;
    return *this;
  }
  unsigned int useCount() { return refCounter->count; }
  ~SmartPointer() {
    if (refCounter->count <= 0) {
      delete pData;
      delete refCounter;
    }
    --(*refCounter);
  }
};

#endif