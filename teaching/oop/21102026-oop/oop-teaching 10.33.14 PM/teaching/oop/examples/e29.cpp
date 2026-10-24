#include <iostream>
#include <string>
using namespace std;
class Person {
    string name;
public:
    explicit Person(string n) : name(n) {}
    void introduce() const { cout << "Name: " << name << '\n'; }
};
class Student : public Person {
public:
    explicit Student(string n) : Person(n) {}
    void study() const { cout << "Studying C++\n"; }
};
class Presenter {
public:
    void present() const { cout << "Presenting research\n"; }
};
class ResearchStudent : public Student, public Presenter {
public:
    explicit ResearchStudent(string n) : Student(n) {}
};
int main() {
    ResearchStudent s("Leila");
    s.introduce(); s.study(); s.present();
}
