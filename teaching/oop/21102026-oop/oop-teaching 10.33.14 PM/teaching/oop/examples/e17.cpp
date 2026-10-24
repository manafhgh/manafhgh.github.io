#include<iostream>
#include<string>
using namespace std;

class Box{
private:
   const string color;
   float length;
   float width;
   float height;

   static int count; //declaration of a static data member
                     //we must define it outside the class
                     //static members are common to all objects
                     //there will be only one "count" data member
                     //regardless of how many objects are declared
                     //static members are independent of any object

public:
   Box(float length=1, float width =1, float height=1,string color="red")
   :color(color)//must use an initializer list
                //to initialize const data members
                //(before the body of theconstructor)
   {
       this->length = length; //this->length: length of the calling object
       this->width = width;
       this->height=height;
       count+=1;
   }

   Box(const Box& b):color(b.color) {
       length=b.length;
       width=b.width;
       height=b.height;
       count+=1;
   }

   ~Box() { --count; } // Track live objects, including copies.
   double volume() const
   {  
       return length*width*height;
   }

   // Demonstration only: changing the counter breaks its meaning as a count.
   void modifyCount() const{
       count = count * 2;//ok: const member functions CAN
                         //modify static data members
       //length = length * 2; //error: they cannot modify
                            //non-static data members
       //changeLength(5); //error: const member functions cannot
                        //call non-const member functions
       printData();//ok
   }

   void printData() const {
       cout << length << " " << width << " " << height
       << " " << color << endl;
       cout <<"count of Box objects: " << count <<endl;
   }

   void changeLength(float v) {
       length+=v;
   }

   static int getCount(){
       //cout << length; error: accessing non static member
       return count;
   }

};

int Box::count; //defining the static data member
               //by default, count will be initialized to zero


int main(){
   cout <<"Count: " << Box::getCount()<<endl;//accessing a static
                       //member using class name even before
                       //any object is declared
   const Box b1;
   Box b2(3,4,5,"Yellow");
   Box b3(b1);
   b3.printData();
   cout << "Count: " << b1.getCount() << endl; //accessing a static
                        //member using an object, we will get the
                        //same result if we use b2 or b3

}
