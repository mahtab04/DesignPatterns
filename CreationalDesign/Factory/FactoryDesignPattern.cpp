// Topic: Factory Pattern
// Standard: C++20
// Build: g++ -std=c++20 -o factory FactoryDesignPattern.cpp

#include <algorithm>
#include <cctype>
#include <iostream>
#include <memory>
#include <string>

class Shape
{
public:
  virtual ~Shape() = default;
  virtual void draw() const = 0;
};

class Circle : public Shape
{
public:
  void draw() const override
  {
    std::cout << "Drawing Circle\n";
  }
};

class Rectangle : public Shape
{
public:
  void draw() const override
  {
    std::cout << "Drawing Rectangle\n";
  }
};

class Triangle : public Shape
{
public:
  void draw() const override
  {
    std::cout << "Drawing Triangle\n";
  }
};

class ShapeFactory
{
public:
  static std::unique_ptr<Shape> createShape(std::string type)
  {

    if (type == "circle")
      return std::make_unique<Circle>();

    if (type == "rectangle")
      return std::make_unique<Rectangle>();

    if (type == "triangle")
      return std::make_unique<Triangle>();

    return nullptr;
  }
};

int main()
{
  std::cout << "=== Factory Pattern ===\n\n";

  auto circle = ShapeFactory::createShape("circle");
  auto rectangle = ShapeFactory::createShape("rectangle");
  auto triangle = ShapeFactory::createShape("triangle");
  auto invalid = ShapeFactory::createShape("hexagon");

  if (circle)
    circle->draw();

  if (rectangle)
    rectangle->draw();

  if (triangle)
    triangle->draw();

  if (!invalid)
    std::cout << "Unknown shape type requested\n";

  return 0;
}
