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
int countEven(const int a[], int n) {
    if (n <= 0) return 0;
    return (a[n-1] % 2 == 0 ? 1 : 0) + countEven(a,n-1);
}
int main() {
    int values[5]={1,2,5,0,0};
    cout << countEven(values,5) << "\n";
}
