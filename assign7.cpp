#include <iostream>
#include <iomanip>
#include <cmath>
#include <cstdlib>
#include <limits>
#include <string>
using namespace std;

const double PI = 3.14159;

void clearInput() {
    if (cin.eof()) {                       // no more input available
        cout << "\nInput ended unexpectedly. Exiting." << endl;
        exit(1);
    }
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

double readPositive(const string &prompt) {
    double v;
    while (true) {
        cout << prompt;
        if (cin >> v && v > 0) return v;
        cout << "  Invalid input. Enter a number greater than 0." << endl;
        clearInput();
    }
}

int readIntInRange(const string &prompt, int low, int high) {
    int v;
    while (true) {
        cout << prompt;
        if (cin >> v && v >= low && v <= high) return v;
        cout << "  Invalid input. Enter a value from " << low << " to " << high << "." << endl;
        clearInput();
    }
}

bool isValidTriangle(double a, double b, double c) {
    return (a + b > c) && (a + c > b) && (b + c > a);
}

// ======================================================
// PART 1: Compile-time polymorphism - Function overloading
// ======================================================
class AreaCalculator {
public:
    double area(double radius) {                         // circle
        return PI * radius * radius;
    }
    double area(double length, double breadth) {         // rectangle
        return length * breadth;
    }
    double area(double a, double b, double c) {          // triangle (Heron's formula)
        double s = (a + b + c) / 2;
        return sqrt(s * (s - a) * (s - b) * (s - c));
    }
};

// ======================================================
// PART 2: Compile-time polymorphism - Operator overloading
// ======================================================
class Distance {
private:
    int feet;
    int inches;                                          // always kept between 0 and 11
public:
    Distance(int f = 0, int i = 0) : feet(f), inches(i) {}

    int totalInches() const { return feet * 12 + inches; }

    // Binary + : adds two distances and carries inches into feet
    Distance operator+(const Distance &d) const {
        int total = totalInches() + d.totalInches();
        return Distance(total / 12, total % 12);
    }

    // Binary > : compares two distances
    bool operator>(const Distance &d) const {
        return totalInches() > d.totalInches();
    }

    // Output operator (friend so that it can use cout << object)
    friend ostream& operator<<(ostream &out, const Distance &d) {
        out << d.feet << " ft " << d.inches << " in";
        return out;
    }
};

// ======================================================
// PART 3: Run-time polymorphism - virtual functions
// ======================================================
class Shape {                                            // abstract base class
protected:
    string name;
public:
    Shape(string n) : name(n) {}
    virtual double area() const = 0;                     // pure virtual
    virtual double perimeter() const = 0;                // pure virtual
    virtual void display() const {                       // can be overridden
        cout << name << ": Area = " << area()
             << ", Perimeter = " << perimeter() << endl;
    }
    virtual ~Shape() { cout << "  Shape destructor: " << name << endl; }
};

class Circle : public Shape {
private:
    double radius;
public:
    Circle(double r) : Shape("Circle"), radius(r) {}
    double area() const { return PI * radius * radius; }
    double perimeter() const { return 2 * PI * radius; }
    ~Circle() { cout << "  Circle destructor" << endl; }
};

class Rectangle : public Shape {
private:
    double length, breadth;
public:
    Rectangle(double l, double b) : Shape("Rectangle"), length(l), breadth(b) {}
    double area() const { return length * breadth; }
    double perimeter() const { return 2 * (length + breadth); }
    void display() const {                               // overridden version
        Shape::display();
        if (length == breadth)
            cout << "  (This rectangle is a square)" << endl;
    }
    ~Rectangle() { cout << "  Rectangle destructor" << endl; }
};

class Triangle : public Shape {
private:
    double a, b, c;
public:
    Triangle(double x, double y, double z) : Shape("Triangle"), a(x), b(y), c(z) {}
    double area() const {
        double s = (a + b + c) / 2;
        return sqrt(s * (s - a) * (s - b) * (s - c));
    }
    double perimeter() const { return a + b + c; }
    ~Triangle() { cout << "  Triangle destructor" << endl; }
};

int main() {
    cout << fixed << setprecision(2);

    // ---------- Read dimensions ----------
    cout << "===== Enter dimensions =====" << endl;
    double r = readPositive("Circle radius: ");
    double l = readPositive("Rectangle length: ");
    double b = readPositive("Rectangle breadth: ");
    double t1, t2, t3;
    while (true) {
        t1 = readPositive("Triangle side 1: ");
        t2 = readPositive("Triangle side 2: ");
        t3 = readPositive("Triangle side 3: ");
        if (isValidTriangle(t1, t2, t3)) break;
        cout << "  These sides cannot form a triangle. Enter again." << endl;
    }

    // ---------- Part 1 ----------
    cout << "\n===== 1. Function Overloading =====" << endl;
    AreaCalculator calc;
    cout << "Area of circle    = " << calc.area(r) << endl;
    cout << "Area of rectangle = " << calc.area(l, b) << endl;
    cout << "Area of triangle  = " << calc.area(t1, t2, t3) << endl;

    // ---------- Part 2 ----------
    cout << "\n===== 2. Operator Overloading =====" << endl;
    int f1 = readIntInRange("Distance 1 - feet (0-1000): ", 0, 1000);
    int i1 = readIntInRange("Distance 1 - inches (0-11): ", 0, 11);
    int f2 = readIntInRange("Distance 2 - feet (0-1000): ", 0, 1000);
    int i2 = readIntInRange("Distance 2 - inches (0-11): ", 0, 11);
    Distance d1(f1, i1), d2(f2, i2);
    cout << "Distance 1 = " << d1 << endl;
    cout << "Distance 2 = " << d2 << endl;
    cout << "d1 + d2    = " << d1 + d2 << endl;
    if (d1 > d2)
        cout << "Distance 1 is greater." << endl;
    else if (d2 > d1)
        cout << "Distance 2 is greater." << endl;
    else
        cout << "Both distances are equal." << endl;

    // ---------- Part 3 ----------
    cout << "\n===== 3. Run-time Polymorphism (virtual functions) =====" << endl;
    Shape *shapes[3];                                    // base class pointers
    shapes[0] = new Circle(r);
    shapes[1] = new Rectangle(l, b);
    shapes[2] = new Triangle(t1, t2, t3);

    int largest = 0;
    for (int i = 0; i < 3; i++) {
        shapes[i]->display();                            // derived version is called
        if (shapes[i]->area() > shapes[largest]->area())
            largest = i;
    }
    cout << "Shape with the largest area: ";
    shapes[largest]->display();

    cout << "\nDeleting objects through base class pointers:" << endl;
    for (int i = 0; i < 3; i++)
        delete shapes[i];                                // virtual destructor

    return 0;
}
