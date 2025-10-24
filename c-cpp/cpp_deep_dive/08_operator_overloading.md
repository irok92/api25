# C++ Deep Dive: Operator Overloading

Operator overloading allows you to define the behavior of C++ operators for your own user-defined types (classes and structs). This can make code more intuitive and readable, as it lets your types behave like built-in types.

## 1. Basics of Operator Overloading

An operator is overloaded by writing a function with the name `operator@`, where `@` is the operator you want to overload (e.g., `operator+`, `operator==`).

An operator can be overloaded as:
- A non-static member function.
- A non-member function (often a `friend` of the class to access its private members).

### Example: A `Point` Class

```cpp
class Point {
public:
    int x, y;

    Point(int x = 0, int y = 0) : x(x), y(y) {}

    // Overload '+' as a member function
    Point operator+(const Point& other) const {
        return Point(x + other.x, y + other.y);
    }
};

// Overload '<<' for std::ostream as a non-member function
std::ostream& operator<<(std::ostream& os, const Point& p) {
    os << "(" << p.x << ", " << p.y << ")";
    return os;
}

Point p1(1, 2), p2(3, 4);
Point p3 = p1 + p2; // p3 is (4, 6)
std::cout << p3;    // Prints (4, 6)
```

## 2. Member vs. Non-Member Functions

- **Member Function**:
    - The left-hand operand is the object calling the function (`*this`).
    - Used for operators that modify the state of the object (e.g., `+=`, `++`).
    - Required for assignment (`=`), subscript (`[]`), call (`()`), and member access (`->`).
- **Non-Member Function**:
    - Used for symmetric operators where the left-hand operand might not be an object of your class (e.g., `ostream << my_obj`) or might need type conversion.
    - The left-hand operand is the first parameter.
    - Often declared as `friend` to access private members.

```cpp
class Value {
    int v;
public:
    // Member function for compound assignment
    Value& operator+=(const Value& rhs) {
        this->v += rhs.v;
        return *this;
    }

    // Friend non-member function for symmetric addition
    friend Value operator+(Value lhs, const Value& rhs) {
        lhs += rhs; // Reuse +=
        return lhs;
    }
};
```

## 3. Commonly Overloaded Operators

- **Arithmetic Operators**: `+`, `-`, `*`, `/`, `%`
- **Comparison Operators**: `==`, `!=`, `<`, `>`, `<=`, `>=`
- **Compound Assignment**: `+=`, `-=`, `*=`, etc.
- **Increment/Decrement**: `++`, `--`
    - **Prefix**: `MyType& operator++()`
    - **Postfix**: `MyType operator++(int)` (The `int` is a dummy parameter to differentiate from prefix).
- **Subscript Operator `[]`**: Often returns a reference to allow assignment.
    ```cpp
    class MyArray {
        int data[10];
    public:
        int& operator[](int index) { return data[index]; }
    };
    ```
- **Function Call Operator `()`**: Creates objects that behave like functions (functors).
    ```cpp
    struct Adder {
        int operator()(int a, int b) const {
            return a + b;
        }
    };
    Adder add;
    int sum = add(5, 3); // sum is 8
    ```
- **Stream Insertion/Extraction `<<` and `>>`**: Must be non-member functions.

## 4. Three-Way Comparison Operator `<=>` (C++20)

The "spaceship operator" simplifies comparisons. Overloading `operator<=>` can automatically generate the implementations for `==`, `!=`, `<`, `>`, `<=`, and `>=`.

```cpp
#include <compare>

class Point {
public:
    int x, y;
    // Defaulted three-way comparison
    auto operator<=>(const Point& other) const = default;
};

Point p1{1, 2}, p2{1, 3};
if (p1 < p2) { // This works automatically
    // ...
}
```

## 5. Rules and Restrictions

- You can only overload existing operators. You cannot create new ones (e.g., `operator**`).
- You cannot change the arity (number of operands), precedence, or associativity of an operator.
- At least one operand of an overloaded operator must be a user-defined type.
- The following operators cannot be overloaded: `.` (member access), `.*` (member pointer access), `::` (scope resolution), `?:` (ternary), `sizeof`.
