// Topic: Friend Class (Interview-Oriented)
// Standard: C++20
// Build: g++ -std=c++20 -o FriendClassExample FriendClassExample.cpp

#include <iostream>
#include <string>

class BankAccount {
private:
    std::string owner_;
    double balance_;

public:
    BankAccount(std::string owner, double balance)
        : owner_{std::move(owner)}, balance_{balance} {}

    // Entire Auditor class gets access to private/protected members.
    friend class Auditor;
};

class Auditor {
public:
    void showConfidentialData(const BankAccount& account) const {
        std::cout << "Owner: " << account.owner_ << "\n";
        std::cout << "Balance: " << account.balance_ << "\n";
    }

    bool isLowBalance(const BankAccount& account, double threshold) const {
        return account.balance_ < threshold;
    }
};

int main() {
    BankAccount account{"Alex", 1250.50};
    Auditor auditor;

    auditor.showConfidentialData(account);

    if (auditor.isLowBalance(account, 1500.0)) {
        std::cout << "Alert: Balance is below threshold\n";
    } else {
        std::cout << "Balance is healthy\n";
    }

    // Interview points:
    // 1. Friend class gives all its methods access to private/protected data.
    // 2. Use carefully: it increases coupling between classes.
    // 3. Good for tightly related helper classes (auditor, serializer, operator utilities).

    return 0;
}
