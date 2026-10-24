#include<iostream>
using namespace std;

//introduction
//functions
   //call by address (using pointers)

void swapVal(int *a, int *b){
   int t = *a;
   *a = *b;
   *b = t;
}

int main(){
  
   int x=5,y=10;
   swapVal(&x, &y);
   cout << x << " " << y << endl;
}
