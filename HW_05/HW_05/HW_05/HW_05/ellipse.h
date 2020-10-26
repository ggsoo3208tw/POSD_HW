#ifndef ELLIPSE_H
#define ELLIPSE_H
#include "shape.h"
#include <string>// string
using namespace std;

constexpr auto M_PI = 3.1415926;;

class Ellipse : public Shape {
public:
    Ellipse(string id, double semiMajorAxes, double semiMinorAxes) :Shape(id) {
        // If the ellipse can't be successfully created,
        // handle the exception by throwing string "This is not a ellipse!"
        if (semiMajorAxes <= 0 || semiMinorAxes <= 0) {
            throw std::string("This is not an ellipse!");
        }
        else {
            _semiMajorAxes = semiMajorAxes;
            _semiMinorAxes = semiMinorAxes;
        }
    }
    Ellipse(string id, double semiMajorAxes, double semiMinorAxes, string color) :Shape(id, color) {
        // If the ellipse can't be successfully created,
        // handle the exception by throwing string "This is not a ellipse!"
        if (semiMajorAxes <= 0 || semiMinorAxes <= 0) {
            throw std::string("This is not an ellipse!");
        }
        else {
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

    string info() const {
        // return the info of the Ellipse.
        // ex. Ellipse (3.712, 4.000)
        string toStringSemiMajorAxes = to_string(_semiMajorAxes);
        string toStringSemiMinorAxes = to_string(_semiMinorAxes);
        toStringSemiMajorAxes.erase(toStringSemiMajorAxes.find('.') + 4);
        toStringSemiMinorAxes.erase(toStringSemiMinorAxes.find('.') + 4);
        string result = "Ellipse (" + toStringSemiMajorAxes + ", " + toStringSemiMinorAxes + ")";
        return result;
    }

    string type() const {
        return string("Ellipse");
    }
private:
    //data member
    double _semiMajorAxes, _semiMinorAxes;
};
#endif