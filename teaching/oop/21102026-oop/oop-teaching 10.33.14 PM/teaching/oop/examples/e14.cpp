#include<iostream>
#include<string>
using namespace std;


class Student{
private:
   string fname;
   string lname;
   float gpa;

public:
   //parametrized constructor
   //Also callable as a default constructor; not a = default declaration.
   Student(string="NA",string="NA",float=0);

   //copy constructor
   Student(const Student &stC);
   Student& operator=(const Student&) = default; // Memberwise assignment is sufficient here.

   void print_student() const//you can define the function here or
                       //outside the class
   {
       cout << fname<<" " << lname << " " << gpa<<endl;
   }

   //setters
   void setGPA(float g); //or have the declaration here and
                         //the implementation outside the class
   void set_fname(string fn);
   void set_lname(string ln);
};

Student::Student(string fname,string lname,float g)
{
   this->fname=fname;
   this->lname=lname;
   gpa=0;
   setGPA(g);
   //cout<<"this from constructor: " << this << endl;
}

Student::Student(const Student &stC)
:fname(stC.fname),lname(stC.lname),gpa(stC.gpa)
{
   cout << "COPY CONSTRUCTOR\n";
}

void Student::setGPA(float g){
   if(g>=0&&g<=100) //some validation
       gpa=g;
   else
       cout << "Invalid GPA\n";
}

void Student::set_fname(string fn){
       fname=fn;
}

void Student::set_lname(string ln){
   lname = ln;
}

void printStArr(const Student st[], int size){
   for(int i=0;i<size;i++)
       st[i].print_student();
}

int main(){
   Student s1("Samah");

   const int SIZE=3;
   Student sec3[SIZE]={s1,Student("Salem","Adnan",70)};

   sec3[2]=Student("Maha","Salem",80);

   printStArr(sec3,SIZE);
}
