// Rule of 0: keep only STL members and write no special member functions.
#include <iostream>
#include <string>
#include <vector>

class Student {
private:
        std::string name;
        std::vector<int> marks;

public:
        Student(std::string n, std::vector<int> m) : name(std::move(n)), marks(std::move(m)) {}

        void print() const {
                std::cout << name << ": ";
                for (int x : marks) std::cout << x << ' ';
                std::cout << '\n';
        }
};

int main() {
        Student a("Alice", {90, 80});
        Student b = a;            // compiler-generated copy
        Student c = std::move(a); // compiler-generated move

        b.print();
        c.print();
}
