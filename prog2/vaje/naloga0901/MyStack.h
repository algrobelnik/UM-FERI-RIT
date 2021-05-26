#ifndef MYSTACK_H
#define MYSTACK_H

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "../naloga0502/Date.h"

float randGen(int min, int max) {
  int range = max - min++;
  return rand() % range + min;
}

template <typename T>
class MyStack {
private:
  std::vector<T> values;
  std::string name;
  int len;

public:
  MyStack(std::string name) : name(name), len(0) {}
  bool empty(){
    return values.empty();
  };
  int size(){
    return len;
  };
  T top(){
    return values.back();
  };
  void push(T el){
    len++;
    values.push_back(el);
  };
  bool pop(){
    if(values.empty())
      return false;
    else{
      len--;
      values.pop_back();
      return true;
    }
  };
  bool popX(int x){
    if(len < x){
      return false;
    }
    else{
      for(int i = 0; i < x; i++){
        len--;
        values.pop_back();
      }
      return true;
    }
  };
  std::vector<T> backX(int x){
    std::vector<T> out;
    for (int i = 0; i < x; i++){
      if(len > i)out.push_back(values[len-i-1]);
      else break;
    }
    return out;
  };
  void pushX(std::vector<T> in){
    for(T i: in)
      values.push_back(i);
  };
  void reverse(){
    for(int i = len-1; i > -1; i--)
      std::cout << values[i] << " ";
    std::cout << std::endl;
  };
  void addXToAll(T val){
    for(int i = 0; i < len; i++)
      values[i] += val;
  };
  void deleteRandomElements(){
    int size = len;
    for(int i = 0; i < size; i++){
      if(randGen(-1,1)){
        len--;
        values[i];
      }
    }
  };
  void sort(){
    sort(values.begin(), values.end());
  };
  std::string toString() const{
    std::stringstream ss;
    ss << "[" << name << "]";
    for(int i = 0; i < len; i++){
      ss << (i>0?", ":" ") << values[i];
    }
    return ss.str();
  };
};

template <>
class MyStack<Date> {
private:
  std::vector<Date> values;
  std::string name;
  int len;

public:
  MyStack(std::string name) : name(name), len(0) {}
  bool empty(){
    return values.empty();
  };
  int size(){
    return len;
  };
  Date top(){
    return values.back();
  };
  void push(Date el){
    len++;
    values.push_back(el);
  };
  bool pop(){
    if(values.empty())
      return false;
    else{
      len--;
      values.pop_back();
      return true;
    }
  };
  bool popX(int x){
    if(len < x){
      return false;
    }
    else{
      for(int i = 0; i < x; i++){
        len--;
        values.pop_back();
      }
      return true;
    }
  };
  std::vector<Date> backX(int x){
    std::vector<Date> out;
    for (int i = 0; i < x; i++){
      if(len > i)out.push_back(values[len-i-1]);
      else break;
    }
    return out;
  };
  void pushX(std::vector<Date> in){
    for(Date i: in)
      values.push_back(i);
  };
  std::string toString() const{
    std::stringstream ss;
    ss << "[" << name << "]";
    for(int i = 0; i < len; i++){
      ss << (i>0?", ":" ") << values[i].toString();
    }
    return ss.str();
  };
};

#endif
