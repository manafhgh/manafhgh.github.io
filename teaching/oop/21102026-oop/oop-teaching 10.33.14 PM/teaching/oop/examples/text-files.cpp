#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
using namespace std;
int main() {
    // Default output mode replaces the file's previous contents.
    ofstream out("grades.txt");
    if (!out) {
        cerr << "Cannot create grades.txt in the working directory.\n";
        return 1;
    }
    // One whitespace-separated name and one grade per record.
    out << "Amal 85\nLina 92\n";
    out.close(); // Flush and close before opening a reader.
    if (!out) { cerr << "Writing the file failed.\n"; return 1; }

    ifstream in("grades.txt");
    if (!in) { cerr << "Cannot open grades.txt.\n"; return 1; }
    string name;
    double grade = 0, total = 0;
    int count = 0;
    // Read the name first so an incomplete trailing record is detectable.
    while (in >> name) {
        if (!(in >> grade)) {
            cerr << "Incomplete or invalid grade record.\n";
            return 1;
        }
        cout << name << ": " << grade << '\n';
        total += grade;
        ++count;
    }
    if (!in.eof()) { cerr << "Reading failed.\n"; return 1; }
    if (count > 0)
        cout << fixed << setprecision(1) << "Average: " << total/count << '\n';
    else
        cout << "No records.\n";
    return 0;
}
