#include "point.h"
#include <cmath>
Point::Point(double xx, double yy) : x(xx), y(yy) {}
double Point::distanceTo(const Point& other) const {
    double dx=other.x-x, dy=other.y-y;
    return std::sqrt(dx*dx+dy*dy);
}
