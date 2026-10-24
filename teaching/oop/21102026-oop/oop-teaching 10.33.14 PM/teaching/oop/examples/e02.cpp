#include <iostream>
using namespace std;
//Note about functions that receives by reference:
//If you need to pass a literal value such as 5
//to the a function that receives by reference,
//then you need to store it in a variable and pass
//the variable,
//or specify the parameter as a reference to const
//data as in the function foo below:
void foo(const int &x){
   cout << x<<endl;
}

int main(){
   int a=10;
   foo(a);
   foo(10);
}
