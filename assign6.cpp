// Practical 6: Inheritance
// Real-time scenario: University Management System
// Types shown: Single, Multilevel, Hierarchical, Multiple, Hybrid
//
//   Single       : Person -> Student
//   Multilevel   : Person -> Employee -> Teacher
//   Hierarchical : Person -> Student and Person -> Employee
//   Multiple     : Student + Sports -> SportsStudent
//   Hybrid       : Person -> (Student, Employee) -> TeachingAssistant
#include <iostream>
#include <string>
using namespace std;

// ---------------- Base class ----------------
class Person {
private:
    string phone;               // private: NOT accessible in derived classes
protected:
    string name;                // protected: accessible in derived classes
    int id;
public:
    Person(string n = "Unknown", int i = 0, string ph = "NA") {
        name = n; id = i; phone = ph;
        cout << "  Person constructor: " << name << endl;
    }
    void showPerson() const {
        cout << "  ID: " << id << ", Name: " << name
             << ", Phone: " << phone << endl;
    }
    ~Person() { cout << "  Person destructor: " << name << endl; }
};

// ---------- Single inheritance: Person -> Student ----------
// 'virtual' is used so that only one Person is shared in the hybrid case
class Student : virtual public Person {
protected:
    string course;
public:
    Student(string n, int i, string ph, string c) : Person(n, i, ph) {
        course = c;
        cout << "  Student constructor: " << name << endl;
    }
    void showStudent() const {
        showPerson();
        cout << "  Course: " << course << endl;
    }
    ~Student() { cout << "  Student destructor: " << name << endl; }
};

// ---- Hierarchical inheritance: Employee also derives from Person ----
class Employee : virtual public Person {
protected:
    double salary;
public:
    Employee(string n, int i, string ph, double s) : Person(n, i, ph) {
        salary = s;
        cout << "  Employee constructor: " << name << endl;
    }
    void showEmployee() const {
        showPerson();
        cout << "  Salary: " << salary << endl;
    }
    ~Employee() { cout << "  Employee destructor: " << name << endl; }
};

// ------- Multilevel inheritance: Person -> Employee -> Teacher -------
class Teacher : public Employee {
private:
    string subject;
public:
    // virtual base Person is initialized by the most derived class
    Teacher(string n, int i, string ph, double s, string sub)
        : Person(n, i, ph), Employee(n, i, ph, s) {
        subject = sub;
        cout << "  Teacher constructor: " << name << endl;
    }
    void showTeacher() const {
        showEmployee();
        cout << "  Subject: " << subject << endl;
    }
    ~Teacher() { cout << "  Teacher destructor: " << name << endl; }
};

// ---------------- Second base class for multiple inheritance ----------------
class Sports {
protected:
    string sport;
public:
    Sports(string s) {
        sport = s;
        cout << "  Sports constructor: " << sport << endl;
    }
    ~Sports() { cout << "  Sports destructor: " << sport << endl; }
};

// ---- Multiple inheritance: SportsStudent derives from Student and Sports ----
class SportsStudent : public Student, public Sports {
public:
    SportsStudent(string n, int i, string ph, string c, string sp)
        : Person(n, i, ph), Student(n, i, ph, c), Sports(sp) {
        cout << "  SportsStudent constructor: " << name << endl;
    }
    void showSportsStudent() const {
        showStudent();
        cout << "  Sport: " << sport << endl;
    }
    ~SportsStudent() { cout << "  SportsStudent destructor: " << name << endl; }
};

// ---- Hybrid inheritance: TeachingAssistant derives from Student and Employee ----
// (hierarchical + multiple = diamond shape; virtual base avoids duplicate Person)
class TeachingAssistant : public Student, public Employee {
public:
    TeachingAssistant(string n, int i, string ph, string c, double s)
        : Person(n, i, ph), Student(n, i, ph, c), Employee(n, i, ph, s) {
        cout << "  TeachingAssistant constructor: " << name << endl;
    }
    void showTA() const {
        showPerson();                       // only one copy of Person data
        cout << "  Course: " << course << ", Stipend: " << salary << endl;
    }
    ~TeachingAssistant() { cout << "  TeachingAssistant destructor: " << name << endl; }
};

int main() {
    cout << "===== 1. Single Inheritance (Person -> Student) =====" << endl;
    {
        Student s1("Krish", 101, "9876500001", "B.Tech AIML");
        s1.showStudent();
    }

    cout << "\n===== 2. Multilevel Inheritance (Person -> Employee -> Teacher) =====" << endl;
    {
        Teacher t1("Dr. Khairnar", 201, "9876500002", 85000, "C++");
        t1.showTeacher();
    }

    cout << "\n===== 3. Hierarchical Inheritance (Person -> Student, Employee) =====" << endl;
    {
        Student s2("Rahul", 102, "9876500003", "B.Tech CSE");
        Employee e1("Anita", 202, "9876500004", 40000);
        s2.showStudent();
        e1.showEmployee();
    }

    cout << "\n===== 4. Multiple Inheritance (Student + Sports -> SportsStudent) =====" << endl;
    {
        SportsStudent ss("Aman", 103, "9876500005", "B.Tech AIML", "Cricket");
        ss.showSportsStudent();
    }

    cout << "\n===== 5. Hybrid Inheritance (Student + Employee -> TeachingAssistant) =====" << endl;
    {
        TeachingAssistant ta("Neha", 301, "9876500006", "M.Tech AIML", 15000);
        ta.showTA();
    }

    return 0;
}
