#include <iostream>
#include <string>
using namespace std;
class Student {
private:
    string name;
    int grade;
public:
    Student(string studentName, int initialGrade=0) : name(studentName), grade(0) {
        setGrade(initialGrade);
    }
    string getName() const { return name; }
    int getGrade() const { return grade; }
    bool setGrade(int value) {
        // TODO: accept values from 0 to 100 inclusive.
        // TODO: preserve the old grade if value is invalid.
        (void)value;
        return false;
    }
};
int main() {
    Student a("Amal",85), b("Lina");
    cout << a.getName() << ": " << a.getGrade() << '\n';
    cout << b.getName() << ": " << b.getGrade() << '\n';
    bool accepted=a.setGrade(120);
    cout << boolalpha << "Accepted 120: " << accepted << '\n';
    cout << "Amal's grade is still " << a.getGrade() << '\n';
    return 0;
}
