#include <iostream>
#include <cmath>
// point.h: normally protected by an include guard.
class Point {
    double x, y;
public:
    Point(double xx=0, double yy=0);
    double distanceTo(const Point& other) const;
};
// point.cpp: normally includes "point.h".
Point::Point(double xx, double yy) : x(xx), y(yy) {}
double Point::distanceTo(const Point& other) const {
    double dx=other.x-x, dy=other.y-y;
    return std::sqrt(dx*dx+dy*dy);
}
// main.cpp: normally includes "point.h".
int main() {
    Point origin, p(3,4);
    std::cout << p.distanceTo(origin) << '\n';
}
