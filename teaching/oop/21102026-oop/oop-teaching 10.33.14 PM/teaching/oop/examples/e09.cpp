//Functions
   //static variables
   //scope rules
#include <iostream>
using namespace std;

int x = 5;//global

void fun(){

   cout << x << endl; //will print 5 (global x)
   int x=100;
   cout << x << endl; //will print 100 (local x)
   cout << ::x << "\n\n"; //will print 5 (global x)
}

void foo(){

   //Local non-static variables are declared and allocated memory
   //space every time the function is called
   //Static variable are declared using the keyword static
   //They have static storage duration and are initialized once.
   //they keep that space for the entirety of the program execution

   int x = 1;
   static int y=1; 

   cout << x << " " << y << endl;

   x++;
   y++;
}

int main(){
   fun();

   //what is the output of executing:
   foo();
   foo();
   foo();
}
