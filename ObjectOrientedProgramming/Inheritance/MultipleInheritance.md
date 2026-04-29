# Multiple Inheritance (C++)

## Definition
Multiple inheritance means a class derives from more than one base class.

Example:
- `Printer`
- `Scanner`
- `AllInOneMachine : Printer, Scanner`

So `AllInOneMachine` can use members from both base classes.

## Interview Quick Line
"Multiple inheritance allows a derived class to combine behavior from two or more base classes in a single type."

## Minimal Example Flow
- `device.print()` from `Printer`
- `device.scan()` from `Scanner`
- `device.fax()` from `AllInOneMachine`

## Caution
Use multiple inheritance carefully. If base classes expose overlapping members, ambiguity can occur. In diamond-shaped hierarchies, C++ uses virtual inheritance to avoid duplicate base subobjects.

## 5-Year Interview Perspective
- Prefer multiple inheritance for combining distinct capabilities, especially interface-like bases.
- Be explicit when discussing ambiguity and the diamond problem.
- If the design mixes stateful base classes heavily, composition is often cleaner.