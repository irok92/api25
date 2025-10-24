# Constraints and concepts

## Constraints and concepts

### [Constraints and concepts](https://en.cppreference.com/w/cpp/language/constraints.html) (C++20)

**Code-related Keywords:**
- `concept Name = constraint;` - Define concept (C++20)
- `requires` clause - Specify requirements
- `template<ConceptName T>` - Constrained template parameter
- Standard concepts - `std::integral`, `std::floating_point`, etc.

**Theory Keywords:**
- **concept** - Named set of requirements (C++20)
- **constraint** - Compile-time predicate on template arguments
- **better errors** - Clear messages when requirements not met
- **concept-based overloading** - Overload on concepts

**Example:**
```cpp
#include <concepts>

// Define concept:
template<typename T>
concept Numeric = std::is_arithmetic_v<T>;  // int, float, double, etc.

// Use concept:
template<Numeric T>
T add(T a, T b) {         // T must be Numeric
    return a + b;
}

auto x = add(3, 5);       // OK: int is Numeric
auto y = add(1.5, 2.7);   // OK: double is Numeric
// auto z = add("a", "b"); // ERROR: const char* not Numeric

// Requires clause:
template<typename T>
requires std::integral<T>  // T must be integral
T multiply(T a, T b) {
    return a * b;
}

// Compound concept:
template<typename T>
concept Comparable = requires(T a, T b) {
    { a < b } -> std::convertible_to<bool>;
    { a > b } -> std::convertible_to<bool>;
};

template<Comparable T>
T max(T a, T b) {
    return a > b ? a : b;
}

// Concept-based overloading:
template<std::integral T>
void process(T value) {
    std::cout << "Integer: " << value << '\n';
}

template<std::floating_point T>
void process(T value) {
    std::cout << "Float: " << value << '\n';
}

process(42);              // "Integer: 42"
process(3.14);            // "Float: 3.14"
```

### [requires expression](https://en.cppreference.com/w/cpp/language/requires.html) (C++20)

**Code-related Keywords:**
- `requires { ... }` - Inline requirements (C++20)
- Simple requirement - [Expression](../../04_expressions/expressions.md) must be valid
- Type requirement - `typename T::type;`
- Compound requirement - `{ expr } -> Concept;`
- Nested requirement - `requires Concept<T>;`

**Theory Keywords:**
- **requirements** - What must be valid for template instantiation
- **validation** - Compile-time checking

**Example:**
```cpp
// Simple requirement:
template<typename T>
concept Addable = requires(T a, T b) {
    a + b;                // Must support operator+
};

// Type requirement:
template<typename T>
concept HasValueType = requires {
    typename T::value_type;  // Must have nested type
};

// Compound requirement (return type check):
template<typename T>
concept Incrementable = requires(T x) {
    { ++x } -> std::same_as<T&>;  // ++x returns T&
    { x++ } -> std::same_as<T>;   // x++ returns T
};

// Nested requirement:
template<typename T>
concept Copyable = requires {
    requires std::is_copy_constructible_v<T>;
    requires std::is_copy_assignable_v<T>;
};

// Complex example:
template<typename T>
concept Container = requires(T c) {
    typename T::value_type;       // Has value_type
    typename T::iterator;         // Has iterator
    { c.begin() } -> std::same_as<typename T::iterator>;
    { c.end() } -> std::same_as<typename T::iterator>;
    { c.size() } -> std::convertible_to<std::size_t>;
};

template<Container C>
void printSize(const C& container) {
    std::cout << container.size() << '\n';
}

std::vector<int> v = {1, 2, 3};
printSize(v);             // OK: vector satisfies Container
// printSize(42);         // ERROR: int doesn't satisfy Container
```
