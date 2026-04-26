# Polymorphism (C++)

## Definition
**Polymorphism** means "many forms" — the same interface can trigger different behavior depending on the object/type.

## Types in C++

1. **Compile-time polymorphism (Static binding)**
   - Function overloading
   - Operator overloading
   - Templates

2. **Run-time polymorphism (Dynamic binding)**
   - Base pointer/reference + `virtual` function
   - Method is resolved at runtime based on actual object type

## Quick Difference

| Aspect | Compile-time | Run-time |
|---|---|---|
| Binding | Early | Late |
| Mechanism | Overloading/Templates | Virtual functions/override |
| Speed | Faster | Slight runtime overhead |
| Flexibility | Lower | Higher |

## Interview Perspective

### One-liner
"Polymorphism lets us write generic client code using a common interface while behavior changes based on actual type."

### Common Questions
- **Q: Why do we need a virtual destructor in polymorphic base class?**  
  A: To ensure proper cleanup when deleting derived object through base pointer.

- **Q: What is dynamic binding?**  
  A: Selecting overridden virtual function at runtime using vtable mechanism.

- **Q: Overloading vs Overriding?**  
  A: Overloading = same function name, different parameters (compile-time). Overriding = derived class redefines virtual base method (run-time).

### Rule of Thumb
- Use **compile-time polymorphism** when behavior is known at compile time and performance is critical.
- Use **run-time polymorphism** when behavior must vary dynamically through a common interface.
