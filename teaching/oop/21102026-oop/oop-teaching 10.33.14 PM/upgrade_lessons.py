"""One-time content migration: Revision group, I/O, and Classes model lesson."""
import json
from pathlib import Path
root=Path(__file__).resolve().parent/'teaching/oop'
examples=json.loads((root/'content.json').read_text())
topics=json.loads((root/'topics.json').read_text())
examples=[e for e in examples if e['id'] not in {'console-io','mixed-input','text-files','point-basics','student-validation'}]
topics=[t for t in topics if t['id'] not in {'console-io','text-files'}]
for e in examples:e.pop('origin',None)
for t in topics[:6]: t['group']='revision'
def example(id,title,topic,note,code,stdin=''):
    e=dict(id=id,title=title,topic=topic,note=note,code=code.strip()+'\n',stdin=stdin)
    examples.append(e);return e
console=example('console-io','Read a name and a numeric grade','console-io','getline reads a complete line, including spaces. Formatted extraction with >> converts numeric input. Check the stream before using a value.',r'''
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;
int main() {
    string name;
    double grade = 0;
    cout << "Enter your full name:\n";
    if (!getline(cin, name)) {
        cerr << "Could not read the name.\n";
        return 1;
    }
    cout << "Enter a grade from 0 to 100:\n";
    if (!(cin >> grade) || !(grade >= 0 && grade <= 100)) {
        cerr << "Invalid grade.\n";
        return 1;
    }
    cout << fixed << setprecision(1);
    cout << name << ": " << grade << '\n';
    return 0;
}
''','Manaf Gharaibeh\n85.5\n')
example('mixed-input','Mix >> and getline without losing a line','console-io','After extracting the ID, ignore discards the rest of that input line, including its newline. Without it, getline would read the leftover newline as an empty line.',r'''
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
''','123\nLeila Ali\n')
files=example('text-files','Write records, close the file, then read them','text-files','ofstream writes and ifstream reads. The example creates its own input file during the same run, so it does not need an uploaded file. It reads only complete records and checks for malformed input.',r'''
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
''')
def new_topic(id,title,intro,e,question,answer,task,hint,solution,explanation,lesson):
    return dict(id=id,title=title,intro=intro,group='revision',question=question,answer=answer,lesson=lesson,
        exercise=dict(id='practice-'+id,example=e['id'],task=task,hint=hint,solution=solution,explanation=explanation,stdin=e['stdin']))
io_topic=new_topic('console-io','Console input and output','Read complete lines, validate numeric input, and format results.',console,
    'What is the difference between cin >> name and getline(cin, name)?',
    '>> reads one whitespace-delimited word. getline reads up to the newline and can retain spaces inside a full name.',
    'Read two grades in [0,100]. Print their average with one digit after the decimal point. Reject nonnumeric or out-of-range input.',
    'Use double values, test both extractions, then apply fixed and setprecision(1).',r'''
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
''','With input 80 91, the output is Average: 85.5. Integer division is avoided by using double.',
'''<div class="lesson-copy"><h4>Streams carry data</h4><p>Include <code>&lt;iostream&gt;</code> for <code>std::cin</code>, <code>std::cout</code>, and <code>std::cerr</code>. The operator <code>&lt;&lt;</code> inserts data into an output stream; <code>&gt;&gt;</code> extracts and converts input. Chain operations to read or print several values.</p><p><code>std::getline(cin, name)</code> reads a full line. After numeric extraction, a newline may remain in the stream; the second example shows how to discard that line before using <code>getline</code>.</p><p>Always check extraction before using input. A failed conversion sets a stream error state. An interactive retry loop would call <code>cin.clear()</code> and discard the invalid line before trying again. These small programs report an error and stop instead.</p><p><code>&lt;iomanip&gt;</code> supplies <code>fixed</code> and <code>setprecision</code>. With <code>fixed</code>, precision means the number of digits after the decimal point. In this page, enter all input in the input box before Run; prompts do not open an interactive terminal.</p></div>''')
io_topic['exercise']['stdin']='80 91\n'
file_solution=files['code'].replace('out << "Amal 85\\nLina 92\\n";', 'out << "Amal 85\\nLina 92\\n";').replace('    ifstream in("grades.txt");','    ofstream append("grades.txt", ios::app);\n    if (!append) { cerr << "Cannot append.\\n"; return 1; }\n    append << "Omar 78\\n";\n    append.close();\n    if (!append) { cerr << "Appending failed.\\n"; return 1; }\n\n    ifstream in("grades.txt");')
file_topic=new_topic('text-files','Reading and writing text files','Use file streams and check that opening, writing, and reading succeed.',files,
    'Why is while (!in.eof()) a poor way to read records?',
    'eof() describes a previous operation; it does not predict the next read. Test the extraction itself so you do not process stale data after a failed read.',
    'After writing Amal 85 and Lina 92, append Omar 78 using ios::app. Read all three records and print their average.',
    'Close the first output stream, open a second one with ios::app, close it, then open the input stream.',
    file_solution,'The names and grades are printed, followed by Average: 85.0. Opening with ios::app preserves the existing records.',
'''<div class="lesson-copy"><h4>A file stream has an open/close lifetime</h4><p>Include <code>&lt;fstream&gt;</code>. Use <code>ofstream</code> to write, <code>ifstream</code> to read, or <code>fstream</code> for both. Once open, a file stream uses the same <code>&lt;&lt;</code>, <code>&gt;&gt;</code>, and <code>getline</code> operations as console streams.</p><p>The relative path <code>grades.txt</code> is resolved from the program’s working directory, which may differ from the directory containing its source. Check <code>if (!stream)</code> after opening. Close the writer before reading so buffered data is flushed. A stream also closes automatically when its object goes out of scope.</p><p>Normal <code>ofstream</code> opening truncates an existing file. Add <code>ios::app</code> to append instead. The record format below permits single-word names; use a line-based format or a delimiter if names can contain spaces.</p><p><strong>Online files are temporary.</strong> This example writes and reads its own file in one run. It does not access files on your computer, and a later Run starts a separate sandbox. Download the program to keep its generated file locally: <code>g++ -std=c++17 example.cpp -o example</code>, then <code>./example</code>. If the online service blocks file access, use that local workflow.</p></div>''')
topics=topics[:6]+[io_topic,file_topic]+topics[6:]
for i,t in enumerate(topics):t['number']=i+1
classes=next(t for t in topics if t['id']=='classes');classes['title']='Classes and Objects';classes['model']=True
classes['intro']='Learn to model state and behavior, construct independent objects, and protect their data through a clear interface.'
example('point-basics','Point: build two independent objects','classes','Run this after predicting the output. Each object has its own x and y values. The same member functions operate on the object named to the left of the dot.',r'''
#include <iostream>
using namespace std;
class Point {
private:
    int x, y;
public:
    Point(int initialX=0, int initialY=0) : x(initialX), y(initialY) {}
    int getX() const { return x; }
    int getY() const { return y; }
    void setX(int value) { x=value; }
    void setY(int value) { y=value; }
    void moveBy(int dx, int dy) { x+=dx; y+=dy; }
    void print() const { cout << '(' << x << ',' << y << ")\n"; }
};
int main() {
    Point p1(2,3), p2;
    p1.print();
    p2.print();
    p2.setX(8);
    p1.moveBy(1,-1);
    p1.print();
    p2.print();
    return 0;
}
''')
student=r'''
#include <iostream>
#include <string>
using namespace std;
class Student {
private:
    string name;
    int grade;
public:
    Student(string studentName, int initialGrade=0) : name(studentName), grade(0) {
        setGrade(initialGrade);
    }
    string getName() const { return name; }
    int getGrade() const { return grade; }
    bool setGrade(int value) {
        if (value < 0 || value > 100) return false;
        grade=value;
        return true;
    }
};
int main() {
    Student a("Amal",85), b("Lina");
    cout << a.getName() << ": " << a.getGrade() << '\n';
    cout << b.getName() << ": " << b.getGrade() << '\n';
    bool accepted=a.setGrade(120);
    cout << boolalpha << "Accepted 120: " << accepted << '\n';
    cout << "Amal's grade is still " << a.getGrade() << '\n';
    return 0;
}
'''
example('student-validation','Student: protect a grade invariant','classes','An invariant is a rule that should remain true for every valid object. Here grade always stays in [0,100]. Invalid updates return false and preserve the previous value. An invalid initial grade leaves the fallback grade of 0.',student)
# Basics appear first; retain the more advanced Point example as an extension.
classes_examples=[e for e in examples if e['topic']=='classes']
examples=[e for e in examples if e['topic']!='classes']
pos=next(i for i,e in enumerate(examples) if e['topic']=='lifetime')
examples[pos:pos]=sorted(classes_examples,key=lambda e:{'point-basics':0,'student-validation':1,'e11':2}[e['id']])
starter=student.replace('        if (value < 0 || value > 100) return false;\n        grade=value;\n        return true;', '        // TODO: accept values from 0 to 100 inclusive.\n        // TODO: preserve the old grade if value is invalid.\n        (void)value;\n        return false;')
tests=r'''
#undef main
int main() {
    int passed=0;
    auto check=[&](bool ok, const char* label) {
        cout << (ok ? "PASS: " : "FAIL: ") << label << '\n';
        if (ok) ++passed;
    };
    Student a("Amal");
    check(a.getName()=="Amal" && a.getGrade()==0,"Default grade and name");
    Student b("Lina",85);
    check(b.getGrade()==85,"Constructor accepts a valid grade");
    bool low=b.setGrade(0); bool lowOk=low && b.getGrade()==0;
    bool high=b.setGrade(100);
    check(lowOk && high && b.getGrade()==100,"Both boundaries: 0 and 100");
    bool rejectedLow=!b.setGrade(-1);
    bool rejectedHigh=!b.setGrade(101);
    check(rejectedLow && rejectedHigh && b.getGrade()==100,"Invalid updates preserve the previous grade");
    Student c("Omar",150);
    check(c.getGrade()==0,"Invalid initial grade keeps safe fallback");
    a.setGrade(70); b.setGrade(90);
    check(a.getGrade()==70 && b.getGrade()==90,"Objects have independent state");
    cout << "Checks passed: " << passed << "/6\n";
    if (passed==6) cout << "OOP_CHECKPOINT_PASS\n";
    return passed==6 ? 0 : 1;
}
'''
model=dict(starter=starter.strip()+'\n',solution=student.strip()+'\n',tests=tests,
    quiz=[
      dict(id='class-object',prompt='Which statement best describes a class and its objects?',options=['A class defines a type; each object is an instance with its own non-static data.','Every object contains every other object of the same class.','A class is simply a variable holding one value.'],correct=0,explanation='The class defines the structure and operations. p1 and p2 are separate objects; each stores its own x and y.'),
      dict(id='private',prompt='Which statement is valid outside Point when x is private and setX is public?',options=['p1.x = 8;','p1.setX(8);','Point.x = 8;'],correct=1,explanation='Use the public interface. private blocks direct access from unrelated code; it does not prevent member functions from using x.'),
      dict(id='constructor',prompt='What does Point p; produce in the basic example?',options=['Uninitialized coordinates, because p has no arguments.','A function named p.','A Point with coordinates (0,0), using the constructor’s default arguments.'],correct=2,explanation='The constructor can be called with no arguments and explicitly initializes both members. Point p(); would instead declare a function.'),
      dict(id='independence',prompt='Point a(2,3), b; b.setX(8); What is a.getX()?',options=['8','0','2'],correct=2,explanation='The call updates b. a still has its own x value, 2.'),
      dict(id='const-query',prompt='Why is getX() declared const?',options=['It promises not to modify ordinary instance state through this call.','It makes every Point permanently immutable.','It makes the returned int a reference.'],correct=0,explanation='A const query can be called on const objects. It does not make other objects or all member functions immutable.')],
    steps=[
      dict(code='// No Point objects have been declared yet.',objects=[],note='The class declaration defines a type. It does not create p1 or p2.'),
      dict(code='Point p1(2,3);',objects=[dict(name='p1',x=2,y=3)],note='The constructor initializes p1’s two coordinates.'),
      dict(code='Point p2;',objects=[dict(name='p1',x=2,y=3),dict(name='p2',x=0,y=0)],note='The same constructor uses default arguments for p2. p1 is unchanged.'),
      dict(code='p2.setX(8);',objects=[dict(name='p1',x=2,y=3),dict(name='p2',x=8,y=0)],note='Only p2.x changes. The object before the dot selects which state the method uses.'),
      dict(code='p1.setY(7);',objects=[dict(name='p1',x=2,y=7),dict(name='p2',x=8,y=0)],note='Only p1.y changes. Both objects share the member-function definitions, not coordinate values.'),
      dict(code='Point p3 = p1;',objects=[dict(name='p1',x=2,y=7),dict(name='p2',x=8,y=0),dict(name='p3',x=2,y=7)],note='The compiler-provided copy constructor copies this simple class’s int members into a new object.'),
      dict(code='p3.setX(-1);',objects=[dict(name='p1',x=2,y=7),dict(name='p2',x=8,y=0),dict(name='p3',x=-1,y=7)],note='Changing the copy does not change p1. This independence is for these value members; owning pointer members need special care later.'),
      dict(code='p2 = p1;',objects=[dict(name='p1',x=2,y=7),dict(name='p2',x=2,y=7),dict(name='p3',x=-1,y=7)],note='Assignment updates an existing object. It differs from creating a new object by copy construction.')])
(root/'model.json').write_text(json.dumps(model,indent=2))
(root/'content.json').write_text(json.dumps(examples,indent=2))
(root/'topics.json').write_text(json.dumps(topics,indent=2))
for e in examples:(root/'examples'/f"{e['id']}.cpp").write_text(e['code'])
for t in topics:(root/'examples'/f"{t['exercise']['id']}.cpp").write_text(t['exercise']['solution'].strip()+'\n')
(root/'examples/student-checkpoint-starter.cpp').write_text(starter.strip()+'\n')
(root/'examples/student-checkpoint-solution.cpp').write_text(student.strip()+'\n')
print(len(topics),'lessons;',len(examples),'examples; Revision has 8 sublessons')
