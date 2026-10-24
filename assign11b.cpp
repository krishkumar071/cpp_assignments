// Practical 11(b): STL vector container
// A menu driven program that performs the common operations on vector<int>
#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <cstdlib>
#include <limits>
using namespace std;

// Reads an integer and repeats until the input is valid
int readInt(const char *message) {
    int value;
    while (true) {
        cout << message;
        if (cin >> value) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }
        if (cin.eof()) {
            cout << "\nInput ended unexpectedly. Exiting." << endl;
            exit(1);
        }
        cout << "  Invalid input. Please enter a whole number." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

// Reads an integer between low and high
int readIntInRange(const char *message, int low, int high) {
    int value = readInt(message);
    while (value < low || value > high) {
        cout << "  Invalid input. Enter a value from " << low << " to " << high << "." << endl;
        value = readInt(message);
    }
    return value;
}

void displayVector(vector<int> &numbers) {
    if (numbers.empty()) {
        cout << "  The vector is empty." << endl;
        return;
    }
    int count = (int)numbers.size();
    cout << "  Vector elements: ";
    for (int i = 0; i < count; i++) {
        cout << numbers[i] << " ";
    }
    cout << endl;
    cout << "  Size = " << numbers.size()
         << ", Capacity = " << numbers.capacity()
         << ", First = " << numbers.front()
         << ", Last = " << numbers.back() << endl;
}

int main() {
    vector<int> numbers;
    int choice = -1;

    while (choice != 0) {
        cout << "\n========== VECTOR MENU ==========" << endl;
        cout << "1. Add at the end (push_back)" << endl;
        cout << "2. Insert at a position (insert)" << endl;
        cout << "3. Delete from the end (pop_back)" << endl;
        cout << "4. Delete at a position (erase)" << endl;
        cout << "5. Update an element at a position" << endl;
        cout << "6. Search a value" << endl;
        cout << "7. Sort the vector (sort)" << endl;
        cout << "8. Reverse the vector (reverse)" << endl;
        cout << "9. Sum, average, largest and smallest" << endl;
        cout << "10. Display the vector" << endl;
        cout << "11. Clear the vector (clear)" << endl;
        cout << "0. Exit" << endl;
        choice = readIntInRange("Enter your choice (0-11) > ", 0, 11);

        if (choice == 1) {
            int value = readInt("Enter value > ");
            numbers.push_back(value);
            cout << "  " << value << " added at the end." << endl;
        }
        else if (choice == 2) {
            // valid positions are 1 to size + 1 (size + 1 means the end)
            int maxPosition = numbers.size() + 1;
            int position = readIntInRange("Enter position > ", 1, maxPosition);
            int value = readInt("Enter value > ");
            numbers.insert(numbers.begin() + (position - 1), value);
            cout << "  " << value << " inserted at position " << position << "." << endl;
        }
        else if (choice == 3) {
            if (numbers.empty()) {
                cout << "  Cannot delete. The vector is empty." << endl;
            } else {
                cout << "  " << numbers.back() << " deleted from the end." << endl;
                numbers.pop_back();
            }
        }
        else if (choice == 4) {
            if (numbers.empty()) {
                cout << "  Cannot delete. The vector is empty." << endl;
            } else {
                int position = readIntInRange("Enter position to delete > ", 1, numbers.size());
                int deleted = numbers[position - 1];
                numbers.erase(numbers.begin() + (position - 1));
                cout << "  " << deleted << " deleted from position " << position << "." << endl;
            }
        }
        else if (choice == 5) {
            if (numbers.empty()) {
                cout << "  Cannot update. The vector is empty." << endl;
            } else {
                int position = readIntInRange("Enter position to update > ", 1, numbers.size());
                int value = readInt("Enter new value > ");
                int old = numbers[position - 1];
                numbers[position - 1] = value;
                cout << "  Position " << position << " changed from " << old << " to " << value << "." << endl;
            }
        }
        else if (choice == 6) {
            if (numbers.empty()) {
                cout << "  Cannot search. The vector is empty." << endl;
            } else {
                int value = readInt("Enter value to search > ");
                int position = 0;
                int count = (int)numbers.size();
                for (int i = 0; i < count; i++) {
                    if (numbers[i] == value) {
                        position = i + 1;
                        break;
                    }
                }
                if (position > 0)
                    cout << "  " << value << " found at position " << position << "." << endl;
                else
                    cout << "  " << value << " not found." << endl;
            }
        }
        else if (choice == 7) {
            if (numbers.empty()) {
                cout << "  Nothing to sort. The vector is empty." << endl;
            } else {
                sort(numbers.begin(), numbers.end());
                cout << "  The vector is sorted." << endl;
                displayVector(numbers);
            }
        }
        else if (choice == 8) {
            if (numbers.empty()) {
                cout << "  Nothing to reverse. The vector is empty." << endl;
            } else {
                reverse(numbers.begin(), numbers.end());
                cout << "  The vector is reversed." << endl;
                displayVector(numbers);
            }
        }
        else if (choice == 9) {
            if (numbers.empty()) {
                cout << "  The vector is empty. No result." << endl;
            } else {
                double sum = 0;                 // double avoids overflow for large values
                int largest = numbers[0];
                int smallest = numbers[0];
                int count = (int)numbers.size();
                for (int i = 0; i < count; i++) {
                    sum = sum + numbers[i];
                    if (numbers[i] > largest) largest = numbers[i];
                    if (numbers[i] < smallest) smallest = numbers[i];
                }
                double average = sum / count;
                cout << fixed << setprecision(0) << "  Sum = " << sum;
                cout << setprecision(2) << ", Average = " << average << endl;
                cout << "  Largest = " << largest << ", Smallest = " << smallest << endl;
            }
        }
        else if (choice == 10) {
            displayVector(numbers);
        }
        else if (choice == 11) {
            numbers.clear();
            cout << "  The vector is cleared. Size = " << numbers.size() << endl;
        }
    }

    cout << "\nProgram ended." << endl;
    return 0;
}
