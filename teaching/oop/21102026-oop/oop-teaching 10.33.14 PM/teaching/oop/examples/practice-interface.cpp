#include <iostream>
#include <cmath>
// point.h: normally protected by an include guard.
class Point {
    double x, y;
public:
    Point(double xx=0, double yy=0);
    double getX() const;
    double distanceTo(const Point& other) const;
};
// point.cpp: normally includes "point.h".
Point::Point(double xx, double yy) : x(xx), y(yy) {}
double Point::distanceTo(const Point& other) const {
    double dx=other.x-x, dy=other.y-y;
    return std::sqrt(dx*dx+dy*dy);
}
double Point::getX() const { return x; }
// main.cpp: normally includes "point.h".

int main() {
    Point p(3,4);
    std::cout << p.getX() << "\n";
}
