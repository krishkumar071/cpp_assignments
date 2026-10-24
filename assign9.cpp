#include <iostream>
#include <string>
#include <vector>
#include <utility>      // std::move
#include <memory>       // std::unique_ptr
#include <chrono>
#include <limits>
#include <cstdlib>
using namespace std;

// ---------------------------------------------------------------
// Class that owns dynamic memory: shows copy vs move clearly
// ---------------------------------------------------------------
class DataBuffer {
private:
    string name;
    int *data;
    size_t size;

public:
    // Normal constructor
    DataBuffer(const string &n, size_t s, int value) : name(n), data(nullptr), size(s) {
        if (size > 0) {
            data = new int[size];
            for (size_t i = 0; i < size; i++) data[i] = value;
        }
        cout << "  [Constructor] " << name << " (size " << size << ")" << endl;
    }

    // Copy constructor: allocates new memory and copies every element (expensive)
    DataBuffer(const DataBuffer &other)
        : name(other.name + "_copy"), data(nullptr), size(other.size) {
        if (size > 0) {
            data = new int[size];
            for (size_t i = 0; i < size; i++) data[i] = other.data[i];
        }
        cout << "  [Copy constructor] " << name << " copied from " << other.name << endl;
    }

    // Move constructor: steals the pointer, no copying (cheap)
    DataBuffer(DataBuffer &&other) noexcept
        : name(other.name + "_moved"), data(other.data), size(other.size) {
        other.data = nullptr;               // leave the source in a safe empty state
        other.size = 0;
        cout << "  [Move constructor] " << name << " took resources from " << other.name << endl;
    }

    // Copy assignment
    DataBuffer& operator=(const DataBuffer &other) {
        cout << "  [Copy assignment] " << name << " = " << other.name << endl;
        if (this != &other) {
            delete[] data;
            size = other.size;
            data = (size > 0) ? new int[size] : nullptr;
            for (size_t i = 0; i < size; i++) data[i] = other.data[i];
        }
        return *this;
    }

    // Move assignment: release own memory, then steal the other's memory
    DataBuffer& operator=(DataBuffer &&other) noexcept {
        cout << "  [Move assignment] " << name << " = " << other.name << endl;
        if (this != &other) {               // protects against self-move
            delete[] data;
            data = other.data;
            size = other.size;
            other.data = nullptr;
            other.size = 0;
        } else {
            cout << "  (self-move ignored)" << endl;
        }
        return *this;
    }

    ~DataBuffer() {
        cout << "  [Destructor] " << name << " (size " << size << ")" << endl;
        delete[] data;
    }

    size_t getSize() const { return size; }

    void show() const {
        cout << "  " << name << ": ";
        if (size == 0) {
            cout << "[empty]";
        } else {
            cout << "[";
            for (size_t i = 0; i < size && i < 5; i++)
                cout << data[i] << (i + 1 < size && i < 4 ? " " : "");
            if (size > 5) cout << " ...";
            cout << "] size=" << size;
        }
        cout << endl;
    }
};

// Generic swap written with std::move (no copying of the resources)
template <typename T>
void mySwap(T &x, T &y) {
    T temp(std::move(x));
    x = std::move(y);
    y = std::move(temp);
}

// ---------- Input helper: repeats until a valid value is entered ----------
long readSize(const string &prompt, long low, long high) {
    long v;
    while (true) {
        cout << prompt;
        if (cin >> v) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (v >= low && v <= high) return v;
            cout << "  Invalid input. Enter a value from " << low << " to " << high << "." << endl;
        } else {
            if (cin.eof()) {
                cout << "\nInput ended unexpectedly. Exiting." << endl;
                exit(1);
            }
            cout << "  Invalid input. Enter a value from " << low << " to " << high << "." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

int main() {
    cout << "===== 1. std::move with std::string =====" << endl;
    {
        string s1 = "Move semantics avoids expensive copying in C++";   // long string (heap memory)
        string s2 = s1;                       // copy: s1 keeps its value
        string s3 = std::move(s1);            // move: s3 takes the memory of s1
        cout << "  s2 (copy)  = " << s2 << endl;
        cout << "  s3 (moved) = " << s3 << endl;
        cout << "  s1 length after move = " << s1.size()
             << " (valid but unspecified; usually empty)" << endl;
    }

    cout << "\n===== 2. Copy vs move of a class =====" << endl;
    {
        DataBuffer a("A", 5, 7);
        DataBuffer b = a;                     // copy constructor
        DataBuffer c = std::move(a);          // move constructor
        a.show();
        b.show();
        c.show();

        cout << "\n  -- Move assignment --" << endl;
        DataBuffer d("D", 3, 1);
        d = std::move(c);                     // move assignment
        d.show();
        c.show();
        cout << "\n  -- End of block: objects destroyed --" << endl;
    }

    cout << "\n===== 3. std::move with a vector of objects =====" << endl;
    {
        vector<DataBuffer> v;
        v.reserve(3);                         // no reallocation, so only the moves below are shown
        cout << "  push_back(temporary):" << endl;
        v.push_back(DataBuffer("T1", 2, 5));  // temporary is an rvalue: move constructor
        DataBuffer e("E", 4, 9);
        cout << "  push_back(std::move(e)):" << endl;
        v.push_back(std::move(e));            // explicit move
        e.show();
        cout << "  Vector now holds " << v.size() << " buffers." << endl;
        cout << "\n  -- Reusing a moved-from object --" << endl;
        e = DataBuffer("E2", 2, 3);           // assign a new value to the moved-from object
        e.show();
        cout << "\n  -- End of block: objects destroyed --" << endl;
    }

    cout << "\n===== 4. Swap using std::move =====" << endl;
    {
        string x = "first", y = "second";
        mySwap(x, y);
        cout << "  x = " << x << ", y = " << y << endl;
        DataBuffer p("P", 2, 1), q("Q", 3, 2);
        mySwap(p, q);
        p.show();
        q.show();
        cout << "\n  -- End of block: objects destroyed --" << endl;
    }

    cout << "\n===== 5. Ownership transfer with unique_ptr =====" << endl;
    {
        unique_ptr<DataBuffer> p1(new DataBuffer("U", 2, 8));
        // unique_ptr<DataBuffer> p2 = p1;     // error: unique_ptr cannot be copied
        unique_ptr<DataBuffer> p2 = std::move(p1);
        cout << "  p1 is " << (p1 ? "not null" : "null") << ", p2 is "
             << (p2 ? "not null" : "null") << endl;
        p2->show();
        cout << "\n  -- End of block: objects destroyed --" << endl;
    }

    cout << "\n===== 6. Boundary cases =====" << endl;
    {
        DataBuffer empty("Empty", 0, 0);
        DataBuffer f = std::move(empty);      // moving an empty object is safe
        f.show();
        DataBuffer g("G", 2, 4);
        DataBuffer &ref = g;
        g = std::move(ref);                   // self-move must not destroy the data
        g.show();
        cout << "\n  -- End of block: objects destroyed --" << endl;
    }

    cout << "\n===== 7. Performance: copy vs move of a large vector =====" << endl;
    long n = readSize("Enter number of elements (1 to 10000000) > ", 1, 10000000);
    {
        vector<int> big(static_cast<size_t>(n), 1);

        auto t1 = chrono::steady_clock::now();
        vector<int> copied = big;             // copies every element
        auto t2 = chrono::steady_clock::now();
        vector<int> moved = std::move(big);   // only transfers the internal pointer
        auto t3 = chrono::steady_clock::now();

        long long copyTime = chrono::duration_cast<chrono::microseconds>(t2 - t1).count();
        long long moveTime = chrono::duration_cast<chrono::microseconds>(t3 - t2).count();

        cout << "  Elements in copy  : " << copied.size() << endl;
        cout << "  Elements in moved : " << moved.size() << endl;
        cout << "  Source size after move = " << big.size() << " (usually 0)" << endl;
        cout << "  Copy time = " << copyTime << " microseconds" << endl;
        cout << "  Move time = " << moveTime << " microseconds" << endl;
    }

    return 0;
}
