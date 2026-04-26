// Topic: Compile-time Polymorphism
// Standard: C++20
// Build: g++ -std=c++20 -o compile_poly CompileTimePolymorphism.cpp

#include <iostream>
#include <string>

class Printer {
public:
    void print(int value) const {
        std::cout << "int: " << value << "\n";
    }

    void print(double value) const {
        std::cout << "double: " << value << "\n";
    }

    void print(const std::string& value) const {
        std::cout << "string: " << value << "\n";
    }
};

template <typename T>
T add(T left, T right) {
    return left + right;
}

int main() {
    std::cout << "=== Compile-time Polymorphism ===\n\n";

    Printer printer;
    printer.print(10);
    printer.print(3.14);
    printer.print("Hello C++");

    std::cout << "\nTemplate add<int>: " << add<int>(4, 6) << "\n";
    std::cout << "Template add<double>: " << add<double>(1.5, 2.5) << "\n";

    std::cout << "\nInterview Notes:\n";
    std::cout << "1) Function overloading decided at compile time\n";
    std::cout << "2) Templates generate type-specific code at compile time\n";
    std::cout << "3) No virtual dispatch overhead\n";

    return 0;
}
