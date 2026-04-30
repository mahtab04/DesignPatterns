// Rule of 3: if class manages raw memory, define destructor, copy ctor, copy assignment.
#include <cstring>
#include <iostream>

class Buffer {
private:
        char* data;

public:
        Buffer(const char* text = "") {
                data = new char[std::strlen(text) + 1];
                std::strcpy(data, text);
        }

        ~Buffer() {
                delete[] data;
        }

        Buffer(const Buffer& other) {
                data = new char[std::strlen(other.data) + 1];
                std::strcpy(data, other.data);
        }

        Buffer& operator=(const Buffer& other) {
                if (this == &other) return *this;
                char* temp = new char[std::strlen(other.data) + 1];
                std::strcpy(temp, other.data);
                delete[] data;
                data = temp;
                return *this;
        }

        void setFirst(char c) {
                if (data[0] != '\0') data[0] = c;
        }

        void print(const char* label) const {
                std::cout << label << ": " << data << '\n';
        }
};

int main() {
        Buffer a("hello");
        Buffer b = a;   // copy constructor
        b.setFirst('y');

        Buffer c("temp");
        c = a;          // copy assignment

        a.print("a");
        b.print("b");
        c.print("c");
}
