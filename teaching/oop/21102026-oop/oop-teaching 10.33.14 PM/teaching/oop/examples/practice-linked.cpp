
#include <iostream>
using namespace std;
class Node {
public:
    int value;
    Node* next;
    Node(int v, Node* n=nullptr) : value(v), next(n) {}
};
int countNodes(const Node* head) {
    int count=0;
    while (head!=nullptr) { ++count; head=head->next; }
    return count;
}
void printChain(const Node* head) {
    while (head!=nullptr) { cout << head->value << ' '; head=head->next; }
    cout << '\n';
}
int main() {
    Node a(10), b(20), c(30), extra(15);
    a.next=&b; b.next=&c; // c.next is already nullptr.
    printChain(&a);
    cout << "Count: " << countNodes(&a) << '\n';
    cout << "Empty count: " << countNodes(nullptr) << '\n';
    extra.next=a.next; // Preserve the old successor first.
    a.next=&extra;
    printChain(&a);
    cout << "After insertion: " << countNodes(&a) << '\n';
    return 0;
}
