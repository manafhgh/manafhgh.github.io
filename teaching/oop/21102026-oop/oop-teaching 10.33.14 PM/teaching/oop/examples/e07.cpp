#include <iostream>
using namespace std;
int main() {
    int* empty = nullptr; // Initialize pointers; never dereference nullptr.
    cout << boolalpha << "Null pointer: " << (empty == nullptr) << '\n';
    int x = 5, y = 10;
    int* ptr = &x;
    cout << "*ptr: " << *ptr << '\n';
    *ptr = 100;
    cout << "x: " << x << '\n';
    ptr = &y; // ptr now points to y, rather than x.
    int* p2 = ptr; // Both pointers now point to y.
    cout << "Same address: " << (p2 == ptr) << '\n';
    int& num = x;
    num = y; // Copies y's value into x; it does not reseat num.
    cout << "x: " << x << " y: " << y << '\n';
    cout << "Alias has same address: " << (&num == &x) << '\n';
}
