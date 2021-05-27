#ifndef SMARTPOINTER_H
#define SMARTPOINTER_H

template <typename T>
class SmartPointer {
  private:
    T* pData;

  public:
    SmartPointer(T* d): pData(d){} 
    T& operator*() {
      return *pData;
    }
    T* operator->(){
      return pData;
    }
    ~SmartPointer(){
      delete pData;
    } 
};
#endif