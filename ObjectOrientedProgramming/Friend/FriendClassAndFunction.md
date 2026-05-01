# Friend Function and Friend Class (C++)

## What is a Friend Function?
A **friend function** is a non-member function that can access private and protected members of a class.

### Syntax
```cpp
class A {
    friend void helper(A& obj);
};
```

### Key Interview Points
- It is **not** a class member.
- It is declared using `friend` inside the class.
- Useful when operation logically needs access to internals but should remain non-member.
- Common usage: operator overloading (`operator<<`, `operator>>`).

## What is a Friend Class?
A **friend class** can access private/protected members of another class.

### Syntax
```cpp
class B;

class A {
    friend class B;
};
```

### Key Interview Points
- Friendship is granted explicitly by host class.
- Friendship is **not mutual** by default.
- Friendship is **not inherited**.
- Use sparingly because it increases coupling.

## Interview-Oriented Q&A

### Q1: Why use friend if encapsulation is important?
A: Friend is an exception used for tightly coupled utilities where exposing public getters would weaken design or add noisy APIs.

### Q2: Is friend function part of polymorphism?
A: No. Friend controls access, not dynamic dispatch.

### Q3: Is friend relationship transitive?
A: No. If A is friend of B and B is friend of C, A is not automatically friend of C.

### Q4: Can friendship be revoked?
A: Yes, by removing `friend` declaration and recompiling.

## Practical Rule for Interviews
Use this line:
"I use friend only when two entities are tightly related and public APIs would expose unnecessary internals. Otherwise, I prefer regular member/public interface design."

## Files in this folder
- `FriendFunctionExample.cpp`
- `FriendClassExample.cpp`
- `FriendClassAndFunction.md`
