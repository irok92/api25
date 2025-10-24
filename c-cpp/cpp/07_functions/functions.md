# Functions

## [Functions](https://en.cppreference.com/w/cpp/language/functions.html)

### [Function declaration](https://en.cppreference.com/w/cpp/language/function.html)

**Code-related Keywords:**
- `ReturnType funcName(params);` - Function [declaration](../../05_declarations/declarations.md)
- `ReturnType funcName(params) { }` - Definition
- `void` - No return value
- `return expr;` - Return value
- Function overloading - Same name, different parameters
- `noexcept` - No [exceptions](../../11_exceptions/exceptions.md) thrown

**Theory Keywords:**
- **signature** - Function name + parameter types (not return type)
- **function prototype** - Declaration without definition
- **return value optimization (RVO)** - Compiler optimization avoiding copies

**Example:**
```cpp
// Declaration (prototype):
int add(int a, int b);    // Forward declaration

// Definition:
int add(int a, int b) {
    return a + b;
}

void print(std::string s) {  // void: no return
    std::cout << s << '\n';
}

// Overloading (different signatures):
int max(int a, int b) { return a > b ? a : b; }
double max(double a, double b) { return a > b ? a : b; }

// noexcept:
int safe() noexcept {     // Guarantees no exceptions
    return 42;
}

// Auto return type (C++14):
auto multiply(int a, int b) {
    return a * b;         // Return type deduced: int
}
```

### [Default arguments](https://en.cppreference.com/w/cpp/language/default_arguments.html)

**Code-related Keywords:**
- `void func(int x = 10);` - Default parameter value
- Right-to-left rule - Defaults must be rightmost

**Theory Keywords:**
- **optional parameters** - Caller can omit arguments
- **declaration only** - Defaults in declaration, not redefinition

**Example:**
```cpp
void greet(std::string name, std::string greeting = "Hello") {
    std::cout << greeting << ", " << name << '\n';
}

greet("Alice");           // Uses default: "Hello, Alice"
greet("Bob", "Hi");       // "Hi, Bob"

// Multiple defaults (right-to-left):
void config(int a, int b = 2, int c = 3) { }

config(1);                // a=1, b=2, c=3
config(1, 5);             // a=1, b=5, c=3
config(1, 5, 7);          // a=1, b=5, c=7

// ERROR if not rightmost:
// void bad(int x = 1, int y);  // ERROR: non-default follows default
```

### [Variadic arguments](https://en.cppreference.com/w/cpp/language/variadic_arguments.html)

**Code-related Keywords:**
- `void func(int n, ...);` - C-style variadic (legacy)
- `va_list`, `va_start`, `va_arg`, `va_end` - Macros to access args
- `template<typename... Args>` - Variadic [templates](../../10_templates/templates.md) (C++11, preferred)

**Theory Keywords:**
- **type-unsafe** - C-style variadics lack type checking
- **variadic templates** - Modern C++11 type-safe alternative

**Example:**
```cpp
#include <cstdarg>

// C-style (legacy, avoid):
int sum(int count, ...) {
    va_list args;
    va_start(args, count);
    
    int total = 0;
    for (int i = 0; i < count; ++i) {
        total += va_arg(args, int);  // Extract int
    }
    
    va_end(args);
    return total;
}

int s = sum(3, 10, 20, 30);  // 60

// C++11 variadic template (preferred):
template<typename... Args>
auto sum_modern(Args... args) {
    return (args + ...);      // Fold expression (C++17)
}

auto s2 = sum_modern(10, 20, 30);  // 60, type-safe
```

### [Lambda expression](https://en.cppreference.com/w/cpp/language/lambda.html) (C++11)

**Code-related Keywords:**
- `[captures](params) { body }` - Lambda syntax
- `[&]` - Capture all by reference
- `[=]` - Capture all by copy
- `[x, &y]` - Specific captures
- `[x = expr]` - Init-capture (C++14)
- `mutable` - Allow modification of copied captures
- `-> ReturnType` - Trailing return type
- `constexpr` - Constexpr lambda (C++17)
- `consteval` - Immediate function lambda (C++20)
- `static` - Static lambda (C++23)
- `[*this]` - Capture enclosing object by copy (C++17)
- `template<typename T>` - Explicit template parameters (C++20)
- `[this]` - Explicit this capture (C++20)

**Theory Keywords:**
- **closure** - Function [object](../../02_types_and_objects/object.md) capturing environment
- **anonymous function** - Function without a name
- **capture list** - Variables from enclosing scope
- **closure type** - Unique unnamed class type created for lambda
- **stateless lambda** - Capture-less lambda convertible to function pointer

**Example:**
```cpp
// === C++11: Basic lambdas ===
auto add = [](int a, int b) { return a + b; };
int result = add(3, 4);   // 7

// Capture by value:
int x = 10;
auto f1 = [x]() { return x * 2; };  // x captured by copy
std::cout << f1();        // 20

// Capture by reference:
int y = 5;
auto f2 = [&y]() { y += 10; };  // y captured by reference
f2();
std::cout << y;           // 15

// Capture all:
int a = 1, b = 2;
auto f3 = [=]() { return a + b; };  // All by copy
auto f4 = [&]() { a++; b++; };      // All by reference

// Mutable (modify copied captures):
int z = 0;
auto f5 = [z]() mutable { return ++z; };  // Modifies copy, not original
f5();                     // Returns 1
std::cout << z;           // 0 (original unchanged)

// Capture-less lambda converts to function pointer:
void (*fp)(int) = [](int n) { std::cout << n; };
fp(42);                   // 42

// === C++14: Generic lambdas & init-capture ===
auto generic = [](auto x, auto y) { return x + y; };
generic(1, 2);            // 3
generic(1.5, 2.5);        // 4.0

// Init-capture (move-only types, computed captures):
auto ptr = std::make_unique<int>(42);
auto f6 = [p = std::move(ptr)]() { return *p; };  // Move capture
std::cout << f6();        // 42

int val = 5;
auto f7 = [twice = val * 2]() { return twice; };  // Computed capture
std::cout << f7();        // 10

// === C++17: constexpr & *this capture ===
constexpr auto square = [](int n) { return n * n; };
static_assert(square(5) == 25);  // Compile-time evaluation

struct S {
    int x = 42;
    auto get_lambda() {
        return [*this]() { return x; };  // Captures copy of *this
    }
};

// === C++20: Template parameters & explicit this ===
auto f8 = []<typename T>(T x, T y) { return x + y; };
f8(1, 2);                 // OK: T = int
// f8(1, 2.0);            // Error: different types

auto f9 = []<typename T>(std::vector<T> const& v) {
    return v.size();
};

// === C++23: Static lambdas & deducing this ===
auto f10 = []() static { return 42; };  // No capture, static member function

// Deducing this (recursive lambda without std::function):
auto fib = [](this auto self, int n) -> int {
    if (n <= 1) return n;
    return self(n-1) + self(n-2);
};
std::cout << fib(10);     // 55

// With algorithms:
std::vector<int> v = {1, 2, 3, 4, 5};
std::for_each(v.begin(), v.end(), [](int& n) { n *= 2; });  // v = {2,4,6,8,10}
```
