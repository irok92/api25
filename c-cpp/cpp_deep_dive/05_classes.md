# C++ Deep Dive: Classes

Classes are the cornerstone of object-oriented programming in C++. A class is a user-defined type that bundles data (member variables) and functions that operate on that data (member functions).

## 1. Defining a Class

- **`class` vs. `struct`**: The only difference is the default access level.
    - `class`: Default access for members is `private`.
    - `struct`: Default access for members is `public`.
    By convention, `struct` is used for simple data aggregates, while `class` is used for types with complex behavior and invariants.

```cpp
class MyClass {
    // Members are private by default
    int data;
public:
    void set_data(int d) { data = d; }
};

struct MyStruct {
    // Members are public by default
    int data;
};
```

## 2. Access Specifiers

- **`public`**: Members are accessible from anywhere.
- **`private`**: Members are only accessible by other member functions of the same class (and `friend`s).
- **`protected`**: Members are accessible by member functions of the same class and by member functions of derived classes.

## 3. Constructors

A constructor is a special member function that initializes an object when it is created. It has the same name as the class and no return type.

- **Default Constructor**: A constructor that can be called with no arguments.
    ```cpp
    class A {
    public:
        A() { /* ... */ } // User-defined default constructor
    };
    A a; // Calls default constructor
    ```
- **Parameterized Constructor**: A constructor that accepts arguments.
    ```cpp
    class B {
        int value;
    public:
        B(int v) : value(v) {} // Use member initializer list
    };
    B b(42);
    ```
- **Copy Constructor**: Initializes an object from another object of the same type.
    ```cpp
    class C {
    public:
        C() {}
        C(const C& other) { /* copy logic */ }
    };
    C c1;
    C c2 = c1; // Calls copy constructor
    ```
- **Move Constructor (C++11)**: Initializes an object by "stealing" resources from a temporary (rvalue) object.
    ```cpp
    class D {
        int* data;
    public:
        D(D&& other) noexcept : data(other.data) {
            other.data = nullptr;
        }
    };
    ```

## 4. Destructor

A special member function that is called when an object is destroyed. It's used to release resources (e.g., free memory, close files). It has the same name as the class, preceded by a tilde (`~`), and has no parameters or return type.

```cpp
class MyClass {
    int* data;
public:
    MyClass() : data(new int[100]) {}
    ~MyClass() {
        delete[] data; // Release resources
    }
};
```

## 5. Member Functions

- **`const` Member Functions**: A `const` member function promises not to modify the object's state. It can be called on `const` objects.
    ```cpp
    class MyClass {
        int value;
    public:
        int get_value() const { // This function cannot change 'value'
            return value;
        }
    };
    ```
- **`static` Member Variables and Functions**:
    - **`static` member variable**: A single copy of the variable is shared among all objects of the class.
    - **`static` member function**: Can be called without creating an object of the class. It can only access `static` member variables.
    ```cpp
    class Counter {
    public:
        static int count; // Declaration
        static void increment() { count++; }
    };
    int Counter::count = 0; // Definition

    Counter::increment(); // Call static function
    ```

## 6. The `this` Pointer

Inside a non-static member function, the `this` keyword is a pointer to the object on which the function was called.

```cpp
class Point {
    int x, y;
public:
    Point& move(int dx, int dy) {
        this->x += dx;
        this->y += dy;
        return *this; // Return a reference to the current object for chaining
    }
};
Point p;
p.move(1, 2).move(3, 4); // Chaining calls
```
