// Topic: Inheritance
// Standard: C++20
// Build: g++ -std=c++20 -o single_inheritance SingleInheritance.cpp

#include <iostream>
#include <string>

class Animal {
public:
    void eat() const {
        std::cout << "Animal is eating\n";
    }
};

class Dog : public Animal {
public:
    void bark() const {
        std::cout << "Dog is barking\n";
    }
};

int main() {
    Dog dog;

    dog.eat();   // inherited from Animal
    dog.bark();  // Dog's own behavior

    // Interview one-liner:
    // Inheritance allows a derived class to reuse base class members and add its own behavior.
    //
    // Additional interview points:
    // 1) Use inheritance only for true "is-a" relation.
    // 2) If only behavior reuse is needed, prefer composition.
    // 3) In polymorphic base classes, add virtual destructor.

    return 0;
}
