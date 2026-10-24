#include <iostream>
using namespace std;
int main() {
    int* p=nullptr;
    int* alias=nullptr;
    p=new int(7);
    alias=p;
    *alias=12;
    cout << "Allocation A: " << *p << '\n';
    delete p; // Releases the int, not the pointer variables.
    // Both p and alias are now dangling: do not dereference either one.
    p=nullptr; // Does not change alias.
    alias=nullptr;
    int* values=new int[3]{1,2,3};
    values[1]=9;
    cout << "Array: ";
    for (int i=0;i<3;++i) cout << values[i] << (i==2?'\n':' ');
    delete[] values; // Match new[] with delete[].
    values=nullptr;
    cout << "All allocations released; pointers reset.\n";
    return 0;
}
