#ifndef UTILITY_H
#define UTILITY_H

#include "shape.h"
#include "iterator.h"
#include "shape_iterator.h"

#include <list>
#include <string>
#include <deque>
using namespace std;

Shape* getShapeById(Shape* shape, string id) {
    // access the shape with iterator pattern.
    // DO NOT use Type Checking or Dynamic Type that would violate OCP to implement the function.
    // return a shape under the input shape tree sturcture that matches the id.
    // throw std::string "Only compound shape can get shape!" when the input shape is not iterable.
    // throw std::string "Expected get shape but shape not found" when no shape found with the given id.
    Iterator* it = shape->createIterator();
    if(it->isDone()) throw string("Only compound shape can get shape!");
    for(it->first();!it->isDone();it->next()){
      if (it->currentItem()->id() == id) {
          return it->currentItem();
      }
      Iterator* ita = it->currentItem()->createIterator();
      if (!ita->isDone()) {
        try {
          return getShapeById(it->currentItem(), id);
        }catch (string e) {
        }
      }
    }
    throw string("Expected get shape but shape not found");
    //return shape->getShapeById(id);
}


template <class Filter>
deque<Shape*> filterShape(Shape* shape, Filter filter) {
    // access the shape with iterator pattern.
    // DO NOT use Type Checking or Dynamic Type that would violate OCP to implement the function.
    // return the shapes under the input shape tree sturcture that match the given filter.
    // throw std::string "Only compound shape can filter shape!" when the input shape is not iterable.
    deque<Shape*> _shape;
    //cout << "The filterShape is call and Shape => " << shape->info() << endl;
    Iterator* it = shape->createIterator();
    try {
        it->currentItem();
    }catch(string e){
        throw string("Only compound shape can filter shape!");
    }
    for (it->first(); !it->isDone(); it->next()) {
        //cout << it->currentItem()->type() << " : " << it->currentItem()->id() << " , " << it->currentItem()->info() << " , " << it->currentItem()->area() <<  " , " << it->currentItem()->perimeter() <<  " , " << it->currentItem()->color() << endl;
        if (filter(it->currentItem())) {
            _shape.push_back(it->currentItem());
        }
        Iterator* ita = it->currentItem()->createIterator();
        if (!ita->isDone()) {
            deque<Shape*> getDequeShape = filterShape(it->currentItem(), filter);
            for (deque<Shape*>::iterator ita = getDequeShape.begin(); ita != getDequeShape.end(); ita++) {
                _shape.push_back(*ita);
            }
        }
    }
    return _shape;
}

class AreaFilter {
public:
    AreaFilter(double upperBound, double lowerBound):_upperBound(upperBound), _lowerBound(lowerBound) {}
    bool operator() (Shape* shape) const {
      //cout << "_upperBound = " << _upperBound << " , " << "_lowerBound = " << _lowerBound << endl;
      return (shape->area() <= _upperBound) && (shape->area() >= _lowerBound);
    }
private:
    double _upperBound, _lowerBound;
};

class PerimeterFilter {
public:
    PerimeterFilter(double upperBound, double lowerBound) :_upperBound(upperBound), _lowerBound(lowerBound) {}
    bool operator() (Shape* shape) const {
        //cout << "_upperBound = " << _upperBound << " , " << "_lowerBound = " << _lowerBound << endl;
        return (shape->perimeter() <= _upperBound) && (shape->perimeter() >= _lowerBound);
    }
private:
    double _upperBound, _lowerBound;
};

class ColorFilter {
public:
    ColorFilter(string color):_color(color) {}
    bool operator() (Shape* shape) const {
      //cout << "_color = " << _color << endl;
      return shape->color() == _color;
    }
private:
    string _color;
};

class TypeFilter {
public:
    TypeFilter(string type):_type(type) {}
    bool operator() (Shape* shape) const {
      //cout << "_type = " << _type << endl;
      return shape->type() == _type;
    }
private:
    string _type;
};

#endif
