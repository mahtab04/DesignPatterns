# Multilevel Inheritance (C++)

## Definition
Multilevel inheritance means a class derives from another derived class.

Example chain:
- `Animal` (base)
- `Mammal : Animal`
- `Dog : Mammal`

So `Dog` gets members from both `Mammal` and `Animal`.

## Interview Quick Line
"In multilevel inheritance, inheritance happens in levels. A derived class can indirectly inherit base behavior through an intermediate class."

## Minimal Example Flow
- `dog.eat()` from `Animal`
- `dog.walk()` from `Mammal`
- `dog.bark()` from `Dog`

## Caution
Use multilevel inheritance when relationship is truly hierarchical. If hierarchy grows too deep, readability and maintenance become harder.

## 5-Year Interview Perspective
- Keep hierarchy depth small; deep trees are hard to refactor safely.
- Prefer composition when features vary orthogonally.
- If you must keep hierarchy, document responsibilities per layer clearly.
