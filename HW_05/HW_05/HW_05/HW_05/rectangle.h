#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "shape.h"

#include <string>
using namespace std;

class Rectangle : public Shape {
public:
    Rectangle(string id, double length, double width) :Shape(id) {
        // If the rectangle can't be successfully created,
        // handle the exception by throwing string "This is not a rectangle!"
        if (width <= 0 || length <= 0)
            throw string("This is not a rectangle!");
        _width = width;
        _length = length;
    }

    Rectangle(string id, double length, double width, string color) :Shape(id, color) {
        // If the rectangle can't be successfully created,
        // handle the exception by throwing string "This is not a rectangle!"
        if (width <= 0 || length <= 0)
            throw string("This is not a rectangle!");
        _width = width;
        _length = length;
    }

    double area() const {
        // return the area of the Rectangle.
        return _width * _length;
    }

    double perimeter() const {
        // return the perimeter of the Rectangle.
        return (_width + _length) * 2;
    }

    string info() const {
        // return the info of the Rectangle.
        // ex. Rectangle (3.712, 4.000)
        string toStringWidth = to_string(_width);
        string toStringLength = to_string(_length);
        toStringWidth.erase(toStringWidth.find('.') + 4);
        toStringLength.erase(toStringLength.find('.') + 4);
        string result = "Rectangle (" + toStringWidth + ", " + toStringLength + ")";
        return result;
        //return std::str(boost::format("Rectangle(%.3f, %.3f)") % _width % _length);
    }

    string type() const {
        return string("Rectangle");
    }
private:
    //data members
    double _width, _length;
};
#endif
