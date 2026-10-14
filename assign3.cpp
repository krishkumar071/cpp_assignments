#include <iostream>
using namespace std;

class Student
{
private:
    int marks;

public:
    // Default Constructor
    Student()
    {
        marks = 0;
        cout << "Default Constructor Called" << endl;
    }

    // Parameterized Constructor
    Student(int m)
    {
        marks = m;
        cout << "Parameterized Constructor Called" << endl;
    }

    // Operator Overloading (+)
    Student operator +(Student s)
    {
        Student temp;
        temp.marks = marks + s.marks;
        return temp;
    }

    // Member Function
    void display()
    {
        cout << "Marks = " << marks << endl;
    }
};

int main()
{
    cout << "===== OPERATOR OVERLOADING IN C++ =====" << endl;

    Student s1;          // Default Constructor
    Student s2(80);      // Parameterized Constructor
    Student s3(70);      // Parameterized Constructor

    Student s4 = s2 + s3;   // + Operator Overloaded

    cout << "\nStudent 2:" << endl;
    s2.display();

    cout << "\nStudent 3:" << endl;
    s3.display();

    cout << "\nTotal Marks (Student 2 + Student 3):" << endl;
    s4.display();

    return 0;
}
