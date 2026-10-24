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
    int size = 5;
    double* values = new double[size]{}; // Value-initialize every element to zero.
    values[0] = 10; values[1] = 22.44;
    *(values + 3) = 11.11;
    for (int i=0; i<size; ++i) cout << values[i] << ' ';
    cout << '\n';
    delete[] values;
    values = nullptr; // Avoid retaining this dangling pointer.
    int* ptr = new int(300);
    cout << *ptr << '\n';
    delete ptr; // Release the allocation before reusing ptr.
    int x = 333;
    ptr = &x; // Non-owning pointer to a local object. Do not delete ptr now.
    cout << *ptr << '\n';
    Point p1(4,15), p2(30,40);
    Point* a = new Point;
    Point* b = new Point(p1);
    a->printPoint(); b->printPoint();
    delete a; delete b;
    Point* points = new Point[5]{{2,3}, {20,40}, p2};
    points[4] = p1;
    for (int i=0; i<5; ++i) points[i].printPoint();
    delete[] points;
}
