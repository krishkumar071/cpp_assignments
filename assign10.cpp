#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <limits>
#include <stdexcept>
using namespace std;

string itos(int v) {
    ostringstream o;
    o << v;
    return o.str();
}

// Stop the program if the input has ended (avoids an infinite loop)
void checkInputEnded() {
    if (cin.eof()) {
        cout << "\nInput ended unexpectedly. Exiting." << endl;
        exit(1);
    }
}

// ================================================================
// FUNCTION TEMPLATES
// ================================================================

// Reads a value of any type T and repeats until the input is valid
template <typename T>
T readValue(const string &prompt) {
    T v;
    while (true) {
        cout << prompt;
        if (cin >> v) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return v;
        }
        checkInputEnded();
        cout << "  Invalid input. Please enter a valid number." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

int readIntInRange(const string &prompt, int low, int high) {
    while (true) {
        int v = readValue<int>(prompt);
        if (v >= low && v <= high) return v;
        cout << "  Invalid input. Enter a value from " << low << " to " << high << "." << endl;
    }
}

// Returns the larger of two values of the same type
template <typename T>
T maxOf(T a, T b) {
    return (a > b) ? a : b;
}

// Explicit specialization: C-strings must be compared with strcmp, not with >
template <>
const char* maxOf<const char*>(const char *a, const char *b) {
    return (strcmp(a, b) > 0) ? a : b;
}

// Swaps two values of the same type
template <typename T>
void swapValues(T &a, T &b) {
    T temp = a;
    a = b;
    b = temp;
}

// Sum of the first n elements (returns 0 for n <= 0)
template <typename T>
T sumArray(const T arr[], int n) {
    T total = T();
    for (int i = 0; i < n; i++)
        total = total + arr[i];
    return total;
}

// Largest of the first n elements (throws if the array is empty)
template <typename T>
T findMax(const T arr[], int n) {
    if (n <= 0)
        throw invalid_argument("Array is empty: cannot find the largest element.");
    T best = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > best) best = arr[i];
    return best;
}

template <typename T>
double average(const T arr[], int n) {
    if (n <= 0)
        throw invalid_argument("Array is empty: cannot calculate the average.");
    return static_cast<double>(sumArray(arr, n)) / n;
}

// Two different type parameters
template <typename T, typename U>
void showPair(const T &a, const U &b) {
    cout << "  (" << a << ", " << b << ")" << endl;
}

// ================================================================
// CLASS TEMPLATES
// ================================================================

// Stack of any type T with a fixed capacity SIZE (non-type parameter)
template <typename T, int SIZE>
class Stack {
private:
    T items[SIZE];
    int top;
public:
    Stack() : top(-1) {}

    bool isEmpty() const { return top == -1; }
    bool isFull() const { return top == SIZE - 1; }

    void push(const T &value) {
        if (isFull())
            throw overflow_error("Stack overflow: the stack is full (capacity " + itos(SIZE) + ").");
        items[++top] = value;
    }

    T pop() {
        if (isEmpty())
            throw underflow_error("Stack underflow: the stack is empty.");
        return items[top--];
    }

    T peek() const {
        if (isEmpty())
            throw underflow_error("Stack underflow: the stack is empty.");
        return items[top];
    }

    void display() const;                       // defined outside the class
};

template <typename T, int SIZE>
void Stack<T, SIZE>::display() const {
    if (isEmpty()) {
        cout << "  Stack is empty." << endl;
        return;
    }
    cout << "  Stack (top to bottom):";
    for (int i = top; i >= 0; i--)
        cout << " " << items[i];
    cout << endl;
}

// Pair of two values of different types
template <typename T1, typename T2>
class Pair {
private:
    T1 first;
    T2 second;
public:
    Pair(const T1 &a, const T2 &b) : first(a), second(b) {}
    T1 getFirst() const { return first; }
    T2 getSecond() const { return second; }
    Pair<T2, T1> reversed() const { return Pair<T2, T1>(second, first); }
    void display() const {
        cout << "(" << first << ", " << second << ")";
    }
};

int main() {
    cout << fixed << setprecision(2);

    // ---------------- 1. maxOf and swapValues ----------------
    cout << "===== 1. Function templates: maxOf and swapValues =====" << endl;
    int i1 = readValue<int>("Enter first integer > ");
    int i2 = readValue<int>("Enter second integer > ");
    double d1 = readValue<double>("Enter first decimal number > ");
    double d2 = readValue<double>("Enter second decimal number > ");

    cout << "  maxOf(" << i1 << ", " << i2 << ") = " << maxOf(i1, i2) << "   (T = int)" << endl;
    cout << "  maxOf(" << d1 << ", " << d2 << ") = " << maxOf(d1, d2) << "   (T = double)" << endl;
    cout << "  maxOf('a', 'Z') = " << maxOf('a', 'Z') << "   (T = char, compared by ASCII value)" << endl;
    cout << "  maxOf(\"apple\", \"mango\") = " << maxOf(string("apple"), string("mango")) << "   (T = string)" << endl;
    cout << "  maxOf(\"pear\", \"kiwi\") = " << maxOf("pear", "kiwi") << "   (specialization for const char*)" << endl;

    swapValues(i1, i2);
    swapValues(d1, d2);
    string s1 = "left", s2 = "right";
    swapValues(s1, s2);
    cout << "  After swap: integers (" << i1 << ", " << i2 << "), doubles (" << d1 << ", " << d2
         << "), strings (" << s1 << ", " << s2 << ")" << endl;
    cout << "  showPair with different types:" << endl;
    showPair(101, "Krish");
    showPair(99.5, 'A');

    // ---------------- 2. Arrays ----------------
    cout << "\n===== 2. Function templates with arrays =====" << endl;
    int n = readIntInRange("Enter number of elements (1 to 10) > ", 1, 10);
    int arr[10];
    for (int i = 0; i < n; i++)
        arr[i] = readValue<int>("Enter element " + itos(i + 1) + " > ");
    cout << "  Sum     = " << sumArray(arr, n) << endl;
    cout << "  Largest = " << findMax(arr, n) << endl;
    cout << "  Average = " << average(arr, n) << endl;

    double prices[3] = {1.5, 2.5, 3.0};
    cout << "  Same templates with a double array {1.5, 2.5, 3.0}: sum = " << sumArray(prices, 3)
         << ", largest = " << findMax(prices, 3) << endl;

    try {
        double m = findMax(prices, 0);              // boundary: empty array
        cout << "  Largest = " << m << endl;
    } catch (const invalid_argument &e) {
        cout << "  Error [Empty array]: " << e.what() << endl;
    }

    // ---------------- 3. Stack ----------------
    cout << "\n===== 3. Class template: Stack<int, 3> =====" << endl;
    Stack<int, 3> st;
    while (true) {
        cout << "\nSTACK MENU: 1.Push  2.Pop  3.Peek  4.Display  0.Exit" << endl;
        int choice = readIntInRange("Enter choice (0-4) > ", 0, 4);
        if (choice == 0) break;
        try {
            if (choice == 1) {
                int v = readValue<int>("Enter value to push > ");
                st.push(v);
                cout << "  Pushed " << v << endl;
            } else if (choice == 2) {
                int v = st.pop();
                cout << "  Popped " << v << endl;
            } else if (choice == 3) {
                int v = st.peek();
                cout << "  Top element = " << v << endl;
            } else {
                st.display();
            }
        } catch (const overflow_error &e) {
            cout << "  Error [Overflow]: " << e.what() << endl;
        } catch (const underflow_error &e) {
            cout << "  Error [Underflow]: " << e.what() << endl;
        }
    }

    cout << "\n  Stack<string, 3> with the same class template:" << endl;
    Stack<string, 3> names;
    try {
        names.push("Asha");
        names.push("Ravi");
        names.push("Neha");
        names.display();
        names.push("Imran");                        // fourth push: overflow
    } catch (const overflow_error &e) {
        cout << "  Error [Overflow]: " << e.what() << endl;
    }
    string firstOut = names.pop();                  // separate statements: fixed order of evaluation
    string secondOut = names.pop();
    cout << "  Popped " << firstOut << ", then " << secondOut << endl;

    // ---------------- 4. Pair ----------------
    cout << "\n===== 4. Class template: Pair<T1, T2> =====" << endl;
    Pair<int, string> p1(101, "Krish");
    Pair<string, double> p2("Price", 99.5);
    cout << "  p1 = "; p1.display(); cout << endl;
    cout << "  p1 reversed = "; p1.reversed().display(); cout << endl;
    cout << "  p2 = "; p2.display(); cout << endl;
    cout << "  p2 reversed = "; p2.reversed().display(); cout << endl;

    return 0;
}
