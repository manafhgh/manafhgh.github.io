#include <iostream>
using namespace std;
class Node {
public:
    int value;
    Node* next;
    Node(int v, Node* n=nullptr) : value(v), next(n) {}
};
int countNodes(const Node* head) {
    // TODO: follow next links and count nodes until nullptr.
    (void)head;
    return 0;
}
void printChain(const Node* head) {
    // TODO: print each value followed by a space, then a newline.
    (void)head;
    cout << '\n';
}
int main() {
    Node a(10), b(20), c(30), extra(15);
    // TODO: connect a -> b -> c -> nullptr.
    printChain(&a);
    cout << "Count: " << countNodes(&a) << '\n';
    cout << "Empty count: " << countNodes(nullptr) << '\n';
    // TODO: insert extra after a without losing the rest of the chain.
    printChain(&a);
    cout << "After insertion: " << countNodes(&a) << '\n';
    return 0;
}
