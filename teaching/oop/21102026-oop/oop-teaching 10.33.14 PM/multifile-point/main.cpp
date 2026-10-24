#include "point.h"
#include <iostream>
int main() {
    Point origin, p(3,4);
    std::cout << p.distanceTo(origin) << '\n';
}
