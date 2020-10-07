#include <cmath>
#include "shape.h"
#ifndef ELLIPSE_H
#define ELLIPSE_H
class Ellipse: public Shape {
public:
    Ellipse(double semiMajorAxes, double semiMinorAxes) {
        // If the ellipse can't be successfully created,
        // handle the exception by throwing string "This is not a ellipse!"
        if(semiMajorAxes < semiMinorAxes || semiMajorAxes <= 0 || semiMinorAxes <= 0){
            throw std::string("This is not an ellipse!");
        }else{
          _semiMajorAxes = semiMajorAxes;
          _semiMinorAxes = semiMinorAxes;
        }
    }

    double area() const {
        // return the area of the Ellipse.
        return M_PI * _semiMajorAxes * _semiMinorAxes;
    }

    double perimeter() const {
        // return the perimeter of the Ellipse.
        return 2 * M_PI * _semiMinorAxes + 4 * (_semiMajorAxes - _semiMinorAxes);
    }

    std::string info() const {
        // return the info of the Ellipse.
        // ex. Ellipse (3.712, 4.000)
        char string[100];
        sprintf(string, "Ellipse (%.3f, %.3f)", _semiMajorAxes, _semiMinorAxes);
        return std::string(string);
    }
private:
    //data member
    double _semiMajorAxes, _semiMinorAxes;
};
#endif
