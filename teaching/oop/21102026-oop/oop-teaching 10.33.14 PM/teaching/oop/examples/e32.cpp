#include <iostream>
#include <string>
using namespace std;
class Student {
    string name;
    double grade;
public:
    Student(string n, double g=0) : name(n), grade(g) {}
    Student& operator++() { ++grade; return *this; } // Prefix.
    Student operator++(int) { // Postfix: unnamed dummy int distinguishes it.
        Student old(*this);
        ++(*this);
        return old;
    }
    friend ostream& operator<<(ostream& out, const Student& s) {
        return out << s.name << ' ' << s.grade;
    }
    friend istream& operator>>(istream& in, Student& s) {
        double value;
        if (in >> value) s.grade=value;
        return in;
    }
};
int main() {
    Student s("Hazem",65);
    cout << "Postfix result: " << s++ << '\n';
    cout << "After postfix: " << s << '\n';
    cout << "Prefix result: " << ++s << '\n';
    if (!(cin >> s)) { cerr << "Expected a numeric grade\n"; return 1; }
    cout << "After input: " << s << '\n';
}
