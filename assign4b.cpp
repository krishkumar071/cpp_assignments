#include <iostream>
using namespace std;
 
class Student {
private:
    int *marks;     
    int n;          
public:
    Student(int subjects) {
        n = subjects;
        marks = new int[n];
        cout << "Memory allocated for " << n << " subjects." << endl;
    }
 
    void input() {
        for (int i = 0; i < n; i++) {
            cout << "Enter marks of subject " << i + 1 << ": ";
            cin >> marks[i];
        }
    }
 
    void display() const {
        int total = 0, highest = marks[0];
        for (int i = 0; i < n; i++) {
            total += marks[i];
            if (marks[i] > highest) highest = marks[i];
        }
        cout << "Total   = " << total << endl;
        cout << "Average = " << (float)total / n << endl;
        cout << "Highest = " << highest << endl;
    }
 
    ~Student() {
        delete[] marks;
        cout << "Memory released by destructor." << endl;
    }
};
 
int main() {
    int *p = new int;
    *p = 25;
    cout << "--- Dynamic variable ---" << endl;
    cout << "Value stored in dynamic variable = " << *p << endl;
    delete p;
    p = NULL;
 
    int n;
    cout << "\n--- Dynamic array ---" << endl;
    cout << "Enter number of elements: ";
    cin >> n;
    int *arr = new int[n];
    for (int i = 0; i < n; i++) {
        cout << "Enter element " << i + 1 << ": ";
        cin >> arr[i];
    }
    int sum = 0;
    for (int i = 0; i < n; i++) sum += arr[i];
    cout << "Sum of elements = " << sum << endl;
    delete[] arr;
    arr = NULL;
 
    int subjects;
    cout << "\n--- Dynamic object ---" << endl;
    cout << "Enter number of subjects: ";
    cin >> subjects;
    Student *s = new Student(subjects);
    s->input();
    s->display();
    delete s;          
 
    return 0;
}
 
