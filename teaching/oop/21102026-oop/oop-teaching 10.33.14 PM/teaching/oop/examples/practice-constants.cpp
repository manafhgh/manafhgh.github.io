#include <iostream>
using namespace std;

int main() {
    int x=42, y=10;
    const int* const p=&x;
    cout << *p << " " << y << "\n";
    // *p=7; // Cannot change data through p.
    // p=&y; // Cannot change the address held in p.
}
