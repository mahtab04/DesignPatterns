# Liskov Substitution Principle (LSP)

## Definition
> Objects of a superclass should be **replaceable with objects of a subclass** without affecting the correctness of the program.

*Introduced by Barbara Liskov in 1987.*

## Key Idea
If class `B` is a subclass of class `A`, then you should be able to use `B` anywhere `A` is expected **without surprises**. The subclass must honor the contract (behavior, preconditions, postconditions) of the parent class.

## Why It Matters
- **Correctness**: Code using a base class reference works correctly regardless of which derived class is actually used.
- **Polymorphism Safety**: You can trust that substituting a subclass won't break existing logic.
- **Design Integrity**: Prevents misuse of inheritance for code reuse when "is-a" doesn't truly hold.

## Violation Example
A classic example — `Square` inheriting from `Rectangle`:

```cpp
class Rectangle {
public:
    virtual void setWidth(int w) { width = w; }
    virtual void setHeight(int h) { height = h; }
    int area() { return width * height; }
protected:
    int width, height;
};

class Square : public Rectangle {
public:
    void setWidth(int w) override { width = height = w; }
    void setHeight(int h) override { width = height = h; }
};
```

A function expecting a `Rectangle*` might set width=5 and height=10, expecting area=50. But if a `Square` is passed, area becomes 100 — **the contract is broken**.

## Correct Approach
- Don't make `Square` inherit from `Rectangle` if it can't honor `Rectangle`'s contract.
- Use a common abstract `Shape` base class instead.
- Or use composition rather than inheritance.

## Rules for LSP Compliance
| Rule | Description |
|---|---|
| **Preconditions** | A subclass must not strengthen preconditions (must accept at least what parent accepts) |
| **Postconditions** | A subclass must not weaken postconditions (must deliver at least what parent promises) |
| **Invariants** | A subclass must preserve all invariants of the parent |
| **History constraint** | A subclass should not introduce state changes the parent doesn't allow |

## Real-World Analogy
If you order a **"vehicle"** for transport and receive a **car**, that works. If you receive a **toy car**, it technically "is a" vehicle but it can't transport you — the substitution breaks the contract.

## Rules of Thumb
1. If a subclass throws exceptions for methods it inherits, LSP is likely violated.
2. If you need to check the actual type of an object before using it, LSP may be violated.
3. "Is-a" in the real world doesn't always mean "is-a" in code — validate the behavioral contract.
4. Prefer **composition over inheritance** when in doubt.
