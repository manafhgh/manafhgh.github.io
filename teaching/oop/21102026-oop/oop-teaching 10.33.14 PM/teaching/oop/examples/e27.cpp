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


int main() {
 //Animal animal1; //we can't define objects of an Abstract class
 Cat cat1;
 Dog dog1;
 Penguin peng1;

 cout << endl;
 cat1.makeSound(); // Virtual call on a known concrete object.
 dog1.makeSound();//we are calling makeSound from class Dog
 peng1.makeSound();
 cout << endl;
 cat1.purr();
 dog1.bringNewsPaper();
 peng1.swim();
 cout << endl;

 cout << cat1.getSpecies() << endl;
 cout << dog1.getSpecies() << endl;
 cout << peng1.getSpecies() << endl;


 //(late binding (dynamic linkage) vs early binding(static linkage)
 cout << "\n\n-----------------\n";
 Animal * ptr;
 ptr = &cat1;
 ptr->makeSound();
 //goes first to makeSound in Animal
 //because it is a virtual function
 //The final overrider is selected based on the
 //type of the object that ptr is pointing to (Cat in this case)
 cout << ptr->getSpecies()<< endl;

 Animal * ptrArr[3];//
 ptrArr[0] = &cat1;
 ptrArr[1] = &dog1;
 ptrArr[2] = new Cat();

 for (int i =0; i<3;i++)
   ptrArr[i]->makeSound();

 delete ptrArr[2]; // Only this element owns a dynamically allocated object.
}
