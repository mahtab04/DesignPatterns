// Topic: Abstraction
// Standard: C++20
// Build: g++ -std=c++20 -o abstraction abstraction.cpp

// Q: What is abstraction?
// A: Showing only WHAT something does, hiding HOW it does it.
//    User calls area() without knowing the formula inside.
//
// Interview Notes:
// - Abstraction focuses on exposing relevant behavior and hiding implementation details.
// - Achieved via abstract classes (pure virtual) or interfaces.
// - Real-world analogy: You press a button to start a car — you don't care how the engine works.
// - Abstraction vs Encapsulation:
//     Abstraction  = hiding complexity (WHAT vs HOW)
//     Encapsulation = hiding data (private members + public methods)
// - In C++, abstract class = at least one pure virtual function (= 0).
// - You CANNOT instantiate an abstract class directly.

#include <iostream>
#include <format>
#include <memory>
#include <numbers>

// Abstract class — cannot be instantiated
class Shape {
public:
    virtual ~Shape() = default;
    virtual double area() const = 0;   // pure virtual = "must implement"
};

class Circle : public Shape {
    double r_;
public:
    explicit Circle(double r) : r_{r} {}
    double area() const override {
        return std::numbers::pi * r_ * r_;   // HOW is hidden here
    }
};

class Rectangle : public Shape {
    double w_, h_;
public:
    Rectangle(double w, double h) : w_{w}, h_{h} {}
    double area() const override {
        return w_ * h_;                       // different HOW, same WHAT
    }
};

// Caller only knows "shape has area()" — doesn't care which shape
void printArea(const Shape& s) {
    std::cout << std::format("  Area = {:.2f}\n", s.area());
}

int main() {
    Circle c{5.0};
    Rectangle r{4.0, 6.0};

    // Shape s;           // compile error — abstract class!

    printArea(c);         // Area = 78.54
    printArea(r);         // Area = 24.00
    // ^ caller uses same interface, doesn't know Circle vs Rectangle

    // Polymorphism via pointer
    std::unique_ptr<Shape> shape = std::make_unique<Circle>(3.0);
    std::cout << std::format("  Area = {:.2f}\n", shape->area());

    // Key Points:
    // 1. Abstract class = has at least one pure virtual (= 0)
    // 2. Cannot create object of abstract class
    // 3. Derived class MUST override all pure virtuals
    // 4. Abstraction = show WHAT, hide HOW
    // 5. Abstraction != Encapsulation (common interview trap)
    //    Encapsulation = data hiding, Abstraction = detail hiding
    //
    // Interview Quick Line:
    // "Abstraction lets the caller work with a simple interface without
    //  knowing the underlying implementation — like calling area() on any
    //  Shape without knowing if it's a Circle or Rectangle."
    //
    // Follow-up Q: Can we have an abstract class with some implemented methods?
    // A: Yes — only needs one pure virtual. Other methods can have bodies.
    //    This is different from a pure interface (all pure virtual).

    return 0;
}
