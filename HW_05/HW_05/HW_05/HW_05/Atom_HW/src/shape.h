#ifndef SHAPE_H
#define SHAPE_H

#include <string>
using namespace std;

class Shape {
public:
  Shape(string id); // interface for default color "white".
  Shape(string id, string color); // interface for color input by user.
  virtual double area() const = 0;
  virtual double perimeter() const = 0;
  virtual string info() const = 0;
  virtual string type() const = 0;
  string id() const; // return id of shape.
  string color() const; // return color of shape.
  virtual void addShape(Shape* shape); // throw std::string "Only compound shape can add shape!"
  virtual void deleteShapeById(string id); // throw std::string "Only compound shape can delete shape!"
  virtual Shape* getShapeById(string id) const; // throw std::string "Only compound shape can get shape!"
  virtual Iterator* createIterator() const;
  virtual ~Shape();
private:
  string _id, _color;
};
#endif
