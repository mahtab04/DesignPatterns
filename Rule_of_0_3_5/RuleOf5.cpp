// Rule of 5: Rule of 3 + move constructor + move assignment.
#include <iostream>
#include <utility>

class IntArray {
private:
        int* data;
        std::size_t size;

public:
        IntArray(std::size_t n = 0) : data(n ? new int[n] : nullptr), size(n) {
                for (std::size_t i = 0; i < size; ++i) data[i] = static_cast<int>(i + 1);
        }

        ~IntArray() { delete[] data; }

        IntArray(const IntArray& other) : data(other.size ? new int[other.size] : nullptr), size(other.size) {
                for (std::size_t i = 0; i < size; ++i) data[i] = other.data[i];
        }

        IntArray& operator=(const IntArray& other) {
                if (this == &other) return *this;
                int* temp = other.size ? new int[other.size] : nullptr;
                for (std::size_t i = 0; i < other.size; ++i) temp[i] = other.data[i];
                delete[] data;
                data = temp;
                size = other.size;
                return *this;
        }

        IntArray(IntArray&& other) noexcept : data(other.data), size(other.size) {
                other.data = nullptr;
                other.size = 0;
        }

        IntArray& operator=(IntArray&& other) noexcept {
                if (this == &other) return *this;
                delete[] data;
                data = other.data;
                size = other.size;
                other.data = nullptr;
                other.size = 0;
                return *this;
        }

        void print(const char* label) const {
                std::cout << label << ": ";
                for (std::size_t i = 0; i < size; ++i) std::cout << data[i] << ' ';
                std::cout << '\n';
        }
};

int main() {
        IntArray a(5);
        IntArray b = a;          // copy constructor
        IntArray c;
        c = a;                   // copy assignment

        IntArray d = std::move(a); // move constructor
        IntArray e;
        e = std::move(b);          // move assignment

        c.print("c");
        d.print("d");
        e.print("e");
}
