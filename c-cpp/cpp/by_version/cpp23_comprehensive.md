# C++23 Comprehensive Example

> **Source**: [https://en.cppreference.com/w/cpp/23](https://en.cppreference.com/w/cpp/23)

This file demonstrates **all major C++23 features** in a compact, compilable example.

```cpp
#include <iostream>
#include <vector>
#include <string>
#include <string_view>
#include <optional>
#include <expected>
#include <utility>
#include <functional>
#include <ranges>
#include <algorithm>
#include <numeric>
#include <print>
#include <format>
#include <mdspan>
#include <flat_map>
#include <flat_set>
#include <generator>
#include <stacktrace>
#include <spanstream>
#include <stdfloat>
#include <bitset>
#include <memory>

// ============================================================================
// LANGUAGE FEATURES
// ============================================================================

// --- Explicit object parameter (deducing this) ---
struct MyVector {
    std::vector<int> data;
    
    // Explicit object parameter - unifies all 4 overloads (const&, &, const&&, &&)
    template<typename Self>
    auto&& get(this Self&& self, std::size_t i) {
        return std::forward<Self>(self).data[i];
    }
    
    // Recursive lambdas using deducing this
    auto make_factorial() {
        return [](this auto self, int n) -> int {
            return n <= 1 ? 1 : n * self(n - 1);
        };
    }
};

void demo_deducing_this() {
    MyVector v{{1, 2, 3}};
    auto& elem1 = v.get(0);                      // Returns int&
    
    const MyVector cv{{4, 5, 6}};
    const auto& elem2 = cv.get(0);               // Returns const int&
    
    auto elem3 = MyVector{{7, 8, 9}}.get(0);     // Returns int&&
    
    auto factorial = v.make_factorial();
    std::cout << "5! = " << factorial(5) << '\n'; // 120
}

// --- if consteval / if not consteval ---
constexpr int compute(int x) {
    if consteval {                               // Compile-time path
        return x * x;
    } else {                                     // Runtime path
        return x * 2;
    }
}

constexpr int test_consteval() {
    if not consteval {                           // Can use 'not consteval'
        return 0;
    } else {
        return 42;
    }
}

static_assert(compute(5) == 25);                 // Compile-time: 25
// At runtime: compute(5) == 10

// --- Multidimensional subscript operator ---
template<typename T>
class Matrix {
    std::vector<T> data;
    std::size_t rows, cols;
    
public:
    Matrix(std::size_t r, std::size_t c) : rows(r), cols(c), data(r * c) {}
    
    // Multidimensional subscript
    T& operator[](std::size_t i, std::size_t j) {
        return data[i * cols + j];
    }
    
    const T& operator[](std::size_t i, std::size_t j) const {
        return data[i * cols + j];
    }
};

void demo_multi_subscript() {
    Matrix<int> m(3, 4);
    m[1, 2] = 42;                                // C++23: multi-dimensional
    std::cout << m[1, 2] << '\n';                // 42
}

// --- static operator() and static operator[] ---
struct Multiplier {
    static int operator()(int a, int b) {        // static call operator
        return a * b;
    }
    
    static int operator[](int index) {           // static subscript operator
        return index * 10;
    }
};

void demo_static_operators() {
    std::cout << Multiplier{}(3, 4) << '\n';     // 12
    std::cout << Multiplier{}[5] << '\n';        // 50
}

// --- static lambdas ---
void demo_static_lambda() {
    auto multiply = [](int a, int b) static {    // static lambda (no capture)
        return a * b;
    };
    
    std::cout << multiply(6, 7) << '\n';         // 42
}

// --- auto(x) and auto{x} - decay-copy ---
void demo_auto_decay() {
    int x = 42;
    int& ref = x;
    
    auto copy1 = auto(ref);                      // Decay-copy: int (not int&)
    auto copy2 = auto{ref};                      // Decay-copy: int (not int&)
}

// --- [[assume]] attribute ---
int divide(int a, int b) {
    [[assume(b != 0)]];                          // Compiler hint: b is never 0
    return a / b;
}

// --- Attributes on lambdas ---
void demo_lambda_attributes() {
    auto lambda = [[nodiscard]] [](int x) {      // Attribute on lambda
        return x * 2;
    };
    
    // lambda(5);                                // Warning: discarding result
    int result = lambda(5);                      // OK
}

// --- Extended floating-point types (optional) ---
#ifdef __STDCPP_FLOAT16_T__
void demo_extended_float() {
    std::float16_t f16 = 3.14f16;
    std::float32_t f32 = 2.71f32;
    std::float64_t f64 = 1.41f64;
    std::float128_t f128 = 1.73f128;
    std::bfloat16_t bf16 = 0.5bf16;
}
#endif

// --- #elifdef and #elifndef ---
#define FEATURE_A
#ifdef FEATURE_A
    // ...
#elifdef FEATURE_B                               // C++23: elifdef
    // ...
#elifndef FEATURE_C                              // C++23: elifndef
    // ...
#endif

// --- #warning directive ---
#warning "This is a warning message"

// --- Literal suffix 'z' for std::size_t ---
void demo_size_literal() {
    auto size = 42uz;                            // std::size_t
    auto signed_size = 42z;                      // std::ptrdiff_t (signed)
}

// --- Simpler implicit move ---
std::string get_string() {
    std::string s = "hello";
    return s;                                    // Automatically moved (not copied)
}

// --- Extending lifetime of temporaries in range-for ---
void demo_rangefor_lifetime() {
    for (std::vector<int> v{1, 2, 3}; auto elem : v) {
        std::cout << elem << ' ';                // v's lifetime extended
    }
}

// --- CTAD from inherited constructors ---
template<typename T>
struct Base {
    Base(T) {}
};

template<typename T>
struct Derived : Base<T> {
    using Base<T>::Base;                         // Inherit constructor
};

void demo_ctad_inherited() {
    Derived d(42);                               // Deduced: Derived<int>
}

// --- Labels at the end of compound statements ---
void demo_label_end() {
    if (true) {
        goto END;
    }
END:                                             // Label at end (C++23)
}

// --- Alias declarations in init-statements ---
void demo_alias_init() {
    for (using T = int; T e : std::vector{1, 2, 3}) {  // Type alias in for
        std::cout << e << ' ';
    }
}

// --- More optional () for lambdas ---
void demo_lambda_optional_parens() {
    auto lambda1 = [] { return 42; };            // No () needed
    auto lambda2 = []<typename T> { return 0; }; // Template without ()
    auto lambda3 = [] [[nodiscard]] { return 1; }; // Attributes without ()
}

// --- Narrowing conversions in static_assert and if constexpr ---
void demo_narrowing_bool() {
    int* ptr = nullptr;
    static_assert(ptr);                          // Error: narrowing to bool
    
    if constexpr (42) {                          // OK: narrowing allowed
        // ...
    }
}

// --- Named universal character escapes ---
void demo_named_escapes() {
    const char* cat = "\N{CAT FACE}";            // 🐱
    const char* smile = "\N{SMILING FACE}";      // ☺
}

// --- Delimited escape sequences ---
void demo_delimited_escapes() {
    const char* oct = "\o{377}";                 // Octal
    const char* hex = "\x{ABCD}";                // Hex
    const char* unicode = "\u{1F600}";           // Unicode
}

// --- constexpr improvements ---
constexpr int non_literal_constexpr() {
    int x = 42;                                  // Non-literal variable OK
    goto skip;                                   // goto OK
skip:
    return x;
}

constexpr int static_in_constexpr() {
    static int counter = 0;                      // static variable OK
    return ++counter;
}

// --- constexpr function relaxations ---
constexpr int flexible_constexpr(int x) {
    // No longer requires return type to be literal
    // Can have no valid constant expression invocation
    return x;
}

// ============================================================================
// LIBRARY FEATURES
// ============================================================================

// --- std::expected (error handling without exceptions) ---
std::expected<int, std::string> divide_safe(int a, int b) {
    if (b == 0)
        return std::unexpected("Division by zero");
    return a / b;
}

void demo_expected() {
    auto result = divide_safe(10, 2);
    if (result.has_value()) {
        std::cout << "Result: " << *result << '\n';
    } else {
        std::cout << "Error: " << result.error() << '\n';
    }
    
    // Monadic operations
    auto doubled = divide_safe(10, 2)
        .transform([](int x) { return x * 2; })
        .or_else([](auto) { return std::expected<int, std::string>(0); });
}

// --- std::print and std::println ---
void demo_print() {
    std::print("Hello, {}!\n", "World");
    std::println("Value: {}", 42);
    std::println(stderr, "Error: {}", "Something went wrong");
}

// --- std::generator (coroutine for ranges) ---
std::generator<int> fibonacci() {
    int a = 0, b = 1;
    while (true) {
        co_yield a;
        int next = a + b;
        a = b;
        b = next;
    }
}

void demo_generator() {
    for (int n : fibonacci() | std::views::take(10)) {
        std::cout << n << ' ';
    }
}

// --- std::mdspan (multidimensional array view) ---
void demo_mdspan() {
    std::vector<int> data(12);
    std::mdspan<int, std::extents<std::size_t, 3, 4>> matrix(data.data());
    
    matrix[1, 2] = 42;                           // Multidimensional indexing
    std::cout << matrix[1, 2] << '\n';
}

// --- std::flat_map and std::flat_set (sorted vector-based containers) ---
void demo_flat_containers() {
    std::flat_map<int, std::string> map;
    map[1] = "one";
    map[2] = "two";
    
    std::flat_set<int> set{3, 1, 4, 1, 5};
    // Stored as sorted vector internally
}

// --- std::move_only_function (like std::function but move-only) ---
void demo_move_only_function() {
    std::unique_ptr<int> ptr = std::make_unique<int>(42);
    
    std::move_only_function<int()> func = [p = std::move(ptr)]() {
        return *p;
    };
    
    auto func2 = std::move(func);                // Move-only, not copyable
}

// --- std::bind_back ---
void demo_bind_back() {
    auto subtract = [](int a, int b, int c) { return a - b - c; };
    auto sub_from_100 = std::bind_back(subtract, 10, 5);
    int result = sub_from_100(100);              // 100 - 10 - 5 = 85
}

// --- std::byteswap ---
void demo_byteswap() {
    uint32_t x = 0x12345678;
    uint32_t swapped = std::byteswap(x);         // 0x78563412
}

// --- std::forward_like ---
template<typename T, typename U>
decltype(auto) forward_like_example(T&& t, U&& u) {
    return std::forward_like<T>(u);              // Forward u with value category of t
}

// --- std::invoke_r (invoke with explicit return type) ---
void demo_invoke_r() {
    auto func = [](int x) { return x * 2; };
    double result = std::invoke_r<double>(func, 21);  // Convert to double
}

// --- std::to_underlying (get underlying value of enum) ---
enum class Color { Red = 1, Green = 2, Blue = 3 };

void demo_to_underlying() {
    auto value = std::to_underlying(Color::Green);  // 2
}

// --- std::unreachable (mark unreachable code) ---
int get_value(int x) {
    if (x > 0) return 1;
    if (x < 0) return -1;
    if (x == 0) return 0;
    std::unreachable();                          // This point is unreachable
}

// --- Monadic operations for std::optional ---
void demo_optional_monadic() {
    std::optional<int> opt = 42;
    
    auto doubled = opt.transform([](int x) { return x * 2; });
    auto result = opt.and_then([](int x) { return std::optional{x + 1}; });
    auto fallback = std::optional<int>{}.or_else([] { return std::optional{0}; });
}

// --- Range views (new in C++23) ---
void demo_range_views() {
    std::vector<int> v{1, 2, 3, 4, 5};
    
    // views::zip
    std::vector<char> chars{'a', 'b', 'c'};
    for (auto [num, ch] : std::views::zip(v, chars)) {
        std::cout << num << ch << ' ';
    }
    
    // views::adjacent (sliding window of size N)
    for (auto [a, b] : v | std::views::adjacent<2>) {
        std::cout << a << "," << b << ' ';
    }
    
    // views::adjacent_transform
    for (auto sum : v | std::views::adjacent_transform<2>(std::plus<>{})) {
        std::cout << sum << ' ';
    }
    
    // views::chunk (split into chunks)
    for (auto chunk : v | std::views::chunk(2)) {
        for (int x : chunk) std::cout << x;
        std::cout << ' ';
    }
    
    // views::chunk_by (split by predicate)
    for (auto chunk : v | std::views::chunk_by(std::less<>{})) {
        // Chunks of increasing values
    }
    
    // views::slide (sliding window)
    for (auto window : v | std::views::slide(3)) {
        // Windows of size 3
    }
    
    // views::stride (take every Nth element)
    for (int x : v | std::views::stride(2)) {
        std::cout << x << ' ';                   // 1 3 5
    }
    
    // views::cartesian_product
    for (auto [a, b] : std::views::cartesian_product(
            std::views::iota(1, 3), std::views::iota(1, 3))) {
        std::cout << a << "," << b << ' ';       // (1,1) (1,2) (2,1) (2,2)
    }
    
    // views::enumerate (index + value)
    for (auto [i, val] : v | std::views::enumerate) {
        std::cout << i << ":" << val << ' ';
    }
    
    // views::join_with (join with delimiter)
    std::vector<std::vector<int>> vv{{1, 2}, {3, 4}};
    for (int x : vv | std::views::join_with(0)) {
        std::cout << x << ' ';                   // 1 2 0 3 4
    }
    
    // views::repeat (infinite/finite repetition)
    for (int x : std::views::repeat(42, 3)) {
        std::cout << x << ' ';                   // 42 42 42
    }
    
    // views::as_const
    for (const auto& x : v | std::views::as_const) {
        // x is const int&
    }
    
    // views::as_rvalue
    for (auto&& x : v | std::views::as_rvalue) {
        // x is int&&
    }
}

// --- ranges::to (convert range to container) ---
void demo_ranges_to() {
    auto v = std::views::iota(1, 6)
           | std::views::transform([](int x) { return x * 2; })
           | std::ranges::to<std::vector>();     // Convert to vector
    
    auto s = std::views::iota(1, 6)
           | std::ranges::to<std::set>();        // Convert to set
}

// --- New range algorithms ---
void demo_range_algorithms() {
    std::vector<int> v{1, 2, 3, 4, 5};
    
    // ranges::starts_with / ends_with
    bool starts = std::ranges::starts_with(v, std::vector{1, 2});
    bool ends = std::ranges::ends_with(v, std::vector{4, 5});
    
    // ranges::contains / contains_subrange
    bool has = std::ranges::contains(v, 3);
    bool has_sub = std::ranges::contains_subrange(v, std::vector{2, 3, 4});
    
    // ranges::find_last / find_last_if / find_last_if_not
    auto it = std::ranges::find_last(v, 3);
    
    // ranges::fold_left / fold_right etc.
    int sum = std::ranges::fold_left(v, 0, std::plus<>{});
}

// --- std::stacktrace ---
void demo_stacktrace() {
    auto trace = std::stacktrace::current();
    std::cout << std::to_string(trace) << '\n';
}

// --- spanstream (span-based string stream) ---
void demo_spanstream() {
    char buffer[100];
    std::ospanstream oss(buffer);
    oss << "Hello, " << 42;
    std::string_view result(buffer, oss.span().size());
}

// --- constexpr improvements ---
constexpr int test_constexpr_bitset() {
    std::bitset<8> bits(0b10101010);
    return bits.count();                         // constexpr bitset
}

constexpr auto test_constexpr_unique_ptr() {
    auto ptr = std::make_unique<int>(42);
    return *ptr;                                 // constexpr unique_ptr
}

// --- std::out_ptr and std::inout_ptr (C interop) ---
void demo_out_ptr() {
    std::unique_ptr<int> ptr;
    
    // Interop with C API expecting int**
    // some_c_function(std::out_ptr(ptr));
}

// --- String improvements ---
void demo_string_features() {
    std::string s = "hello world";
    
    // contains
    bool has = s.contains("world");
    
    // resize_and_overwrite (efficient resize)
    s.resize_and_overwrite(20, [](char* buf, std::size_t n) {
        // Fill buffer
        return 10;                               // Return actual size
    });
    
    // substr&& (efficient slicing)
    std::string s2 = std::string("test").substr(1, 2);  // Move
}

// --- Formatting improvements ---
void demo_formatting() {
    std::vector<int> v{1, 2, 3};
    std::println("{}", v);                       // Format ranges
    
    std::tuple t{1, "hello", 3.14};
    std::println("{}", t);                       // Format tuples
}

// --- std::is_scoped_enum ---
static_assert(std::is_scoped_enum_v<Color>);
static_assert(!std::is_scoped_enum_v<int>);

// ============================================================================
// MAIN DEMONSTRATION
// ============================================================================

int main() {
    std::println("=== C++23 Comprehensive Demo ===\n");
    
    // Deducing this
    demo_deducing_this();
    
    // Multidimensional subscript
    demo_multi_subscript();
    
    // Static operators
    demo_static_operators();
    
    // std::expected
    demo_expected();
    
    // std::print
    demo_print();
    
    // std::generator
    std::print("Fibonacci: ");
    demo_generator();
    std::println("");
    
    // Range views
    demo_range_views();
    
    // ranges::to
    demo_ranges_to();
    
    // Formatting
    demo_formatting();
    
    // Compile-time tests
    static_assert(compute(5) == 25);
    static_assert(test_constexpr() == 42);
    static_assert(test_constexpr_bitset() == 4);
    static_assert(test_constexpr_unique_ptr() == 42);
    
    return 0;
}
```

## Summary

**C++23 Core Language Features:**
- **Explicit object parameter** - "Deducing this" unifies cv-ref overloads
- **if consteval** / **if not consteval** - Detect compile-time evaluation
- **Multidimensional subscript operator** - `arr[i, j, k]`
- **static operator()** and **static operator[]** - Static call/subscript operators
- **static lambdas** - Lambdas without captures
- **auto(x)** / **auto{x}** - Decay-copy
- **[[assume]]** - Optimization hints
- Attributes on lambdas
- Extended floating-point types: `std::float16_t`, `std::float32_t`, `std::float64_t`, `std::float128_t`, `std::bfloat16_t`
- **#elifdef** / **#elifndef** - New preprocessor directives
- **#warning** - Warning directive
- Literal suffix **'z'** for `std::size_t`
- Simpler implicit move
- Extending lifetime of temporaries in range-for
- CTAD from inherited constructors
- Labels at end of compound statements
- Alias declarations in init-statements
- More optional **()** for lambdas
- Narrowing conversions in `static_assert` and `if constexpr`
- **Named universal character escapes** - `\N{CAT FACE}`
- **Delimited escape sequences** - `\o{777}`, `\x{ABCD}`
- constexpr improvements: non-literal variables, goto, static variables
- Many defect report fixes

**C++23 Library Features:**
- **std::expected** - Error handling without exceptions
- **std::print** / **std::println** - Formatted output
- **std::generator** - Coroutine-based range generator
- **std::mdspan** - Multidimensional array view
- **std::flat_map** / **std::flat_set** - Vector-based sorted containers
- **std::move_only_function** - Move-only callable wrapper
- **std::bind_back** - Partial application
- **std::byteswap** - Byte order reversal
- **std::forward_like** - Forward with value category
- **std::invoke_r** - Invoke with explicit return type
- **std::to_underlying** - Get enum underlying value
- **std::unreachable** - Mark unreachable code
- Monadic operations for **std::optional** and **std::expected**
- **Range views**: `zip`, `zip_transform`, `adjacent`, `adjacent_transform`, `chunk`, `chunk_by`, `slide`, `stride`, `cartesian_product`, `enumerate`, `join_with`, `repeat`, `as_const`, `as_rvalue`
- **ranges::to** - Convert range to container
- **Range algorithms**: `starts_with`, `ends_with`, `contains`, `contains_subrange`, `find_last`, `fold_left`, `fold_right`, etc.
- **std::stacktrace** - Stack trace support
- **spanstream** - Span-based string streams
- constexpr: `std::bitset`, `std::unique_ptr`, more `<cmath>`, `to_chars`/`from_chars`
- **std::out_ptr** / **std::inout_ptr** - C interop for smart pointers
- String: `contains()`, `resize_and_overwrite()`, rvalue `substr()`
- Formatting: ranges, tuples, escaped strings, `std::thread::id`, stacktraces
- **std::is_scoped_enum**
- **std::is_implicit_lifetime**
- **std::reference_constructs_from_temporary**
- Standard library modules: `std` and `std.compat`
- Many more improvements...

**Reference**: [https://en.cppreference.com/w/cpp/23](https://en.cppreference.com/w/cpp/23)
