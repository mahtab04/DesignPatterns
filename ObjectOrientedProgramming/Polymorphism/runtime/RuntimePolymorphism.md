# Run-time Polymorphism

## What it is
Calling an overridden method through a base class pointer/reference so C++ chooses the derived implementation at runtime.

## Key Requirements
- Base class method must be `virtual`
- Derived class overrides with `override`
- Usually use base pointer/reference in client code

## Example in this folder
- `PaymentMethod` is base interface
- `CreditCard`, `UPI`, `Cash` are concrete implementations
- `checkout()` accepts `const PaymentMethod&` and works with all methods

## Interview Quick Line
"Run-time polymorphism enables flexible behavior selection at execution time via virtual functions and dynamic dispatch."
