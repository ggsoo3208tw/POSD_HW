#ifndef ITERATOR_H
#define ITERATOR_H

class Iterator {
public:
  virturl void first() = 0;
  virturl void next() = 0;
  virtual bool isDone() const = 0;
  virtual Shape* currentItem() const = 0;
};
#endif
