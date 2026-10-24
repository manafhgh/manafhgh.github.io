#include<iostream>
using namespace std;
//Functions
   //default arguments
   //Notes:
       //only trailing arguments (most right)
       // can have default values
       //Default arguments are used in place of
       // the missing trailing arguments 
void sum(int x, int y=10){
   cout << x+y << endl;
}
int main(){
   sum(5,20);//calls sum(5,20)
   sum(5);//calls sum(5,10)
   // sum(); // Intentional compile error: x has no default value.
}
