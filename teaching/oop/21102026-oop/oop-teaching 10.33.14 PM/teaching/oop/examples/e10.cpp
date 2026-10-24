#include <iostream>
using namespace std;
void printArray(const int a[], int n) {
    for (int i = 0; i < n; ++i) cout << a[i] << ' ';
    cout << '\n';
}
int sumArray_iterative(const int a[], int n) {
    int total = 0;
    for (int i = 0; i < n; ++i) total += a[i];
    return total;
}
int sumArray_recursive(const int a[], int n) {
    if (n <= 0) return 0;
    return a[n - 1] + sumArray_recursive(a, n - 1);
}
int main() {
    constexpr int SIZE = 5;
    int a1[SIZE] = {1, 2, 5}; // {1, 2, 5, 0, 0}
    int a2[] = {1, 2, 5}; // Three elements, not five.
    printArray(a1, SIZE);
    cout << "a2 size: " << sizeof(a2) / sizeof(a2[0]) << '\n';
    cout << "Recursive sum: " << sumArray_recursive(a1, SIZE) << '\n';
    cout << "Iterative sum: " << sumArray_iterative(a1, SIZE) << '\n';
}
