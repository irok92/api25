# C++20 Features

C++20 is the largest release since C++11, fundamentally transforming how C++ is written with concepts, modules, coroutines, and ranges.

## 🔥 Major Features

### Concepts
- 📁 [Concepts](../10_templates/constraints_and_concepts.md#constraints-and-concepts) - Named template constraints
- 📁 [requires expression](../10_templates/constraints_and_concepts.md#requires-expression) - Inline requirements
- **Replaces SFINAE** with readable syntax
```cpp
// Define a concept
template<typename T>
concept Addable = requires(T a, T b) {
    { a + b } -> std::same_as<T>;
};

// Use it
template<Addable T>
T add(T a, T b) {
    return a + b;
}

// Or shorter syntax
auto add(Addable auto a, Addable auto b) {
    return a + b;
}
```

### Modules
- 📁 [Modules](../03a_modules/modules.md) - Modern replacement for `#include`
- **Faster compilation** - No more header parsing
- **Better encapsulation** - Explicit exports
- **No include guards needed**
```cpp
// math.cppm
export module math;

export int add(int a, int b) {
    return a + b;
}

// main.cpp
import math;  // Instead of #include
import std;   // C++23: standard library modules

int main() {
    return add(2, 3);
}
```

### Coroutines
- 📁 [Coroutines](../07_functions/advanced_function_types.md#coroutines) - Functions that can suspend/resume
- 📁 `co_await`, `co_yield`, `co_return` keywords
- **Async programming** made easier
- **Generators** for lazy evaluation
```cpp
Generator<int> counter() {
    for (int i = 0; i < 10; ++i) {
        co_yield i;  // Suspend and return value
    }
}

for (int n : counter()) {
    std::cout << n << ' ';
}
```

### Ranges
- 📁 [Ranges](../12_miscellaneous/miscellaneous.md) - Composable algorithms
- **Pipeline-style** operations
- **Lazy evaluation**
- **View composition**
```cpp
auto even = [](int n) { return n % 2 == 0; };
auto square = [](int n) { return n * n; };

auto result = numbers 
    | std::views::filter(even)
    | std::views::transform(square)
    | std::views::take(5);
```

## Language Features

### Three-Way Comparison (Spaceship Operator)
- 📁 [operator<=>](../04_expressions/operators.md) - Three-way comparison
- 📁 [Default comparisons](../09_classes/special_member_function_control.md#default-comparisons) - Generate all 6 comparison operators
```cpp
class Point {
    int x, y;
public:
    auto operator<=>(const Point&) const = default;  // All 6 comparisons!
};

Point p1{1, 2}, p2{3, 4};
if (p1 < p2) { /*...*/ }   // Works!
if (p1 == p2) { /*...*/ }  // Works!
```

### Designated Initializers
- 📁 [Designated initializers](../06_initialization/basic_initialization_forms.md) - Named member initialization (from C99)
```cpp
struct Point { int x, y, z; };
Point p{.x = 1, .y = 2, .z = 3};  // Clear and explicit
```

### consteval and constinit
- 📁 [consteval](../05_declarations/specifiers_and_qualifiers.md#consteval-specifier) - Must evaluate at compile time
- 📁 [constinit](../05_declarations/specifiers_and_qualifiers.md#constinit-specifier) - Guaranteed constant initialization
```cpp
consteval int square(int n) {
    return n * n;
}

constexpr int x = square(5);  // OK: compile-time
// int y = square(getUserInput());  // ERROR: consteval requires compile-time

constinit int global = 42;  // Guaranteed initialized at compile time
```

### Attributes
- 📁 [[[likely]] / [[unlikely]]](../05_declarations/attributes.md) - Branch prediction hints
```cpp
if (condition) [[likely]] {
    // Common path
} else [[unlikely]] {
    // Rare error path
}
```

### Other Language Features
- 📁 [char8_t type](../04_expressions/literals.md) - UTF-8 character type
- 📁 [Range-for with init](../08_statements/iteration_statements.md) - `for (init; elem : range)`
- 📁 [Translation-unit-local](../05_declarations/storage_and_linkage.md#translation-unit-local) - Module linkage
- 📁 [Conditionally explicit](../09_classes/conversion_functions.md) - `explicit(bool)`
- Lambda improvements: template syntax, pack expansion in capture
- Aggregate initialization for types with base classes
- `using enum` - Bring enum members into scope

## Templates

### Concepts Replace SFINAE
```cpp
// C++17: SFINAE (hard to read)
template<typename T>
std::enable_if_t<std::is_integral_v<T>, T>
process(T value) {
    return value * 2;
}

// C++20: Concepts (clear and readable)
template<std::integral T>
T process(T value) {
    return value * 2;
}

// Or even shorter
auto process(std::integral auto value) {
    return value * 2;
}
```

### Abbreviated Function Templates
```cpp
// C++17
template<typename T, typename U>
auto add(T a, U b) {
    return a + b;
}

// C++20: abbreviated
auto add(auto a, auto b) {
    return a + b;
}
```

## Standard Library

### Ranges Library
- Range algorithms
- Views: `filter`, `transform`, `take`, `drop`, `reverse`, etc.
- Projections in algorithms

### Concepts Library
- Standard concepts: `std::integral`, `std::floating_point`, `std::same_as`, etc.
- Iterator concepts: `std::input_iterator`, `std::random_access_iterator`, etc.

### New Utilities
- `std::span<T>` - Non-owning view of contiguous sequence
- `std::format` - Python-style string formatting (like `printf` but type-safe)
```cpp
std::string s = std::format("Hello {}, you are {} years old", name, age);
```

### Calendar and Timezone
- Extended `<chrono>` with calendar and timezone support
```cpp
auto today = std::chrono::year_month_day{std::chrono::system_clock::now()};
```

### Other Additions
- `std::source_location` - Better than `__FILE__` and `__LINE__`
- `std::bit_cast` - Type-safe bit casting
- `std::endian` - Detect endianness
- `std::jthread` - RAII thread with automatic join
- `std::counting_semaphore`, `std::binary_semaphore` - Synchronization
- `std::latch`, `std::barrier` - Coordination primitives
- `std::erase`, `std::erase_if` - Uniform erasure

## Removed/Deprecated
- ⚡ `throw()` exception specifications (removed, use `noexcept`)

## Philosophy

C++20 represents a paradigm shift:

### Before C++20 (SFINAE hell):
```cpp
template<typename T>
typename std::enable_if<
    std::is_integral<T>::value && 
    !std::is_same<T, bool>::value,
    T
>::type
process(T value) {
    return value * 2;
}
```

### C++20 (readable):
```cpp
template<std::integral T>
requires (!std::same_as<T, bool>)
T process(T value) {
    return value * 2;
}
```

## Impact

C++20 fundamentally changes how C++ is written:

- **Concepts** - Templates become readable and errors comprehensible
- **Modules** - Compilation times improve, better encapsulation
- **Coroutines** - Async code becomes manageable
- **Ranges** - Functional programming patterns become natural
- **Spaceship operator** - Writing comparable types becomes trivial

It's the most significant update since C++11, establishing C++ as a modern language competitive with newer languages while maintaining backward compatibility.

## Adoption

C++20 features require:
- Recent compilers (GCC 10+, Clang 10+, MSVC 2019+)
- Some features (especially modules) still being stabilized
- Gradual adoption in industry (concepts widely used, modules slowly)

## Comprehensive Example

This example demonstrates C++20 features including [concepts](#concepts), [ranges](#ranges), [coroutines](#coroutines), [spaceship operator](#three-way-comparison-spaceship-operator-), and other improvements. Note: Modules and coroutines require special compiler support, so this focuses on widely-supported features.

```cpp
#include <iostream>
#include <vector>
#include <ranges>
#include <algorithm>
#include <string>
#include <compare>
#include <concepts>
#include <span>
#include <format>
#include <numbers>
#include <bit>

// ============================================================================
// CONCEPTS: Named template constraints (C++20)
// ============================================================================
// Standard concepts from <concepts>
template<typename T>
concept Numeric = std::integral<T> || std::floating_point<T>;

template<typename T>
concept Printable = requires(T t) {
    { std::cout << t } -> std::convertible_to<std::ostream&>;
};

template<typename T>
concept Addable = requires(T a, T b) {
    { a + b } -> std::same_as<T>;
};

// Use concepts instead of SFINAE!
template<Numeric T>
T square(T value) {
    return value * value;
}

// Abbreviated function template (C++20)
auto add(Addable auto a, Addable auto b) {
    return a + b;
}

// Constrained auto
void printValue(Printable auto value) {
    std::cout << "Value: " << value << "\n";
}

// Multiple constraints with requires clause
template<typename T>
requires Numeric<T> && (!std::floating_point<T>)
T doubleIfInt(T value) {
    return value * 2;  // Only for integral types
}

// ============================================================================
// SPACESHIP OPERATOR: Three-way comparison (C++20)
// ============================================================================
struct Point {
    int x, y;
    
    // C++20: One operator generates all comparisons!
    auto operator<=>(const Point&) const = default;
    
    // Also need equality if you want it (or = default both)
    bool operator==(const Point&) const = default;
};

// Custom spaceship implementation
class Version {
public:
    int major, minor, patch;
    
    // Custom three-way comparison
    auto operator<=>(const Version& other) const {
        // Lexicographic comparison
        if (auto cmp = major <=> other.major; cmp != 0) return cmp;
        if (auto cmp = minor <=> other.minor; cmp != 0) return cmp;
        return patch <=> other.patch;
    }
    
    bool operator==(const Version&) const = default;
};

// ============================================================================
// RANGES: Composable algorithms (C++20)
// ============================================================================
namespace ranges_demo {
    void demonstrateRanges() {
        std::cout << "\n--- Ranges Library ---\n";
        
        std::vector<int> numbers{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        
        // C++20 Ranges: Composable views (lazy evaluation!)
        auto evens = numbers 
            | std::views::filter([](int n) { return n % 2 == 0; })
            | std::views::transform([](int n) { return n * n; });
        
        std::cout << "Even squares: ";
        for (int n : evens) {
            std::cout << n << " ";  // 4, 16, 36, 64, 100
        }
        std::cout << "\n";
        
        // Take first N elements
        auto first5 = numbers | std::views::take(5);
        std::cout << "First 5: ";
        for (int n : first5) std::cout << n << " ";
        std::cout << "\n";
        
        // Drop first N elements
        auto afterFirst5 = numbers | std::views::drop(5);
        std::cout << "After first 5: ";
        for (int n : afterFirst5) std::cout << n << " ";
        std::cout << "\n";
        
        // Reverse view
        auto reversed = numbers | std::views::reverse;
        std::cout << "Reversed: ";
        for (int n : reversed) std::cout << n << " ";
        std::cout << "\n";
        
        // Complex pipeline
        auto result = numbers
            | std::views::filter([](int n) { return n > 3; })
            | std::views::transform([](int n) { return n * 2; })
            | std::views::take(3);
        
        std::cout << "Filtered, transformed, taken: ";
        for (int n : result) std::cout << n << " ";
        std::cout << "\n";
        
        // iota view - infinite range!
        auto infinite = std::views::iota(1)
            | std::views::take(10)
            | std::views::filter([](int n) { return n % 2 == 0; });
        
        std::cout << "First 10 evens from infinite range: ";
        for (int n : infinite) std::cout << n << " ";
        std::cout << "\n";
    }
}

// ============================================================================
// SPAN: Non-owning array view (C++20)
// ============================================================================
void processArray(std::span<const int> data) {
    std::cout << "Processing " << data.size() << " elements: ";
    for (int val : data) {
        std::cout << val << " ";
    }
    std::cout << "\n";
}

// ============================================================================
// CONSTEXPR IMPROVEMENTS: Much more allowed in constexpr (C++20)
// ============================================================================
constexpr int factorial(int n) {
    // C++20: Can use std::vector in constexpr!
    if (n <= 1) return 1;
    return n * factorial(n - 1);
}

constexpr bool isPalindrome(std::string_view str) {
    // C++20: Much more complex constexpr logic
    int left = 0;
    int right = str.size() - 1;
    
    while (left < right) {
        if (str[left] != str[right]) return false;
        ++left;
        --right;
    }
    return true;
}

// Compile-time verification
static_assert(factorial(5) == 120);
static_assert(isPalindrome("radar"));
static_assert(!isPalindrome("hello"));

// ============================================================================
// DESIGNATED INITIALIZERS: Named initialization (C++20)
// ============================================================================
struct Config {
    int width = 800;
    int height = 600;
    bool fullscreen = false;
    std::string title = "App";
};

// ============================================================================
// CONSTEVAL: Guaranteed compile-time (C++20)
// ============================================================================
consteval int compileTimeOnly(int n) {
    return n * n;  // MUST be evaluated at compile time
}

// ============================================================================
// CONSTINIT: Ensure static initialization (C++20)
// ============================================================================
constinit int globalValue = 42;  // Guaranteed compile-time init

// ============================================================================
// LAMBDA IMPROVEMENTS: Template and capture improvements (C++20)
// ============================================================================
void demonstrateLambdas() {
    std::cout << "\n--- Lambda Improvements ---\n";
    
    // Template lambda (C++20)
    auto genericAdd = []<typename T>(T a, T b) {
        return a + b;
    };
    
    std::cout << "genericAdd(5, 3) = " << genericAdd(5, 3) << "\n";
    std::cout << "genericAdd(2.5, 1.5) = " << genericAdd(2.5, 1.5) << "\n";
    
    // Pack expansion in lambda init-capture
    auto multiCapture = [](auto... args) {
        return (... + args);  // Fold expression
    };
    
    std::cout << "multiCapture(1,2,3,4,5) = " << multiCapture(1, 2, 3, 4, 5) << "\n";
}

// ============================================================================
// MATHEMATICAL CONSTANTS: <numbers> header (C++20)
// ============================================================================
void demonstrateMath() {
    std::cout << "\n--- Mathematical Constants ---\n";
    std::cout << "π = " << std::numbers::pi << "\n";
    std::cout << "e = " << std::numbers::e << "\n";
    std::cout << "√2 = " << std::numbers::sqrt2 << "\n";
    std::cout << "ln(2) = " << std::numbers::ln2 << "\n";
}

// ============================================================================
// BIT OPERATIONS: <bit> header (C++20)
// ============================================================================
void demonstrateBitOps() {
    std::cout << "\n--- Bit Operations ---\n";
    
    unsigned int value = 0b11010110;
    
    std::cout << "Value: " << std::bitset<8>(value) << "\n";
    std::cout << "popcount (number of 1s): " << std::popcount(value) << "\n";
    std::cout << "has_single_bit (power of 2): " << std::boolalpha << std::has_single_bit(16u) << "\n";
    std::cout << "bit_ceil (next power of 2): " << std::bit_ceil(20u) << "\n";
    std::cout << "bit_floor (prev power of 2): " << std::bit_floor(20u) << "\n";
    std::cout << "countl_zero (leading zeros): " << std::countl_zero(0b00001111u) << "\n";
    std::cout << "countr_zero (trailing zeros): " << std::countr_zero(0b11110000u) << "\n";
}

// ============================================================================
// CONTAINS for associative containers (C++20)
// ============================================================================
void demonstrateContains() {
    std::cout << "\n--- Container contains() ---\n";
    
    std::vector<int> vec{1, 2, 3, 4, 5};
    
    // C++20: contains() for maps/sets
    std::map<std::string, int> ages{{"Alice", 25}, {"Bob", 30}};
    
    std::cout << "Map contains 'Alice': " << std::boolalpha << ages.contains("Alice") << "\n";
    std::cout << "Map contains 'Charlie': " << ages.contains("Charlie") << "\n";
}

// ============================================================================
// USING ENUM: Import enum values (C++20)
// ============================================================================
enum class Color { Red, Green, Blue };

void demonstrateUsingEnum() {
    std::cout << "\n--- using enum ---\n";
    
    using enum Color;  // C++20: Import all enum values
    
    Color c = Red;  // No need for Color::Red!
    
    switch (c) {
        case Red:   std::cout << "Color is Red\n"; break;
        case Green: std::cout << "Color is Green\n"; break;
        case Blue:  std::cout << "Color is Blue\n"; break;
    }
}

// ============================================================================
// MAIN: Demonstrate C++20 features
// ============================================================================
int main() {
    std::cout << "=== C++20 Features Demo ===\n\n";
    
    // ========================================================================
    // CONCEPTS
    // ========================================================================
    std::cout << "--- Concepts ---\n";
    std::cout << "square(5) = " << square(5) << "\n";
    std::cout << "square(3.14) = " << square(3.14) << "\n";
    std::cout << "add(10, 20) = " << add(10, 20) << "\n";
    std::cout << "add(1.5, 2.5) = " << add(1.5, 2.5) << "\n";
    
    printValue(42);
    printValue("Hello C++20");
    printValue(3.14);
    
    std::cout << "doubleIfInt(21) = " << doubleIfInt(21) << "\n";
    // doubleIfInt(3.14);  // Would fail to compile!
    
    // ========================================================================
    // SPACESHIP OPERATOR
    // ========================================================================
    std::cout << "\n--- Spaceship Operator ---\n";
    
    Point p1{1, 2}, p2{3, 4}, p3{1, 2};
    
    std::cout << "p1 == p3: " << std::boolalpha << (p1 == p3) << "\n";
    std::cout << "p1 != p2: " << (p1 != p2) << "\n";
    std::cout << "p1 < p2: " << (p1 < p2) << "\n";
    std::cout << "p1 <= p3: " << (p1 <= p3) << "\n";
    
    Version v1{1, 2, 3}, v2{1, 3, 0}, v3{1, 2, 3};
    std::cout << "v1 == v3: " << (v1 == v3) << "\n";
    std::cout << "v1 < v2: " << (v1 < v2) << "\n";
    
    // ========================================================================
    // RANGES
    // ========================================================================
    ranges_demo::demonstrateRanges();
    
    // ========================================================================
    // SPAN
    // ========================================================================
    std::cout << "\n--- std::span ---\n";
    
    int arr[] = {1, 2, 3, 4, 5};
    std::vector<int> vec{6, 7, 8, 9, 10};
    
    processArray(arr);           // Works with C array
    processArray(vec);           // Works with vector
    processArray({11, 12, 13});  // Works with initializer list
    
    // Subspan
    std::span<int> fullSpan(arr);
    auto subSpan = fullSpan.subspan(1, 3);  // Elements 1-3
    processArray(subSpan);
    
    // ========================================================================
    // CONSTEXPR IMPROVEMENTS
    // ========================================================================
    std::cout << "\n--- constexpr Improvements ---\n";
    constexpr int fact10 = factorial(10);
    std::cout << "factorial(10) = " << fact10 << " (compile-time!)\n";
    
    constexpr bool check = isPalindrome("level");
    std::cout << "isPalindrome('level') = " << std::boolalpha << check << "\n";
    
    // ========================================================================
    // DESIGNATED INITIALIZERS
    // ========================================================================
    std::cout << "\n--- Designated Initializers ---\n";
    
    Config cfg{
        .width = 1920,
        .height = 1080,
        .fullscreen = true,
        .title = "My App"
    };
    
    std::cout << "Config: " << cfg.width << "x" << cfg.height 
              << " fullscreen=" << std::boolalpha << cfg.fullscreen << "\n";
    
    // Can skip members (uses defaults)
    Config cfg2{.title = "Small Window"};
    std::cout << "Config2: " << cfg2.width << "x" << cfg2.height << "\n";
    
    // ========================================================================
    // CONSTEVAL
    // ========================================================================
    std::cout << "\n--- consteval ---\n";
    constexpr int cval = compileTimeOnly(5);  // Compile-time
    std::cout << "compileTimeOnly(5) = " << cval << "\n";
    
    // int runtime = 5;
    // compileTimeOnly(runtime);  // Would fail! Must be compile-time
    
    // ========================================================================
    // LAMBDA IMPROVEMENTS
    // ========================================================================
    demonstrateLambdas();
    
    // ========================================================================
    // MATHEMATICAL CONSTANTS
    // ========================================================================
    demonstrateMath();
    
    // ========================================================================
    // BIT OPERATIONS
    // ========================================================================
    demonstrateBitOps();
    
    // ========================================================================
    // CONTAINS
    // ========================================================================
    demonstrateContains();
    
    // ========================================================================
    // USING ENUM
    // ========================================================================
    demonstrateUsingEnum();
    
    // ========================================================================
    // CONSTINIT
    // ========================================================================
    std::cout << "\n--- constinit ---\n";
    std::cout << "Global value: " << globalValue << "\n";
    
    std::cout << "\n=== C++20 Demo Complete ===\n";
    return 0;
}
```

**C++20 Revolutionary Features:**

| Feature | Benefit | Example |
|---------|---------|---------|
| **Concepts** | Readable constraints | `template<Numeric T>` |
| **Ranges** | Composable algorithms | `vec \| filter \| transform` |
| **Spaceship** | Auto comparisons | `auto operator<=>(...)` |
| **Span** | Safe array views | Works with C arrays & vectors |
| **Modules** | Fast compilation | `import std;` |
| **Coroutines** | Async programming | `co_await`, `co_yield` |
| **constexpr** | More compile-time | vectors, algorithms |
| **consteval** | Force compile-time | Guaranteed evaluation |

**Major Impact:**
- 🎯 **Concepts**: Templates finally readable, errors understandable
- 🔄 **Ranges**: Functional programming patterns natural in C++
- ⚡ **Spaceship**: Writing value types becomes trivial
- 📦 **Modules**: Build times drastically improved (when adopted)
- 🔢 **Coroutines**: Async/await style programming in C++

