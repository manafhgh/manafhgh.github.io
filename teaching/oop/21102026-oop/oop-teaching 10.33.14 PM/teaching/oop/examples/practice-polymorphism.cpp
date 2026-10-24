#include <iostream>
#include <string>
using namespace std;


// Base class
class Animal {
 private:
   string species;
 protected:
   int numberOfLegs;
 public:
   Animal(string s= "Animal",int n = 0){
     cout<< "Base constructor\n";
     species = s;
     numberOfLegs = n;
   }

   //pure virtual function
   //have the form:
   //virtual type functionName(paramList) = 0;
   //with no implementation
   //they make the class abstract
   //we cannot instantiate objects of an Abstract class
   //if pure virtual functions are not overridden
   //in a derived class, then the derived class inherits
   //the pure virtual function and becomes abstract itself
   virtual ~Animal() = default;
   virtual void makeSound() = 0;
   //{cout << "Animals make sounds!\n" ;}

   //no need to override getSpecies in derived classes
   //this base class method will function correctly
   //for all objects of the derived classes
   //(i.e., it will return the correct species)
   string getSpecies() const {
     return species;
   }
};

// Derived class
class Cat : public Animal {
 private:
   bool likesWetFood = true;
 public:
   Cat():Animal("Felis catus",4){cout<<"Cat constructor\n";}

   void makeSound() override {
     cout << "Meow!\n" ;
   }

   void purr(){
     cout << "Feeling good!\n";
   }

};

// Derived class
class Dog : public Animal {
 public:
   Dog():Animal("Canis lupus",4) {cout<<"Dog constructor\n";}

   void makeSound() override {
     cout << "Woof!\n" ;
   }

   void bringNewsPaper(){
     cout << "Woof, here's your wet newspaper!\n";
   }
};


//derived class
class Penguin : public Animal {
 public:
 Penguin() : Animal("Aptenodytes forsteri",2) {}
 void swim(){cout << "Look at that fish\n";}
 void makeSound() override {cout<<"It's too cold here!\n";}
};


class Cow : public Animal {
public:
    Cow() : Animal("Bos taurus",4) {}
    void makeSound() override { cout << "Moo!\n"; }
};
int main() {
    Cow cow; Animal* animal=&cow; animal->makeSound();
}
