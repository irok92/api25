# Exception specification

## Exception specification

### [noexcept specification](https://en.cppreference.com/w/cpp/language/noexcept_spec.html) (C++11)

**Code-related Keywords:**
- `noexcept` - Function doesn't throw (C++11)
- `noexcept(true)` - Same as `noexcept`
- `noexcept(false)` - Can throw
- `noexcept(expr)` - Conditional noexcept

**Theory Keywords:**
- **non-throwing guarantee** - Function never throws
- **optimization** - Compiler can optimize noexcept [functions](../../07_functions/functions.md)
- **move semantics** - Important for move constructors/assignment
- **terminate on throw** - `std::terminate` called if noexcept function throws

**Example:**
```cpp
// Basic noexcept:
int safeFunc() noexcept {  // Guarantees no exceptions
    return 42;
}

// Conditional noexcept:
template<typename T>
void swap(T& a, T& b) noexcept(std::is_nothrow_move_constructible_v<T>) {
    T temp = std::move(a);
    a = std::move(b);
    b = std::move(temp);
}

// Move operations should be noexcept:
class String {
    char* data;
    
public:
    String(String&& other) noexcept {  // noexcept for performance
        data = other.data;
        other.data = nullptr;
    }
    
    String& operator=(String&& other) noexcept {
        if (this != &other) {
            delete[] data;
            data = other.data;
            other.data = nullptr;
        }
        return *this;
    }
};

// std::vector uses noexcept for optimization:
// If move constructor is noexcept, vector uses move; otherwise copy

// Destructors implicitly noexcept:
class Foo {
    ~Foo() { }            // Implicitly noexcept
};

// Breaking noexcept = std::terminate:
void bad() noexcept {
    throw std::runtime_error("Error");  // Calls std::terminate!
}
```

### [Dynamic exception specification](https://en.cppreference.com/w/cpp/language/except_spec.html) (until C++17)

**Code-related Keywords:**
- `throw(Type)` - Can throw Type (deprecated, removed C++17)
- `throw()` - No exceptions (use `noexcept` instead)

**Theory Keywords:**
- **deprecated** - Removed in C++17
- **runtime check** - Checked at runtime (inefficient)
- **use noexcept** - Modern replacement

**Example:**
```cpp
// Legacy (don't use):
// void func() throw(std::exception) {  // REMOVED in C++17
//     throw std::runtime_error("Error");
// }

// throw() equivalent to noexcept:
void oldStyle() throw() {    // Legacy: no exceptions
    // ...
}

void newStyle() noexcept {   // Modern: use this
    // ...
}

// Why dynamic specs were removed:
// - Runtime overhead
// - Called std::unexpected if violated
// - Didn't compose well with templates
// - noexcept is checked at compile time and more efficient
```
