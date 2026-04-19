# Interface Segregation Principle (ISP)

## Definition
> **No client should be forced to depend on methods it does not use.** Prefer many small, specific interfaces over one large, general-purpose interface.

## Key Idea
Instead of creating one "fat" interface that covers everything, break it into smaller, focused interfaces. Classes then implement only the interfaces relevant to them.

## Why It Matters
- **Decoupling**: Clients depend only on what they actually use.
- **Flexibility**: Adding new capabilities doesn't force changes on unrelated classes.
- **Cleaner Code**: No empty or dummy method implementations just to satisfy an interface.
- **Easier Testing**: Smaller interfaces are easier to mock and test.

## Violation Example
A single `IWorker` interface that forces all workers to implement every method:

```cpp
class IWorker {
public:
    virtual void work() = 0;
    virtual void eat() = 0;
    virtual void sleep() = 0;
    virtual void code() = 0;
    virtual void manage() = 0;
};
```

A `Developer` doesn't need `manage()`, and a `Manager` doesn't need `code()`. Both are forced to provide dummy implementations or throw exceptions — violating ISP.

## Correct Approach
Split into focused interfaces:

```cpp
class IWorkable {
public:
    virtual void work() = 0;
};

class IFeedable {
public:
    virtual void eat() = 0;
};

class ICodable {
public:
    virtual void code() = 0;
};

class IManageable {
public:
    virtual void manage() = 0;
};
```

Now each class picks only the interfaces it needs:

| Class | Implements |
|---|---|
| `Developer` | `IWorkable`, `IFeedable`, `ICodable` |
| `Manager` | `IWorkable`, `IFeedable`, `IManageable` |
| `Robot` | `IWorkable` (no eating or sleeping!) |

## Real-World Analogy
Think of a **TV remote control**:
- A basic TV only needs power, volume, and channel buttons.
- A smart TV also needs streaming, browser, and app buttons.

Forcing a basic TV to have all the smart TV buttons is wasteful. Better to have separate "remote modules" — basic controls + optional smart controls.

## Rules of Thumb
1. If a class implementing an interface leaves methods empty or throws "not supported" exceptions, the interface is too fat.
2. Create interfaces based on **client needs**, not on class capabilities.
3. It's better to have many small interfaces than one big one.
4. In C++, use **multiple inheritance** of pure abstract classes to achieve interface segregation.
