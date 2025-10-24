# C++23 Features

C++23 is the latest ratified standard (as of 2024), building on C++20 with refinements and new practical features. It's a smaller release focused on improving usability and completing C++20 features.

## Language Features

### if consteval
- 📁 [if consteval](../08_statements/conditional_statements.md#if-consteval) - Check if in constant evaluation context
```cpp
consteval int compiletime(int n) {
    return n * n;
}

constexpr int either(int n) {
    if consteval {
        return compiletime(n);  // Compile-time path
    } else {
        return n * n;           // Runtime path
    }
}
```

### Preprocessor Improvements
- 📁 [#elifdef / #elifndef](../03_keywords_and_preprocessor/preprocessor.md#elifdef---elifndef) - Cleaner conditional compilation
- 📁 [#warning](../03_keywords_and_preprocessor/preprocessor.md#warning) - Emit compile-time warnings
```cpp
#ifdef FEATURE_A
    // Code for A
#elifdef FEATURE_B   // C++23: cleaner than #elif defined(FEATURE_B)
    // Code for B
#else
    #warning "Neither feature enabled"  // C++23: emit warning
#endif
```

### Multidimensional Subscript Operator
- `operator[]` can now take multiple arguments
```cpp
class Matrix {
public:
    int& operator[](size_t row, size_t col) {  // C++23: multiple indices
        return data[row * cols + col];
    }
};

Matrix m(10, 10);
m[3, 4] = 42;  // C++23: natural syntax
// C++20: m[3][4] or m.at(3, 4)
```

### static operator()
- Allow `static operator()` for stateless function objects
```cpp
struct Adder {
    static int operator()(int a, int b) {  // C++23
        return a + b;
    }
};
```

### Deducing this
- Explicit object parameters for member functions
- Eliminates need for duplicate `const`/non-const overloads
```cpp
struct Widget {
    // C++23: single function handles all cases
    auto&& get(this auto&& self) {
        return std::forward<decltype(self)>(self).data;
    }
    
    // Before C++23: needed 4 overloads!
    // const Data& get() const&;
    // Data& get() &;
    // const Data&& get() const&&;
    // Data&& get() &&;
};
```

### auto(x) and auto{x}
- Explicit decay copy
```cpp
void func(const std::string& str) {
    // C++23: explicitly make a copy
    auto copy = auto(str);
}
```

## Standard Library

### std::expected<T, E>
- Error handling alternative to exceptions
- Like Rust's `Result<T, E>`
```cpp
std::expected<int, std::string> divide(int a, int b) {
    if (b == 0) {
        return std::unexpected("Division by zero");
    }
    return a / b;
}

auto result = divide(10, 0);
if (result) {
    std::cout << *result;
} else {
    std::cout << "Error: " << result.error();
}
```

### std::mdspan
- Multidimensional array view
```cpp
std::mdspan<int, std::extents<int, 3, 4>> matrix(data);
matrix[1, 2] = 42;
```

### import std
- 📁 [Standard library modules](../03a_modules/modules.md) - Import entire standard library
```cpp
import std;  // C++23: entire standard library as module

int main() {
    std::vector<int> v{1, 2, 3};
    std::cout << v.size();
}
```

### std::print and std::println
- Modern, type-safe printing (like Python's print)
```cpp
std::print("Hello {}!\n", name);
std::println("x = {}, y = {}", x, y);  // Auto newline
```

### Ranges Improvements
- `std::ranges::to` - Convert ranges to containers
```cpp
auto vec = range 
    | std::views::filter(pred)
    | std::views::transform(func)
    | std::ranges::to<std::vector>();  // C++23: materialize to vector
```

- New views: `zip`, `zip_transform`, `adjacent`, `join_with`, `slide`, `chunk`, `stride`
```cpp
std::vector v1{1, 2, 3};
std::vector v2{'a', 'b', 'c'};

for (auto [num, ch] : std::views::zip(v1, v2)) {
    std::cout << num << ch << ' ';  // 1a 2b 3c
}
```

### std::flat_map and std::flat_set
- Sorted containers using contiguous storage
- Better cache performance than `std::map`/`std::set`

### String and String View Enhancements
- `std::string::contains`
- `std::string::starts_with` / `ends_with` improvements
- `std::string_view` lifetime improvements

### <stacktrace>
- Stack trace library for debugging
```cpp
#include <stacktrace>
auto trace = std::stacktrace::current();
std::cout << trace;
```

### Other Additions
- `std::byteswap` - Byte order reversal
- `std::unreachable()` - Mark unreachable code
- `std::to_underlying` - Get underlying enum value
- `std::optional` monadic operations: `and_then`, `or_else`, `transform`
- `std::is_scoped_enum` - Check if scoped enum
- Improvements to `<chrono>`
- `std::move_only_function` - Like `std::function` but for move-only types

## Removed/Deprecated Features
- Various legacy features cleaned up
- More aggressive removal of deprecated C++17 features

## Key Improvements

### Better Error Handling
```cpp
// C++20: exceptions or error codes
try {
    auto result = may_fail();
    use(result);
} catch (...) {
    handle_error();
}

// C++23: std::expected
auto result = may_fail();
if (result) {
    use(*result);
} else {
    handle_error(result.error());
}
```

### Cleaner Ranges
```cpp
// C++20: verbose materialization
auto v = range | view1 | view2;
std::vector<int> vec(v.begin(), v.end());

// C++23: direct conversion
auto vec = range 
    | view1 
    | view2 
    | std::ranges::to<std::vector>();
```

### Simpler Member Functions
```cpp
// C++20: 4 overloads for all cases
struct S {
    int& get() & { return data; }
    const int& get() const& { return data; }
    int&& get() && { return std::move(data); }
    const int&& get() const&& { return std::move(data); }
};

// C++23: 1 function
struct S {
    auto&& get(this auto&& self) {
        return std::forward<decltype(self)>(self).data;
    }
};
```

## Status and Adoption

- **Ratified**: 2023
- **Compiler support**: Gradual (GCC 13+, Clang 16+, MSVC 2022+)
- **Focus**: Completing C++20 features, improving usability
- **Philosophy**: Evolutionary, not revolutionary

## Compared to C++20

C++23 is to C++20 what C++14 was to C++11:
- **Completes** features (e.g., ranges materialization)
- **Refines** existing features (e.g., deducing this)
- **Adds** practical utilities (e.g., `std::expected`, `std::print`)
- **Improves** usability (e.g., better ranges, cleaner conditionals)

## Impact

While not as groundbreaking as C++20, C++23 makes modern C++ more practical:
- **std::expected** - Functional error handling without exceptions
- **Ranges improvements** - More complete and usable
- **Deducing this** - Eliminates boilerplate
- **std::print** - Modern output that's actually usable
- **import std** - Modules for standard library

## Comprehensive Example

This example demonstrates C++23 features including [std::expected](#stdexpected), [std::print](#stdprint), [deducing this](#deducing-this), [multidimensional subscript](#multidimensional-subscript-operator), and other improvements.

```cpp
#include <iostream>
#include <expected>
#include <optional>
#include <string>
#include <vector>
#include <ranges>
#include <algorithm>
#include <print>       // C++23: std::print
#include <stacktrace>  // C++23: stack traces
#include <mdspan>      // C++23: multidimensional views
#include <spanstream>  // C++23: span streams

// ============================================================================
// STD::EXPECTED: Functional error handling (C++23)
// ============================================================================
enum class ErrorCode {
    NotFound,
    InvalidInput,
    DivisionByZero,
    OutOfRange
};

// Return value or error (no exceptions!)
std::expected<double, ErrorCode> safeDivide(double a, double b) {
    if (b == 0.0) {
        return std::unexpected(ErrorCode::DivisionByZero);
    }
    return a / b;
}

std::expected<int, ErrorCode> parseInteger(const std::string& str) {
    if (str.empty()) {
        return std::unexpected(ErrorCode::InvalidInput);
    }
    
    try {
        return std::stoi(str);
    } catch (...) {
        return std::unexpected(ErrorCode::InvalidInput);
    }
}

// Chain expected operations
std::expected<double, ErrorCode> calculateResult(const std::string& numStr, double divisor) {
    // C++23: Use and_then, or_else, transform
    auto num = parseInteger(numStr);
    if (!num) return std::unexpected(num.error());
    
    return safeDivide(*num, divisor);
}

void demonstrateExpected() {
    std::println("\n--- std::expected ---");
    
    // Success case
    if (auto result = safeDivide(10.0, 2.0); result) {
        std::println("10 / 2 = {}", *result);
    }
    
    // Error case
    if (auto result = safeDivide(10.0, 0.0); !result) {
        std::println("Division by zero error!");
        
        // Can check error code
        if (result.error() == ErrorCode::DivisionByZero) {
            std::println("Error code: DivisionByZero");
        }
    }
    
    // value_or for default
    double value = safeDivide(10.0, 0.0).value_or(-1.0);
    std::println("With default: {}", value);
    
    // Chaining
    auto chain_result = calculateResult("42", 2.0);
    if (chain_result) {
        std::println("Chain result: {}", *chain_result);
    }
}

// ============================================================================
// STD::PRINT: Modern formatted output (C++23)
// ============================================================================
void demonstratePrint() {
    std::println("\n--- std::print & std::println ---");
    
    // std::print with format string (like Python!)
    std::print("Hello, {}!\n", "World");
    
    // std::println adds newline automatically
    std::println("The answer is {}", 42);
    
    // Multiple arguments
    std::println("{} + {} = {}", 2, 3, 5);
    
    // Formatting options
    std::println("Pi: {:.2f}", 3.14159);
    std::println("Hex: {:#x}", 255);
    std::println("Binary: {:#b}", 42);
    
    // Width and alignment
    std::println("Left:  |{:<10}|", "text");
    std::println("Right: |{:>10}|", "text");
    std::println("Center:|{:^10}|", "text");
    
    // Containers (if custom formatter available)
    std::vector<int> nums{1, 2, 3, 4, 5};
    // std::println("Vector: {}", nums);  // With custom formatter
}

// ============================================================================
// DEDUCING THIS: Eliminate code duplication (C++23)
// ============================================================================
class Container {
public:
    std::vector<int> data;
    
    // C++23: Deducing this - one function for const and non-const!
    auto& get(this auto& self, size_t index) {
        return self.data[index];
    }
    
    // Works for both lvalue and rvalue refs
    auto&& getValue(this auto&& self, size_t index) {
        return std::forward<decltype(self)>(self).data[index];
    }
    
    // Perfect forwarding with deducing this
    template<typename Self>
    auto&& at(this Self&& self, size_t index) {
        if (index >= self.data.size()) {
            throw std::out_of_range("Index out of range");
        }
        return std::forward<Self>(self).data[index];
    }
};

void demonstrateDeducingThis() {
    std::println("\n--- Deducing This ---");
    
    Container c{{1, 2, 3, 4, 5}};
    
    // Non-const access
    c.get(0) = 10;
    std::println("Modified: {}", c.data[0]);
    
    // Const access
    const Container& cc = c;
    std::println("Const access: {}", cc.get(0));
    
    // Rvalue access
    std::println("Rvalue: {}", Container{{5, 6, 7}}.getValue(1));
}

// ============================================================================
// MULTIDIMENSIONAL SUBSCRIPT: Matrix[i, j] syntax (C++23)
// ============================================================================
class Matrix {
public:
    Matrix(size_t rows, size_t cols) 
        : rows_(rows), cols_(cols), data_(rows * cols) {}
    
    // C++23: Multi-dimensional subscript operator!
    double& operator[](size_t row, size_t col) {
        return data_[row * cols_ + col];
    }
    
    const double& operator[](size_t row, size_t col) const {
        return data_[row * cols_ + col];
    }
    
    size_t rows() const { return rows_; }
    size_t cols() const { return cols_; }
    
private:
    size_t rows_, cols_;
    std::vector<double> data_;
};

void demonstrateMultiDimSubscript() {
    std::println("\n--- Multidimensional Subscript ---");
    
    Matrix mat(3, 3);
    
    // C++23: Can use [i, j] syntax!
    mat[0, 0] = 1.0;
    mat[0, 1] = 2.0;
    mat[1, 0] = 3.0;
    mat[1, 1] = 4.0;
    
    std::println("mat[0, 0] = {}", mat[0, 0]);
    std::println("mat[0, 1] = {}", mat[0, 1]);
    std::println("mat[1, 0] = {}", mat[1, 0]);
    std::println("mat[1, 1] = {}", mat[1, 1]);
}

// ============================================================================
// IF CONSTEVAL: Check if compile-time context (C++23)
// ============================================================================
constexpr int getValue() {
    if consteval {
        // Compile-time branch
        return 42;
    } else {
        // Runtime branch
        return 99;
    }
}

constexpr int compute(int n) {
    if consteval {
        // Simpler compile-time version
        return n * n;
    } else {
        // Complex runtime version with logging
        std::println("Computing at runtime: {}", n);
        return n * n;
    }
}

// ============================================================================
// STATIC OPERATOR(): Static call operator (C++23)
// ============================================================================
struct Comparator {
    static bool operator()(int a, int b) {
        return a < b;
    }
};

// ============================================================================
// RANGES IMPROVEMENTS: Better ranges support (C++23)
// ============================================================================
void demonstrateRanges23() {
    std::println("\n--- C++23 Ranges Improvements ---");
    
    std::vector<int> numbers{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    
    // C++23: ranges::to for materialization
    auto evens = numbers 
        | std::views::filter([](int n) { return n % 2 == 0; })
        | std::ranges::to<std::vector>();  // Materialize to vector
    
    std::print("Evens: ");
    for (int n : evens) std::print("{} ", n);
    std::println("");
    
    // C++23: ranges::contains
    bool has5 = std::ranges::contains(numbers, 5);
    std::println("Contains 5: {}", has5);
    
    // C++23: ranges::find_last
    auto it = std::ranges::find_last(numbers, 5);
    if (it != numbers.end()) {
        std::println("Found last 5 at position");
    }
}

// ============================================================================
// OPTIONAL IMPROVEMENTS: Monadic operations (C++23)
// ============================================================================
void demonstrateOptionalMonadic() {
    std::println("\n--- Optional Monadic Operations ---");
    
    std::optional<int> opt1 = 42;
    std::optional<int> opt2 = std::nullopt;
    
    // C++23: and_then, or_else, transform
    auto result1 = opt1.transform([](int x) { return x * 2; });
    std::println("Transformed: {}", result1.value_or(-1));
    
    auto result2 = opt2.transform([](int x) { return x * 2; })
                       .or_else([] { return std::optional<int>{100}; });
    std::println("With fallback: {}", result2.value_or(-1));
}

// ============================================================================
// SIZE_T LITERALS: zu suffix (C++23)
// ============================================================================
void demonstrateSizeLiterals() {
    std::println("\n--- size_t Literals ---");
    
    // C++23: Can use 'zu' suffix for size_t literals
    auto size = 10zu;  // size_t literal
    std::println("Size: {} (type: size_t)", size);
    
    std::vector<int> vec(5zu);  // No more warnings!
}

// ============================================================================
// AUTO(x) and DECAY_COPY: Explicit decay (C++23)
// ============================================================================
template<typename T>
void processValue(T&& value) {
    // C++23: auto(x) for explicit decay copy
    auto copy = auto(value);  // Decays and copies
    std::println("Decayed copy created");
}

// ============================================================================
// STACKTRACE: Get stack traces (C++23)
// ============================================================================
void demonstrateStacktrace() {
    std::println("\n--- std::stacktrace ---");
    
    // C++23: Get current stack trace
    auto trace = std::stacktrace::current();
    
    std::println("Stack depth: {}", trace.size());
    
    // Can print stack trace
    // std::println("{}", trace);  // Formatted output
}

// ============================================================================
// MAIN: Demonstrate C++23 features
// ============================================================================
int main() {
    std::println("=== C++23 Features Demo ===");
    
    // ========================================================================
    // STD::EXPECTED
    // ========================================================================
    demonstrateExpected();
    
    // ========================================================================
    // STD::PRINT
    // ========================================================================
    demonstratePrint();
    
    // ========================================================================
    // DEDUCING THIS
    // ========================================================================
    demonstrateDeducingThis();
    
    // ========================================================================
    // MULTIDIMENSIONAL SUBSCRIPT
    // ========================================================================
    demonstrateMultiDimSubscript();
    
    // ========================================================================
    // IF CONSTEVAL
    // ========================================================================
    std::println("\n--- if consteval ---");
    constexpr int compileTime = getValue();  // Uses compile-time branch
    int runtime = getValue();                // Uses runtime branch
    std::println("Compile-time: {}", compileTime);
    std::println("Runtime: {}", runtime);
    
    constexpr int c = compute(5);  // No output (compile-time)
    int r = compute(5);             // Prints output (runtime)
    
    // ========================================================================
    // STATIC OPERATOR()
    // ========================================================================
    std::println("\n--- Static operator() ---");
    std::vector<int> nums{5, 2, 8, 1, 9};
    std::ranges::sort(nums, Comparator{});
    std::print("Sorted: ");
    for (int n : nums) std::print("{} ", n);
    std::println("");
    
    // ========================================================================
    // RANGES IMPROVEMENTS
    // ========================================================================
    demonstrateRanges23();
    
    // ========================================================================
    // OPTIONAL MONADIC OPERATIONS
    // ========================================================================
    demonstrateOptionalMonadic();
    
    // ========================================================================
    // SIZE_T LITERALS
    // ========================================================================
    demonstrateSizeLiterals();
    
    // ========================================================================
    // STACKTRACE
    // ========================================================================
    demonstrateStacktrace();
    
    std::println("\n=== C++23 Demo Complete ===");
    return 0;
}
```

**C++23 Practical Improvements:**

| Feature | Benefit | Example |
|---------|---------|---------|
| **std::expected** | Error handling without exceptions | `expected<T, E>` |
| **std::print** | Modern formatting | `println("x = {}", x)` |
| **Deducing this** | Eliminate const overloads | `auto& f(this auto& self)` |
| **Multi-dim subscript** | Natural matrix syntax | `mat[i, j]` |
| **if consteval** | Detect compile-time | Optimize differently |
| **Ranges::to** | Materialize ranges | `\| ranges::to<vector>()` |
| **Optional monadic** | Chainable operations | `.transform().or_else()` |
| **std::mdspan** | Multidimensional views | Like span for matrices |

**Evolution Focus:**
- 🛠️ **Practical utilities**: expected, print, mdspan make everyday coding easier
- 🎯 **Cleaner syntax**: Deducing this, multi-dim subscript reduce boilerplate
- 📦 **Ranges completion**: to, contains, find_last make ranges fully usable
- 🔍 **Better debugging**: stacktrace, improved diagnostics
- 📚 **Module support**: import std makes modules practical

C++23 is a "consolidation" release - making C++20's groundbreaking features actually practical and usable in production code.

## Looking Forward: C++26

C++26 (next standard) is already in progress with proposed features:
- Reflection
- Pattern matching
- More ranges improvements
- Networking (finally?)
- Executors
