#include <iostream>
using namespace std;

int main() {
    int x=5, y=10;
    int* a=&x; int* b=a;
    *a=20; cout << *b << "\n";
    a=&y; cout << *a << " " << *b << "\n";
}
