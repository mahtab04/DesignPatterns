# Design Patterns in C++

A collection of **Design Pattern** and **SOLID Principle** examples implemented in C++.

---

## 📂 Project Structure

```
DesignPatterns/
├── CreationalDesign/
│   ├── Builder Design Pattern/
│   │   └── BuilderDesignPattern.cpp
│   └── SingletonDesign Pattern/
│       ├── DatabaseExample.cpp
│       ├── Logger.cpp
│       └── singletondesignPattern.md
└── Solid/
    ├── SingleResponsibilityPrinciple.md
    ├── singleResponsibilityPrinciple.cpp
    ├── OpenClosedPrinciple.md
    ├── OpenClosedPrinciple.cpp
    ├── LiskovSubstitutionPrinciple.md
    ├── LiskovSubstitutionPrinciple.cpp
    ├── InterfaceSegregationPrinciple.md
    ├── InterfaceSegregationPrinciple.cpp
    ├── DependencyInversionPrinciple.md
    └── DependencyInversionPrinciple.cpp
```

---

## SOLID Principles

Each principle has a **theory doc** (`.md`) and a **C++ implementation** (`.cpp`) showing both a violation and the correct approach.

| # | Principle | Theory | Code |
|---|-----------|--------|------|
| **S** | Single Responsibility Principle | [SRP Theory](Solid/SingleResponsibilityPrinciple.md) | [SRP Code](Solid/singleResponsibilityPrinciple.cpp) |
| **O** | Open/Closed Principle | [OCP Theory](Solid/OpenClosedPrinciple.md) | [OCP Code](Solid/OpenClosedPrinciple.cpp) |
| **L** | Liskov Substitution Principle | [LSP Theory](Solid/LiskovSubstitutionPrinciple.md) | [LSP Code](Solid/LiskovSubstitutionPrinciple.cpp) |
| **I** | Interface Segregation Principle | [ISP Theory](Solid/InterfaceSegregationPrinciple.md) | [ISP Code](Solid/InterfaceSegregationPrinciple.cpp) |
| **D** | Dependency Inversion Principle | [DIP Theory](Solid/DependencyInversionPrinciple.md) | [DIP Code](Solid/DependencyInversionPrinciple.cpp) |

---

## Creational Design Patterns

| Pattern | Example | Code | Documentation |
|---------|---------|------|---|
| **Builder** | Step-by-step object construction | [BuilderDesignPattern.cpp](CreationalDesign/Builder%20Design%20Pattern/BuilderDesignPattern.cpp) | [Theory](CreationalDesign/Builder%20Design%20Pattern/BuilderDesignPattern.md) |
| **Builder** | HTTP Request construction | [HTTPRequestBuilder.cpp](CreationalDesign/Builder%20Design%20Pattern/HTTPRequestBuilder.cpp) | [HTTP Example](CreationalDesign/Builder%20Design%20Pattern/HTTPRequestBuilder.md) |
| **Singleton** | Database connection | [DatabaseExample.cpp](CreationalDesign/SingletonDesign%20Pattern/DatabaseExample.cpp) | [Theory](CreationalDesign/SingletonDesign%20Pattern/singletondesignPattern.md) |
| **Singleton** | Logger instance | [Logger.cpp](CreationalDesign/SingletonDesign%20Pattern/Logger.cpp) | [Theory](CreationalDesign/SingletonDesign%20Pattern/singletondesignPattern.md) |

---

## How to Run

### SOLID Principles (C++17+)
Compile with C++17 or later:

```bash
g++ -std=c++17 -o output Solid/OpenClosedPrinciple.cpp
./output
```

### Creational Design Patterns (C++20)
All creational patterns use C++20 features (primarily `std::format`):

```bash
# Builder Pattern - Computer Configuration
g++ -std=c++20 -o builder CreationalDesign/Builder\ Design\ Pattern/BuilderDesignPattern.cpp
./builder

# Builder Pattern - HTTP Request Construction
g++ -std=c++20 -o http_request CreationalDesign/Builder\ Design\ Pattern/HTTPRequestBuilder.cpp
./http_request

# Singleton - Database Example
g++ -std=c++20 -o database CreationalDesign/SingletonDesign\ Pattern/DatabaseExample.cpp
./database

# Singleton - Logger Example
g++ -std=c++20 -o logger CreationalDesign/SingletonDesign\ Pattern/Logger.cpp
./logger
```

---

## License

This project is for educational purposes.
