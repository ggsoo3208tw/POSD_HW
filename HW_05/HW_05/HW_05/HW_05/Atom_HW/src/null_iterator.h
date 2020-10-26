#ifndef NULLITERATOR_H
#define NULLITERATOR_H

#include "iterator.h"

class NULLIterator : public Iterator {
public:
  void first() {
    throw std::string "No child member!";
  }
  void next() {
    throw std::string "No child member";
  }
  void isDone() const {
    return true;
  }
  Shape* currentItem() const {
    throw std::string "No child member";
  }
};
#endif
