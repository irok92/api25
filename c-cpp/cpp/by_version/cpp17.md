# C++17 Features

C++17 continued to evolve C++, focusing on making the language simpler and more consistent while adding practical features for everyday programming.

## 🔥 Major Features

### Structured Bindings
- 📁 [Structured bindings](../05_declarations/structured_bindings_and_enumerations.md#structured-bindings) - Unpack multiple return values
```cpp
auto [a, b, c] = std::tuple{1, 2.5, "hello"};
auto [key, value] = *map.begin();  // Unpack map iterator

std::map<std::string, int> m{{"Alice", 25}};
for (auto [name, age] : m) {
    std::cout << name << " is " << age << '\n';
}
```

### if constexpr
- 📁 [if constexpr](../08_statements/conditional_statements.md#if-constexpr) - Compile-time branching
- 📁 [Template metaprogramming](../05_declarations/specifiers_and_qualifiers.md#constexpr-specifier) - Cleaner than SFINAE
```cpp
template<typename T>
auto process(T value) {
    if constexpr (std::is_integral_v<T>) {
        return value * 2;
    } else if constexpr (std::is_floating_point_v<T>) {
        return value * 1.5;
    } else {
        return value;
    }
}
```

### Class Template Argument Deduction (CTAD)
- 📁 [CTAD](../10_templates/template_argument_deduction.md#class-template-argument-deduction-ctad) - Omit template arguments
```cpp
std::pair p{42, 3.14};              // Deduced: std::pair<int, double>
std::vector v{1, 2, 3};             // Deduced: std::vector<int>
std::mutex mtx;
std::lock_guard lock{mtx};          // No need for std::lock_guard<std::mutex>
```

### Fold Expressions
- 📁 [Fold expressions](../10_templates/advanced_template_features.md#fold-expressions) - Apply operator to parameter pack
```cpp
template<typename... Args>
auto sum(Args... args) {
    return (args + ...);  // Fold expression
}

sum(1, 2, 3, 4);  // 10
```

### Guaranteed Copy Elision
- 📁 [Copy elision](../04_expressions/conversions.md#copy-elision) - No copy when returning temporaries
- **Guaranteed** behavior, not just optimization
```cpp
MyClass create() {
    return MyClass();  // C++17: guaranteed no copy, construct in place
}

MyClass obj = create();  // Only one construction, no copy!
```

## Language Features

### Init Statements
- 📁 [if with initializer](../08_statements/conditional_statements.md) - `if (init; condition)`
- 📁 [switch with initializer](../08_statements/conditional_statements.md) - `switch (init; value)`
```cpp
if (auto it = map.find(key); it != map.end()) {
    // Use it here
}  // it goes out of scope

switch (auto val = getValue(); val) {
    case 1: /*...*/
}
```

### Literals and Types
- 📁 [Hex float literals](../04_expressions/literals.md#floating-point-literals) - `0x1.2p3`
- 📁 [Nested namespaces](../05_declarations/namespaces.md) - `namespace A::B::C { }`
```cpp
namespace Company::Product::Feature {  // C++17
    void func();
}
// Instead of:
// namespace Company { namespace Product { namespace Feature {
//     void func();
// }}}
```

### Attributes
- 📁 [[[nodiscard]]](../05_declarations/attributes.md) - Warn if return value ignored
- 📁 [[[maybe_unused]]](../05_declarations/attributes.md) - Suppress unused warnings
- 📁 [[[fallthrough]]](../08_statements/conditional_statements.md) - Intentional switch fallthrough
```cpp
[[nodiscard]] int calculate() { return 42; }
calculate();  // Warning: return value ignored

void func([[maybe_unused]] int param) {
    // No warning about unused param
}
```

### Inline Variables
- 📁 [inline variables](../05_declarations/specifiers_and_qualifiers.md#inline-specifier) - Define in header
- 📁 [Inline variables in initialization](../06_initialization/non_local_variable_initialization.md)
```cpp
// header.h
inline constexpr int MAX_SIZE = 100;  // C++17: can define in header
```

### static_assert Without Message
- 📁 [static_assert](../05_declarations/compile_time_assertions.md) - Message optional
```cpp
static_assert(sizeof(int) == 4);  // C++17: no message needed
```

### Expression Evaluation Order
- 📁 [Evaluation order](../04_expressions/expressions.md) - More predictable
- Function arguments evaluated left-to-right for certain operators
```cpp
f(a(), b(), c());  // C++17: evaluated left-to-right
```

## Templates and Type System

### std::void_t
- 📁 [std::void_t](../10_templates/dependent_names.md) - Detection idiom helper
```cpp
template<typename, typename = std::void_t<>>
struct has_size : std::false_type {};

template<typename T>
struct has_size<T, std::void_t<decltype(std::declval<T>().size())>> 
    : std::true_type {};
```

## Standard Library

### Filesystem
- `std::filesystem` - Cross-platform file system operations
```cpp
#include <filesystem>
namespace fs = std::filesystem;

for (auto& p : fs::directory_iterator("/path")) {
    std::cout << p.path() << '\n';
}
```

### std::optional
- `std::optional<T>` - May or may not contain a value
```cpp
std::optional<int> find(int key) {
    if (/*found*/) return value;
    return std::nullopt;
}

if (auto result = find(42)) {
    std::cout << *result;
}
```

### std::variant
- 📁 [std::variant](../09_classes/basic_class_concepts.md) - Type-safe union
```cpp
std::variant<int, double, std::string> v;
v = 42;
v = 3.14;
v = "hello";
std::cout << std::get<std::string>(v);
```

### std::any
- `std::any` - Type-erased single value
```cpp
std::any a = 42;
a = 3.14;
a = std::string("hello");
std::cout << std::any_cast<std::string>(a);
```

### std::string_view
- `std::string_view` - Non-owning string reference
```cpp
void process(std::string_view sv) {  // No copy!
    std::cout << sv;
}

process("hello");
process(myString);
process(myString.substr(0, 5));
```

### Parallel Algorithms
- Execution policies for standard algorithms
```cpp
std::sort(std::execution::par, v.begin(), v.end());
```

### Other Utilities
- `std::byte` - Type for raw bytes
- `std::apply` - Call function with tuple
- `std::invoke` - Call any callable
- `std::clamp` - Clamp value between min/max
- `std::gcd`, `std::lcm` - Math functions

## Key Improvements

### Cleaner Code
```cpp
// C++14
std::map<std::string, int> map;
auto it = map.find("key");
if (it != map.end()) {
    std::cout << it->second;
}

// C++17
if (auto it = map.find("key"); it != map.end()) {
    std::cout << it->second;
}

// Or with structured bindings:
for (auto [key, value] : map) {
    std::cout << key << ": " << value << '\n';
}
```

### Better Generic Programming
```cpp
// C++14: Complex SFINAE
template<typename T>
std::enable_if_t<std::is_integral<T>::value>
process(T value) { /*...*/ }

// C++17: Clean compile-time branching
template<typename T>
void process(T value) {
    if constexpr (std::is_integral_v<T>) {
        // integral handling
    } else {
        // other handling
    }
}
```

## Impact

C++17 made C++ significantly more ergonomic:
- **Structured bindings** - More intuitive multi-value returns
- **if constexpr** - Cleaner template metaprogramming
- **CTAD** - Less template noise
- **Filesystem** - Finally, standard file operations!
- **std::optional/variant/any** - Better vocabulary types
- **Guaranteed copy elision** - Performance you can rely on

## Comprehensive Example

This example demonstrates C++17 features including [structured bindings](#structured-bindings), [if constexpr](#if-constexpr), [fold expressions](#fold-expressions), [CTAD](#class-template-argument-deduction-ctad), [std::optional](#stdoptional), [std::variant](#stdvariant), and [filesystem](#filesystem-library).

```cpp
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <tuple>
#include <optional>
#include <variant>
#include <filesystem>
#include <fstream>
#include <algorithm>
#include <any>
#include <string_view>

namespace fs = std::filesystem;

// ============================================================================
// STRUCTURED BINDINGS: Decompose objects elegantly (C++17)
// ============================================================================
std::tuple<int, double, std::string> getPersonInfo() {
    return {25, 5.9, "Alice"};
}

std::map<std::string, int> getScores() {
    return {{"Math", 95}, {"Physics", 87}, {"Chemistry", 92}};
}

// Custom struct for structured binding
struct Point3D {
    double x, y, z;
};

// ============================================================================
// IF CONSTEXPR: Compile-time conditional (C++17)
// ============================================================================
template<typename T>
auto processValue(T value) {
    if constexpr (std::is_integral_v<T>) {
        // Compiled only for integral types
        std::cout << "Processing integer: " << value << "\n";
        return value * 2;
    } else if constexpr (std::is_floating_point_v<T>) {
        // Compiled only for floating point types
        std::cout << "Processing float: " << value << "\n";
        return value * 3.14;
    } else if constexpr (std::is_same_v<T, std::string>) {
        // Compiled only for strings
        std::cout << "Processing string: " << value << "\n";
        return value + " processed";
    } else {
        std::cout << "Processing unknown type\n";
        return value;
    }
}

// Different implementations based on type traits
template<typename T>
void printContainer(const T& container) {
    if constexpr (requires { container.size(); }) {
        // Has size() method
        std::cout << "Container with " << container.size() << " elements: ";
    } else {
        std::cout << "Container elements: ";
    }
    
    for (const auto& item : container) {
        std::cout << item << " ";
    }
    std::cout << "\n";
}

// ============================================================================
// FOLD EXPRESSIONS: Variadic template magic (C++17)
// ============================================================================
// Sum all arguments with fold expression
template<typename... Args>
auto sum(Args... args) {
    return (... + args);  // Left fold: ((arg1 + arg2) + arg3) + ...
}

// Multiply all arguments
template<typename... Args>
auto multiply(Args... args) {
    return (args * ...);  // Right fold: arg1 * (arg2 * (arg3 * ...))
}

// Print all arguments
template<typename... Args>
void printAll(Args&&... args) {
    ((std::cout << args << " "), ...);  // Fold with comma operator
    std::cout << "\n";
}

// Check if all values are positive
template<typename... Args>
bool allPositive(Args... args) {
    return (... && (args > 0));  // Fold with logical AND
}

// Check if any value is zero
template<typename... Args>
bool anyZero(Args... args) {
    return (... || (args == 0));  // Fold with logical OR
}

// Push all arguments to vector
template<typename T, typename... Args>
void pushAll(std::vector<T>& vec, Args&&... args) {
    (vec.push_back(std::forward<Args>(args)), ...);
}

// ============================================================================
// CLASS TEMPLATE ARGUMENT DEDUCTION (CTAD) - C++17
// ============================================================================
// No need to specify template arguments!

template<typename T>
class Container {
public:
    Container(T value) : data(value) {}
    T get() const { return data; }
private:
    T data;
};

// Custom deduction guide (optional)
template<typename T>
Container(T) -> Container<T>;

// ============================================================================
// STD::OPTIONAL: Type-safe nullable values (C++17)
// ============================================================================
std::optional<int> findValue(const std::vector<int>& vec, int target) {
    auto it = std::find(vec.begin(), vec.end(), target);
    if (it != vec.end()) {
        return *it;  // Return value
    }
    return std::nullopt;  // No value found
}

std::optional<std::string> getMiddleName(bool hasMiddle) {
    if (hasMiddle) {
        return "Marie";
    }
    return std::nullopt;
}

// Safe division with optional
std::optional<double> safeDivide(double a, double b) {
    if (b == 0.0) return std::nullopt;
    return a / b;
}

// ============================================================================
// STD::VARIANT: Type-safe union (C++17)
// ============================================================================
using Value = std::variant<int, double, std::string>;

void processVariant(const Value& value) {
    // Visit pattern - type-safe access
    std::visit([](const auto& v) {
        std::cout << "Value: " << v << "\n";
    }, value);
}

// Get type name from variant
std::string getTypeName(const Value& value) {
    return std::visit([](const auto& v) -> std::string {
        using T = std::decay_t<decltype(v)>;
        if constexpr (std::is_same_v<T, int>) return "int";
        else if constexpr (std::is_same_v<T, double>) return "double";
        else if constexpr (std::is_same_v<T, std::string>) return "string";
        else return "unknown";
    }, value);
}

// ============================================================================
// STD::ANY: Hold any type (C++17)
// ============================================================================
void demonstrateAny() {
    std::any value;
    
    value = 42;
    std::cout << "Holds int: " << std::any_cast<int>(value) << "\n";
    
    value = 3.14;
    std::cout << "Holds double: " << std::any_cast<double>(value) << "\n";
    
    value = std::string("Hello");
    std::cout << "Holds string: " << std::any_cast<std::string>(value) << "\n";
    
    // Check type
    if (value.type() == typeid(std::string)) {
        std::cout << "Current type: string\n";
    }
}

// ============================================================================
// STRING_VIEW: Non-owning string reference (C++17)
// ============================================================================
void processString(std::string_view sv) {
    // No copy, just a view into the string
    std::cout << "Processing (length=" << sv.length() << "): " << sv << "\n";
    
    // Can slice efficiently
    if (sv.size() > 5) {
        std::cout << "First 5 chars: " << sv.substr(0, 5) << "\n";
    }
}

// ============================================================================
// INLINE VARIABLES: Variables in headers (C++17)
// ============================================================================
inline int globalCounter = 0;  // Can be in header, no ODR violation!

// ============================================================================
// NESTED NAMESPACES: Cleaner syntax (C++17)
// ============================================================================
namespace Company::Product::Module {  // C++17: nested namespace
    void doWork() {
        std::cout << "Working in nested namespace\n";
    }
}

// ============================================================================
// FILESYSTEM LIBRARY: Cross-platform file operations (C++17)
// ============================================================================
void demonstrateFilesystem() {
    std::cout << "\n--- Filesystem Library ---\n";
    
    // Current path
    fs::path currentPath = fs::current_path();
    std::cout << "Current path: " << currentPath << "\n";
    
    // Create directory
    fs::path testDir = currentPath / "test_cpp17";
    if (!fs::exists(testDir)) {
        fs::create_directory(testDir);
        std::cout << "Created directory: " << testDir << "\n";
    }
    
    // Create a test file
    fs::path testFile = testDir / "example.txt";
    {
        std::ofstream ofs(testFile);
        ofs << "C++17 filesystem example\n";
    }
    std::cout << "Created file: " << testFile << "\n";
    
    // Check file properties
    if (fs::exists(testFile)) {
        std::cout << "File size: " << fs::file_size(testFile) << " bytes\n";
        std::cout << "Is regular file: " << std::boolalpha << fs::is_regular_file(testFile) << "\n";
    }
    
    // Iterate directory
    std::cout << "Contents of " << testDir << ":\n";
    for (const auto& entry : fs::directory_iterator(testDir)) {
        std::cout << "  " << entry.path().filename() << "\n";
    }
    
    // Cleanup
    fs::remove(testFile);
    fs::remove(testDir);
    std::cout << "Cleaned up test directory\n";
}

// ============================================================================
// INIT STATEMENT in if/switch (C++17)
// ============================================================================
void demonstrateInitStatements() {
    std::cout << "\n--- Init Statements ---\n";
    
    std::map<std::string, int> data{{"x", 10}, {"y", 20}};
    
    // C++17: Init statement in if
    if (auto it = data.find("x"); it != data.end()) {
        std::cout << "Found x: " << it->second << "\n";
        // 'it' is scoped to this if block
    }
    
    // Init statement with structured binding
    if (auto [iter, inserted] = data.insert({"z", 30}); inserted) {
        std::cout << "Inserted z: " << iter->second << "\n";
    }
    
    // Init statement in switch
    switch (auto value = 42; value) {
        case 42:
            std::cout << "Value is: " << value << "\n";
            break;
        default:
            break;
    }
}

// ============================================================================
// CONSTEXPR LAMBDA (C++17)
// ============================================================================
constexpr auto square = [](int x) { return x * x; };
constexpr auto add = [](int a, int b) { return a + b; };

// Use in constexpr context
constexpr int result = square(5) + add(3, 4);  // Compile-time!

// ============================================================================
// MAIN: Demonstrate C++17 features
// ============================================================================
int main() {
    std::cout << "=== C++17 Features Demo ===\n\n";
    
    // ========================================================================
    // STRUCTURED BINDINGS
    // ========================================================================
    std::cout << "--- Structured Bindings ---\n";
    
    // Unpack tuple
    auto [age, height, name] = getPersonInfo();
    std::cout << name << " is " << age << " years old and " << height << " feet tall\n";
    
    // Unpack map entries
    for (const auto& [subject, score] : getScores()) {
        std::cout << subject << ": " << score << "\n";
    }
    
    // Unpack custom struct
    Point3D point{1.0, 2.0, 3.0};
    auto [x, y, z] = point;
    std::cout << "Point: (" << x << ", " << y << ", " << z << ")\n";
    
    // Unpack pair
    std::pair<int, std::string> data{42, "answer"};
    auto [number, text] = data;
    std::cout << "Number: " << number << ", Text: " << text << "\n";
    
    // ========================================================================
    // IF CONSTEXPR
    // ========================================================================
    std::cout << "\n--- if constexpr ---\n";
    processValue(42);
    processValue(3.14);
    processValue(std::string("Hello"));
    
    std::vector<int> vec{1, 2, 3};
    printContainer(vec);
    
    // ========================================================================
    // FOLD EXPRESSIONS
    // ========================================================================
    std::cout << "\n--- Fold Expressions ---\n";
    std::cout << "sum(1, 2, 3, 4, 5) = " << sum(1, 2, 3, 4, 5) << "\n";
    std::cout << "multiply(2, 3, 4) = " << multiply(2, 3, 4) << "\n";
    
    std::cout << "printAll: ";
    printAll(1, 2.5, "hello", 'x');
    
    std::cout << "allPositive(1,2,3): " << std::boolalpha << allPositive(1, 2, 3) << "\n";
    std::cout << "allPositive(1,-2,3): " << allPositive(1, -2, 3) << "\n";
    std::cout << "anyZero(1,0,3): " << anyZero(1, 0, 3) << "\n";
    
    std::vector<int> numbers;
    pushAll(numbers, 10, 20, 30, 40);
    std::cout << "Pushed numbers: ";
    for (int n : numbers) std::cout << n << " ";
    std::cout << "\n";
    
    // ========================================================================
    // CLASS TEMPLATE ARGUMENT DEDUCTION (CTAD)
    // ========================================================================
    std::cout << "\n--- CTAD ---\n";
    
    // C++17: No need for <int>, <double>, etc.!
    Container c1(42);           // Deduced as Container<int>
    Container c2(3.14);         // Deduced as Container<double>
    Container c3("hello");      // Deduced as Container<const char*>
    
    std::cout << "c1: " << c1.get() << "\n";
    std::cout << "c2: " << c2.get() << "\n";
    std::cout << "c3: " << c3.get() << "\n";
    
    // Standard library CTAD
    std::pair p{1, 3.14};                    // pair<int, double>
    std::tuple t{1, "hello", 3.14};          // tuple<int, const char*, double>
    std::vector v{1, 2, 3, 4, 5};            // vector<int>
    
    // ========================================================================
    // STD::OPTIONAL
    // ========================================================================
    std::cout << "\n--- std::optional ---\n";
    
    std::vector<int> values{10, 20, 30};
    auto found = findValue(values, 20);
    if (found) {
        std::cout << "Found: " << *found << "\n";
    }
    
    auto notFound = findValue(values, 99);
    std::cout << "Search for 99: " << (notFound ? "found" : "not found") << "\n";
    
    // value_or for default
    std::cout << "Middle name: " << getMiddleName(true).value_or("None") << "\n";
    std::cout << "Middle name: " << getMiddleName(false).value_or("None") << "\n";
    
    // Safe division
    if (auto result = safeDivide(10.0, 2.0); result) {
        std::cout << "10 / 2 = " << *result << "\n";
    }
    std::cout << "10 / 0 = " << safeDivide(10.0, 0.0).value_or(-1.0) << " (error)\n";
    
    // ========================================================================
    // STD::VARIANT
    // ========================================================================
    std::cout << "\n--- std::variant ---\n";
    
    Value v1 = 42;
    Value v2 = 3.14;
    Value v3 = std::string("Hello");
    
    processVariant(v1);
    processVariant(v2);
    processVariant(v3);
    
    std::cout << "v1 type: " << getTypeName(v1) << "\n";
    std::cout << "v2 type: " << getTypeName(v2) << "\n";
    std::cout << "v3 type: " << getTypeName(v3) << "\n";
    
    // Check current type
    if (std::holds_alternative<int>(v1)) {
        std::cout << "v1 holds int: " << std::get<int>(v1) << "\n";
    }
    
    // ========================================================================
    // STD::ANY
    // ========================================================================
    std::cout << "\n--- std::any ---\n";
    demonstrateAny();
    
    // ========================================================================
    // STRING_VIEW
    // ========================================================================
    std::cout << "\n--- string_view ---\n";
    std::string str = "Hello, C++17!";
    processString(str);               // From string
    processString("Literal string");  // From literal
    
    std::string_view sv = str;
    processString(sv.substr(0, 5));   // Efficient substring
    
    // ========================================================================
    // NESTED NAMESPACES
    // ========================================================================
    std::cout << "\n--- Nested Namespaces ---\n";
    Company::Product::Module::doWork();
    
    // ========================================================================
    // INIT STATEMENTS
    // ========================================================================
    demonstrateInitStatements();
    
    // ========================================================================
    // CONSTEXPR LAMBDA
    // ========================================================================
    std::cout << "\n--- constexpr Lambda ---\n";
    std::cout << "square(5) + add(3,4) = " << result << " (compile-time!)\n";
    static_assert(result == 32, "constexpr lambda calculation wrong");
    
    // ========================================================================
    // INLINE VARIABLES
    // ========================================================================
    std::cout << "\n--- Inline Variables ---\n";
    globalCounter = 100;
    std::cout << "Global counter: " << globalCounter << "\n";
    
    // ========================================================================
    // FILESYSTEM LIBRARY
    // ========================================================================
    demonstrateFilesystem();
    
    std::cout << "\n=== C++17 Demo Complete ===\n";
    return 0;
}
```

**C++17 Key Improvements:**

| Feature | Benefit | Example |
|---------|---------|---------|
| **Structured bindings** | Elegant unpacking | `auto [x, y] = point;` |
| **if constexpr** | True compile-time branching | No runtime overhead |
| **Fold expressions** | Clean variadic templates | `(... + args)` |
| **CTAD** | Less template syntax | `vector v{1,2,3};` |
| **std::optional** | Type-safe nullable | No more `-1` sentinel |
| **std::variant** | Type-safe union | Visitor pattern |
| **string_view** | Non-owning strings | Zero-copy operations |
| **Filesystem** | Portable file operations | Cross-platform paths |

**Major Benefits:**
- 🎯 **Better syntax**: Structured bindings, CTAD, nested namespaces
- ⚡ **Compile-time**: if constexpr, constexpr lambda, fold expressions
- 🛡️ **Type safety**: optional, variant, any
- 📁 **Standard filesystem**: No more boost::filesystem!

