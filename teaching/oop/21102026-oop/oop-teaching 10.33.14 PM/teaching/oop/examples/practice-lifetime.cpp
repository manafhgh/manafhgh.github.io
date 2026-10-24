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
    Point outer(1,1);
    { Point inner(2,2); }
    cout << "Back in outer scope\n";
}
