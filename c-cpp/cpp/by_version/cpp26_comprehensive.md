# C++26 Comprehensive Example

> **Source**: [https://en.cppreference.com/w/cpp/26](https://en.cppreference.com/w/cpp/26)

This file demonstrates **all major C++26 features** in a compact, compilable example.

**Note**: C++26 is still under development. Some features may not be finalized or widely supported yet.

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
#include <format>
#include <span>
#include <mdspan>
#include <text_encoding>
#include <debugging>
#include <hazard_pointer>
#include <rcu>
#include <inplace_vector>
#include <linalg>
#include <simd>
#include <hive>
#include <contracts>

// ============================================================================
// LANGUAGE FEATURES
// ============================================================================

// --- Pack indexing ---
template<typename... Ts>
void demo_pack_indexing() {
    using FirstType = Ts...[0];                  // First type in pack
    using SecondType = Ts...[1];                 // Second type in pack
    
    auto get_nth = []<std::size_t N>(auto... args) {
        return args...[N];                       // Nth value in pack
    };
    
    int value = get_nth.template operator()<1>(10, 20, 30);  // 20
}

// --- Placeholder variables with no name ---
void demo_placeholder_variables() {
    auto [_, y, _] = std::tuple{1, 2, 3};        // Multiple _ allowed
    // Only y is accessible
    
    for (auto [_, value] : std::vector{std::pair{1, 10}, std::pair{2, 20}}) {
        std::cout << value << ' ';               // Ignore keys
    }
}

// --- Structured bindings can introduce a pack ---
void demo_structured_binding_pack() {
    auto tuple = std::make_tuple(1, 2.0, "three");
    auto [...pack] = tuple;                      // Pack from structured binding
    
    // Use pack in fold expression
    auto sum = (pack + ...);
}

// --- Attributes for structured bindings ---
void demo_structured_binding_attributes() {
    auto [[[maybe_unused]] x, y] = std::pair{1, 2};  // Attribute on binding
}

// --- User-generated static_assert messages ---
void demo_static_assert_messages() {
    constexpr int x = 5;
    static_assert(x > 10, std::format("Value {} is too small", x));
}

// --- = delete("reason") ---
struct NonCopyable {
    NonCopyable() = default;
    NonCopyable(const NonCopyable&) = delete("Copying is expensive");
    NonCopyable& operator=(const NonCopyable&) = delete("Use move instead");
};

// --- Variadic friends ---
template<typename... Ts>
struct Container {
    template<typename... Us>
    friend struct Container;                     // All instantiations are friends
};

// --- constexpr placement new ---
constexpr int test_placement_new() {
    alignas(int) char buffer[sizeof(int)];
    int* ptr = new (buffer) int(42);             // placement new in constexpr
    int value = *ptr;
    ptr->~int();
    return value;
}

static_assert(test_placement_new() == 42);

// --- Structured binding as a condition ---
void demo_structured_binding_condition() {
    std::map<int, std::string> map{{1, "one"}};
    
    if (auto [it, inserted] = map.insert({2, "two"}); inserted) {
        std::cout << "Inserted: " << it->second << '\n';
    }
}

// --- constexpr cast from void* ---
constexpr int test_constexpr_void_cast() {
    int x = 42;
    void* ptr = &x;
    int* iptr = static_cast<int*>(ptr);          // constexpr cast from void*
    return *iptr;
}

static_assert(test_constexpr_void_cast() == 42);

// --- constexpr structured bindings ---
constexpr auto test_constexpr_structured_binding() {
    constexpr auto [a, b] = std::pair{1, 2};
    return a + b;
}

static_assert(test_constexpr_structured_binding() == 3);

// --- constexpr exceptions ---
#if __cpp_constexpr >= 202611L
constexpr int test_constexpr_exceptions() {
    try {
        throw 42;
    } catch (int e) {
        return e;
    }
}

static_assert(test_constexpr_exceptions() == 42);
#endif

// --- Oxford variadic comma ---
void oxford_comma(auto... args) {
    // Can use trailing comma in parameter packs
    auto tuple = std::tuple{args...,};           // Trailing comma allowed
}

// --- #embed (embed binary data) ---
#if __has_embed("data.bin")
constexpr auto data = 
#embed "data.bin"                                // Embed file contents
;
#endif

// --- Concept and variable-template template-parameters ---
template<template<typename> std::integral auto V>  // Variable template as template param
struct Example {};

// --- Trivial relocatability ---
struct [[trivially_relocatable]] TriviallyRelocatable {
    int* ptr;
    // Move is equivalent to memcpy
};

// --- Contracts ---
#if __cpp_contracts >= 202600L
int divide(int a, int b)
    pre(b != 0)                                  // Precondition
    post(r: r == a / b)                          // Postcondition
{
    return a / b;
}

void process(std::vector<int>& v)
    pre(!v.empty())                              // Precondition
    post(v.size() == old(v.size()))              // Ensure size unchanged
{
    // Process vector
}
#endif

// --- [[indeterminate]] attribute ---
void demo_indeterminate() {
    [[indeterminate]] int x;                     // Mark uninitialized read as OK
    // Reading x before initialization is defined behavior
}

// ============================================================================
// LIBRARY FEATURES
// ============================================================================

// --- std::text_encoding (text encoding identification) ---
void demo_text_encoding() {
    auto enc = std::text_encoding::system();
    std::cout << "System encoding: " << enc.name() << '\n';
    
    if (enc == std::text_encoding::UTF8) {
        std::cout << "UTF-8 encoding\n";
    }
}

// --- std::inplace_vector (fixed-capacity vector) ---
void demo_inplace_vector() {
    std::inplace_vector<int, 10> vec;            // Max 10 elements, no heap
    vec.push_back(1);
    vec.push_back(2);
    // vec.capacity() == 10
    // sizeof(vec) includes all elements
}

// --- std::hive (bucket container with stable references) ---
void demo_hive() {
    std::hive<int> h;
    auto it1 = h.insert(42);                     // Insert returns iterator
    auto it2 = h.insert(100);
    
    h.erase(it1);                                // Erase, it2 still valid
    h.insert(50);                                // Reuses erased slot
    
    // Iterators remain valid across insertions/erasures
}

// --- std::hazard_pointer (safe memory reclamation) ---
void demo_hazard_pointer() {
    std::atomic<int*> ptr;
    
    // Reader thread
    std::hazard_pointer hp = std::make_hazard_pointer();
    int* p = hp.protect(ptr);                    // Protect from deletion
    if (p) {
        // Safe to use *p
    }
}

// --- std::rcu (Read-Copy-Update) ---
void demo_rcu() {
    std::rcu_domain domain;
    std::atomic<int*> ptr;
    
    // Reader
    domain.lock();
    int* p = ptr.load();
    // Use p safely
    domain.unlock();
    
    // Writer
    int* new_data = new int(42);
    int* old_data = ptr.exchange(new_data);
    domain.retire(old_data);                     // Safe deferred deletion
}

// --- std::linalg (linear algebra) ---
void demo_linalg() {
    std::vector<double> data1{1, 2, 3, 4};
    std::vector<double> data2{5, 6, 7, 8};
    std::vector<double> result(4);
    
    std::mdspan A(data1.data(), 2, 2);
    std::mdspan B(data2.data(), 2, 2);
    std::mdspan C(result.data(), 2, 2);
    
    std::linalg::matrix_product(A, B, C);        // Matrix multiplication
}

// --- std::simd (data-parallel types) ---
void demo_simd() {
    std::simd<float> a{1.0f, 2.0f, 3.0f, 4.0f};
    std::simd<float> b{5.0f, 6.0f, 7.0f, 8.0f};
    
    auto c = a + b;                              // Parallel addition
    auto d = a * b;                              // Parallel multiplication
}

// --- std::function_ref (non-owning callable reference) ---
void execute(std::function_ref<int(int)> func) {
    std::cout << func(42) << '\n';
}

void demo_function_ref() {
    auto lambda = [](int x) { return x * 2; };
    execute(lambda);                             // No allocation, just reference
}

// --- std::copyable_function (copyable std::move_only_function) ---
void demo_copyable_function() {
    std::copyable_function<int(int)> func = [](int x) { return x * 2; };
    auto copy = func;                            // Copyable
}

// --- views::concat (concatenate ranges) ---
void demo_views_concat() {
    std::vector v1{1, 2, 3};
    std::vector v2{4, 5, 6};
    
    for (int x : std::views::concat(v1, v2)) {
        std::cout << x << ' ';                   // 1 2 3 4 5 6
    }
}

// --- String concatenation ---
void demo_string_concat() {
    std::string s1 = "Hello";
    std::string_view sv = " World";
    
    std::string result = s1 + sv;                // Direct concatenation
}

// --- ranges::generate_random ---
void demo_generate_random() {
    std::vector<int> v(10);
    std::ranges::generate_random(v, 1, 100);     // Fill with random [1, 100]
}

// --- std::span over initializer list ---
void process_span(std::span<const int> s) {
    for (int x : s) std::cout << x << ' ';
}

void demo_span_initializer_list() {
    process_span({1, 2, 3, 4, 5});               // Span from initializer list
}

// --- std::span::at() ---
void demo_span_at() {
    std::vector v{1, 2, 3, 4, 5};
    std::span s{v};
    
    int x = s.at(2);                             // Bounds-checked access
    // s.at(10); // Throws std::out_of_range
}

// --- Formatting improvements ---
void demo_formatting() {
    std::filesystem::path p = "/usr/bin/gcc";
    std::println("{}", p);                       // Format filesystem::path
    
    int* ptr = nullptr;
    std::println("{}", static_cast<void*>(ptr)); // Format pointers
    
    std::println();                              // Print blank line
}

// --- Saturation arithmetic ---
void demo_saturation() {
    auto result = std::add_sat(200, 100);        // Saturating add (caps at max)
    auto diff = std::sub_sat(10, 50);            // Saturating sub (caps at min)
}

// --- std::debugging (debugging support) ---
void demo_debugging() {
    if (std::is_debugger_present()) {
        std::breakpoint();                       // Trigger debugger breakpoint
    }
}

// --- constexpr stable sorting ---
constexpr auto test_constexpr_stable_sort() {
    std::array arr{3, 1, 4, 1, 5, 9, 2, 6};
    std::ranges::stable_sort(arr);               // constexpr stable_sort
    return arr[0];
}

static_assert(test_constexpr_stable_sort() == 1);

// --- std::submdspan (multidimensional slicing) ---
void demo_submdspan() {
    std::vector<int> data(24);
    std::mdspan md(data.data(), 4, 6);
    
    auto sub = std::submdspan(md, std::pair{1, 3}, std::pair{2, 5});  // Slice
}

// --- std::is_virtual_base_of ---
struct Base {};
struct Derived : virtual Base {};

static_assert(std::is_virtual_base_of_v<Base, Derived>);

// --- std::philox_engine (counter-based RNG) ---
void demo_philox() {
    std::philox_engine engine;
    auto value = engine();                       // Generate random number
}

// --- std::optional range support ---
void demo_optional_range() {
    std::optional<int> opt = 42;
    
    for (int x : opt) {                          // Iterate over optional
        std::cout << x << '\n';                  // Executes if has_value
    }
}

// --- Atomic improvements ---
void demo_atomic() {
    std::atomic<int> a{10};
    std::atomic<int> b{20};
    
    a.fetch_max(15);                             // Atomic maximum
    b.fetch_min(18);                             // Atomic minimum
}

// --- std::indirect and std::polymorphic (vocabulary types) ---
void demo_indirect() {
    std::indirect<std::string> ind{"hello"};     // Value semantics, heap storage
    std::indirect<std::string> copy = ind;       // Deep copy
    
    struct Base { virtual ~Base() = default; };
    struct Derived : Base {};
    
    std::polymorphic<Base> poly = Derived{};     // Polymorphic value type
}

// --- constexpr containers ---
constexpr auto test_constexpr_containers() {
    std::vector<int> v{1, 2, 3};
    std::map<int, int> m{{1, 10}, {2, 20}};
    std::set<int> s{1, 2, 3};
    
    return v.size() + m.size() + s.size();
}

static_assert(test_constexpr_containers() == 9);

// --- Trivial relocatability traits ---
static_assert(std::is_trivially_relocatable_v<std::string>);  // Implementation-defined

// ============================================================================
// MAIN DEMONSTRATION
// ============================================================================

int main() {
    std::println("=== C++26 Comprehensive Demo ===\n");
    
    // Pack indexing
    demo_pack_indexing<int, double, char>();
    
    // Placeholder variables
    demo_placeholder_variables();
    
    // Text encoding
    demo_text_encoding();
    
    // inplace_vector
    demo_inplace_vector();
    
    // views::concat
    demo_views_concat();
    std::println("");
    
    // String concatenation
    demo_string_concat();
    
    // span initializer list
    demo_span_initializer_list();
    std::println("");
    
    // Formatting
    demo_formatting();
    
    // Compile-time tests
    static_assert(test_placement_new() == 42);
    static_assert(test_constexpr_void_cast() == 42);
    static_assert(test_constexpr_structured_binding() == 3);
    static_assert(test_constexpr_stable_sort() == 1);
    static_assert(test_constexpr_containers() == 9);
    
    return 0;
}
```

## Summary

**C++26 Core Language Features:**
- **Pack indexing** - `Ts...[N]` to access Nth element in parameter pack
- **Placeholder variables with no name** - Multiple `_` allowed
- **Structured bindings can introduce a pack** - `auto [...pack] = tuple;`
- **Attributes for structured bindings** - `auto [[attr]] x = value;`
- **User-generated static_assert messages** - `static_assert(cond, std::format(...))`
- **= delete("reason")** - Explanatory messages for deleted functions
- **Variadic friends** - `template<typename... Us> friend struct T;`
- **constexpr placement new** - Placement new in constexpr contexts
- **Structured binding as a condition** - `if (auto [a, b] = ...; cond)`
- **constexpr cast from void*** - Cast from `void*` in constexpr
- **constexpr structured bindings** - Structured bindings in constexpr
- **constexpr exceptions** - try/catch in constexpr functions
- **Oxford variadic comma** - Trailing comma in parameter packs
- **#embed** - Embed binary file contents
- **Concept and variable-template template-parameters**
- **Trivial relocatability** - `[[trivially_relocatable]]`
- **Trivial unions** - More relaxed union rules
- **Contracts** - `pre`, `post`, `assert` conditions
- **[[indeterminate]]** - Mark uninitialized reads as intentional
- Removing deprecated features: arithmetic conversion on enums, array comparisons

**C++26 Library Features:**
- **std::text_encoding** - Text encoding identification
- **std::inplace_vector** - Fixed-capacity vector (no heap)
- **std::hive** - Bucket container with stable references
- **std::hazard_pointer** - Safe memory reclamation
- **std::rcu** - Read-Copy-Update
- **std::linalg** - Linear algebra (BLAS-based)
- **std::simd** - Data-parallel types
- **std::function_ref** - Non-owning callable reference
- **std::copyable_function** - Copyable move-only function
- **views::concat** - Concatenate ranges
- **String concatenation** - Direct string/string_view concat
- **ranges::generate_random** - Fill range with random values
- **std::span over initializer list**
- **std::span::at()** - Bounds-checked access
- **Formatting improvements**: `std::filesystem::path`, pointers, blank lines
- **Saturation arithmetic** - `add_sat`, `sub_sat`, etc.
- **std::debugging** - `is_debugger_present()`, `breakpoint()`
- **constexpr stable sorting**
- **std::submdspan** - Multidimensional slicing
- **std::is_virtual_base_of** - Virtual base detection
- **std::philox_engine** - Counter-based RNG
- **std::optional range support** - Iterate over optional
- **Atomic maximum/minimum** - `fetch_max`, `fetch_min`
- **std::indirect** / **std::polymorphic** - Value semantic wrappers
- **constexpr containers**: `deque`, `list`, `map`, `set`, etc.
- **Trivial relocatability traits** - `is_trivially_relocatable`
- **Standard library hardening** - Runtime bounds checking
- Many more improvements and defect report fixes...

**New Headers:**
- `<contracts>`, `<debugging>`, `<hazard_pointer>`, `<hive>`, `<inplace_vector>`, `<linalg>`, `<rcu>`, `<simd>`, `<text_encoding>`, `<stdbit.h>`, `<stdckdint.h>`

**Reference**: [https://en.cppreference.com/w/cpp/26](https://en.cppreference.com/w/cpp/26)

**Note**: C++26 is expected to be finalized around 2026. Feature availability and exact specifications may change.
