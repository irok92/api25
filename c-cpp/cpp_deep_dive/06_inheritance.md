# C++ Deep Dive: Inheritance

Inheritance is a fundamental concept of object-oriented programming that allows a new class (the **derived class**) to be based on an existing class (the **base class**). The derived class inherits the members (variables and functions) of the base class, enabling code reuse and the creation of a type hierarchy.

## 1. Basic Inheritance

To create a derived class, you specify the base class after the derived class's name, preceded by an access specifier.

```cpp
class Base {
public:
    void base_function() { /* ... */ }
};

class Derived : public Base { // Derived inherits from Base
public:
    void derived_function() { /* ... */ }
};

Derived d;
d.base_function();    // Accessible from Derived object
d.derived_function();
```

## 2. Inheritance Access Specifiers

The access specifier used in the inheritance declaration determines the access level of the inherited members in the derived class.

- **`public` inheritance**:
    - `public` members of the base class become `public` members of the derived class.
    - `protected` members of the base class become `protected` members of the derived class.
    - This models an "is-a" relationship (e.g., a `Dog` is an `Animal`). This is the most common form of inheritance.
- **`protected` inheritance**:
    - `public` and `protected` members of the base class become `protected` members of the derived class.
- **`private` inheritance**:
    - `public` and `protected` members of the base class become `private` members of the derived class.
    - This models a "has-a" or "is-implemented-in-terms-of" relationship. Composition is often preferred over private inheritance.

## 3. Polymorphism and Virtual Functions

Polymorphism allows objects of different derived classes to be treated as objects of a common base class. This is achieved through **virtual functions**.

- **`virtual` keyword**: When you declare a function in a base class as `virtual`, you allow derived classes to provide their own implementation of that function.
- **Function Overriding**: A derived class provides a specific implementation for a virtual function declared in its base class.
- **`override` keyword (C++11)**: Used to explicitly state that a function is meant to override a base class function. It helps catch errors at compile time (e.g., if the function signature doesn't match).
- **`final` keyword (C++11)**: Specifies that a virtual function cannot be overridden further down the inheritance chain, or that a class cannot be used as a base class.

```cpp
class Shape {
public:
    virtual void draw() const { /* draw generic shape */ }
    virtual ~Shape() = default; // Always make base class destructors virtual!
};

class Circle final : public Shape {
public:
    void draw() const override { /* draw a circle */ }
};

class Square : public Shape {
public:
    void draw() const override { /* draw a square */ }
};

void render_shape(const Shape& s) {
    s.draw(); // Calls the correct draw() based on the object's actual type
}
```
**Why virtual destructors?** If you `delete` a derived object through a base class pointer and the destructor is *not* virtual, only the base class destructor is called, leading to a resource leak. A virtual destructor ensures the correct chain of destructors is called.

## 4. Abstract Classes and Pure Virtual Functions

An **abstract class** is a class that cannot be instantiated on its own and is meant to be used as a base class. A class becomes abstract if it has at least one **pure virtual function**.

A pure virtual function is a virtual function that is declared but has no implementation, indicated by `= 0`. Derived classes *must* provide an implementation for it.

```cpp
class AbstractShape { // This is an abstract class
public:
    virtual void draw() const = 0; // Pure virtual function
    virtual ~AbstractShape() = default;
};

// AbstractShape shape; // Error: cannot instantiate abstract class

class Triangle : public AbstractShape {
public:
    void draw() const override { /* draw a triangle */ } // Must be implemented
};
```

## 5. Multiple Inheritance

A class can inherit from more than one base class.

```cpp
class A { public: void func_a() {} };
class B { public: void func_b() {} };
class C : public A, public B {}; // C inherits from both A and B

C c;
c.func_a();
c.func_b();
```

- **The Diamond Problem**: A common issue in multiple inheritance where a class inherits from two classes that both inherit from the same base class. This creates ambiguity.
- **Virtual Inheritance**: Solves the diamond problem by ensuring that the derived class gets only one copy of the shared base class.
    ```cpp
    class Top { public: int x; };
    class Left : virtual public Top {};
    class Right : virtual public Top {};
    class Bottom : public Left, public Right {};

    Bottom b;
    b.x = 10; // No ambiguity, there is only one 'x'
    ```
