# C++11 Features

C++11 was a major modernization of C++, introducing many features that make the language safer, more expressive, and easier to use.

## � Official Reference
**Primary Source**: [cppreference.com C++11](https://en.cppreference.com/w/cpp/11)

## 🔥 Core Language Features

### Type Deduction & Inference
- 📁 [auto specifier](../05_declarations/type_specifiers.md#auto-specifier) - Automatic type deduction from initializer
- 📁 [decltype specifier](../05_declarations/type_specifiers.md#decltype-specifier) - Query type of expression
- Return type deduction (`auto func() -> ReturnType`)

### Move Semantics & Rvalue References
- 📁 [Rvalue references](../05_declarations/compound_types.md#references) - `T&&` for move semantics
- 📁 [Move constructor](../09_classes/special_member_functions.md#move-constructor) - Efficient resource transfer
- 📁 [Move assignment](../09_classes/special_member_functions.md#move-assignment-operator) - Move assignment operator
- `std::move()` and `std::forward()` utilities

### Lambda Expressions
- 📁 [Lambda expressions](../07_functions/functions.md#lambda-expression) - `[capture](params) { body }`
- Capture modes: by value `[=]`, by reference `[&]`, mixed captures
- Mutable lambdas: `[=]() mutable { }`

### Uniform Initialization
- 📁 [List initialization](../06_initialization/basic_initialization_forms.md#list-initialization) - `T obj{args...}`
- Prevents narrowing conversions
- `std::initializer_list<T>` for container initialization

### Variadic Templates
- 📁 [Variadic templates](../10_templates/template_parameters.md#variadic-template-parameters) - `template<typename... Args>`
- Parameter pack expansion: `sizeof...(Args)`
- Perfect forwarding with variadic templates

### Compile-Time Programming
- 📁 [constexpr](../03_keywords/keywords.md#constexpr) - Compile-time evaluation of functions and variables
- 📁 [static_assert](../08_statements/declaration_statements.md#static-assert) - Compile-time assertions
- Literal types for constexpr

### Type System Enhancements
- 📁 [nullptr](../03_keywords/keywords.md#nullptr) - Null pointer literal replacing NULL
- 📁 [long long](../05_declarations/fundamental_types.md#integer-types) - Extended integer type (at least 64 bits)
- 📁 [char16_t and char32_t](../05_declarations/fundamental_types.md#character-types) - Unicode character types
- 📁 [Type aliases](../05_declarations/type_aliases.md) - `using` syntax: `using Int = int;`
- Strongly-typed enums: `enum class Color { Red, Green, Blue };`

### Function Enhancements
- 📁 [Defaulted functions](../09_classes/special_member_functions.md#defaulted-functions) - `= default`
- 📁 [Deleted functions](../09_classes/special_member_functions.md#deleted-functions) - `= delete`
- 📁 [Delegating constructors](../09_classes/constructors.md#delegating-constructors) - Constructor chaining
- 📁 [Inheriting constructors](../09_classes/constructors.md#inheriting-constructors) - `using Base::Base;`
- 📁 [override](../03_keywords/keywords.md#override) - Explicit virtual override
- 📁 [final](../03_keywords/keywords.md#final) - Prevent overriding or inheritance
- 📁 [noexcept](../03_keywords/keywords.md#noexcept) - Exception specification

### Class Features
- Non-static data member initializers (NSDMI): `int x = 42;` in class body
- Unrestricted unions - unions can contain non-trivial types
- 📁 [Attributes](../03_keywords/attributes.md) - `[[noreturn]]`, `[[carries_dependency]]`

### Memory & Alignment
- 📁 [alignas](../03_keywords/keywords.md#alignas) - Specify alignment requirements
- 📁 [alignof](../03_keywords/keywords.md#alignof) - Query alignment requirements

### Literals & Strings
- 📁 [Raw string literals](../04_expressions/literals.md#string-literals) - `R"(raw\nstring)"`
- 📁 [User-defined literals](../04_expressions/literals.md#user-defined-literals) - `123_km`, `"hello"s`
- UTF-8/16/32 string literals: `u8"text"`, `u"text"`, `U"text"`

### Control Flow
- 📁 [range-for](../08_statements/iteration_statements.md#range-for) - `for (auto elem : container)`

### Threading & Concurrency
- 📁 [thread_local](../03_keywords/keywords.md#thread-local) - Thread-local storage
- Memory model for multithreading

### Other Core Features
- Inline namespaces: `inline namespace V2 { }`
- Unrestricted unions
- Extended friend declarations
- Template aliases: `template<typename T> using Vec = std::vector<T>;`

## 📦 Standard Library Additions

### Smart Pointers (memory management)
- `std::unique_ptr<T>` - Exclusive ownership
- `std::shared_ptr<T>` - Shared ownership with reference counting
- `std::weak_ptr<T>` - Non-owning reference to shared_ptr
- `std::make_shared<T>()` - Efficient shared_ptr creation

### Containers
- `std::array<T, N>` - Fixed-size array container
- `std::forward_list<T>` - Singly-linked list
- `std::unordered_map<K, V>` - Hash table
- `std::unordered_set<T>` - Hash set
- `std::unordered_multimap<K, V>` - Multi-key hash table
- `std::unordered_multiset<T>` - Multi-value hash set

### Multithreading Support
- `<thread>` - `std::thread`, `std::this_thread`
- `<mutex>` - `std::mutex`, `std::lock_guard`, `std::unique_lock`
- `<condition_variable>` - Thread synchronization
- `<future>` - `std::future`, `std::promise`, `std::async`, `std::packaged_task`
- `<atomic>` - Lock-free atomic operations

### Utilities
- `<tuple>` - `std::tuple<T...>`, `std::tie`, `std::make_tuple`
- `<functional>` - `std::function<R(Args...)>`, `std::bind`, `std::ref`, `std::cref`
- `<type_traits>` - Type introspection and transformation
- `<ratio>` - Compile-time rational arithmetic
- `<chrono>` - Time utilities: `std::chrono::duration`, `std::chrono::time_point`

### Algorithms & Iterators
- Move iterators: `std::make_move_iterator()`
- `std::begin()`, `std::end()` - Non-member begin/end functions

### String & Numeric
- `<regex>` - Regular expression library
- `<random>` - Random number generation (engines and distributions)
- Numeric conversion: `std::stoi`, `std::stod`, `std::to_string`

### Error Handling
- `std::exception_ptr` - Store and rethrow exceptions
- `std::current_exception()`, `std::rethrow_exception()`
- `std::nested_exception` - Exception chaining
- `<system_error>` - System error codes


##  Comprehensive Example

Compact demonstration of C++11 features based on [cppreference.com/w/cpp/11](https://en.cppreference.com/w/cpp/11). Each section shows practical usage with inline comments.

```cpp
#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <thread>
#include <mutex>
#include <future>
#include <chrono>
#include <random>
#include <regex>
#include <tuple>
#include <functional>
#include <array>
#include <unordered_map>
#include <forward_list>
#include <atomic>
#include <type_traits>

//=== CORE LANGUAGE FEATURES ===//

// 1. Auto type deduction & decltype
auto deduceTypes() {
    auto x = 42;           // int
    auto y = 3.14;         // double  
    auto ptr = &x;         // int*
    decltype(x) z = 10;    // same type as x (int)
    return x;
}

// 2. Nullptr - type-safe null pointer
void useNullptr(int* ptr = nullptr) {
    if (ptr != nullptr) { /* safe check */ }
}

// 3. Enum class - strongly typed enums
enum class Color { Red, Green, Blue };
enum class TrafficLight { Red, Yellow, Green }; // No collision with Color::Red!

// 4. Type aliases with 'using'
using IntVec = std::vector<int>;
template<typename T> using Ptr = std::unique_ptr<T>;

// 5. Constexpr - compile-time evaluation
constexpr int factorial(int n) { return n <= 1 ? 1 : n * factorial(n - 1); }
constexpr int fib(int n) { return n <= 1 ? n : fib(n-1) + fib(n-2); }
static_assert(factorial(5) == 120, "Compile-time test");

// 6. User-defined literals
constexpr long long operator""_KB(unsigned long long kb) { return kb * 1024; }
constexpr long double operator""_deg(long double deg) { return deg * 3.14159 / 180.0; }

// 7. Raw string literals - no escaping needed
const char* json = R"({"name": "C++11", "version": 2011})";
const char* regex_pattern = R"(\d{3}-\d{3}-\d{4})"; // Phone pattern

// 8. Unicode literals
const char* utf8 = u8"UTF-8 string";
const char16_t* utf16 = u"UTF-16 string";
const char32_t* utf32 = U"UTF-32 string";

// 9. Long long type
long long big_number = 9223372036854775807LL;

// 10. Rvalue references & Move semantics
class Buffer {
    int* data;
    size_t size;
public:
    Buffer(size_t sz) : data(new int[sz]), size(sz) {}
    ~Buffer() { delete[] data; }
    
    // Move constructor (C++11) - transfer ownership
    Buffer(Buffer&& other) noexcept : data(other.data), size(other.size) {
        other.data = nullptr; other.size = 0;
    }
    
    // Move assignment
    Buffer& operator=(Buffer&& other) noexcept {
        if(this != &other) {
            delete[] data;
            data = other.data; size = other.size;
            other.data = nullptr; other.size = 0;
        }
        return *this;
    }
    
    Buffer(const Buffer&) = delete; // Deleted copy constructor
    Buffer& operator=(const Buffer&) = delete; // Deleted copy assignment
};

// 11. Defaulted and deleted functions
struct Point {
    int x = 0, y = 0; // Non-static data member initializers
    Point() = default; // Explicitly defaulted
    Point(int x, int y) : x(x), y(y) {}
    Point(const Point&) = delete; // Explicitly deleted (no copy)
};

// 12. Override and final
struct Base {
    virtual void func() {}
    virtual ~Base() = default;
};
struct Derived final : Base {  // 'final' prevents further inheritance
    void func() override {}     // 'override' makes intent explicit
};

// 13. Delegating constructors
class Widget {
    int value;
    std::string name;
public:
    Widget() : Widget(0) {}             // Delegates to next constructor
    Widget(int v) : Widget(v, "default") {}  // Delegates
    Widget(int v, std::string n) : value(v), name(n) {} // Target constructor
};

// 14. Inheriting constructors
struct BaseClass {
    BaseClass(int x) {}
    BaseClass(double d) {}
};
struct DerivedClass : BaseClass {
    using BaseClass::BaseClass; // Inherit all constructors
};

// 15. Noexcept specification
void guaranteed_no_throw() noexcept {}
void might_throw() {}

// 16. Lambda expressions
void lambdaDemo() {
    int x = 10;
    auto simple = [](int a, int b) { return a + b; };          // No capture
    auto capture_val = [x](int a) { return a + x; };           // Capture by value
    auto capture_ref = [&x](int a) { x = a; };                 // Capture by reference
    auto capture_all = [=](int a) { return a + x; };           // Capture all by value
    auto mutable_lambda = [x]() mutable { return ++x; };       // Mutable capture
    
    // Generic lambda (C++14), but showing basic lambda
    std::vector<int> v{1,2,3,4,5};
    std::for_each(v.begin(), v.end(), [](int n) { std::cout << n << " "; });
}

// 17. Variadic templates & parameter packs
template<typename... Args>
void print(Args... args) {
    int dummy[] = { (std::cout << args << " ", 0)... }; // Pack expansion
    (void)dummy;
}

template<typename... Args>
constexpr size_t count_args(Args... args) {
    return sizeof...(args);  // sizeof... operator
}

// 18. Trailing return type
template<typename T, typename U>
auto add(T t, U u) -> decltype(t + u) {  // Return type deduced from expression
    return t + u;
}

// 19. Uniform initialization (list initialization)
void initDemo() {
    int x{42};                          // Prevents narrowing
    std::vector<int> v{1, 2, 3};        // Container init
    int arr[]{10, 20, 30};              // Array init
    std::pair<int, std::string> p{1, "one"}; // Pair init
}

// 20. Range-based for loop
void rangeForDemo() {
    std::vector<int> vec{1, 2, 3, 4, 5};
    for (auto x : vec) {          // Copy
        std::cout << x << " ";
    }
    for (const auto& x : vec) {   // Const reference (efficient)
        std::cout << x << " ";
    }
}

// 21. Attributes
[[noreturn]] void terminate_program() { std::exit(1); }
[[carries_dependency]] int* get_ptr(int* p) { return p; }

// 22. Alignas/alignof
struct alignas(16) AlignedStruct { char c; };  // Force 16-byte alignment
static_assert(alignof(AlignedStruct) == 16, "Alignment check");

// 23. Thread-local storage
thread_local int tls_counter = 0; // Each thread has its own copy

// 24. Static assertions
static_assert(sizeof(int) >= 4, "int must be at least 4 bytes");
static_assert(std::is_pod<Point>::value, "Point must be POD");

//=== STANDARD LIBRARY FEATURES ===//

// 25. Smart pointers
void smartPointerDemo() {
    std::unique_ptr<int> up(new int(10));                 // Exclusive ownership
    
    auto shared1 = std::make_shared<int>(20);             // Reference counting
    auto shared2 = shared1;                               // Shared ownership
    std::cout << "Use count: " << shared1.use_count();    // 2
    
    std::weak_ptr<int> weak = shared1;                    // Non-owning reference
}

// 26. Containers
void containerDemo() {
    std::array<int, 5> arr{1,2,3,4,5};                   // Fixed-size array
    std::forward_list<int> flist{1,2,3};                 // Singly-linked list
    std::unordered_map<std::string, int> umap{           // Hash table
        {"one", 1}, {"two", 2}
    };
    std::unordered_set<int> uset{1,2,3};                 // Hash set
}

// 27. Tuple
void tupleDemo() {
    auto t = std::make_tuple(1, "hello", 3.14);
    int x = std::get<0>(t);
    std::tie(x, std::ignore, std::ignore) = t;  // Unpack with ignore
}

// 28. Function wrapper & bind
int add_ints(int a, int b) { return a + b; }
void functionDemo() {
    std::function<int(int, int)> func = add_ints;
    auto bound = std::bind(add_ints, 10, std::placeholders::_1); // Bind first arg
    int result = bound(5);  // Calls add_ints(10, 5)
}

// 29. Threading primitives
std::mutex mtx;
std::atomic<int> atomic_counter{0};

void threadDemo() {
    std::thread t1([]() {
        std::lock_guard<std::mutex> lock(mtx);  // RAII lock
        // Critical section
    });
    
    std::thread t2([]() {
        atomic_counter.fetch_add(1, std::memory_order_relaxed); // Atomic operation
    });
    
    t1.join();
    t2.join();
}

// 30. Async & Future
int compute() { return 42; }
void asyncDemo() {
    std::future<int> result = std::async(std::launch::async, compute);
    int value = result.get();  // Block until ready
    
    std::promise<int> prom;
    std::future<int> fut = prom.get_future();
    std::thread([&prom](){ prom.set_value(100); }).detach();
}

// 31. Condition variables
std::condition_variable cv;
bool ready = false;
void condVarDemo() {
    std::unique_lock<std::mutex> lock(mtx);
    cv.wait(lock, []{ return ready; });  // Wait with predicate
}

// 32. Chrono library
void chronoDemo() {
    auto start = std::chrono::high_resolution_clock::now();
    // ... work ...
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    
    std::this_thread::sleep_for(std::chrono::seconds(1));
}

// 33. Random number generation
void randomDemo() {
    std::random_device rd;
    std::mt19937 gen(rd());                           // Mersenne Twister engine
    std::uniform_int_distribution<> dis(1, 6);        // Dice roll
    int roll = dis(gen);
    
    std::normal_distribution<> normal(0.0, 1.0);      // Normal distribution
}

// 34. Regular expressions
void regexDemo() {
    std::regex pattern(R"(\d{3}-\d{3}-\d{4})");  // Phone number
    std::string phone = "123-456-7890";
    bool matches = std::regex_match(phone, pattern);
    
    std::smatch match;
    if (std::regex_search(phone, match, pattern)) {
        std::cout << "Found: " << match[0] << '\n';
    }
}

// 35. Type traits
template<typename T>
void typeTraitDemo() {
    static_assert(std::is_pod<T>::value, "Must be POD");
    using NoCV = typename std::remove_cv<T>::type;
}

// 36. Numeric conversions
void conversionDemo() {
    int x = std::stoi("123");
    double d = std::stod("3.14");
    std::string s = std::to_string(42);
}

// 37. Exception handling utilities
void exceptionDemo() {
    try {
        throw std::runtime_error("Error!");
    } catch(...) {
        std::exception_ptr eptr = std::current_exception();
        try {
            if (eptr) std::rethrow_exception(eptr);
        } catch(const std::exception& e) {
            std::cout << e.what();
        }
    }
}

// 38. Initializer list
class Container {
    std::vector<int> data;
public:
    Container(std::initializer_list<int> init) : data(init) {}
};

// 39. Memory model guarantees - thread-safe static init
class Singleton {
    static Singleton& instance() {
        static Singleton inst;  // Thread-safe since C++11
        return inst;
    }
};

int main() {
    // Type deduction
    auto x = deduceTypes();
    
    // Constexpr compile-time computation
    constexpr int fact5 = factorial(5);  // Computed at compile-time
    
    // User-defined literals
    auto size = 10_KB;
    
    // Range-based for
    IntVec vec{1, 2, 3, 4, 5};
    for (auto val : vec) std::cout << val << " ";
    
    // Lambda
    auto square = [](int n) { return n * n; };
    std::cout << square(5) << '\n';
    
    // Move semantics
    Buffer buf1(100);
    Buffer buf2(std::move(buf1));  // Transfer ownership, not copy
    
    // Smart pointers
    smartPointerDemo();
    
    // Multithreading
    threadDemo();
    
    // Variadic templates
    print("Values:", 42, 3.14, "hello");
    
    // Nullptr
    int* ptr = nullptr;
    
    // Enum class
    Color c = Color::Red;
    
    return 0;
}
```

### Feature Coverage Summary

**Core Language**: auto, decltype, nullptr, rvalue references, move semantics, lambda expressions, constexpr, static_assert, long long, char16_t/char32_t, type aliases (using), enum class, uniform initialization, range-for, variadic templates, noexcept, override, final, defaulted/deleted functions, delegating/inheriting constructors, raw strings, user-defined literals, alignas/alignof, thread_local, attributes, trailing return type, NSDMI

**Standard Library**: unique_ptr, shared_ptr, weak_ptr, array, forward_list, unordered_map/set, tuple, function, bind, thread, mutex, lock_guard, atomic, future, promise, async, condition_variable, chrono, random, regex, type_traits, initializer_list, exception_ptr, numeric conversions

**Reference**: All features verified against [C++11 on cppreference.com](https://en.cppreference.com/w/cpp/11)
