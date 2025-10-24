# C++20 Comprehensive Example

> **Source**: [https://en.cppreference.com/w/cpp/20](https://en.cppreference.com/w/cpp/20)

This file demonstrates **all major C++20 features** in a compact, compilable example.

```cpp
#include <iostream>
#include <vector>
#include <string>
#include <string_view>
#include <span>
#include <ranges>
#include <concepts>
#include <compare>
#include <coroutine>
#include <format>
#include <numbers>
#include <bit>
#include <source_location>
#include <version>
#include <syncstream>
#include <barrier>
#include <latch>
#include <semaphore>
#include <stop_token>
#include <algorithm>
#include <numeric>

// ============================================================================
// LANGUAGE FEATURES
// ============================================================================

// --- Concepts (constrain templates) ---
template<typename T>
concept Numeric = std::integral<T> || std::floating_point<T>;

template<Numeric T>
T add(T a, T b) {
    return a + b;
}

// Custom concept
template<typename T>
concept Printable = requires(T t) {
    std::cout << t;              // Must support <<
};

template<Printable T>
void print(const T& value) {
    std::cout << value << '\n';
}

// Concept with multiple requirements
template<typename T>
concept Container = requires(T t) {
    typename T::value_type;
    typename T::iterator;
    t.begin();
    t.end();
    t.size();
};

// --- Abbreviated function templates (auto parameters are concepts) ---
void process(auto value) {       // Same as: template<typename T> void process(T value)
    std::cout << value << '\n';
}

void sorted_only(std::ranges::random_access_range auto& range) {
    std::ranges::sort(range);
}

// --- Ranges ---
void demo_ranges() {
    std::vector<int> v{5, 2, 8, 1, 9};
    
    // Ranges algorithms
    std::ranges::sort(v);                        // Shorter than std::sort(v.begin(), v.end())
    
    // Range views (lazy, composable)
    auto even = v | std::views::filter([](int n) { return n % 2 == 0; })
                  | std::views::transform([](int n) { return n * 2; });
    
    for (int n : even) {
        std::cout << n << ' ';
    }
    
    // Take first 3 elements
    for (int n : v | std::views::take(3)) {
        std::cout << n << ' ';
    }
    
    // Reverse view
    for (int n : v | std::views::reverse) {
        std::cout << n << ' ';
    }
    
    // Generate infinite range
    for (int n : std::views::iota(1) | std::views::take(5)) {
        std::cout << n << ' ';                   // 1 2 3 4 5
    }
}

// --- Three-way comparison (spaceship operator <=> ---
struct Point {
    int x, y;
    
    auto operator<=>(const Point&) const = default;  // Generates all 6 comparisons
};

void demo_spaceship() {
    Point p1{1, 2}, p2{1, 3};
    
    bool b1 = p1 < p2;                           // true
    bool b2 = p1 <= p2;                          // true
    bool b3 = p1 == p2;                          // false
    bool b4 = p1 != p2;                          // true
    bool b5 = p1 > p2;                           // false
    bool b6 = p1 >= p2;                          // false
    
    // Get ordering category
    auto cmp = p1 <=> p2;
    if (cmp < 0) std::cout << "p1 < p2\n";
}

// Custom three-way comparison
struct Name {
    std::string first, last;
    
    std::strong_ordering operator<=>(const Name& other) const {
        if (auto cmp = last <=> other.last; cmp != 0)
            return cmp;
        return first <=> other.first;
    }
};

// --- Modules (no example - requires separate module files) ---
// import std;                   // Import standard library module
// export module mymodule;       // Define module

// --- Coroutines (simplified generator) ---
template<typename T>
struct Generator {
    struct promise_type {
        T current_value;
        
        auto initial_suspend() { return std::suspend_always{}; }
        auto final_suspend() noexcept { return std::suspend_always{}; }
        Generator get_return_object() {
            return Generator{std::coroutine_handle<promise_type>::from_promise(*this)};
        }
        void unhandled_exception() { std::terminate(); }
        auto yield_value(T value) {
            current_value = value;
            return std::suspend_always{};
        }
        void return_void() {}
    };
    
    std::coroutine_handle<promise_type> coro;
    
    Generator(std::coroutine_handle<promise_type> h) : coro(h) {}
    ~Generator() { if (coro) coro.destroy(); }
    
    bool next() {
        coro.resume();
        return !coro.done();
    }
    
    T value() { return coro.promise().current_value; }
};

Generator<int> fibonacci() {
    int a = 0, b = 1;
    while (true) {
        co_yield a;
        int next = a + b;
        a = b;
        b = next;
    }
}

void demo_coroutines() {
    auto gen = fibonacci();
    for (int i = 0; i < 10; ++i) {
        gen.next();
        std::cout << gen.value() << ' ';
    }
}

// --- Designated initializers ---
struct Config {
    int width = 640;
    int height = 480;
    std::string title = "Window";
};

void demo_designated_init() {
    Config cfg{
        .width = 1920,
        .height = 1080,
        .title = "My App"
    };
    
    Config cfg2{.title = "Other"};  // width and height use defaults
}

// --- consteval (immediate functions, compile-time only) ---
consteval int compile_time_square(int n) {
    return n * n;
}

void demo_consteval() {
    constexpr int x = compile_time_square(5);  // OK: compile time
    static_assert(x == 25);
    
    // int y = compile_time_square(5);         // Error: must be constexpr context
}

// --- constinit (force compile-time initialization) ---
constinit int global_value = 42;             // Initialized at compile time

// --- char8_t (UTF-8 character type) ---
void demo_char8() {
    char8_t c = u8'A';
    const char8_t* str = u8"Hello";
    std::u8string s = u8"UTF-8 string";
}

// --- [[likely]] and [[unlikely]] (branch prediction hints) ---
int process_value(int x) {
    if (x > 0) [[likely]] {                  // Hint: likely branch
        return x * 2;
    } else [[unlikely]] {                    // Hint: unlikely branch
        return 0;
    }
}

// --- [[no_unique_address]] (empty base optimization for members) ---
struct Empty {};

struct Optimized {
    [[no_unique_address]] Empty e;           // Takes no space
    int data;
};

static_assert(sizeof(Optimized) == sizeof(int));

// --- Init-statement in range-for ---
void demo_rangefor_init() {
    for (std::vector<int> v{1, 2, 3}; auto& elem : v) {  // Init v in for statement
        std::cout << elem << ' ';
    }
}

// --- Pack-expansion in lambda captures ---
template<typename... Args>
auto make_lambda(Args... args) {
    return [...args = std::move(args)]() {   // Pack expansion in capture
        return (args + ...);                 // Fold expression
    };
}

// --- constexpr improvements ---
constexpr int factorial(int n) {
    int result = 1;
    for (int i = 2; i <= n; ++i) {
        result *= i;
    }
    return result;
}

constexpr auto test_constexpr() {
    std::vector<int> v{1, 2, 3};             // constexpr vector in C++20!
    v.push_back(4);
    return v.size();
}

// --- constexpr virtual functions ---
struct Base {
    constexpr virtual int value() const { return 1; }
};

struct Derived : Base {
    constexpr int value() const override { return 2; }
};

constexpr int get_value() {
    Derived d;
    Base* p = &d;
    return p->value();                       // Virtual call at compile time
}

static_assert(get_value() == 2);

// --- constexpr dynamic_cast and typeid ---
constexpr int test_dynamic_cast() {
    Derived d;
    Base* b = &d;
    Derived* pd = dynamic_cast<Derived*>(b); // dynamic_cast at compile time
    return pd ? 1 : 0;
}

// --- using enum (import enum values) ---
enum class Color { Red, Green, Blue };

void demo_using_enum() {
    using enum Color;                        // Import all enumerators
    Color c = Red;                           // No need for Color::Red
}

// --- Aggregate initialization with parentheses ---
struct Aggregate {
    int a, b;
};

void demo_aggregate_paren() {
    Aggregate a(1, 2);                       // Parentheses now allowed
    Aggregate b{3, 4};                       // Braces still work
}

// --- [[nodiscard]] with message ---
[[nodiscard("Ignoring return value wastes computation")]]
int expensive_computation() {
    return 42;
}

// --- [[nodiscard]] for constructors ---
struct [[nodiscard]] Resource {
    Resource() {}
};

void demo_nodiscard_ctor() {
    // Resource{};                           // Warning: discarding value
    Resource r{};                            // OK
}

// --- Class template argument deduction for aggregates ---
template<typename T>
struct Pair {
    T first, second;
};

void demo_ctad_aggregates() {
    Pair p{1, 2};                            // Deduced: Pair<int>
}

// --- Class template argument deduction for alias templates ---
template<typename T>
using Vec = std::vector<T>;

void demo_ctad_alias() {
    Vec v{1, 2, 3};                          // Deduced: Vec<int> = std::vector<int>
}

// --- Lambdas in unevaluated contexts ---
void demo_lambda_unevaluated() {
    auto hash = [](auto x) { return std::hash<decltype(x)>{}(x); };
    decltype(hash) other_hash;               // Lambda in unevaluated context
}

// --- Default constructible/assignable stateless lambdas ---
void demo_lambda_default() {
    auto lambda = [](int x) { return x * 2; };
    decltype(lambda) copy;                   // Default constructible
    copy = lambda;                           // Assignable
}

// --- explicit(bool) (conditionally explicit) ---
template<typename T>
struct Wrapper {
    T value;
    
    explicit(!std::is_convertible_v<T, int>) Wrapper(T v) : value(v) {}
};

void demo_explicit_bool() {
    Wrapper w1 = 42;                         // OK: int is convertible
    // Wrapper<std::string> w2 = "hi";       // Error: explicit constructor
    Wrapper<std::string> w3{"hi"};           // OK: explicit call
}

// --- constexpr std::string and std::vector ---
constexpr int test_constexpr_containers() {
    std::string s = "hello";
    std::vector<int> v{1, 2, 3};
    return s.size() + v.size();
}

// --- Immediate move for rvalue references ---
void demo_implicit_move() {
    auto get_string = []() -> std::string {
        std::string s = "hello";
        return s;                            // Automatically moved (not copied)
    };
}

// --- std::is_constant_evaluated() ---
constexpr int runtime_or_compile(int x) {
    if (std::is_constant_evaluated()) {
        return x * 2;                        // Compile-time path
    } else {
        return x * 3;                        // Runtime path
    }
}

// ============================================================================
// LIBRARY FEATURES
// ============================================================================

// --- std::format (type-safe formatting) ---
void demo_format() {
    std::string s = std::format("Hello, {}!", "world");
    std::string num = std::format("Value: {:.2f}", 3.14159);
    std::string hex = std::format("Hex: {:#x}", 255);  // 0xff
    
    // Positional arguments
    std::string pos = std::format("{1} {0}", "world", "Hello");
}

// --- std::span (non-owning view of contiguous sequence) ---
void process_data(std::span<int> data) {     // Works with any contiguous container
    for (int& x : data) {
        x *= 2;
    }
}

void demo_span() {
    std::vector<int> v{1, 2, 3, 4, 5};
    int arr[] = {1, 2, 3};
    
    process_data(v);                         // Works with vector
    process_data(arr);                       // Works with array
    process_data(std::span{v}.subspan(1, 3)); // Subspan
}

// --- std::source_location (replacement for __FILE__ and __LINE__) ---
void log(std::string_view message,
         std::source_location loc = std::source_location::current()) {
    std::cout << "File: " << loc.file_name()
              << " (" << loc.line() << ":"
              << loc.column() << ") "
              << "`" << loc.function_name() << "`: "
              << message << '\n';
}

// --- std::endian ---
void demo_endian() {
    if constexpr (std::endian::native == std::endian::little) {
        std::cout << "Little endian\n";
    } else if constexpr (std::endian::native == std::endian::big) {
        std::cout << "Big endian\n";
    }
}

// --- std::bit_cast (type-safe reinterpret) ---
void demo_bit_cast() {
    float f = 3.14f;
    auto bits = std::bit_cast<std::uint32_t>(f);  // Safe type punning
}

// --- Bit operations ---
void demo_bit_ops() {
    unsigned int x = 8;
    
    int zeros = std::countl_zero(x);         // Count leading zeros
    int ones = std::popcount(x);             // Count set bits
    auto rotated = std::rotl(x, 2);          // Rotate left
    
    bool is_pow2 = std::has_single_bit(x);   // Check if power of 2
    auto next_pow2 = std::bit_ceil(x);       // Next power of 2
    auto prev_pow2 = std::bit_floor(x);      // Previous power of 2
    int width = std::bit_width(x);           // Width in bits
}

// --- Mathematical constants ---
void demo_math_constants() {
    double pi = std::numbers::pi;
    double e = std::numbers::e;
    double sqrt2 = std::numbers::sqrt2;
    double phi = std::numbers::phi;          // Golden ratio
}

// --- std::midpoint and std::lerp ---
void demo_midpoint_lerp() {
    int mid = std::midpoint(10, 20);         // 15 (safe, no overflow)
    double lerp = std::lerp(0.0, 10.0, 0.5); // 5.0 (linear interpolation)
}

// --- std::starts_with / std::ends_with ---
void demo_string_checks() {
    std::string s = "Hello, World!";
    bool starts = s.starts_with("Hello");    // true
    bool ends = s.ends_with("World!");       // true
    
    std::string_view sv = "test.txt";
    bool is_txt = sv.ends_with(".txt");      // true
}

// --- std::erase / std::erase_if (uniform container erasure) ---
void demo_erase() {
    std::vector<int> v{1, 2, 3, 2, 4, 2, 5};
    std::erase(v, 2);                        // Remove all 2's: {1,3,4,5}
    
    std::vector<int> v2{1, 2, 3, 4, 5};
    std::erase_if(v2, [](int n) { return n % 2 == 0; });  // Remove evens: {1,3,5}
}

// --- std::jthread (automatically joining thread) ---
void demo_jthread() {
    std::jthread t([](std::stop_token st) {
        while (!st.stop_requested()) {
            // Do work...
        }
    });
    // Automatically joins and requests stop on destruction
}

// --- std::latch and std::barrier ---
void demo_sync_primitives() {
    std::latch latch(3);                     // Wait for 3 threads
    
    auto worker = [&latch]() {
        // Do work...
        latch.count_down();                  // Signal completion
    };
    
    // In main thread:
    // latch.wait();                         // Wait for all workers
    
    std::barrier barrier(3);                 // Reusable barrier
}

// --- std::counting_semaphore ---
void demo_semaphore() {
    std::counting_semaphore<10> sem(5);      // Initial count: 5
    
    sem.acquire();                           // Decrement
    // Critical section
    sem.release();                           // Increment
}

// --- std::osyncstream (synchronized output stream) ---
void demo_osyncstream() {
    std::osyncstream(std::cout) << "Thread-safe output\n";
}

// --- constexpr algorithms ---
constexpr int test_constexpr_algo() {
    std::array<int, 5> arr{5, 2, 8, 1, 9};
    std::sort(arr.begin(), arr.end());       // constexpr sort
    return arr[0];                           // 1
}

// --- std::to_array ---
void demo_to_array() {
    auto arr = std::to_array({1, 2, 3, 4});  // Creates std::array<int, 4>
}

// --- std::ssize (signed size) ---
void demo_ssize() {
    std::vector<int> v{1, 2, 3};
    auto size = std::ssize(v);               // Returns signed type
}

// --- std::remove_cvref ---
template<typename T>
using clean_type = std::remove_cvref_t<T>;

// --- std::type_identity (block type deduction) ---
template<typename T>
void func(std::type_identity_t<T> arg) {    // T must be explicitly specified
}

// --- std::bind_front (partial application) ---
void demo_bind_front() {
    auto add = [](int a, int b, int c) { return a + b + c; };
    auto add5 = std::bind_front(add, 5);
    int result = add5(10, 20);               // 35
}

// --- std::shift_left / std::shift_right ---
void demo_shift() {
    std::vector<int> v{1, 2, 3, 4, 5};
    std::shift_left(v.begin(), v.end(), 2);  // {3, 4, 5, 4, 5}
}

// --- Safe integer comparisons ---
void demo_safe_cmp() {
    int a = -1;
    unsigned int b = 1;
    
    // std::cmp_less instead of a < b (which would be false due to conversion)
    bool less = std::cmp_less(a, b);         // true
    bool equal = std::cmp_equal(a, b);       // false
}

// --- std::assume_aligned ---
void demo_assume_aligned() {
    void* ptr = aligned_alloc(64, 128);
    int* aligned_ptr = std::assume_aligned<64>(static_cast<int*>(ptr));
    free(ptr);
}

// --- Heterogeneous lookup in unordered containers ---
void demo_heterogeneous_unordered() {
    std::unordered_map<std::string, int, std::hash<std::string_view>,
                       std::equal_to<>> map;
    map["key"] = 42;
    
    // Can lookup with string_view (no temporary string)
    auto it = map.find("key");
}

// --- std::make_shared for arrays ---
void demo_make_shared_array() {
    auto arr = std::make_shared<int[]>(10);  // shared_ptr to array
}

// --- constexpr <numeric> ---
constexpr int test_constexpr_numeric() {
    std::array<int, 5> arr{1, 2, 3, 4, 5};
    return std::accumulate(arr.begin(), arr.end(), 0);
}

// --- std::unwrap_reference / std::unwrap_ref_decay ---
void demo_unwrap_ref() {
    int x = 42;
    auto ref = std::ref(x);
    using T = std::unwrap_reference_t<decltype(ref)>;  // int&
}

// ============================================================================
// MAIN DEMONSTRATION
// ============================================================================

int main() {
    std::cout << "=== C++20 Comprehensive Demo ===\n\n";
    
    // Concepts
    std::cout << "add(5, 10) = " << add(5, 10) << '\n';
    print("Hello, Concepts!");
    
    // Ranges
    std::cout << "Ranges: ";
    demo_ranges();
    std::cout << '\n';
    
    // Spaceship operator
    demo_spaceship();
    
    // Coroutines
    std::cout << "Fibonacci: ";
    demo_coroutines();
    std::cout << '\n';
    
    // Formatting
    std::cout << std::format("Pi: {:.5f}\n", std::numbers::pi);
    
    // Source location
    log("Test message");
    
    // Endianness
    demo_endian();
    
    // String checks
    demo_string_checks();
    
    // Compile-time tests
    static_assert(factorial(5) == 120);
    static_assert(test_constexpr() == 4);
    static_assert(compile_time_square(7) == 49);
    
    return 0;
}
```

## Summary

**C++20 Core Language Features:**
- **Concepts** - Constrain template parameters
- **Modules** - Replace header files
- **Coroutines** - Suspend and resume execution
- **Ranges** - Composable lazy views and algorithms
- **Three-way comparison** (`<=>`) - Spaceship operator
- Designated initializers
- `consteval` - Immediate functions
- `constinit` - Compile-time initialization
- `char8_t` - UTF-8 character type
- `[[likely]]` / `[[unlikely]]` - Branch hints
- `[[no_unique_address]]` - Empty member optimization
- Init-statement in range-for
- Pack-expansion in lambda captures
- Template parameter lists for lambdas
- `constexpr` improvements (virtual, dynamic_cast, try-catch, containers)
- `using enum` - Import enum values
- Aggregate initialization with parentheses
- `[[nodiscard]]` with message and for constructors
- CTAD for aggregates and alias templates
- Lambdas in unevaluated contexts
- Default constructible stateless lambdas
- `explicit(bool)` - Conditionally explicit
- Implicit move for rvalue references
- `std::is_constant_evaluated()`
- Abbreviated function templates
- Many defect report fixes

**C++20 Library Features:**
- **`std::format`** - Type-safe formatting
- **`std::span`** - Non-owning view
- **`std::source_location`** - File/line info
- **`std::ranges`** - Range algorithms and views
- **Concepts library** - Standard concepts
- **`<chrono>` calendar/timezone** - Date/time support
- `std::endian` - Byte order
- `std::bit_cast` - Safe type punning
- Bit operations: `popcount`, `rotl`, `countl_zero`, etc.
- Mathematical constants: `pi`, `e`, `sqrt2`, etc.
- `std::midpoint`, `std::lerp`
- `std::starts_with`, `std::ends_with`
- `std::erase`, `std::erase_if` - Uniform erasure
- `std::jthread` - Auto-joining thread
- `std::stop_token` - Thread cancellation
- `std::latch`, `std::barrier` - Synchronization
- `std::counting_semaphore`
- `std::osyncstream` - Synchronized output
- `constexpr` for algorithms, string, vector, numeric
- `std::to_array`
- `std::ssize` - Signed size
- `std::remove_cvref`
- `std::type_identity`
- `std::bind_front`
- `std::shift_left`, `std::shift_right`
- Safe integer comparisons: `std::cmp_less`, etc.
- `std::assume_aligned`
- Heterogeneous lookup in unordered containers
- `std::make_shared` for arrays
- `std::unwrap_reference`
- Floating-point atomics
- `std::atomic_ref`
- Many more improvements...

**Reference**: [https://en.cppreference.com/w/cpp/20](https://en.cppreference.com/w/cpp/20)
