// Practical 11(a): STL list container
// A menu driven program that performs the common operations on list<int>
#include <iostream>
#include <list>
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

void displayList(list<int> &numbers) {
    if (numbers.empty()) {
        cout << "  The list is empty." << endl;
        return;
    }
    cout << "  List elements: ";
    list<int>::iterator it;
    for (it = numbers.begin(); it != numbers.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;
    cout << "  Size = " << numbers.size()
         << ", First = " << numbers.front()
         << ", Last = " << numbers.back() << endl;
}

int main() {
    list<int> numbers;
    int choice = -1;

    while (choice != 0) {
        cout << "\n========== LIST MENU ==========" << endl;
        cout << "1. Add at the end (push_back)" << endl;
        cout << "2. Add at the beginning (push_front)" << endl;
        cout << "3. Insert at a position (insert)" << endl;
        cout << "4. Delete from the beginning (pop_front)" << endl;
        cout << "5. Delete from the end (pop_back)" << endl;
        cout << "6. Remove all occurrences of a value (remove)" << endl;
        cout << "7. Sort the list (sort)" << endl;
        cout << "8. Reverse the list (reverse)" << endl;
        cout << "9. Search a value" << endl;
        cout << "10. Display the list" << endl;
        cout << "0. Exit" << endl;
        choice = readIntInRange("Enter your choice (0-10) > ", 0, 10);

        if (choice == 1) {
            int value = readInt("Enter value > ");
            numbers.push_back(value);
            cout << "  " << value << " added at the end." << endl;
        }
        else if (choice == 2) {
            int value = readInt("Enter value > ");
            numbers.push_front(value);
            cout << "  " << value << " added at the beginning." << endl;
        }
        else if (choice == 3) {
            // valid positions are 1 to size + 1 (size + 1 means the end)
            int maxPosition = numbers.size() + 1;
            int position = readIntInRange("Enter position > ", 1, maxPosition);
            int value = readInt("Enter value > ");
            list<int>::iterator it = numbers.begin();
            for (int i = 1; i < position; i++) {
                ++it;
            }
            numbers.insert(it, value);
            cout << "  " << value << " inserted at position " << position << "." << endl;
        }
        else if (choice == 4) {
            if (numbers.empty()) {
                cout << "  Cannot delete. The list is empty." << endl;
            } else {
                cout << "  " << numbers.front() << " deleted from the beginning." << endl;
                numbers.pop_front();
            }
        }
        else if (choice == 5) {
            if (numbers.empty()) {
                cout << "  Cannot delete. The list is empty." << endl;
            } else {
                cout << "  " << numbers.back() << " deleted from the end." << endl;
                numbers.pop_back();
            }
        }
        else if (choice == 6) {
            if (numbers.empty()) {
                cout << "  Cannot remove. The list is empty." << endl;
            } else {
                int value = readInt("Enter value to remove > ");
                int before = numbers.size();
                numbers.remove(value);
                int removed = before - numbers.size();
                if (removed == 0)
                    cout << "  " << value << " was not found." << endl;
                else
                    cout << "  " << removed << " occurrence(s) of " << value << " removed." << endl;
            }
        }
        else if (choice == 7) {
            if (numbers.empty()) {
                cout << "  Nothing to sort. The list is empty." << endl;
            } else {
                numbers.sort();
                cout << "  The list is sorted." << endl;
                displayList(numbers);
            }
        }
        else if (choice == 8) {
            if (numbers.empty()) {
                cout << "  Nothing to reverse. The list is empty." << endl;
            } else {
                numbers.reverse();
                cout << "  The list is reversed." << endl;
                displayList(numbers);
            }
        }
        else if (choice == 9) {
            if (numbers.empty()) {
                cout << "  Cannot search. The list is empty." << endl;
            } else {
                int value = readInt("Enter value to search > ");
                int position = 1;
                bool found = false;
                list<int>::iterator it;
                for (it = numbers.begin(); it != numbers.end(); ++it) {
                    if (*it == value) {
                        found = true;
                        break;
                    }
                    position++;
                }
                if (found)
                    cout << "  " << value << " found at position " << position << "." << endl;
                else
                    cout << "  " << value << " not found." << endl;
            }
        }
        else if (choice == 10) {
            displayList(numbers);
        }
    }

    cout << "\nProgram ended." << endl;
    return 0;
}
