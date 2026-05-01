// Topic: Friend Function (Interview-Oriented)
// Standard: C++20
// Build: g++ -std=c++20 -o FriendFunctionExample FriendFunctionExample.cpp

#include <iostream>

class Box {
private:
    int length_;
    int width_;
    int height_;

public:
    Box(int l, int w, int h) : length_{l}, width_{w}, height_{h} {}

    int volume() const {
        return length_ * width_ * height_;
    }

    // Friend function declaration.
    // This non-member function can access private members of Box.
    friend void compareVolume(const Box& a, const Box& b);
};

void compareVolume(const Box& a, const Box& b) {
    int volumeA = a.length_ * a.width_ * a.height_;
    int volumeB = b.length_ * b.width_ * b.height_;

    std::cout << "Box A Volume: " << volumeA << "\n";
    std::cout << "Box B Volume: " << volumeB << "\n";

    if (volumeA > volumeB) {
        std::cout << "Box A is larger\n";
    } else if (volumeA < volumeB) {
        std::cout << "Box B is larger\n";
    } else {
        std::cout << "Both boxes have equal volume\n";
    }
}

int main() {
    Box box1{4, 5, 6};
    Box box2{3, 7, 6};

    compareVolume(box1, box2);

    // Interview points:
    // 1. Friend function is NOT a member of class.
    // 2. It is declared inside class with keyword 'friend'.
    // 3. It can directly access private/protected members.
    // 4. Friendship is not inherited and not mutual by default.

    return 0;
}
