#include <iostream>
using namespace std;
class Point {
    double x, y;
public:
    Point(double xx=0, double yy=0) : x(xx), y(yy) {
        cout << "Construct "; printPoint();
    }
    Point(const Point& p) : x(p.x), y(p.y) {
        cout << "Copy "; printPoint();
    }
    ~Point() { cout << "Destroy "; printPoint(); }
    void printPoint() const { cout << '(' << x << ',' << y << ")\n"; }
};
void byValue(Point p) { cout << "In byValue "; p.printPoint(); }
void byReference(const Point& p) { cout << "In byReference "; p.printPoint(); }
int main() {
    Point p1(1, 2);
    byValue(p1);
    byReference(p1);
    Point p2(p1); // Explicit copy construction.
}
