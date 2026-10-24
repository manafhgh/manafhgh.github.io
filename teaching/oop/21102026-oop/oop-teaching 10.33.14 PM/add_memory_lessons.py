"""One-time migration for memory walkthroughs and the optional chain exercise."""
import json
from pathlib import Path
root=Path(__file__).resolve().parent/'teaching/oop'
topics=json.loads((root/'topics.json').read_text())
examples=json.loads((root/'content.json').read_text())
linked=next(t for t in topics if t['id']=='linked')
topics=[t for t in topics if t['id']!='linked']
for i,t in enumerate(topics):t['number']=i+1
def add(id,title,topic,note,code):
    examples.append(dict(id=id,title=title,topic=topic,note=note,code=code.strip()+'\n',stdin=''))
pointer_code=r'''
#include <iostream>
using namespace std;
int main() {
    int x=5, y=10;
    int* ptr=&x;
    int* p2=ptr;
    int& num=x; // An alias for x, not a separately reseatable pointer.
    *ptr=100;
    cout << "After *ptr=100: x=" << x << ", y=" << y << '\n';
    ptr=&y; // Reseat ptr; p2 still points to x.
    num=y;  // Copy y's value into x. num remains an alias for x.
    cout << "After num=y: x=" << x << ", y=" << y << '\n';
    *p2=42;
    ptr=nullptr;
    cout << "Final: x=" << x << ", y=" << y << '\n';
    cout << boolalpha << "ptr is null: " << (ptr==nullptr) << '\n';
    cout << "p2 still points to x: " << (p2==&x) << '\n';
    cout << "num still aliases x: " << (&num==&x) << '\n';
    return 0;
}
'''
dynamic_code=r'''
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
'''
add('memory-pointers','Run the pointer/reference walkthrough','pointers','This runnable trace matches the diagram’s statements. A pointer can change its target; assigning to a reference changes its original object.',pointer_code)
add('memory-dynamic','Run the allocation/deallocation walkthrough','dynamic','This trace matches the diagram and never dereferences a dangling pointer. Setting one pointer to nullptr does not reset copies of its address.',dynamic_code)
starter=r'''
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
'''
solution=starter.replace('    // TODO: follow next links and count nodes until nullptr.\n    (void)head;\n    return 0;', '    int count=0;\n    while (head!=nullptr) { ++count; head=head->next; }\n    return count;')
solution=solution.replace('    // TODO: print each value followed by a space, then a newline.\n    (void)head;', '    while (head!=nullptr) { cout << head->value << \' \'; head=head->next; }')
solution=solution.replace('    // TODO: connect a -> b -> c -> nullptr.', '    a.next=&b; b.next=&c; // c.next is already nullptr.')
solution=solution.replace('    // TODO: insert extra after a without losing the rest of the chain.', '    extra.next=a.next; // Preserve the old successor first.\n    a.next=&extra;')
add('linked-starter','Optional chain exercise starter','linked','The starter compiles but its traversal functions and links are incomplete. All nodes are local objects; do not use delete on them.',starter)
linked.update(title='Optional exercise: link objects into a chain',intro='Apply objects and pointer links after studying dynamic memory. This is an optional extension, not a separate core lesson.')
linked['question']='Does a next pointer own or automatically construct the Node it points to?'
linked['answer']='No. A pointer stores an address. In this exercise the nodes are local objects, so their lifetimes are controlled by their scopes. Do not delete them.'
linked['exercise'].update(example='linked-starter',task='Connect a(10), b(20), and c(30) into a chain ending in nullptr. Implement printChain and countNodes, including an empty chain. Then insert extra(15) after a while preserving b and c.',hint='Walk a const Node* until nullptr. For insertion, set extra.next to the old a.next before changing a.next to &extra.',solution=solution,explanation='The counts are 3, 0, and 4. The chains print 10 20 30 and then 10 15 20 30. Reversing the insertion assignments can create a self-loop or lose the remaining chain.')
linked['exercise'].pop('output',None)
def ps(code,x,y,ptr=None,p2=None,ref=False,note=''):
    return dict(code=code,x=x,y=y,ptr=ptr,p2=p2,ref=ref,note=note)
pointers=dict(id='pointers',title='Memory walkthrough: pointers and reference aliases',kind='pointers',
    intro='Step through the same statements used in the runnable walkthrough below. Arrows mean “stores the address of.” A reference is shown as another name on the object it aliases—not as a separately reseatable pointer.',
    steps=[
    ps('int x=5, y=10;',5,10,note='x and y are two separate int objects with automatic storage duration.'),
    ps('int* ptr = &x;',5,10,'x',note='ptr is a pointer object. Its value is the address of x. & takes an address; *ptr would access the int at that address.'),
    ps('int* p2 = ptr;',5,10,'x','x',note='Copying the pointer copies its address value, not the int. Both pointers now refer to x.'),
    ps('int& num = x;',5,10,'x','x',True,'num is another name for x. The language does not require a separate storage cell for this reference.'),
    ps('*ptr = 100;',100,10,'x','x',True,'Dereferencing ptr selects x. x becomes 100, and num observes that same object.'),
    ps('ptr = &y;',100,10,'y','x',True,'Reseating ptr changes only ptr. p2 and the reference num still refer to x.'),
    ps('num = y;',10,10,'y','x',True,'This copies 10 into x. It does not rebind num to y. Equal values do not mean two objects share storage.'),
    ps('*p2 = 42;',42,10,'y','x',True,'p2 still points to x, so x becomes 42. y remains 10.'),
    ps('ptr = nullptr;',42,10,'null','x',True,'ptr now has no target. x and y still exist. Never dereference a null pointer.')])
def ds(code,p,alias,a=None,array=None,values=None,note=''):
    return dict(code=code,p=p,alias=alias,allocation=a,array=array,values=values,note=note)
dynamic=dict(id='dynamic',title='Memory walkthrough: allocation, aliases, and deletion',kind='dynamic',
    intro='The pointer variables and dynamically allocated objects have separate lifetimes. “Heap” is the usual implementation term for dynamic storage; locations A and B are symbolic, not real addresses.',
    steps=[
    ds('int* p=nullptr; int* alias=nullptr;','null','null',note='Two pointer objects exist locally, but neither points to an allocation.'),
    ds('p = new int(7);','A','null',dict(live=True,value=7),note='new creates and initializes a dynamic int, then returns its address to p.'),
    ds('alias = p;','A','A',dict(live=True,value=7),note='Both pointers store the same address. There is still only one dynamically allocated int.'),
    ds('*alias = 12;','A','A',dict(live=True,value=12),note='The shared allocation changes to 12. Reading *p would also produce 12.'),
    ds('delete p;','dangling-A','dangling-A',dict(live=False),note='The int’s lifetime ends and its storage is released. p and alias still exist but are dangling; neither may be used to access the deleted int. The old value is deliberately no longer shown.'),
    ds('p = nullptr;','null','dangling-A',dict(live=False),note='Resetting p changes only p. alias is still dangling. Do not dereference it.'),
    ds('alias = nullptr;','null','null',dict(live=False),note='Both pointer objects are now null. Resetting pointers is separate from releasing an allocation.'),
    ds('int* values = new int[3]{1,2,3};','null','null',dict(live=False),dict(live=True,cells=[1,2,3]),'B',note='new[] creates a contiguous array of three int elements. values points to its first element.'),
    ds('values[1] = 9;','null','null',dict(live=False),dict(live=True,cells=[1,9,3]),'B',note='Index 1 is the second element. values[i] and *(values+i) refer to the same element within bounds.'),
    ds('delete[] values;','null','null',dict(live=False),dict(live=False),'dangling-B',note='delete[] releases the whole array. values still exists but is dangling. Match new[] with delete[], not delete.'),
    ds('values = nullptr;','null','null',dict(live=False),dict(live=False),'null',note='Both allocations have been released, and all three pointer variables have been reset. No pointer is dereferenced after deletion.')])
(root/'memory.json').write_text(json.dumps([pointers,dynamic],indent=2))
(root/'optional.json').write_text(json.dumps([linked],indent=2))
(root/'topics.json').write_text(json.dumps(topics,indent=2))
(root/'content.json').write_text(json.dumps(examples,indent=2))
for e in examples:(root/'examples'/f"{e['id']}.cpp").write_text(e['code'])
(root/'examples/practice-linked.cpp').write_text(solution)
print(len(topics),'core lessons;',len(examples),'examples; one optional chain exercise')
