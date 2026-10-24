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
   Point operator+() const { return *this; }
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
    Point p(2,4); Point copy=+p;
    cout << boolalpha << (copy==p) << "\n";
}
