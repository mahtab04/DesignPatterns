// Topic: Multiple Inheritance
// Standard: C++20
// Build: g++ -std=c++20 -o multiple_inheritance MultipleInheritance.cpp

#include <iostream>

class Printer {
public:
    void print() const {
        std::cout << "Printing document\n";
    }
};

class Scanner {
public:
    void scan() const {
        std::cout << "Scanning document\n";
    }
};

class AllInOneMachine : public Printer, public Scanner {
public:
    void fax() const {
        std::cout << "Faxing document\n";
    }
};

int main() {
    AllInOneMachine device;

    device.print();  // from Printer
    device.scan();   // from Scanner
    device.fax();    // from AllInOneMachine

    // Interview one-liner:
    // Multiple inheritance lets one class reuse behavior from more than one base class.
    // Example: AllInOneMachine is both a Printer and a Scanner.
    //
    // Additional interview points:
    // 1) Use it carefully because member-name ambiguity can appear.
    // 2) The diamond problem is handled in C++ with virtual inheritance when needed.
    // 3) Prefer interface-style bases when combining unrelated capabilities.

    return 0;
}