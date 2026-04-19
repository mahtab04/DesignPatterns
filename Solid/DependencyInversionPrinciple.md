# Dependency Inversion Principle (DIP)

## Definition
> 1. **High-level modules should not depend on low-level modules.** Both should depend on abstractions.
> 2. **Abstractions should not depend on details.** Details should depend on abstractions.

## Key Idea
Instead of high-level business logic directly depending on concrete low-level implementations (database, file system, network), both should depend on an **interface/abstraction**. This inverts the traditional dependency direction.

## Why It Matters
- **Loose Coupling**: High-level modules are independent of low-level implementation details.
- **Easy Swapping**: You can replace a database, logger, or service without touching business logic.
- **Testability**: You can inject mocks or stubs for unit testing.
- **Maintainability**: Changes in low-level modules don't cascade into high-level policy.

## Violation Example

```cpp
class MySQLDatabase {
public:
    void save(const std::string& data) { /* MySQL-specific save */ }
};

class UserService {
private:
    MySQLDatabase db;  // Directly depends on concrete class!
public:
    void createUser(const std::string& name) {
        db.save(name);
    }
};
```

`UserService` is tightly coupled to `MySQLDatabase`. Switching to PostgreSQL or an in-memory database requires modifying `UserService`.

## Correct Approach
Introduce an abstraction (interface):

```cpp
class IDatabase {
public:
    virtual void save(const std::string& data) = 0;
    virtual ~IDatabase() = default;
};

class MySQLDatabase : public IDatabase {
public:
    void save(const std::string& data) override { /* MySQL save */ }
};

class PostgreSQLDatabase : public IDatabase {
public:
    void save(const std::string& data) override { /* PostgreSQL save */ }
};

class UserService {
private:
    IDatabase& db;  // Depends on abstraction!
public:
    UserService(IDatabase& database) : db(database) {}
    void createUser(const std::string& name) {
        db.save(name);
    }
};
```

Now `UserService` depends only on `IDatabase`. You can inject any implementation:

```cpp
MySQLDatabase mysql;
UserService service(mysql);  // or PostgreSQLDatabase, or MockDatabase
```

## Dependency Direction

| Without DIP | With DIP |
|---|---|
| `UserService` → `MySQLDatabase` | `UserService` → `IDatabase` ← `MySQLDatabase` |
| High depends on Low | Both depend on Abstraction |

## Real-World Analogy
Think of a **wall socket**:
- Your lamp doesn't care if power comes from solar, wind, or coal.
- It depends on the **socket interface** (abstraction), not the power plant (concrete implementation).
- The power plant also conforms to the socket standard.

Both the lamp and the power plant depend on the abstraction (socket standard), not on each other.

## Techniques to Achieve DIP
1. **Constructor Injection** — Pass dependencies via the constructor.
2. **Setter Injection** — Provide a setter method to assign dependencies.
3. **Interface Injection** — The dependency provides an injector method.
4. **Abstract Factory Pattern** — Create objects through an abstract factory interface.

## Rules of Thumb
1. If you see `new ConcreteClass()` inside a high-level module, DIP is likely violated.
2. Depend on **interfaces**, not on **concrete classes**.
3. Use **dependency injection** to provide concrete implementations at runtime.
4. High-level policy should define the interface; low-level modules should implement it.
