#include <iostream>

class Shape {
   public:
       virtual ~Shape() = default;
       virtual void draw() = 0;
};

class Rectangle : public Shape {
   public:
       void draw() override {
           std::cout << "Drawing a rectangle" << std::endl;
       }
};

class Circle : public Shape {
   public:
       void draw() override {
           std::cout << "Drawing a circle" << std::endl;
       }
};

int main() {

   // Upcasting
   Shape* shape_ptr = new Circle();

   // Downcasting (this would work)
   // because we are casting a base pointer
   // that points to Rectangle object
   // to a Rectangle pointer
   Rectangle* rectangle_ptr = dynamic_cast<Rectangle*>(shape_ptr);
   if (rectangle_ptr) {
       rectangle_ptr->draw();
   } else {
       std::cout << "Could not cast shape_ptr to a Rectangle" << std::endl;
   }

   // Downcasting (this will not work)
   // because we are casting a base pointer
   // that points to Rectangle object
   // to a Circle pointer 
   Circle * circle_ptr = dynamic_cast<Circle*>(shape_ptr);
   if (circle_ptr) {
       circle_ptr->draw();
   } else {
       std::cout << "Could not cast shape_ptr to a Circle" << std::endl;
   }

   delete shape_ptr;
   return 0;
}
