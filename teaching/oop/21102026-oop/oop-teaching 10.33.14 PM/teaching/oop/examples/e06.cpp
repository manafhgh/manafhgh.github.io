#include <iostream>
using namespace std;

//Functions
  //Recursion

void printN(int n){
   if(n<=0)
       return;   
   printN(n-1);
   cout << n << " ";

}

int sum(int n){
   if(n<=0)
       return 0;
   return n+sum(n-1);
}

int main(){
   printN(5);
   cout << endl;

   int result = sum(10);
   cout << result << endl;
}
