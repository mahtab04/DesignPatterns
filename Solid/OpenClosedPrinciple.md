# Open/Closed Principle (OCP)

## Definition
> Software entities (classes, modules, functions) should be **open for extension** but **closed for modification**.

## Key Idea
You should be able to add new behavior to a system **without changing existing code**. This is typically achieved through **abstraction** — interfaces, abstract classes, and polymorphism.

## Why It Matters
- **Stability**: Existing, tested code is not modified, reducing the risk of introducing bugs.
- **Extensibility**: New features can be added by writing new classes rather than editing old ones.
- **Scalability**: The codebase grows by addition, not by alteration.

## Violation Example
An `AreaCalculator` class that uses `if/else` or `typeid` checks to determine which shape it's dealing with:

```cpp
if (typeid(*shape) == typeid(Rectangle)) { ... }
else if (typeid(*shape) == typeid(Circle)) { ... }
```

Every time a new shape (e.g., Triangle) is added, you must **modify** `AreaCalculator` — violating OCP.

## Correct Approach
Define an abstract base class `Shape` with a pure virtual method `calculate_area()`:

```cpp
class Shape {
public:
    virtual float calculate_area() = 0;
};
```

Each shape (Rectangle, Circle, Triangle, etc.) **extends** `Shape` and provides its own implementation. The calculator just calls `calculate_area()` on any `Shape*` — no modification needed.

| Adding a new shape | Without OCP | With OCP |
|---|---|---|
| Modify existing code? | Yes — edit AreaCalculator | No |
| Risk of breaking things? | High | Low |
| Where does new code go? | Inside existing class | New class file |

## Real-World Analogy
Think of a **USB port**:
- The port specification is **closed for modification** — you don't redesign the port for every new device.
- But it's **open for extension** — you can plug in a keyboard, mouse, flash drive, etc.

## Techniques to Achieve OCP
1. **Abstract classes / Interfaces** — Define contracts that new types implement.
2. **Polymorphism** — Use base class pointers/references to call derived behavior.
3. **Strategy Pattern** — Inject behavior via composition instead of hard-coding it.
4. **Template Method Pattern** — Define a skeleton algorithm with overridable steps.

## Rules of Thumb
1. If adding a new feature requires modifying existing `if/else` or `switch` chains, OCP is being violated.
2. Favor **composition and polymorphism** over conditional logic.
3. Design for extension from the start — think about what's likely to change.
