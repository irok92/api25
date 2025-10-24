# C++26 Features

C++26 is currently under development (expected finalization in 2026). This document covers features that have been voted into the working draft or are highly likely to be included.

**⚠️ Note**: This is a preview of upcoming features. Compiler support and final syntax may change before ratification.

## 🔥 Major Features (Approved/Likely)

### Static Reflection
- 📁 [Reflection proposal](https://wg21.link/P2996) - Compile-time introspection
- **Inspect types, members, and attributes at compile-time**
- **Generate code based on type information**
```cpp
// Proposed syntax (subject to change)
template<typename T>
void print_members(const T& obj) {
    constexpr auto members = ^T;  // Reflect on T
    
    [:expand(members):] >> [&]<auto member> {
        std::print("{}: {}\n", 
                   member_name(member), 
                   obj.[:member:]);
    };
}

struct Point { int x, y; };
Point p{1, 2};
print_members(p);  // Prints: x: 1, y: 2
```

### Pattern Matching
- 📁 [Pattern matching proposal](https://wg21.link/P2688) - Powerful switch alternative
- **Match values, types, and structure**
- **Destructure in match patterns**
```cpp
// Proposed inspect expression
auto result = inspect(value) {
    0 => "zero";
    [1, 2, 3] => "small";
    [x, y] if (x == y) => "equal pair";
    std::string s => s;
    _ => "other";
};

// Match on variant
std::variant<int, double, std::string> v = 42;
inspect(v) {
    <int> i => std::println("int: {}", i);
    <double> d => std::println("double: {}", d);
    <std::string> s => std::println("string: {}", s);
};
```

### Contracts
- 📁 [Contracts proposal](https://wg21.link/P2900) - Preconditions, postconditions, assertions
- **Specify function requirements**
- **Runtime/compile-time checking**
```cpp
// Pre and post conditions
int divide(int a, int b)
    pre(b != 0)
    post(r => r * b == a)
{
    return a / b;
}

// Class invariants
class BankAccount {
    int balance;
    
    contract_assert balance >= 0;  // Always maintained
    
public:
    void withdraw(int amount)
        pre(amount > 0)
        pre(amount <= balance)
    {
        balance -= amount;
    }
};
```

### Senders/Receivers (Async improvements)
- 📁 [P2300](https://wg21.link/P2300) - Standard async execution model
- **Composable async operations**
- **Better than callbacks and raw coroutines**
```cpp
// Async pipeline
auto work = just(42)
    | then([](int x) { return x * 2; })
    | then([](int x) { std::println("Result: {}", x); });

// Execute on specific context
sync_wait(on(scheduler, work));

// Error handling
auto safe_work = just(10)
    | then([](int x) -> int { 
        if (x == 0) throw std::runtime_error("error");
        return 100 / x; 
    })
    | upon_error([](auto e) { 
        std::println("Error caught"); 
        return 0; 
    });
```

## 🆕 New Features

### Pack Indexing
- 📁 [P2662](https://wg21.link/P2662) - Index into parameter packs
```cpp
template<typename... Ts>
void process(Ts... args) {
    // C++26: Can index into pack!
    auto first = args...[0];
    auto second = args...[1];
    
    std::println("First: {}, Second: {}", first, second);
}

process(1, 2.5, "hello");  // first=1, second=2.5
```

### Placeholder Variables with User-Specified Names
- 📁 [P2169](https://wg21.link/P2169) - Meaningful unused variable names
```cpp
// C++26: Can use any identifier starting with underscore
auto [_row, _col, value] = parseData();  // Only need value

for (auto [_key, value] : map) {  // Clearer than [[maybe_unused]]
    process(value);
}
```

### Delete Non-Functions
- 📁 [P2644](https://wg21.link/P2644) - Delete variables and types
```cpp
// C++26: Prevent variable creation
int dangerous_global = delete;  // Can't be used

// Prevent template instantiation
template<typename T>
struct Forbidden = delete;
```

### constexpr cast from void*
- 📁 [P2738](https://wg21.link/P2738) - More constexpr power
```cpp
constexpr int getValue() {
    int x = 42;
    void* ptr = &x;
    // C++26: Can cast back in constexpr context
    int* iptr = static_cast<int*>(ptr);
    return *iptr;
}
```

### Saturation Arithmetic
- 📁 [P0543](https://wg21.link/P0543) - Clamping integer operations
```cpp
#include <numeric>

// C++26: Operations that saturate instead of overflow
uint8_t a = 200;
uint8_t b = 100;

auto sum = std::add_sat(a, b);  // 255 (saturates, doesn't overflow)
auto diff = std::sub_sat(10u, 20u);  // 0 (saturates at minimum)
auto prod = std::mul_sat(200u, 2u);  // 255 (saturates)
```

### std::inplace_vector
- 📁 [P0843](https://wg21.link/P0843) - Fixed-capacity vector
```cpp
// C++26: Vector with stack storage
std::inplace_vector<int, 10> vec;  // Max 10 elements, no heap allocation

vec.push_back(1);
vec.push_back(2);
// vec.push_back(...) 11 times would throw

// Perfect for embedded systems or hot paths
```

### std::hive (formerly colony)
- 📁 [P0447](https://wg21.link/P0447) - Stable-reference container
```cpp
// C++26: Container where iterators/pointers stay valid
std::hive<int> h;

auto it1 = h.insert(42);
auto it2 = h.insert(99);

h.insert(100);  // it1 and it2 still valid!
h.erase(it2);   // it1 still valid!

// Unlike vector, references don't invalidate
```

### Hazard Pointers
- 📁 [P1121](https://wg21.link/P1121) - Safe memory reclamation
```cpp
// C++26: Lock-free safe memory management
std::hazard_pointer hp = std::make_hazard_pointer(ptr);

// Protected from reclamation while hp exists
use(*hp);

// Safe concurrent deletion
```

### std::debugging (Debugging Support)
- 📁 [P2546](https://wg21.link/P2546) - Standard debugging interface
```cpp
// C++26: Query debug mode
if constexpr (std::debugging::is_debugger_present()) {
    std::debugging::breakpoint();  // Programmatic breakpoint
}

// Check if running under sanitizer
if constexpr (std::debugging::is_address_sanitizer_present()) {
    // Adjust behavior
}
```

## 📚 Library Additions

### Text Formatting Improvements
- 📁 [P2909](https://wg21.link/P2909) - More format string features
```cpp
// C++26: Enhanced formatting
std::println("Binary: {:0>8b}", 42);  // 00101010
std::println("Date: {:%Y-%m-%d}", std::chrono::system_clock::now());

// Format ranges directly
std::vector<int> v{1, 2, 3};
std::println("{}", v);  // [1, 2, 3]
```

### std::flat_map and std::flat_set
- 📁 [P0429](https://wg21.link/P0429) - Contiguous storage maps
```cpp
// C++26: Map with vector storage (better cache locality)
std::flat_map<int, std::string> map;
map[1] = "one";
map[2] = "two";

// Faster iteration, slower insertion than std::map
// Better for read-heavy workloads
```

### Linear Algebra Support
- 📁 [P1673](https://wg21.link/P1673) - BLAS-like operations
```cpp
// C++26: Standard linear algebra
std::linalg::matrix<double> A(3, 3);
std::linalg::matrix<double> B(3, 3);

auto C = A * B;  // Matrix multiplication

std::linalg::vector<double> v(3);
auto result = A * v;  // Matrix-vector multiply
```

### std::text and std::text_view (Unicode)
- 📁 [P1629](https://wg21.link/P1629) - Proper Unicode strings
```cpp
// C++26: Native Unicode support
std::text utf8_str = u8"Hello 🌍";
std::text utf16_str = u"Hello 🌍";

// Normalize, compare, iterate grapheme clusters
for (auto grapheme : utf8_str.graphemes()) {
    std::println("{}", grapheme);
}

// Proper Unicode comparison
bool equal = std::text::compare(str1, str2, 
                                std::text::normalization::nfc);
```

## 🔧 Language Refinements

### Structured Bindings Can Introduce Pack
- 📁 [P1061](https://wg21.link/P1061) - Unpack to parameter pack
```cpp
// C++26: Structured bindings with packs
auto [...elements] = tuple;  // Unpack to pack

template<typename... Ts>
void foo(Ts... args) {
    auto [...vals] = std::tuple{args...};
    // Use vals as pack
}
```

### constexpr Function Parameters
- 📁 [P1045](https://wg21.link/P1045) - Compile-time parameters
```cpp
// C++26: Some parameters compile-time only
void process(constexpr int option, int value) {
    if constexpr (option == 1) {
        // Branch 1 - optimized away if option != 1
    } else if constexpr (option == 2) {
        // Branch 2
    }
}

process<1>(42);  // Only branch 1 compiled
```

### Trivial Relocability
- 📁 [P1144](https://wg21.link/P1144) - Optimize move operations
```cpp
// C++26: Mark types as trivially relocatable
struct [[trivially_relocatable]] MyType {
    std::string data;
};

// Enables memcpy-based optimizations in containers
std::vector<MyType> vec;  // Can use faster reallocation
```

### Expansion Statements
- 📁 [P1306](https://wg21.link/P1306) - Loop over packs
```cpp
// C++26: More natural pack expansion
template<typename... Ts>
void print_all(Ts... args) {
    for... (auto arg : args) {
        std::println("{}", arg);
    }
}

// Expands to multiple statements
```

## 🎯 Standard Library Improvements

### Ranges Enhancements
- More range adaptors and algorithms
- Better views composition
- Performance improvements

### Networking (maybe)
- 📁 [Networking TS](https://wg21.link/N4771) - Possible inclusion
- Asio-based networking
- Sockets, timers, async I/O

### Executors
- 📁 [P2300](https://wg21.link/P2300) - Unified execution model
- Standard async framework
- Replaces ad-hoc threading

### Better Compile-Time Programming
- More constexpr support
- Better metaprogramming tools
- Reflection-based codegen

## Impact

C++26 aims to be transformative:

- **Reflection** - Eliminates boilerplate, enables serialization/introspection
- **Pattern Matching** - More expressive control flow
- **Contracts** - Catch bugs at boundaries
- **Senders/Receivers** - Modern async that actually works
- **Better Unicode** - First-class text handling

Combined with C++20's concepts and modules, C++26 could make C++ feel like a completely modern language.

## Compiler Support

Expected timeline:
- **GCC 14+** - Gradual adoption starting 2024-2025
- **Clang 18+** - Experimental support for approved features
- **MSVC 2026** - Following standard finalization

Full support will take 2-3 years after ratification.

## Adoption Strategy

For production code:
1. **2026-2027**: Wait for compiler support
2. **2027-2028**: Adopt reflection, pattern matching in new code
3. **2028+**: Broader adoption across codebases

Early adopters can experiment with compiler-specific implementations and proposals.

## Looking Forward: C++29 and Beyond

Future directions being discussed:
- **More reflection** - Expand capabilities
- **Better coroutines** - Simplify async code
- **Improved modules** - Faster compilation
- **Memory safety** - Borrow checking, lifetime analysis
- **Compatibility** - Interop with C, Rust, Python

C++ continues to evolve, balancing modern features with backward compatibility and zero-overhead abstractions.
