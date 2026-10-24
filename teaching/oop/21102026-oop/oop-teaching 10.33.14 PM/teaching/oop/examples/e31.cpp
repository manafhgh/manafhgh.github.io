#include <iostream>
using namespace std;

// - unary vs binary
// member vs non-member
// non-member as friend vs non-friend

class Point {
 protected:
   float x;
   float y;
  
 public:
   Point(float x=0, float y=0);
   void printPoint() const;

   Point(const Point&) = default; // Keep copy semantics explicit in this demonstration.
   Point & operator=(const Point &p){
     x=p.x;
     y=p.y;
     return *this;
   }

   //- as unuary and as a member function
   Point operator-() const {
     Point tmp;
     tmp.x  = -x;
     tmp.y  = -y;

     return tmp;
   }

   float getX()const {return x;}
   float getY()const {return y;}

   void setX(float x){this->x = x;}
   void setY(float y){this->y = y;}

/*
//- as binary and as a member function
   Point operator-(const Point &p) const {
     Point tmpP;
     tmpP.x = x - p.x;
     tmpP.y = y - p.y;

     return tmpP;
   }
*/
   bool operator==(const Point &p) const {
     if(x == p.x && y == p.y)
       return true;
     return false;
   }

   //friend Point operator-(const Point &, const Point &);

};

Point::Point(float x, float y){
 this->x = x;
 this->y = y;
}

void Point::printPoint() const {
 cout<<"(" <<x<<", " << y<< ")\n";
}



//- as binary and as a non-member (non-friend) function
Point operator-(const Point &pt1, const Point &pt2) {
     Point tmpP;
     tmpP.setX(pt1.getX() - pt2.getX());
     tmpP.setY(pt1.getY() - pt2.getY());

     return tmpP;
}

int main() {

 Point p1(2,4);
 Point p2(2,4);



 Point p3 = -p1; //unary - : interpreted as p1.operator-()
 p1.printPoint(); //p1 still the same
 p3.printPoint();

 p1.printPoint();
 p2.printPoint();
 Point p4 = p1-p2; // the compiler will interpret this as p1.operator-(p2) if operator- is implemented as a member function
 //and
 //as operator-(p1,p2) if operator- is implemented as a non-member function
 cout << "p1 - p2:\n";
 p4.printPoint();

 if(p1==p2)
   cout << "p1 equals p2\n";
 else
  cout << "p1 doesn't equal p2\n";

 //you can  call the overloaded operator functions explicitly. For example:
 if(p1.operator==(p2))
   cout << "p1 equals p2\n";
 else
  cout << "p1 doesn't equal p2\n"; 

 p4=p3=p2=p1;
  p1.printPoint();
  p2.printPoint();
  p3.printPoint();
  p4.printPoint();

}
