#include<iostream>
using namespace std;

class A{
friend class B;//can be placed anywhere in the class
public:
   A(){
       x=5;
   }
   void printX(){
       cout << x << endl;
   }
private:
   int x;
};

//all member function of class B are
//friend functions of class A
//they can access private, protected, and public
//members of class A
class B{
public:
   void changeX(A & a,int delta){
       a.x += delta;
   }
};

int main(){
   A a1;
   B b;

   b.changeX(a1,222);
   a1.printX();//prints 227
}
