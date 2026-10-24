#include <iostream>
#include <iomanip>
using namespace std;
int main() {
    double a=0,b=0;
    if (!(cin >> a >> b) || !(a>=0 && a<=100) || !(b>=0 && b<=100)) {
        cerr << "Invalid grades.\n";
        return 1;
    }
    cout << fixed << setprecision(1) << "Average: " << (a+b)/2.0 << '\n';
    return 0;
}
