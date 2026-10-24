#include <iostream>
using namespace std;
class Point {
private:
    int x, y;
public:
    Point(int initialX=0, int initialY=0) : x(initialX), y(initialY) {}
    int getX() const { return x; }
    int getY() const { return y; }
    void setX(int value) { x=value; }
    void setY(int value) { y=value; }
    void moveBy(int dx, int dy) { x+=dx; y+=dy; }
    void print() const { cout << '(' << x << ',' << y << ")\n"; }
};
int main() {
    Point p1(2,3), p2;
    p1.print();
    p2.print();
    p2.setX(8);
    p1.moveBy(1,-1);
    p1.print();
    p2.print();
    return 0;
}
