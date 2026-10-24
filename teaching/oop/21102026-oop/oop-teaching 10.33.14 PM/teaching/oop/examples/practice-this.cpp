#include <iostream>
using namespace std;
class A {
    int x=5;
public:
    A& add(int amount) { x += amount; return *this; }
    A byValue() const { return *this; }
    A& byReference() { return *this; }
    void boo() { x += 55; }
    void print() const { cout << x << '\n'; }
};

int main() {
    A a; a.add(10).add(20); a.print();
}
