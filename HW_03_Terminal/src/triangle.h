#include "two_dimensional_coordinate.h"
#include "shape.h"
#ifndef TRIANGLE_H
#define TRIANGLE_H
class Triangle: public Shape {
public:
    Triangle(std::vector<TwoDimensionalCoordinate*> vectors) {
        // If the triangle can't be successfully created,
        // handle the exception by throwing string "This is not a triangle!"
        if (vectors.size() == 3){
          double x1, x2, x3, y1, y2, y3, m, n, q;
          x1 = vectors[0] -> getX();
          y1 = vectors[0] -> getY();
          x2 = vectors[1] -> getX();
          y2 = vectors[1] -> getY();
          x3 = vectors[2] -> getX();
          y3 = vectors[2] -> getY();
          m = sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2));
          n = sqrt((x1 - x3)*(x1 - x3) + (y1 - y3)*(y1 - y3));
          q = sqrt((x3 - x2)*(x3 - x2) + (y3 - y2)*(y3 - y2));
          if(!(m + n > q && n + q > m && m + q > n))
              throw std::string("This is not a triangle!");
          _x1 = vectors[0] -> getX();
          _y1 = vectors[0] -> getY();
          _x2 = vectors[1] -> getX();
          _y2 = vectors[1] -> getY();
          _x3 = vectors[2] -> getX();
          _y3 = vectors[2] -> getY();
        }else{
          throw std::string("This is not a triangle!");
        }
    }

    double area() const {
        // return the area of the Triangle.
        return 0.5 * abs((_x1 * _y2 - _x2 * _y1) + (_x2 * _y3 - _x3 * _y2) + (_x3 * _y1 - _x1 * _y3));
    }

    double perimeter() const {
        // return the perimeter of the Triangle.
        return pow(pow(abs(_x1 - _x2),2) + pow(abs(_y1 - _y2),2),0.5) + pow(pow(abs(_x2 - _x3),2) + pow(abs(_y2 - _y3),2),0.5) + pow(pow(abs(_x3 - _x1),2) + pow(abs(_y3- _y1),2),0.5);
    }

    std::string info() const {
        // return the info of the Triangle.
        // ex. Triangle ([0.000, 0.000], [0.000, -3.141], [-4.000, 0.000])
        char string[100];
        sprintf(string, "Triangle ([%.3f, %.3f], [%.3f, %.3f], [%.3f, %.3f])", _x1, _y1, _x2, _y2, _x3, _y3);
        return std::string(string);
    }
private:
    double _x1, _y1, _x2, _y2, _x3, _y3;
};
#endif
