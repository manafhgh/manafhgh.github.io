#ifndef POINT_H
#define POINT_H
class Point {
    double x, y;
public:
    Point(double xx=0, double yy=0);
    double distanceTo(const Point& other) const;
};
#endif
