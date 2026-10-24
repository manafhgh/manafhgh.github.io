#include <iostream>
#include <algorithm>
#include <stdexcept>
using namespace std;
class Student {
    int numberOfGrades;
    double* grades;
public:
    explicit Student(int n=3) : numberOfGrades(n), grades(nullptr) {
        if (n <= 0) throw invalid_argument("Grade count must be positive");
        grades = new double[n]{};
    }
    ~Student() { delete[] grades; }
    Student(const Student& other) : Student(other.numberOfGrades) {
        copy(other.grades, other.grades + numberOfGrades, grades);
    }
    Student& operator=(const Student& other) {
        if (this != &other) {
            // Allocate first: if allocation fails, this object's data survives.
            double* replacement = new double[other.numberOfGrades];
            copy(other.grades, other.grades + other.numberOfGrades, replacement);
            delete[] grades;
            grades = replacement;
            numberOfGrades = other.numberOfGrades;
        }
        return *this;
    }
    void setGrades(istream& in) {
        for (int i=0; i<numberOfGrades; ++i) {
            double value;
            if (!(in >> value) || !(value >= 0 && value <= 100))
                throw invalid_argument("Expected grades in [0,100]");
            grades[i] = value;
        }
    }
    void changeGrade(double delta, int index) {
        if (index < 0 || index >= numberOfGrades) throw out_of_range("Grade index");
        double value = grades[index] + delta;
        if (!(value >= 0 && value <= 100)) throw invalid_argument("Grade range");
        grades[index] = value;
    }
    double avg() const {
        double total=0;
        for (int i=0; i<numberOfGrades; ++i) total += grades[i];
        return total / numberOfGrades;
    }
    void printStudent() const {
        for (int i=0; i<numberOfGrades; ++i) cout << grades[i] << ' ';
        cout << "average: " << avg() << '\n';
    }
};

int main() {
    Student a(3); a.setGrades(cin);
    a=a;
    Student b; b=a; b.changeGrade(5,0);
    a.printStudent(); b.printStudent();
}
