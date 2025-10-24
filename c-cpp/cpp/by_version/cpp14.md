# C++14 Features

C++14 was a smaller, refinement release that improved and completed C++11 features. It focused on making the language more usable and fixing inconsistencies.

## 📚 Official Reference
**Primary Source**: [cppreference.com C++14](https://en.cppreference.com/w/cpp/14)

## 🔥 Core Language Features

### Function Return Type Deduction
- 📁 [Auto return type](../07_functions/functions.md) - Full `auto` return type deduction without trailing return type
- Return type deduced from return statements

### Generic Lambdas (Polymorphic Lambdas)
- 📁 [Generic lambdas](../07_functions/functions.md#lambda-expression) - `auto` parameters in lambdas
- Lambda templates effectively created at compile-time

### Lambda Init-Capture (Generalized Lambda Capture)
- Capture by moving: `[x = std::move(y)]`
- Capture with initialization: `[y = expr]`
- Create new variables in capture clause

### decltype(auto)
- 📁 [decltype(auto)](../05_declarations/type_specifiers.md#auto-specifier) - Preserve exact type including references
- Useful for perfect return type forwarding

### Variable Templates
- 📁 [Variable template](../10_templates/template_types.md#variable-template) - Templates for variables (not just types/functions)
- Useful for constants, traits, etc.

### Relaxed constexpr Restrictions
- 📁 [constexpr functions](../05_declarations/specifiers_and_qualifiers.md#constexpr-specifier) - More permissive rules
- Can now use: local variables, loops, multiple returns, mutations

### Binary Literals
- 📁 [Binary literals](../04_expressions/literals.md#integer-literals) - `0b` or `0B` prefix for binary numbers

### Digit Separators
- 📁 [Digit separators](../04_expressions/literals.md) - Single quote `'` as separator for readability

### Aggregate Member Initialization
- Aggregates can have default member initializers (NSDMI)

### [[deprecated]] Attribute
- 📁 [[[deprecated]]](../05_declarations/attributes.md) - Mark entities as deprecated

## 📦 Standard Library Additions

### Utilities
- `std::make_unique<T>()` - Factory function for unique_ptr (was missing in C++11!)
- `std::exchange(obj, new_val)` - Replace value and return old value

### Type Trait Aliases (_t suffix)
- `std::remove_const_t<T>`, `std::remove_reference_t<T>`, `std::decay_t<T>`, etc.
- Shorthand for `typename std::trait<T>::type`

### User-Defined Literals for Standard Library
- **Chrono**: `h`, `min`, `s`, `ms`, `us`, `ns` - Time duration literals
- **String**: `s` - `std::string` literals
- **Complex**: `i`, `if`, `il` - Complex number literals

### std::integer_sequence
- Compile-time integer sequences for template metaprogramming
- `std::make_integer_sequence`, `std::index_sequence`

### std::shared_timed_mutex & std::shared_lock
- Reader-writer locks for shared/exclusive access

### Transparent Operator Functors
- `std::less<>`, `std::greater<>`, etc. with `void` template parameter
- Enables heterogeneous lookup in associative containers

### Improvements to Containers
- Associative container heterogeneous lookup (when using transparent comparators)

### Library Fundamentals TS v1 Features
- `std::quoted()` - I/O manipulator for quoted strings
- More algorithm improvements

### Chrono
- User-defined literals for time: `100ms`, `2s`, `1h`
```cpp
using namespace std::chrono_literals;
auto duration = 100ms + 2s;
```

### Misc
- `std::quoted` - Stream I/O manipulator for quoted strings
- `std::integer_sequence` - Compile-time integer sequences
- `std::exchange` - Replace value and return old one

## Key Improvements

### Simplified Generic Code
```cpp
// C++11: verbose
template<typename T>

##  Comprehensive Example

Compact demonstration of C++14 features based on [cppreference.com/w/cpp/14](https://en.cppreference.com/w/cpp/14). C++14 refines C++11 with usability improvements.

```cpp
#include <iostream>
#include <memory>
#include <vector>
#include <algorithm>
#include <chrono>
#include <complex>
#include <mutex>
#include <shared_mutex>

//=== CORE LANGUAGE FEATURES ===//

// 1. Function return type deduction (no trailing return type needed)
auto add(int a, int b) {           // Return type deduced as int
    return a + b;
}

auto get_vector() {                // Return type deduced as std::vector<int>
    return std::vector<int>{1, 2, 3};
}

// Multiple returns - all must have same type
auto conditionalReturn(bool flag) {
    if (flag)
        return 42;                 // int
    else
        return 100;                // int - OK, same type
}

// 2. decltype(auto) - preserves exact type including references
decltype(auto) get_value() {
    int x = 42;
    return x;                      // Returns int (not int&)
}

decltype(auto) get_ref(int& x) {
    return (x);                    // Returns int& (preserves reference)
}

// Useful for perfect forwarding
template<typename Container>
decltype(auto) getElement(Container& c, size_t i) {
    return c[i];                   // Preserves reference if c[i] returns one
}

// 3. Generic lambdas - lambdas with auto parameters
void genericLambdaDemo() {
    // Lambda is a template - instantiated for each type used
    auto add = [](auto a, auto b) { return a + b; };
    
    auto i = add(1, 2);            // int + int
    auto d = add(1.5, 2.5);        // double + double
    auto s = add(std::string("Hello"), std::string(" World")); // string + string
    
    // Multiple auto parameters
    auto print = [](auto&&... args) {
        ((std::cout << args << " "), ...);  // C++17 fold, but showing concept
    };
    
    // Generic lambda for algorithms
    std::vector<int> vec{1, 2, 3, 4, 5};
    std::transform(vec.begin(), vec.end(), vec.begin(),
        [](auto x) { return x * 2; }  // Works with any type
    );
}

// 4. Lambda init-capture (generalized lambda capture)
void lambdaCaptureDemo() {
    auto ptr = std::make_unique<int>(42);
    
    // Move capture - transfer ownership into lambda
    auto lambda = [p = std::move(ptr)]() {
        return *p;
    };
    // ptr is now nullptr, lambda owns the unique_ptr
    
    // Capture with expression
    int x = 10;
    auto twice = [y = x * 2]() { return y; };  // Capture computed value
    
    // Capture by moving from member variable
    std::vector<int> data{1, 2, 3, 4, 5};
    auto process = [d = std::move(data)]() {
        // Lambda now owns the vector
        return d.size();
    };
}

// 5. Variable templates
template<typename T>
constexpr T pi = T(3.1415926535897932385);

template<typename T>
constexpr T e = T(2.7182818284590452354);

// Variable template specialization
template<>
constexpr const char* pi<const char*> = "3.14159...";

// Using variable templates for type traits
template<typename T>
constexpr bool is_pointer_v = std::is_pointer<T>::value;  // Simpler than ::value

void variableTemplateDemo() {
    float  f = pi<float>;
    double d = pi<double>;
    long double ld = pi<long double>;
    
    auto euler = e<double>;
}

// 6. Relaxed constexpr - much more permissive
constexpr int factorial(int n) {
    int result = 1;                // Local variable OK
    for (int i = 2; i <= n; ++i) { // Loops OK
        result *= i;
    }
    return result;                 // Multiple returns OK
}

constexpr int fibonacci(int n) {
    if (n <= 1) return n;
    
    int a = 0, b = 1;              // Local variables
    for (int i = 2; i <= n; ++i) { // Loops
        int temp = a + b;
        a = b;
        b = temp;
    }
    return b;
}

// Constexpr with mutation
constexpr int sum_array(const int* arr, size_t size) {
    int total = 0;
    for (size_t i = 0; i < size; ++i) {
        total += arr[i];           // Mutation OK
    }
    return total;
}

// 7. Binary literals and digit separators
void literalsDemo() {
    // Binary literals
    int binary = 0b1010'1010;                    // 170 in decimal
    int mask = 0b1111'0000'0000'0000;
    
    // Digit separators for readability
    int million = 1'000'000;
    long long big = 9'223'372'036'854'775'807;
    double pi_sep = 3.141'592'653'589'793;
    int hex = 0xFF'FF'FF'FF;
    
    // Can place separators anywhere (except at start/end)
    int grouped = 1'2'3'4'5;                     // Same as 12345
}

// 8. Aggregates with default member initializers
struct Config {
    int timeout = 30;              // Default value
    bool enabled = true;
    std::string name = "default";
};

void aggregateDemo() {
    Config c1;                     // Uses defaults
    Config c2{60, false, "custom"}; // Override all
    Config c3{.timeout = 100};     // C++20 designated initializers
}

// 9. [[deprecated]] attribute
[[deprecated]]
void oldFunction() {
    std::cout << "This is deprecated!\n";
}

[[deprecated("Use newProcess() instead")]]
void legacyProcess() {
    // Compiler warning when called
}

class [[deprecated]] OldClass {
    // Entire class marked deprecated
};

//=== STANDARD LIBRARY FEATURES ===//

// 10. std::make_unique - finally added!
void makeUniqueDemo() {
    // C++11 had make_shared but not make_unique
    auto ptr1 = std::make_unique<int>(42);
    auto ptr2 = std::make_unique<std::vector<int>>(10, 5);  // 10 elements of 5
    
    // Array version
    auto arr = std::make_unique<int[]>(10);
}

// 11. std::exchange - replace and return old value
void exchangeDemo() {
    int x = 10;
    int old = std::exchange(x, 20);  // x becomes 20, old is 10
    
    // Useful in move operations
    struct Widget {
        int* data;
        Widget(Widget&& other) noexcept
            : data(std::exchange(other.data, nullptr)) {}  // Concise!
    };
}

// 12. Type trait aliases (_t suffix)
template<typename T>
using RemoveConst = std::remove_const_t<T>;       // Instead of typename ::type

template<typename T>
using Decay = std::decay_t<T>;

template<typename T>
using RemoveRef = std::remove_reference_t<T>;

void typeTraitDemo() {
    using T1 = std::remove_const_t<const int>;    // int
    using T2 = std::decay_t<int&>;                // int
    using T3 = std::remove_reference_t<int&&>;    // int
}

// 13. std::integer_sequence - compile-time integer sequences
template<typename T, T... Ints>
void print_sequence(std::integer_sequence<T, Ints...>) {
    ((std::cout << Ints << ' '), ...);  // C++17 fold expression
}

template<size_t... Indices>
void indexSequenceDemo() {
    // Useful for tuple unpacking and similar metaprogramming
    print_sequence(std::index_sequence<0, 1, 2, 3, 4>{});
}

void integerSequenceDemo() {
    using Seq = std::make_integer_sequence<int, 5>;  // 0, 1, 2, 3, 4
    print_sequence(Seq{});
}

// 14. std::shared_timed_mutex - reader-writer lock
class ThreadSafeCounter {
    mutable std::shared_timed_mutex mutex_;
    int counter_ = 0;
    
public:
    int read() const {
        std::shared_lock<std::shared_timed_mutex> lock(mutex_);  // Shared access
        return counter_;
    }
    
    void increment() {
        std::unique_lock<std::shared_timed_mutex> lock(mutex_);  // Exclusive access
        ++counter_;
    }
};

// 15. Transparent operator functors
void transparentComparatorDemo() {
    std::set<std::string, std::less<>> set;  // Note: std::less<> not std::less<std::string>
    
    set.insert("hello");
    
    // Heterogeneous lookup - can search with string_view or const char*
    // Without creating temporary std::string
    bool found = set.find("hello") != set.end();  // Efficient!
}

// 16. User-defined literals for standard library
void udlDemo() {
    using namespace std::literals;
    
    // String literals
    auto str = "hello"s;                       // std::string, not const char*
    
    // Chrono literals
    auto duration1 = 42s;                      // std::chrono::seconds
    auto duration2 = 100ms;                    // std::chrono::milliseconds
    auto duration3 = 5min;                     // std::chrono::minutes
    auto duration4 = 2h;                       // std::chrono::hours
    
    // Complex number literals
    auto complex1 = 1.0 + 2.0i;               // std::complex<double>
    auto complex2 = 1.0if;                    // std::complex<float>
    auto complex3 = 1.0il;                    // std::complex<long double>
}

// 17. std::quoted - I/O manipulator for quoted strings
void quotedDemo() {
    std::string str = "Hello World";
    std::cout << std::quoted(str) << '\n';     // Outputs: "Hello World"
    
    // Useful for reading/writing strings with spaces
    std::stringstream ss;
    ss << std::quoted(str);
}

int main() {
    using namespace std::literals;
    
    // Auto return type deduction
    auto sum = add(10, 20);
    
    // Generic lambdas
    auto multiply = [](auto a, auto b) { return a * b; };
    std::cout << multiply(5, 10) << '\n';      // int
    std::cout << multiply(2.5, 4.0) << '\n';   // double
    
    // Lambda init-capture  
    auto vec = std::vector<int>{1, 2, 3};
    auto lambda = [v = std::move(vec)]() { return v.size(); };
    std::cout << "Size: " << lambda() << '\n';
    
    // Variable templates
    std::cout << "Pi (float): " << pi<float> << '\n';
    std::cout << "Pi (double): " << pi<double> << '\n';
    
    // Relaxed constexpr
    constexpr int fact10 = factorial(10);
    constexpr int fib15 = fibonacci(15);
    
    // Binary literals and digit separators
    int mask = 0b1111'0000;
    int million = 1'000'000;
    
    // std::make_unique
    auto ptr = std::make_unique<int>(42);
    
    // User-defined literals
    auto str = "C++14"s;
    auto time = 500ms;
    
    // decltype(auto)
    int x = 100;
    decltype(auto) ref = get_ref(x);
    
    return 0;
}
```

### Feature Coverage Summary

**Core Language**: Auto return type deduction, generic lambdas, lambda init-capture, decltype(auto), variable templates, relaxed constexpr (local variables, loops, mutations), binary literals, digit separators, aggregates with NSDMI, [[deprecated]] attribute

**Standard Library**: std::make_unique, std::exchange, type trait aliases (_t suffix), std::integer_sequence, std::shared_timed_mutex, std::shared_lock, transparent operator functors (std::less<>), user-defined literals (chrono: s/ms/min/h, string: s, complex: i/if/il), std::quoted

**Reference**: All features verified against [C++14 on cppreference.com](https://en.cppreference.com/w/cpp/14)
