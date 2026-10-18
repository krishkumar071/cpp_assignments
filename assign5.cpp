// Practical 5: Function Types and Friend Class
// Real-time scenario: Bank Account Management System
// Concepts: class, objects, this pointer, inline function,
//           static member function, friend class
#include <iostream>
#include <string>
using namespace std;

class BankAccount {
private:
    int accNo;
    string name;
    double balance;
    static int totalAccounts;           // shared by all objects

public:
    // Default constructor
    BankAccount() {
        accNo = 0;
        name = "Unknown";
        balance = 0;
        totalAccounts++;
    }

    // Parameterized constructor: 'this' resolves the name clash
    BankAccount(int accNo, string name, double balance) {
        this->accNo = accNo;
        this->name = name;
        this->balance = balance;
        totalAccounts++;
    }

    // 'this' pointer: returning *this allows function chaining
    BankAccount& deposit(double amount) {
        this->balance += amount;
        return *this;
    }

    BankAccount& withdraw(double amount) {
        if (amount <= this->balance)
            this->balance -= amount;
        else
            cout << "Insufficient balance to withdraw " << amount << endl;
        return *this;
    }

    // Returns the object with the higher balance using 'this'
    const BankAccount& richer(const BankAccount &other) const {
        if (this->balance >= other.balance)
            return *this;
        return other;
    }

    // Inline function (defined inside the class)
    double getBalance() const { return balance; }

    // Inline function (declared with the inline keyword, defined outside)
    inline double calcInterest(double rate) const;

    void display() const {
        cout << "Acc No: " << accNo << ", Name: " << name
             << ", Balance: " << balance << endl;
    }

    // Static member function: works on static data, no object needed
    static int getTotalAccounts() {
        return totalAccounts;
    }

    // Auditor can access private members of BankAccount
    friend class Auditor;
};

int BankAccount::totalAccounts = 0;     // definition of static data member

inline double BankAccount::calcInterest(double rate) const {
    return balance * rate / 100;
}

// Friend class: can access private data of BankAccount directly
class Auditor {
public:
    void audit(const BankAccount &acc) {
        cout << "[Audit] Acc " << acc.accNo << " (" << acc.name
             << ") balance = " << acc.balance;
        if (acc.balance < 1000)
            cout << "  -> LOW BALANCE";
        cout << endl;
    }

    void applyPenalty(BankAccount &acc, double fine) {
        acc.balance -= fine;
        cout << "[Audit] Penalty of " << fine << " applied to Acc "
             << acc.accNo << endl;
    }
};

int main() {
    cout << "Accounts before creating objects = "
         << BankAccount::getTotalAccounts() << endl;

    BankAccount a1;                              // default constructor
    BankAccount a2(101, "Krish", 5000);          // parameterized constructor
    BankAccount a3(102, "Rahul", 800);

    cout << "\n--- Account details ---" << endl;
    a1.display();
    a2.display();
    a3.display();

    cout << "\n--- Function chaining using this pointer ---" << endl;
    a2.deposit(1000).withdraw(500).deposit(250);
    a2.display();
    a3.withdraw(2000);

    cout << "\n--- Richer account (this pointer) ---" << endl;
    a2.richer(a3).display();

    cout << "\n--- Inline functions ---" << endl;
    cout << "Balance of a2 = " << a2.getBalance() << endl;
    cout << "Interest on a2 at 4% = " << a2.calcInterest(4) << endl;

    cout << "\n--- Static member function ---" << endl;
    cout << "Total accounts created = " << BankAccount::getTotalAccounts() << endl;

    cout << "\n--- Friend class ---" << endl;
    Auditor auditor;
    auditor.audit(a2);
    auditor.audit(a3);
    auditor.applyPenalty(a3, 100);
    auditor.audit(a3);

    return 0;
}
