#include <iostream>
using namespace std;
//functions
   //Function overloading
float sumVals(float a){
   cout <<"float version\n";
   return a+a;
}

int sumVals(int a, int b){
   cout << "int version\n";
   return a+b;
}
int main() {
 cout << sumVals(2.5f) << endl;
 cout << sumVals(3, 4) << endl;
}
