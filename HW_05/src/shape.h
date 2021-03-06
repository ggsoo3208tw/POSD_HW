#ifndef SHAPE_H
#define SHAPE_H

#include "iterator.h"
#include <string>
using namespace std;

class Shape {
public:
	Shape(string id);
	Shape(string id, string color);
	string id() const;
	string color() const;
	virtual double area() const = 0;
	virtual double perimeter() const = 0;
	virtual string info() const = 0;
	virtual string type() const = 0;
	virtual void addShape(Shape* shape);
	virtual void deleteShapeById(string id);
	virtual Shape* getShapeById(string id) const;
	virtual Iterator * createIterator() const;
	virtual ~Shape(); // "~"It's the destructor, it destroys the instance, frees up memory
private:
	string _id, _color;
};
#endif
