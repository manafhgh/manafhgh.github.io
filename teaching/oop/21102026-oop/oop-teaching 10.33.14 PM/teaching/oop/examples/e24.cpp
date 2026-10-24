#include <iostream>
using namespace std;

// Must be known to TWO
// before declaration of ONE.
class ONE;

class TWO
{
public:
   void print(const ONE &x);
};

class ONE
{
   int a, b;
   friend void TWO::print(const ONE &x);

public:
   ONE() : a(1), b(2) {}
};

void TWO::print(const ONE &x)
{
   cout << "a is " << x.a << endl;
   cout << "b is " << x.b << endl;
}

int main()
{
   ONE xobj;
   TWO yobj;
   yobj.print(xobj);
}
