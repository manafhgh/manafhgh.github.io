#include <iostream>
using namespace std;
void swapValue(int a, int b) {
    int temp = a; a = b; b = temp; // Only the local copies change.
    cout << "Inside swapValue: " << a << ' ' << b << '\n';
}
void swapReference(int& a, int& b) {
    int temp = a; a = b; b = temp; // a and b refer to the caller's variables.
}
int main() {
    int x = 5, y = 10;
    swapValue(x, y);
    cout << "After swapValue: " << x << ' ' << y << '\n';
    swapReference(x, y);
    cout << "After swapReference: " << x << ' ' << y << '\n';
}
