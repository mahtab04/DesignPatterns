# Rule of 0, 3, 5 - Interview Cheat Sheet

## Rule of 0 (Best Default)
What to say:
Use STL/resource-owning members so compiler-generated special member functions are enough.

When to use:
Class has members like std::string, std::vector, std::unique_ptr.

What to write in interview:
No destructor, no copy ctor, no copy assignment, no move ctor, no move assignment.

---

## Rule of 3 (Classic)
What to say:
If a class owns raw resource memory, and you need one of destructor/copy ctor/copy assignment, you usually need all three.

Why:
Default copy is shallow copy and may cause double delete.

What to write in interview:
1. Destructor
2. Copy constructor (deep copy)
3. Copy assignment (deep copy + self-assignment check)

---

## Rule of 5 (Modern C++)
What to say:
Rule of 3 plus move constructor and move assignment for efficient ownership transfer.

What to write in interview:
1. Destructor
2. Copy constructor
3. Copy assignment
4. Move constructor
5. Move assignment

---

## Quick Difference Line (Good for interviews)
Rule of 3 = correctness for resource ownership.
Rule of 5 = correctness + performance.
Rule of 0 = avoid manual ownership logic when possible.

---

## Common Interview Pitfalls
1. Forgetting self-assignment check in copy assignment.
2. Forgetting to null/reset source object in move operations.
3. Using raw pointers when STL wrappers already solve the problem.

---

## Files in this folder
1. RuleOf0.cpp
2. RuleOf3.cpp
3. RuleOf5.cpp

## Compile
```bash
g++ RuleOf0.cpp -std=c++17 -o rule0
g++ RuleOf3.cpp -std=c++17 -o rule3
g++ RuleOf5.cpp -std=c++17 -o rule5
```
