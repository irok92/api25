# Exception operator

## [noexcept operator](https://en.cppreference.com/w/cpp/language/noexcept.html) (C++11)

**Code-related Keywords:**
- `noexcept(expr)` - Check if [expression](../../04_expressions/expressions.md) is noexcept (C++11)
- Returns `bool` - Compile-time check

**Theory Keywords:**
- **noexcept [operator](../../04_expressions/operators.md)** - Query if expression throws (C++11)
- **compile-time** - Evaluated at compile time
- **conditional noexcept** - Make [function](../../07_functions/functions.md) noexcept based on condition

**Example:**
```cpp
// noexcept operator (check if throws):
void func1() noexcept { }
void func2() { }

constexpr bool b1 = noexcept(func1());  // true
constexpr bool b2 = noexcept(func2());  // false

// Conditional noexcept:
template<typename T>
void swap(T& a, T& b) noexcept(noexcept(T(std::move(a)))) {
    // noexcept if T's move constructor is noexcept
    T temp = std::move(a);
    a = std::move(b);
    b = std::move(temp);
}

// Check standard operations:
struct Foo {
    Foo(Foo&&) noexcept { }  // Move constructor noexcept
};

static_assert(noexcept(Foo(std::declval<Foo>())));  // true

// Use with SFINAE:
template<typename T>
auto moveIfNoexcept(T& x) noexcept(noexcept(T(std::move(x))))
    -> decltype(std::move_if_noexcept(x))
{
    return std::move_if_noexcept(x);  // Move if safe, copy otherwise
}
```
