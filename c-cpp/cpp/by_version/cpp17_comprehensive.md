# C++17 Comprehensive Example

> **Source**: [https://en.cppreference.com/w/cpp/17](https://en.cppreference.com/w/cpp/17)

This file demonstrates **all major C++17 features** in a compact, compilable example.

```cpp
#include <iostream>
#include <string>
#include <string_view>
#include <optional>
#include <variant>
#include <any>
#include <tuple>
#include <map>
#include <vector>
#include <algorithm>
#include <numeric>
#include <filesystem>
#include <execution>
#include <memory>
#include <shared_mutex>

// ============================================================================
// LANGUAGE FEATURES
// ============================================================================

// --- Structured bindings ---
void demo_structured_bindings() {
    std::map<std::string, int> m{{"Alice", 25}, {"Bob", 30}};
    
    // Decompose pair from map
    for (const auto& [name, age] : m) {
        std::cout << name << " is " << age << '\n';
    }
    
    // Decompose tuple
    auto [a, b, c] = std::tuple{42, 3.14, "hello"};
    
    // Decompose array
    int arr[3] = {1, 2, 3};
    auto [x, y, z] = arr;
    
    // Decompose struct
    struct Point { int x, y; };
    Point p{10, 20};
    auto [px, py] = p;
}

// --- if constexpr (compile-time branching) ---
template<typename T>
auto process(T value) {
    if constexpr (std::is_integral_v<T>) {
        return value * 2;        // Only compiled for integers
    } else if constexpr (std::is_floating_point_v<T>) {
        return value * 1.5;      // Only compiled for floats
    } else {
        return value;            // Only compiled for others
    }
}

// --- Fold expressions (parameter pack expansion) ---
template<typename... Args>
auto sum(Args... args) {
    return (args + ...);         // Unary right fold: (1 + (2 + 3))
}

template<typename... Args>
void print(Args&&... args) {
    (std::cout << ... << args) << '\n';  // Binary left fold
}

template<typename... Args>
bool all(Args... args) {
    return (... && args);        // Logical AND fold
}

// --- Class Template Argument Deduction (CTAD) ---
void demo_ctad() {
    std::pair p{42, 3.14};           // Deduced: pair<int, double>
    std::vector v{1, 2, 3, 4, 5};    // Deduced: vector<int>
    std::tuple t{1, 2.5, "hello"};   // Deduced: tuple<int, double, const char*>
    
    // User-defined deduction guides
    std::lock_guard lock{std::mutex{}};  // No <std::mutex> needed
}

// --- inline variables ---
inline int global_counter = 0;       // Can be in header, one definition

struct Config {
    inline static std::string name = "default";  // Inline static member
};

// --- constexpr lambda ---
void demo_constexpr_lambda() {
    constexpr auto square = [](int n) { return n * n; };
    static_assert(square(5) == 25);  // Evaluated at compile time
    
    int arr[square(3)];              // Array size from constexpr lambda
}

// --- Lambda capture of *this ---
struct Counter {
    int value = 42;
    
    auto get_lambda() {
        return [*this]() {           // Captures copy of entire object
            return value;
        };
    }
};

// --- Init-statement in if/switch ---
void demo_if_init() {
    std::map<int, std::string> m{{1, "one"}};
    
    // Variable declared in if statement
    if (auto it = m.find(1); it != m.end()) {
        std::cout << it->second << '\n';
    }
    // 'it' is out of scope here
    
    // In switch
    switch (auto val = 42; val) {
        case 42: std::cout << "Matched\n"; break;
    }
}

// --- Nested namespace definition ---
namespace A::B::C {
    int value = 42;
}

// --- constexpr if improvements ---
template<typename T>
constexpr auto get_value(T t) {
    if constexpr (std::is_pointer_v<T>) {
        return *t;               // Different return types!
    } else {
        return t;
    }
}

// --- noexcept as part of type system ---
void f1() noexcept {}
void f2() {}

void demo_noexcept_type() {
    using FuncType1 = void(*)() noexcept;
    using FuncType2 = void(*)();
    
    FuncType1 p1 = f1;           // OK
    // FuncType2 p2 = f1;        // Error in C++17: different types
}

// --- u8 character literals ---
char c = u8'A';                  // UTF-8 character literal

// --- Hexadecimal floating literals ---
double pi_hex = 0x1.921fb54442d18p+1;  // π in hexadecimal

// --- [[fallthrough]], [[nodiscard]], [[maybe_unused]] ---
[[nodiscard]] int compute() { return 42; }

void demo_attributes() {
    [[maybe_unused]] int unused_var = 5;
    
    int x = 1;
    switch (x) {
        case 1:
            std::cout << "One\n";
            [[fallthrough]];     // Explicit fallthrough
        case 2:
            std::cout << "One or Two\n";
            break;
    }
    
    // compute();               // Warning: ignoring [[nodiscard]]
    int result = compute();     // OK
}

// --- Using declaration with multiple names ---
namespace ns1 { int a = 1, b = 2; }
namespace ns2 {
    using ns1::a, ns1::b;        // Declare multiple names at once
}

// --- Attribute namespaces without repetition ---
[[using gnu: const, always_inline, hot]]  // No need to repeat 'gnu::'
void optimized_func() {}

// --- __has_include preprocessor ---
#if __has_include(<optional>)
    #include <optional>
    constexpr bool has_optional = true;
#else
    constexpr bool has_optional = false;
#endif

// --- auto template parameters ---
template<auto Value>
struct ValueHolder {
    static constexpr auto value = Value;
};

void demo_auto_template() {
    ValueHolder<42> int_holder;      // auto deduced as int
    ValueHolder<'x'> char_holder;    // auto deduced as char
}

// --- Guaranteed copy elision & temporary materialization ---
struct NoCopy {
    NoCopy() = default;
    NoCopy(const NoCopy&) = delete;  // Not copyable
};

NoCopy factory() { return NoCopy{}; }  // OK in C++17 (guaranteed elision)

// --- Stricter evaluation order ---
void demo_eval_order() {
    std::string s = "abc";
    // In C++17, evaluation order is guaranteed:
    // s[0] is evaluated before s = "xyz"
    // (Previously undefined behavior)
}

// --- Direct-list-initialization of enums ---
enum class Color { Red, Green, Blue };
void demo_enum_init() {
    Color c{1};                  // Direct-list-init (C++17)
}

// --- Dynamic memory allocation for over-aligned data ---
struct alignas(128) OverAligned {
    char data[128];
};

void demo_aligned_new() {
    auto p = new OverAligned;    // Uses aligned allocation
    delete p;
}

// ============================================================================
// LIBRARY FEATURES
// ============================================================================

// --- std::optional (may or may not contain a value) ---
std::optional<int> find_value(bool found) {
    if (found) return 42;
    return std::nullopt;         // Empty optional
}

void demo_optional() {
    auto opt = find_value(true);
    if (opt) {
        std::cout << "Value: " << *opt << '\n';
    }
    
    // value_or provides default
    int val = find_value(false).value_or(0);
}

// --- std::variant (type-safe union) ---
void demo_variant() {
    std::variant<int, double, std::string> v;
    
    v = 42;                      // Holds int
    v = 3.14;                    // Now holds double
    v = "hello";                 // Now holds string
    
    // Access via visit
    std::visit([](auto&& arg) {
        std::cout << arg << '\n';
    }, v);
    
    // Or via get
    if (auto* s = std::get_if<std::string>(&v)) {
        std::cout << *s << '\n';
    }
}

// --- std::any (type-safe container for any value) ---
void demo_any() {
    std::any a = 42;
    a = 3.14;
    a = std::string("hello");
    
    if (a.type() == typeid(std::string)) {
        std::cout << std::any_cast<std::string>(a) << '\n';
    }
}

// --- std::string_view (non-owning string reference) ---
void process_string(std::string_view sv) {  // No copy!
    std::cout << sv << '\n';
}

void demo_string_view() {
    std::string s = "hello";
    process_string(s);           // No copy
    process_string("world");     // No temporary string
}

// --- std::apply (call function with tuple arguments) ---
void demo_apply() {
    auto add = [](int a, int b, int c) { return a + b + c; };
    auto args = std::make_tuple(1, 2, 3);
    int result = std::apply(add, args);  // Calls add(1, 2, 3)
}

// --- std::make_from_tuple ---
struct MyClass {
    MyClass(int a, double b, std::string c) {}
};

void demo_make_from_tuple() {
    auto args = std::make_tuple(42, 3.14, "hello");
    MyClass obj = std::make_from_tuple<MyClass>(args);
}

// --- std::invoke ---
void demo_invoke() {
    auto lambda = [](int x) { return x * 2; };
    int result = std::invoke(lambda, 21);  // 42
    
    // Works with member functions
    struct S { int double_it(int x) { return x * 2; } };
    S s;
    result = std::invoke(&S::double_it, s, 21);
}

// --- std::clamp (constrain value to range) ---
void demo_clamp() {
    int value = 15;
    int clamped = std::clamp(value, 0, 10);  // 10 (clamped to max)
}

// --- std::gcd, std::lcm (greatest common divisor, least common multiple) ---
void demo_gcd_lcm() {
    int g = std::gcd(12, 18);    // 6
    int l = std::lcm(12, 18);    // 36
}

// --- Parallel algorithms ---
void demo_parallel() {
    std::vector<int> v(1000000);
    std::iota(v.begin(), v.end(), 0);
    
    // Sequential
    std::sort(std::execution::seq, v.begin(), v.end());
    
    // Parallel
    std::sort(std::execution::par, v.begin(), v.end());
    
    // Parallel + vectorized
    std::sort(std::execution::par_unseq, v.begin(), v.end());
}

// --- std::reduce (parallel-friendly accumulation) ---
void demo_reduce() {
    std::vector<int> v{1, 2, 3, 4, 5};
    int sum = std::reduce(v.begin(), v.end());  // 15
    
    // With initial value and operation
    int product = std::reduce(v.begin(), v.end(), 1, std::multiplies<>());
}

// --- std::scoped_lock (multiple mutex locking) ---
void demo_scoped_lock() {
    std::mutex m1, m2;
    std::scoped_lock lock{m1, m2};  // Locks both, prevents deadlock
    // Both automatically unlocked when lock goes out of scope
}

// --- std::shared_mutex (reader-writer lock) ---
void demo_shared_mutex() {
    std::shared_mutex mtx;
    
    // Multiple readers can hold lock simultaneously
    {
        std::shared_lock lock{mtx};  // Read lock
        // Read data...
    }
    
    // Writer has exclusive access
    {
        std::unique_lock lock{mtx};  // Write lock
        // Modify data...
    }
}

// --- std::filesystem ---
void demo_filesystem() {
    namespace fs = std::filesystem;
    
    // Create directory
    fs::create_directory("test_dir");
    
    // Iterate directory
    for (const auto& entry : fs::directory_iterator(".")) {
        std::cout << entry.path() << '\n';
    }
    
    // Path operations
    fs::path p = "dir/file.txt";
    std::cout << "Parent: " << p.parent_path() << '\n';
    std::cout << "Filename: " << p.filename() << '\n';
    std::cout << "Extension: " << p.extension() << '\n';
    
    // File info
    if (fs::exists(p)) {
        auto size = fs::file_size(p);
        auto time = fs::last_write_time(p);
    }
    
    // Remove
    fs::remove_all("test_dir");
}

// --- std::byte ---
void demo_byte() {
    std::byte b{42};
    b |= std::byte{0x80};
    b &= std::byte{0xFF};
    int val = std::to_integer<int>(b);
}

// --- std::as_const ---
void demo_as_const() {
    std::vector<int> v{1, 2, 3};
    // auto& cv = const_cast<const std::vector<int>&>(v);  // Old way
    auto& cv = std::as_const(v);                            // C++17 way
}

// --- std::not_fn (logical negation of callable) ---
void demo_not_fn() {
    auto is_odd = [](int n) { return n % 2 == 1; };
    auto is_even = std::not_fn(is_odd);
    
    std::vector<int> v{1, 2, 3, 4, 5};
    auto it = std::find_if(v.begin(), v.end(), is_even);  // Finds 2
}

// --- Map/set operations ---
void demo_map_operations() {
    std::map<int, std::string> m;
    
    // try_emplace: doesn't overwrite if key exists
    m.try_emplace(1, "one");
    m.try_emplace(1, "ONE");     // No effect
    
    // insert_or_assign: overwrites if exists
    m.insert_or_assign(2, "two");
    m.insert_or_assign(2, "TWO");  // Overwrites
    
    // extract: remove and get node (for moving between containers)
    auto node = m.extract(1);
    std::map<int, std::string> m2;
    m2.insert(std::move(node));
    
    // merge: merge two containers
    m2.merge(m);                 // Moves elements from m to m2
}

// --- Compile-time type traits ---
void demo_type_traits() {
    // _v variable templates (shorter than ::value)
    static_assert(std::is_integral_v<int>);
    static_assert(!std::is_floating_point_v<int>);
    
    // Logical operations
    static_assert(std::conjunction_v<std::is_integral<int>, std::is_signed<int>>);
    static_assert(std::disjunction_v<std::is_integral<int>, std::is_floating_point<int>>);
    static_assert(std::negation_v<std::is_const<int>>);
    
    // New traits
    static_assert(std::is_swappable_v<int>);
    static_assert(std::is_invocable_v<decltype(compute)>);
    
    struct Agg { int a, b; };
    static_assert(std::is_aggregate_v<Agg>);
}

// --- std::size, std::empty, std::data (non-member functions) ---
void demo_container_helpers() {
    int arr[] = {1, 2, 3};
    auto sz = std::size(arr);    // 3
    bool empty = std::empty(arr); // false
    int* ptr = std::data(arr);   // Pointer to first element
    
    std::vector<int> v{1, 2, 3};
    sz = std::size(v);           // Works with containers too
}

// --- Mathematical special functions ---
void demo_special_math() {
    #if __cpp_lib_math_special_functions
    double result;
    
    // Bessel functions
    result = std::cyl_bessel_j(0, 1.0);
    
    // Legendre polynomials
    result = std::legendre(2, 0.5);
    
    // Elliptic integrals
    result = std::ellint_1(0.5, 1.0);
    
    // And many more...
    #endif
}

// --- 3-argument std::hypot ---
void demo_hypot() {
    double dist = std::hypot(3.0, 4.0, 12.0);  // 13.0 (3D distance)
}

// --- std::sample (random sampling) ---
void demo_sample() {
    std::vector<int> population{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::vector<int> sample;
    
    std::sample(population.begin(), population.end(),
                std::back_inserter(sample), 5,
                std::mt19937{std::random_device{}()});
}

// --- Searchers ---
void demo_searchers() {
    std::string text = "hello world hello";
    std::string pattern = "world";
    
    auto searcher = std::default_searcher(pattern.begin(), pattern.end());
    auto it = std::search(text.begin(), text.end(), searcher);
    
    // Also: boyer_moore_searcher, boyer_moore_horspool_searcher
}

// ============================================================================
// MAIN DEMONSTRATION
// ============================================================================

int main() {
    std::cout << "=== C++17 Comprehensive Demo ===\n\n";
    
    // Language features
    demo_structured_bindings();
    std::cout << "sum(1,2,3,4,5) = " << sum(1,2,3,4,5) << '\n';
    print("Hello", " ", "World", " ", 2017);
    std::cout << "process(10) = " << process(10) << '\n';
    std::cout << "process(3.14) = " << process(3.14) << '\n';
    
    // Library features
    demo_optional();
    demo_variant();
    demo_any();
    demo_string_view();
    demo_clamp();
    std::cout << "gcd(12, 18) = " << std::gcd(12, 18) << '\n';
    std::cout << "lcm(12, 18) = " << std::lcm(12, 18) << '\n';
    
    demo_filesystem();
    
    return 0;
}
```

## Summary

**C++17 Core Language Features:**
- Structured bindings
- `if constexpr` (compile-time branching)
- Fold expressions
- Class Template Argument Deduction (CTAD)
- `inline` variables
- `constexpr` lambda
- Lambda capture of `*this`
- Init-statements in `if`/`switch`
- Nested namespace definition (`A::B::C`)
- `noexcept` part of type system
- u8 character literals
- Hexadecimal floating literals
- New attributes: `[[fallthrough]]`, `[[nodiscard]]`, `[[maybe_unused]]`
- `using` with multiple names
- Attribute namespaces
- `__has_include`
- `auto` template parameters
- Guaranteed copy elision
- Stricter evaluation order
- Direct-list-init of enums
- Over-aligned allocation

**C++17 Library Features:**
- `std::optional` (maybe-value)
- `std::variant` (type-safe union)
- `std::any` (type-safe any)
- `std::string_view` (non-owning string)
- `std::apply`
- `std::make_from_tuple`
- `std::invoke`
- `std::filesystem` (file/directory operations)
- `std::byte`
- `std::clamp`
- `std::gcd`, `std::lcm`
- Parallel algorithms (`std::execution::par`)
- `std::reduce`
- `std::scoped_lock`
- `std::shared_mutex`
- `std::as_const`
- `std::not_fn`
- Map/set: `try_emplace`, `insert_or_assign`, `extract`, `merge`
- Type trait variable templates (`_v`)
- Logical type traits: `conjunction`, `disjunction`, `negation`
- `std::is_swappable`, `std::is_invocable`, `std::is_aggregate`
- `std::size`, `std::empty`, `std::data`
- Mathematical special functions
- 3-argument `std::hypot`
- `std::sample`
- Searchers

**Reference**: [https://en.cppreference.com/w/cpp/17](https://en.cppreference.com/w/cpp/17)
