#include <iostream>
using namespace std;
int main() {
    const int z = 11;
    int x = 400, y = 500;
    const int* ptr = &z;
    // *ptr = 22; // Compile error: cannot write through a pointer to const.
    ptr = &x; // Allowed: ptr itself is not const.
    cout << *ptr << '\n';
    int* const p = &x;
    *p = 66; // Allowed: x is not const.
    // p = &y; // Compile error: p cannot be reseated.
    const int* const both = &y;
    cout << *p << ' ' << *both << '\n';
}
