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

long long factorial(int n) {
    if (n <= 1) return 1;
    return n * factorial(n-1);
}
int main() {
    cout << factorial(0) << " " << factorial(1) << " " << factorial(5) << "\n";
}
