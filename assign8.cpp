#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
#include <stdexcept>
#include <new>
#include <limits>
#include <cstdlib>
using namespace std;

// ---------- Helper functions ----------
string money(double v) {
    ostringstream o;
    o << fixed << setprecision(2) << v;
    return o.str();
}

string itos(int v) {
    ostringstream o;
    o << v;
    return o.str();
}

// Stop the program if there is no more input (avoids an infinite loop)
void checkInputEnded() {
    if (cin.eof()) {
        cout << "\nInput ended unexpectedly. Exiting." << endl;
        exit(1);
    }
}

void discardLine() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

double readNumber(const string &prompt) {
    double v;
    while (true) {
        cout << prompt;
        if (cin >> v) { discardLine(); return v; }
        checkInputEnded();
        cout << "  Invalid input. Please enter a number." << endl;
        cin.clear();
        discardLine();
    }
}

int readIntInRange(const string &prompt, int low, int high) {
    int v;
    while (true) {
        cout << prompt;
        if (cin >> v) {
            discardLine();
            if (v >= low && v <= high) return v;
            cout << "  Invalid choice. Enter a value from " << low << " to " << high << "." << endl;
        } else {
            checkInputEnded();
            cout << "  Invalid input. Enter a value from " << low << " to " << high << "." << endl;
            cin.clear();
            discardLine();
        }
    }
}

int readInt(const string &prompt) {
    int v;
    while (true) {
        cout << prompt;
        if (cin >> v) { discardLine(); return v; }
        checkInputEnded();
        cout << "  Invalid input. Please enter a whole number." << endl;
        cin.clear();
        discardLine();
    }
}

// ---------- Custom exception classes (derived from std::exception) ----------
class InvalidAmountException : public exception {
private:
    string msg;
public:
    InvalidAmountException(double amount) {
        msg = "Amount " + money(amount) + " is not valid. It must be greater than 0.";
    }
    virtual const char* what() const throw() { return msg.c_str(); }
    virtual ~InvalidAmountException() throw() {}
};

class InsufficientFundsException : public exception {
private:
    double balance, amount;
    string msg;
public:
    InsufficientFundsException(double b, double a) : balance(b), amount(a) {
        msg = "Balance " + money(balance) + " is less than the requested " + money(amount) + ".";
    }
    double shortBy() const { return amount - balance; }
    virtual const char* what() const throw() { return msg.c_str(); }
    virtual ~InsufficientFundsException() throw() {}
};

// ---------- Account class ----------
class Account {
private:
    string holder;
    double balance;
    vector<string> history;
public:
    Account(const string &h, double opening) : holder(h), balance(opening) {
        history.push_back("Opening balance " + money(opening));
    }

    void deposit(double amount) {
        if (amount <= 0)
            throw InvalidAmountException(amount);
        balance += amount;
        history.push_back("Deposit " + money(amount));
    }

    void withdraw(double amount) {
        if (amount <= 0)
            throw InvalidAmountException(amount);
        if (amount > balance)                      // amount == balance is allowed
            throw InsufficientFundsException(balance, amount);
        balance -= amount;
        history.push_back("Withdraw " + money(amount));
    }

    string getTransaction(int n) const {
        if (n < 1 || n > static_cast<int>(history.size()))
            throw out_of_range("Transaction " + itos(n) + " does not exist. Valid range is 1 to "
                               + itos(static_cast<int>(history.size())) + ".");
        return history[n - 1];
    }

    double getBalance() const { return balance; }
    string getHolder() const { return holder; }
};

// ---------- Stack unwinding demo: destructor runs while the exception travels up ----------
class OperationGuard {
private:
    string op;
public:
    OperationGuard(const string &name) : op(name) {
        cout << "  [Start] " << op << endl;
    }
    ~OperationGuard() {
        cout << "  [End] " << op << " (cleanup done)" << endl;
    }
};

// ---------- Functions that throw ----------
double splitAmount(double amount, int people) {
    if (people == 0)
        throw runtime_error("Division by zero: number of people cannot be 0.");
    if (people < 0)
        throw invalid_argument("Number of people cannot be negative.");
    if (amount <= 0)
        throw InvalidAmountException(amount);
    return amount / people;
}

// Catches an exception, logs it, then rethrows it to the caller
void withdrawWithLog(Account &acc, double amount) {
    try {
        acc.withdraw(amount);
        cout << "  Withdrawn " << money(amount) << " successfully." << endl;
    } catch (const InsufficientFundsException &e) {
        cout << "  [Log] Withdrawal failed, short by " << money(e.shortBy()) << ". Rethrowing..." << endl;
        throw;                                      // rethrow the same exception
    }
}

void memoryDemo() {
    try {
        double *small = new double[1000];
        cout << "  Memory allocated for 1000 entries." << endl;
        delete[] small;
        size_t huge = static_cast<size_t>(-1) / sizeof(double);
        double *big = new double[huge];             // impossible request
        cout << "  Unexpected: huge allocation succeeded." << endl;
        delete[] big;
    } catch (const bad_alloc &) {
        cout << "  Memory allocation failed: not enough memory for the requested size." << endl;
    }
}

void throwByCode(int code) {
    if (code == 1) throw 404;                       // int
    else if (code == 2) throw "Server not responding";  // const char*
    else throw 3.14;                                // double
}

void throwDemo() {
    int code = readIntInRange("Enter error code (1-3) > ", 1, 3);
    try {
        throwByCode(code);
    } catch (int e) {
        cout << "  Caught int exception: code " << e << endl;
    } catch (const char *e) {
        cout << "  Caught string exception: " << e << endl;
    } catch (...) {
        cout << "  Caught unknown exception using catch(...)" << endl;
    }
}

void showMenu() {
    cout << "\nMENU: 1.Deposit  2.Withdraw  3.Balance  4.View transaction  5.Split amount"
         << endl;
    cout << "      6.Memory demo (bad_alloc)  7.Throw different types  0.Exit" << endl;
}

void performOperation(int choice, Account &acc) {
    OperationGuard guard("Operation " + itos(choice));
    if (choice == 1) {
        double amt = readNumber("Enter amount > ");
        acc.deposit(amt);
        cout << "  Deposited " << money(amt) << ". New balance = " << money(acc.getBalance()) << endl;
    } else if (choice == 2) {
        double amt = readNumber("Enter amount > ");
        withdrawWithLog(acc, amt);
        cout << "  New balance = " << money(acc.getBalance()) << endl;
    } else if (choice == 3) {
        cout << "  Account holder: " << acc.getHolder()
             << ", Balance = " << money(acc.getBalance()) << endl;
    } else if (choice == 4) {
        int n = readInt("Enter transaction number > ");
        string t = acc.getTransaction(n);           // may throw, so get it before printing
        cout << "  Transaction " << n << ": " << t << endl;
    } else if (choice == 5) {
        double amt = readNumber("Enter amount to split > ");
        int people = readInt("Enter number of people > ");
        double share = splitAmount(amt, people);    // may throw, so calculate before printing
        cout << "  Each person pays " << money(share) << endl;
    } else if (choice == 6) {
        memoryDemo();
    } else if (choice == 7) {
        throwDemo();
    }
}

int main() {
    Account acc("Krish", 5000);
    cout << "Welcome, " << acc.getHolder() << ". Opening balance = "
         << money(acc.getBalance()) << endl;

    while (true) {
        showMenu();
        int choice = readIntInRange("Enter choice (0-7) > ", 0, 7);
        if (choice == 0) break;

        try {
            performOperation(choice, acc);
        }
        // derived (specific) exceptions are caught before the base class exception
        catch (const InvalidAmountException &e) {
            cout << "  Error [Invalid amount]: " << e.what() << endl;
        }
        catch (const InsufficientFundsException &e) {
            cout << "  Error [Insufficient funds]: " << e.what() << endl;
        }
        catch (const out_of_range &e) {
            cout << "  Error [Out of range]: " << e.what() << endl;
        }
        catch (const invalid_argument &e) {
            cout << "  Error [Invalid argument]: " << e.what() << endl;
        }
        catch (const runtime_error &e) {
            cout << "  Error [Runtime]: " << e.what() << endl;
        }
        catch (const exception &e) {
            cout << "  Error [General]: " << e.what() << endl;
        }
        catch (...) {
            cout << "  Error: unknown exception." << endl;
        }
    }

    cout << "\nThank you for using the bank system. Final balance = "
         << money(acc.getBalance()) << endl;
    return 0;
}
