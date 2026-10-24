#include <iostream>
#include <string>
using namespace std;

class Student{
   friend ostream& operator<<(ostream &, const Student &);//allows the function operator<< to directly access class Student membrs

   private:
       const string name;
       float g;

   public:
       Student(string name,float g=0):name(name){
           this->g=g;
       }
  
       void modifyGrade(float x){
           g+=x;
       }

       bool operator>(const Student&s) const {
           return g > s.g;
       }

       float getGrade() const {return g;}

};

Student& operator+=(Student & s, float x){
           s.modifyGrade(x);
           return s;
}

ostream& operator<<(ostream & out, const Student & s){
   out << s.name << " " << s.g;
   return out;
}


bool operator==(float n, const Student & s){
   return n == s.getGrade();
}

int main(){
   Student s1("Samer",80);
   Student s2("Dalal",100);


   s1+=5; //s1.operator+=(5) if as member
   s1+=3; //as non-member: operaot+=(s1,3)

   cout << s1 << endl; // operator<<(cout,s1)
   s1+=-7;
   cout << s1 << endl; // operator<<(cout,s1)

   if(s1>s2) // Calls s1.operator>(s2).
       cout << s1;
   else if(s2>s1)
       cout << s2 << endl;
   else{
       cout<<s1<<s2<<endl<<"Done";
   }

   if(100 == s2) //if(operator==(100,s1))
       cout << "Perfect!\n";

   //cout << s1++; //s1.operator++(0)

   //cout << ++s1;//s1.operator()

}
