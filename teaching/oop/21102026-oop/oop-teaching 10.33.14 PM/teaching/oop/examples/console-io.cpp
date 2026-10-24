#include <iostream>
#include <iomanip>
#include <string>
using namespace std;
int main() {
    string name;
    double grade = 0;
    cout << "Enter your full name:\n";
    if (!getline(cin, name)) {
        cerr << "Could not read the name.\n";
        return 1;
    }
    cout << "Enter a grade from 0 to 100:\n";
    if (!(cin >> grade) || !(grade >= 0 && grade <= 100)) {
        cerr << "Invalid grade.\n";
        return 1;
    }
    cout << fixed << setprecision(1);
    cout << name << ": " << grade << '\n';
    return 0;
}
