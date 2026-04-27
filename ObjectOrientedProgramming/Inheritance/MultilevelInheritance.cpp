// Topic: Multilevel Inheritance
// Standard: C++20
// Build: g++ -std=c++20 -o multilevel MultilevelInheritance.cpp

#include <iostream>

class Animal {
public:
    void eat() const {
        std::cout << "Animal is eating\n";
    }
};

class Mammal : public Animal {
public:
    void walk() const {
        std::cout << "Mammal is walking\n";
    }
};

class Dog : public Mammal {
public:
    void bark() const {
        std::cout << "Dog is barking\n";
    }
};

int main() {
    Dog dog;

    dog.eat();   // from Animal
    dog.walk();  // from Mammal
    dog.bark();  // from Dog

    // Interview one-liner:
    // Multilevel inheritance forms a chain: Dog -> Mammal -> Animal.
    // The most-derived class reuses behavior from all parent levels.
    //
    // Additional interview points:
    // 1) Keep inheritance depth shallow (usually <= 2-3 levels).
    // 2) Deep hierarchies increase coupling and maintenance cost.
    // 3) Prefer composition when variation is mostly behavioral.

    return 0;
}
