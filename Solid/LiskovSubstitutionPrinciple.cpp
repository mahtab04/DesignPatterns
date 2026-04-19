// Liskov Substitution Principle
// Objects of a superclass should be replaceable with objects of a subclass
// without affecting the correctness of the program. If class B is a subclass of
// class A, we should be able to pass B to any method that expects A and the
// behavior should remain correct.

#include <iostream>
#include <memory>
#include <string>
#include <vector>

// ========================
// Without LSP (Violation)
// ========================

// Classic Rectangle-Square problem
class BadRectangle
{
protected:
  int width, height;

public:
  BadRectangle(int w, int h) : width(w), height(h) {}

  virtual void setWidth(int w) { width = w; }
  virtual void setHeight(int h) { height = h; }

  int getWidth() const { return width; }
  int getHeight() const { return height; }
  int area() const { return width * height; }
};

// Square overrides setWidth and setHeight to keep sides equal
// This BREAKS the expected behavior of Rectangle
class BadSquare : public BadRectangle
{
public:
  BadSquare(int side) : BadRectangle(side, side) {}

  void setWidth(int w) override
  {
    width = w;
    height = w; // Forces height = width
  }

  void setHeight(int h) override
  {
    width = h; // Forces width = height
    height = h;
  }
};

// This function expects a Rectangle to behave like a Rectangle
// But when a Square is passed, the result is unexpected
void printArea(BadRectangle &rect)
{
  rect.setWidth(5);
  rect.setHeight(10);
  // Expected area: 5 * 10 = 50
  std::cout << "Expected area: 50, Got: " << rect.area() << std::endl;
}

// ========================
// With LSP (Correct)
// ========================

// Use a common abstract Shape base class
class Shape
{
public:
  virtual ~Shape() = default;
  virtual double area() const = 0;
  virtual std::string name() const = 0;
};

class Rectangle : public Shape
{
private:
  double width, height;

public:
  Rectangle(double w, double h) : width(w), height(h) {}

  void setWidth(double w) { width = w; }
  void setHeight(double h) { height = h; }

  double area() const override { return width * height; }
  std::string name() const override { return "Rectangle"; }
};

class Square : public Shape
{
private:
  double side;

public:
  Square(double s) : side(s) {}

  void setSide(double s) { side = s; }

  double area() const override { return side * side; }
  std::string name() const override { return "Square"; }
};

class Circle : public Shape
{
private:
  double radius;

public:
  Circle(double r) : radius(r) {}

  double area() const override { return 3.14159 * radius * radius; }
  std::string name() const override { return "Circle"; }
};

// This function works correctly with ANY Shape — LSP is satisfied
void printShapeArea(const Shape &shape)
{
  std::cout << shape.name() << " area: " << shape.area() << std::endl;
}

int main()
{
  std::cout << "=== Without LSP (Violation) ===" << std::endl;
  BadRectangle rect(5, 10);
  BadSquare sq(5);

  printArea(rect); // Works fine: area = 50
  printArea(sq);   // BROKEN: area = 100 instead of 50

  std::cout << "\n=== With LSP (Correct) ===" << std::endl;
  Rectangle r(5, 10);
  Square s(7);
  Circle c(5);

  // All shapes can be substituted without breaking behavior
  printShapeArea(r);
  printShapeArea(s);
  printShapeArea(c);

  // Works with polymorphism too
  std::vector<std::unique_ptr<Shape>> shapes;
  shapes.push_back(std::make_unique<Rectangle>(4, 6));
  shapes.push_back(std::make_unique<Square>(5));
  shapes.push_back(std::make_unique<Circle>(3));

  std::cout << "\nAll shapes via polymorphism:" << std::endl;
  for (const auto &shape : shapes)
  {
    printShapeArea(*shape);
  }

  return 0;
}
