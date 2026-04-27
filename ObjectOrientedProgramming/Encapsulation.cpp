// Topic: Encapsulation
// Standard: C++20
// Build: g++ -std=c++20 -o encapsulation encapsulation.cpp

// Q: What is encapsulation?
// A: Bundling data + methods, restricting direct access to internals.
//    Expose only a controlled public interface.
//
// Interview Notes:
// - Encapsulation = data hiding + controlled access via getters/setters.
// - Purpose: protect object state from invalid modifications.
// - Real-world analogy: ATM lets you withdraw money but won't let you
//   directly reach into the vault.
// - Access specifiers in C++: private, protected, public.
// - Encapsulation vs Abstraction:
//     Encapsulation = WHO can access data (access control)
//     Abstraction   = WHAT is exposed to the user (interface design)
// - Encapsulation is NOT just using 'private'. It's about designing a
//   safe, minimal public interface that maintains class invariants.
// - Expose operations, not raw state, to protect invariants over time.

#include <iostream>
#include <format>

class BankAccount {
private:
    double balance_{0.0};    // hidden — can't do acc.balance_ from outside

public:
    explicit BankAccount(double initial) : balance_{initial} {}

    bool deposit(double amt) {
        if (amt <= 0) return false;   // validation = encapsulation benefit
        balance_ += amt;
        return true;
    }

    bool withdraw(double amt) {
        if (amt <= 0 || amt > balance_) return false;
        balance_ -= amt;
        return true;
    }

    [[nodiscard]] double getBalance() const { return balance_; }
};

int main() {
    BankAccount acc{1000.0};

    acc.deposit(500.0);          // balance = 1500
    acc.withdraw(200.0);         // balance = 1300
    acc.withdraw(5000.0);        // fails — can't overdraw
    acc.deposit(-100.0);         // fails — invalid amount
    // acc.balance_ = 999999;    // compile error — private!

    std::cout << std::format("Balance: ${}\n", acc.getBalance());  // 1300

    // Key Points:
    // 1. Private data → no direct access from outside
    // 2. Public methods → controlled way to read/modify
    // 3. Validation in setters → maintains class invariants
    // 4. Encapsulation != just using 'private' keyword
    //    It's about providing a SAFE interface
    //
    // Interview Quick Line:
    // "Encapsulation bundles data with the methods that operate on it,
    //  and restricts direct access — so the object controls its own state."
    //
    // Follow-up Q: Why not just make everything public?
    // A: Breaks invariants. Anyone could set balance_ to -999.
    //    Encapsulation ensures only valid operations happen.
    //
    // Follow-up Q: Is using 'struct' a violation of encapsulation?
    // A: Not necessarily. struct defaults to public, but you can still
    //    add private members. It's about design intent, not keyword.
    //
    // Additional interview points:
    // - Keep invalid states unrepresentable through API design.
    // - Validate on write paths (deposit/withdraw), not only at read time.

    return 0;
}
