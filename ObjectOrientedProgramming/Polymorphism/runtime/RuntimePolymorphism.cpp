// Topic: Run-time Polymorphism
// Standard: C++20
// Build: g++ -std=c++20 -o runtime_poly RuntimePolymorphism.cpp

#include <iostream>
#include <memory>
#include <string>

class PaymentMethod {
public:
    virtual ~PaymentMethod() = default;
    virtual void pay(double amount) const = 0;
};

class CreditCard : public PaymentMethod {
public:
    void pay(double amount) const override {
        std::cout << "Paid " << amount << " using Credit Card\n";
    }
};

class UPI : public PaymentMethod {
public:
    void pay(double amount) const override {
        std::cout << "Paid " << amount << " using UPI\n";
    }
};

class Cash : public PaymentMethod {
public:
    void pay(double amount) const override {
        std::cout << "Paid " << amount << " using Cash\n";
    }
};

void checkout(const PaymentMethod& method, double amount) {
    method.pay(amount); // runtime decision based on actual object type
}

int main() {
    std::cout << "=== Run-time Polymorphism ===\n\n";

    CreditCard card;
    UPI upi;
    Cash cash;

    checkout(card, 1200.50);
    checkout(upi, 499.99);
    checkout(cash, 200.00);

    std::cout << "\nInterview Notes:\n";
    std::cout << "1) Requires virtual function in base class\n";
    std::cout << "2) Uses base reference/pointer for generic client code\n";
    std::cout << "3) Method call resolved at runtime (dynamic dispatch)\n";

    return 0;
}
