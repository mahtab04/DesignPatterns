// Open Closed Principle
// Software entities should be open for extension but closed for modification.
// In other words, the behavior of a module can be extended without modifying its source code.
// This principle is achieved by using interfaces and abstract classes.

#include <iostream>
#include <string>
#include <vector>
#include <typeinfo>

// Without OCP

class Rectangle
{
public:
    double width, height;
    Rectangle(double w, double h) : width(w), height(h) {}
};

class Circle
{
public:
    double radius;
    Circle(double r) : radius(r) {}
};

class AreaCalculator
{
public:
    void calculate_area(const std::vector<void *> &shapes)
    {
        for (const auto &shape : shapes)
        {
            if (typeid(*shape) == typeid(Rectangle))
            {
                Rectangle *rect = static_cast<Rectangle *>(shape);
                std::cout << "Rectangle area: " << rect->width * rect->height << std::endl;
            }
            else if (typeid(*shape) == typeid(Circle))
            {
                Circle *circle = static_cast<Circle *>(shape);
                std::cout << "Circle area: " << 3.14 * circle->radius * circle->radius << std::endl;
            }
        }
    }
};

// With OCP

class Shape
{
public:
    virtual float calculate_area() = 0;
};

class Rectangle : public Shape
{
private:
    float width, height;

public:
    Rectangle(float w, float h) : width(w), height(h) {}

    float calculate_area() override
    {
        return width * height;
    }
};

class Circle : public Shape
{
private:
    float radius;

public:
    Circle(float r) : radius(r) {}

    float calculate_area() override
    {
        return radius * radius * 3.14;
    }
};
