#include <iostream>
#include <limits>
#include <string>
using namespace std;
int main() {
    int id = 0;
    string fullName;
    cout << "Enter ID on the first line, then full name on the next:\n";
    if (!(cin >> id)) {
        cerr << "Expected a numeric ID.\n";
        return 1;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    if (!getline(cin, fullName)) {
        cerr << "Expected a name on the next line.\n";
        return 1;
    }
    cout << id << " | " << fullName << '\n';
    return 0;
}
