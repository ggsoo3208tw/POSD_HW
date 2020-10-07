#include "shape.h"
#ifndef RECTANGLE_H
#define RECTANGLE_H
class Rectangle: public Shape {
public:
    Rectangle(double length, double width) {
        // If the rectangle can't be successfully created,
        // handle the exception by throwing string "This is not a rectangle!"
        if (width <= 0 || length <= 0)
            throw std::string("This is not a rectangle!");
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

    std::string info() const {
        // return the info of the Rectangle.
        // ex. Rectangle (3.712, 4.000)
        char string[100];
        sprintf(string, "Rectangle (%.3f, %.3f)", _length, _width);
        return std::string(string);
        //return std::str(boost::format("Rectangle(%.3f, %.3f)") % _width % _length);
    }
private:
    //data members
    double _width, _length;
};
#endif 
