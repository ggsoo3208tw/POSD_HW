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
    try {
        Shape* _shape;
        _shape = shape->getShapeById(id);
        return _shape;
    }
    catch (string e) {
        cout << e << endl;
    }
    throw string("Expected get shape but shape not found");
}

deque<Shape*> _shape;
template <class Filter>
deque<Shape*> filterShape(Shape* shape, Filter filter) {
    // access the shape with iterator pattern.
    // DO NOT use Type Checking or Dynamic Type that would violate OCP to implement the function.
    // return the shapes under the input shape tree sturcture that match the given filter.
    // throw std::string "Only compound shape can filter shape!" when the input shape is not iterable.
    Iterator* it = shape->createIterator();
    try {
        it->currentItem();
        for (it->first(); !it->isDone(); it->next()) {
            if (filter(it->currentItem())) {
                _shape.push_back(it->currentItem());
            }
            Iterator* ita = it->currentItem()->createIterator();
            if (!ita->isDone()) { //若為 Compound Shape則繼續下去
                cout << "This is Compound Shape!." << endl;
                try {
                    filterShape(it->currentItem(), filter);
                    return _shape;
                }
                catch (string e) {
                    //cout << e << endl;
                }
            }
        }
        return _shape;
    }catch (string e) {
        throw string("Only compound shape can filter shape!");
    }
}

class AreaFilter {
public:
    AreaFilter(double upperBound, double lowerBound):_upperBound(upperBound), _lowerBound(lowerBound) {}
    bool operator() (Shape* shape) const {
        if (shape->area() <= _upperBound && shape->area() >= _lowerBound) {
            return true;
        }
        else {
            return false;
        }
    }
private:
    double _upperBound, _lowerBound;
};

class PerimeterFilter {
public:
    PerimeterFilter(double upperBound, double lowerBound) :_upperBound(upperBound), _lowerBound(lowerBound) {}
    bool operator() (Shape* shape) const {
        if (shape->perimeter() <= _upperBound && shape->perimeter() >= _lowerBound) {
            return true;
        }
        else {
            return false;
        }
    }
private:
    double _upperBound, _lowerBound;
};

class ColorFilter {
public:
    ColorFilter(string color):_color(color) {}
    bool operator() (Shape* shape) const {
        if (shape->color() == _color) {
            return true;
        }
        else {
            return false;
        }
    }
private:
    string _color;
};

class TypeFilter {
public:
    TypeFilter(string type):_type(type) {}
    bool operator() (Shape* shape) const {
        if (shape->type() == _type) {
            return true;
        }
        else {
            return false;
        }
    }
private:
    string _type;
};

#endif