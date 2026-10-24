#include <iostream>
using namespace std;
int main() {
    int x=5, y=10;
    int* ptr=&x;
    int* p2=ptr;
    int& num=x; // An alias for x, not a separately reseatable pointer.
    *ptr=100;
    cout << "After *ptr=100: x=" << x << ", y=" << y << '\n';
    ptr=&y; // Reseat ptr; p2 still points to x.
    num=y;  // Copy y's value into x. num remains an alias for x.
    cout << "After num=y: x=" << x << ", y=" << y << '\n';
    *p2=42;
    ptr=nullptr;
    cout << "Final: x=" << x << ", y=" << y << '\n';
    cout << boolalpha << "ptr is null: " << (ptr==nullptr) << '\n';
    cout << "p2 still points to x: " << (p2==&x) << '\n';
    cout << "num still aliases x: " << (&num==&x) << '\n';
    return 0;
}
