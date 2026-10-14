#include <iostream>
using namespace std;

class Student
{
private:
    string name;
    int rollNo;
    float marks;

public:
    // Constructor
    Student()
    {
        cout << "Constructor called." << endl;

        cout << "Enter student name: ";
        cin >> name;

        cout << "Enter roll number: ";
        cin >> rollNo;

        cout << "Enter marks: ";
        cin >> marks;
    }

  
    void displayDetails()
    {
        cout << "\n--- Student Details ---" << endl;
        cout << "Name    : " << name << endl;
        cout << "Roll No : " << rollNo << endl;
        cout << "Marks   : " << marks << endl;
    }


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

    // Destructor
    ~Student()
    {
        cout << "\nDestructor called." << endl;
        cout << "Student object destroyed." << endl;
    }
};

int main()
{

    Student s1;

    
    s1.displayDetails();
    s1.calculateGrade();

    return 0;
}
