# Single Responsibility Principle (SRP)

## Definition
> A class should have only **one reason to change**, meaning it should have only **one job** or **one responsibility**.

## Key Idea
Each class or module should be responsible for a single part of the functionality provided by the software. If a class handles multiple concerns, changes to one concern may break or affect the other.

## Why It Matters
- **Reduced Coupling**: When a class has a single responsibility, changes in one area of the system don't ripple into unrelated areas.
- **Easier Testing**: A class doing one thing is simpler to test in isolation.
- **Better Readability**: Smaller, focused classes are easier to understand.
- **Easier Maintenance**: Bug fixes and feature additions are localized to the relevant class.

## Violation Example
A `TodoList` class that:
- Manages tasks (add/delete)
- Handles display/output (printing to console)
- Handles user input (reading from stdin)

All three responsibilities are bundled together. If you change how tasks are displayed, you risk breaking task management logic.

## Correct Approach
Split into focused classes:
| Class | Responsibility |
|---|---|
| `TaskManager` | Manages the task data (add, delete, retrieve) |
| `TaskUI` | Displays tasks to the user |
| `TaskInput` | Handles reading user input |

Each class now has **one reason to change**.

## Real-World Analogy
Think of a restaurant:
- The **chef** cooks food (one job).
- The **waiter** serves customers (one job).
- The **cashier** handles payments (one job).

If the chef also had to serve food and collect payments, any change in billing would affect cooking — that's a violation of SRP.

## Rules of Thumb
1. If you can describe what a class does using "and", it probably has too many responsibilities.
2. A class should have only one reason to change.
3. Separate **what** something does from **how** it presents or persists the result.
