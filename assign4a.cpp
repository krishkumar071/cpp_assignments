#include <iostream>
using namespace std;
 
class Student {
private:
    int marks;
public:
    Student() { marks = 0; }                
    Student(int m) { marks = m; }             
    int getMarks() const { return marks; }
    void setMarks(int m) { marks = m; }
};

void swapByPointer(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}
 
void swapByReference(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}
 
void addBonus(Student &s, int bonus) {
    s.setMarks(s.getMarks() + bonus);
}
 
void showStudent(const Student *s) {
    cout << "Marks (via pointer) = " << s->getMarks() << endl;
}
 
int main() {
    int x = 10;
    int *ptr = &x;      
    int &ref = x;      
 
    cout << "--- Pointer and Reference ---" << endl;
    cout << "Value of x          = " << x << endl;
    cout << "Address of x (&x)   = " << &x << endl;
    cout << "ptr (address)       = " << ptr << endl;
    cout << "*ptr (value)        = " << *ptr << endl;
    cout << "ref (value)         = " << ref << endl;
    *ptr = 20;
    cout << "After *ptr = 20, x  = " << x << ", ref = " << ref << endl;
    ref = 30;
    cout << "After ref = 30, x   = " << x << ", *ptr = " << *ptr << endl;
 

    int a = 5, b = 8;
    cout << "\n--- Swapping ---" << endl;
    cout << "Before swap: a = " << a << ", b = " << b << endl;
    swapByPointer(&a, &b);
    cout << "After swapByPointer: a = " << a << ", b = " << b << endl;
    swapByReference(a, b);
    cout << "After swapByReference: a = " << a << ", b = " << b << endl;
 
    int arr[5] = {10, 20, 30, 40, 50};
    int *p = arr;       
    cout << "\n--- Pointer and Array ---" << endl;
    for (int i = 0; i < 5; i++) {
        cout << "arr[" << i << "] = " << *(p + i) << endl;
    }
 

    Student s1(70);
    Student *sp = &s1;
    cout << "\n--- Pointer and Reference with Objects ---" << endl;
    showStudent(sp);
    addBonus(s1, 5);
    cout << "After addBonus(s1, 5): ";
    showStudent(&s1);
 
    return 0;
}
