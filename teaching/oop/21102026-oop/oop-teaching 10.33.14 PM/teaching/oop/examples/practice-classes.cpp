#include <iostream>
#include <cmath>
using namespace std;
class Point {
private:
    double x, y;
public:
    Point(double xx = 0, double yy = 0) : x(xx), y(yy) {}
    void setX(double xx) { x = xx; }
    void setY(double yy) { y = yy; }
    double getX() const { return x; }
    double getY() const { return y; }
    void printPoint() const { cout << '(' << x << ',' << y << ")\n"; }
    double distanceToOrigin() const { return distanceMember(Point{}); }
    int whichQuadrant() const {
        if (x > 0 && y > 0) return 1;
        if (x < 0 && y > 0) return 2;
        if (x < 0 && y < 0) return 3;
        if (x > 0 && y < 0) return 4;
        return -1; // On an axis, including the origin.
    }
    double distanceMember(const Point& other) const {
        const double dx = other.x - x, dy = other.y - y;
        return sqrt(dx * dx + dy * dy);
    }
};
double distance(const Point& a, const Point& b) {
    const double dx = b.getX() - a.getX(), dy = b.getY() - a.getY();
    return sqrt(dx * dx + dy * dy);
}


int main() {
    Point a(3,4), b;
    cout << a.distanceToOrigin() << " " << b.distanceToOrigin() << "\n";
}
