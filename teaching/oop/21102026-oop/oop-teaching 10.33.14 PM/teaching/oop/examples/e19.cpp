#include <iostream>
using namespace std;

class Node{
  public:
    int val;
    Node * next; 
//next is a pointer (not an object), 
//it will not invoke the Node constructor
    
    Node(int val, Node * next) {
      this->val = val;
      this->next = next;
    }
};


int main(){

    Node n1(100,nullptr);
    Node n2(500,nullptr);
    Node n3(700,nullptr);
    Node n0(300,&n1); 
    
    n1.next=&n2; //next of Node n1 points to Node n2 
                 //(i.e., contains the address of n2)
    n2.next=&n3;
    n3.next=nullptr; //next of n3 is is assigned nullptr
                     //(could also be: 0, NULL)
    //assigning null to a pointer means it does not point 
    //to any location in memory
    
    Node * curr = &n0;
    
    while(curr != nullptr){
      cout << curr->val << " ";
      curr = curr->next;
    }
    cout << "\n";
    return 0;
}
