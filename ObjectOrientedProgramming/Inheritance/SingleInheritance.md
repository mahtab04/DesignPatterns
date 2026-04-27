# Inheritance (C++)

## Definition
Inheritance allows one class (**derived**) to acquire properties/behaviors of another class (**base**).

## Minimal Example
- `Animal` = base class with `eat()`
- `Dog` = derived class that reuses `eat()` and adds `bark()`

## Interview Quick Line
"Inheritance is an *is-a* relationship. A `Dog` is an `Animal`, so it can reuse `Animal` behavior and add specific behavior."

## Common Interview Points
- Use inheritance for real **is-a** relationships.
- Prefer `public` inheritance for behavioral substitutability.
- Don’t overuse inheritance when composition can do better.

## 5-Year Interview Perspective
- Ask first: "Do I need subtype polymorphism or just code reuse?"
- Keep base classes cohesive and behavior-focused, not data-heavy.
- Avoid fragile base class design by minimizing virtual surface area.
