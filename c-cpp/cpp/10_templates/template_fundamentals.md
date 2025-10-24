# Template fundamentals

## Template fundamentals

### [Template parameters](https://en.cppreference.com/w/cpp/language/template_parameters.html)

**Code-related Keywords:**
- `template<typename T>` - Type parameter
- `template<class T>` - Same as typename
- `template<int N>` - Non-type parameter (value)
- `template<template<typename> class C>` - Template template parameter
- Default parameter - `template<typename T = int>`

**Theory Keywords:**
- **type parameter** - Placeholder for any type
- **non-type parameter** - Compile-time constant value
- **parameter constraints** - Requirements on template arguments

**Example:**
```cpp
// Type parameter:
template<typename T>
T add(T a, T b) { return a + b; }

// Multiple type parameters:
template<typename Key, typename Value>
class Map { };

// Non-type parameter:
template<int N>
int factorial() {
    return N * factorial<N-1>();
}
template<>
int factorial<0>() { return 1; }  // Specialization

constexpr int f5 = factorial<5>();  // 120 at compile time

// Default parameter:
template<typename T = int, int Size = 10>
class Array {
    T data[Size];
};

Array<> arr1;             // Array<int, 10>
Array<double> arr2;       // Array<double, 10>
Array<char, 20> arr3;     // Array<char, 20>

// Template template parameter:
template<typename T, template<typename> class Container>
class Wrapper {
    Container<T> data;
};

Wrapper<int, std::vector> w;  // Container = std::vector
```

### [Template arguments](https://en.cppreference.com/w/cpp/language/template_arguments.html)

**Code-related Keywords:**
- `ClassName<Type>` - Explicit template argument
- Deduction - Compiler infers arguments
- `constexpr` values - For non-type parameters

**Theory Keywords:**
- **instantiation** - Creating concrete type from template
- **explicit vs deduced** - Specified vs inferred arguments
- **argument matching** - Rules for deducing template arguments

**Example:**
```cpp
template<typename T>
void print(T value) {
    std::cout << value << '\n';
}

// Explicit argument:
print<int>(42);           // Explicit: T = int

// Deduced argument:
print(3.14);              // Deduced: T = double
print("hello");           // Deduced: T = const char*

// Non-type arguments:
template<typename T, int Size>
class Buffer {
    T data[Size];
public:
    int size() const { return Size; }
};

Buffer<int, 100> buf;     // T = int, Size = 100
constexpr int N = 50;
Buffer<double, N> buf2;   // constexpr value

// Multiple arguments:
template<typename T, typename U>
auto max(T a, U b) -> decltype(a > b ? a : b) {
    return a > b ? a : b;
}

auto m = max(10, 3.14);   // T = int, U = double, returns double
```
