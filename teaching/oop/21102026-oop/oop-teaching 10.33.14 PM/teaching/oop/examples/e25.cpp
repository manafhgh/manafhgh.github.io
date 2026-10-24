#include <iostream>
using namespace std;
class A {
    int x=5;
public:
    A byValue() const { return *this; }
    A& byReference() { return *this; }
    void boo() { x += 55; }
    void print() const { cout << x << '\n'; }
};
int main() {
    A a;
    a.byValue().boo(); // Modifies the temporary copy.
    a.print();
    a.byReference().boo(); // Modifies a.
    a.print();
}
