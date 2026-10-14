#include <iostream>
#include <string>
using namespace std;

class Student
{
private:
    string name;
    int rollNo;
    float marks;

public:

    // 1. Default Constructor
    Student()
    {
        name = "Unknown";
        rollNo = 0;
        marks = 0;
        cout << "Default Constructor Called" << endl;
    }

    // 2. Parameterized Constructor
    Student(string n, int r, float m)
    {
        name = n;
        rollNo = r;
        marks = m;
        cout << "Parameterized Constructor Called" << endl;
    }

    // 3. Copy Constructor
    Student(const Student &s)
    {
        name = s.name;
        rollNo = s.rollNo;
        marks = s.marks;
        cout << "Copy Constructor Called" << endl;
    }

    // Member Function to display details
    void display()
    {
        cout << "Name    : " << name << endl;
        cout << "Roll No : " << rollNo << endl;
        cout << "Marks   : " << marks << endl;
    }

    // Member Function to calculate grade
    void calculateGrade()
    {
        if (marks >= 90)
            cout << "Grade   : A+" << endl;
        else if (marks >= 80)
            cout << "Grade   : A" << endl;
        else if (marks >= 70)
            cout << "Grade   : B" << endl;
        else if (marks >= 60)
            cout << "Grade   : C" << endl;
        else
            cout << "Grade   : D" << endl;
    }
};

int main()
{
    cout << "===== CONSTRUCTOR TYPES IN C++ =====" << endl;

    // Object using Default Constructor
    cout << "\n1. Default Constructor:" << endl;
    Student s1;
    s1.display();
    s1.calculateGrade();

    // Object using Parameterized Constructor
    cout << "\n2. Parameterized Constructor:" << endl;
    Student s2("Krish", 101, 85);
    s2.display();
    s2.calculateGrade();

    // Object using Copy Constructor
    cout << "\n3. Copy Constructor:" << endl;
    Student s3(s2);
    s3.display();
    s3.calculateGrade();

    return 0;
}
