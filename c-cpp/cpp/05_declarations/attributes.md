# Attributes

## [Attributes](https://en.cppreference.com/w/cpp/language/attributes.html) (C++11)

**Code-related Keywords:**
- `[[noreturn]]` (C++11) - Function never returns
- `[[carries_dependency]]` (C++11, removed C++26) - Memory order dependency chain
- `[[deprecated]]` / `[[deprecated("reason")]]` (C++14) - Mark as obsolete
- `[[fallthrough]]` (C++17) - Intentional switch fallthrough
- `[[maybe_unused]]` (C++17) - Suppress unused warnings
- `[[nodiscard]]` / `[[nodiscard("reason")]]` (C++17/C++20) - Warn if return value ignored
- `[[likely]]` / `[[unlikely]]` (C++20) - Branch prediction hints
- `[[no_unique_address]]` (C++20) - Allow empty member optimization
- `[[assume(expression)]]` (C++23) - Optimization assumption
- `[[indeterminate]]` (C++26) - Uninitialized value marker

**Theory Keywords:**
- **compiler hints** - Guide optimization and warnings
- **standard attributes** - Portable across compilers (C++11+)
- **vendor attributes** - Compiler-specific extensions (e.g., `[[gnu::...]]`, `[[msvc::...]]`)

**Example:**
```cpp
// [[nodiscard]]: warn if return value ignored
[[nodiscard]] int calculate() { return 42; }
calculate();                  // Warning: return value discarded

// [[maybe_unused]]: suppress unused warnings
void func([[maybe_unused]] int param) {
    // param not used, but no warning
}

// [[noreturn]]: function doesn't return (exits/throws/loops forever)
[[noreturn]] void terminate() {
    std::exit(1);
}

// [[deprecated]]: mark for removal
[[deprecated("Use newFunc instead")]]
void oldFunc() { }

// [[fallthrough]]: intentional switch fallthrough
int x = 2;
switch (x) {
    case 1: std::cout << "1\n";
        [[fallthrough]];      // Intentional: no warning
    case 2: std::cout << "2\n"; break;
    default: break;
}

// [[likely]]/[[unlikely]]: optimization hints (C++20)
if (condition) [[likely]] {   // Hint: this branch more common
    // fast path
} else [[unlikely]] {
    // rare error path
}

// [[no_unique_address]]: empty base optimization for members (C++20)
struct Empty {};
struct S {
    [[no_unique_address]] Empty e;  // May have zero size
    int data;                        // sizeof(S) may equal sizeof(int)
};

// [[assume]]: optimization hint (C++23)
void divide(int a, int b) {
    [[assume(b != 0)]];       // Tell compiler b is never zero
    return a / b;
}

// Multiple attributes
[[nodiscard, deprecated("Use newFunc")]]
int oldCalculate() { return 42; }

// Attribute namespaces (C++17)
[[using gnu: const, always_inline]]  // gnu::const, gnu::always_inline
void fastFunc() { }
```
