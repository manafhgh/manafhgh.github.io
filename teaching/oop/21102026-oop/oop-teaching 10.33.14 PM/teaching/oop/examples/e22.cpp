// A friend function of two classes
// Add members of two different classes
// using friend functions

#include <iostream>
using namespace std;

// forward class declaration
class ClassB;

class ClassA {
   public:
      // constructor to initialize numA to 500
      ClassA() : numA(500) {}
    
  private:
      int numA;
    
  // friend function declaration
  // can be placed anywhere in the class
  // it would still mean the same
  friend int add(const ClassA &, const ClassB &);
};

class ClassB {

  public:
      // constructor to initialize numB to 166
      ClassB() : numB(166) {}
   private:
      int numB;
      // friend function declaration
      friend int add(const ClassA &, const ClassB &); 
};

// access members of both classes
int add(const ClassA &objectA, const ClassB &objectB) {
  return (objectA.numA + objectB.numB);
}

int main() {
  ClassA objectA;
  ClassB objectB;
  cout << "Sum: " << add(objectA, objectB) << endl;
  return 0;
}
