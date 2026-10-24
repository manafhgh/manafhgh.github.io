#include<iostream>
#include<string>
using namespace std;

class Student{
   private:
       string ID;
       string fname;
   protected:
       string lname;
   public:
       Student(string fn="NA",string ln="NA",string id="NA")
       {
           cout << "Base const.\n";
           ID=id;
           fname=fn;
           lname=ln;
       }
       void print() const {
           cout<< ID << " " << fname << " " << lname << endl;
       }


       virtual ~Student(){cout<<"Base DEST\n";}
};

//Derived or child or sub class
//type of inheritance here is public
//if it was not specified then it's
//considered private by default
class UnderGrad : public Student{
   public:
       UnderGrad(string tc, string fn, string ln, string id)
       :Student(fn,ln,id)//calling parent's constructor
                       //(otherwize, parent's default will be called,
                       //if that happens and there isn't a default
                       //constructor in the parent class, that would
                       //be a compilation error
       {
           cout << "Derived const.\n";
           trainingCompany =  tc;
       }
       void print() const {
           Student::print(); //calling print of base class
           cout << trainingCompany << endl;
       }

       ~UnderGrad()
       {cout<<"Derived DEST\n";}
   private:
       string trainingCompany;
};

int main()
{
   //Student s1("Mohammad", "Ali", "567");
   //s1.print();

   UnderGrad ugs1("ABC", "Leila", "Ali", "123");
   ugs1.print();

}
