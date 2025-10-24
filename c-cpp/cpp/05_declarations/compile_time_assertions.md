# Compile-time assertions

## [static_assert](https://en.cppreference.com/w/cpp/language/static_assert.html) (C++11)

**Code-related Keywords:**
- `static_assert(cond, "msg");` - Compile-time check (C++11)
- `static_assert(cond);` (C++17) - Message optional

**Theory Keywords:**
- **compile-time validation** - Check constraints before runtime
- **constexpr requirement** - Condition must be constant [expression](../../04_expressions/expressions.md)
- **template constraints** - Validate [template](../../10_templates/templates.md) parameters

**Example:**
```cpp
// Basic assertions:
static_assert(sizeof(int) >= 4, "int must be at least 4 bytes");
static_assert(sizeof(void*) == 8);  // C++17: no message required

// Template constraints:
template<typename T>
class Container {
    static_assert(std::is_copy_constructible_v<T>, 
                  "T must be copy constructible");
    static_assert(!std::is_pointer_v<T>,
                  "Pointer types not allowed");
};

// Constexpr validation:
constexpr int SIZE = 100;
static_assert(SIZE > 0 && SIZE <= 1000, "SIZE out of range");

// Check alignment:
struct alignas(16) Vec4 { float x, y, z, w; };
static_assert(alignof(Vec4) == 16, "Vec4 must be 16-byte aligned");

// Architecture checks:
static_assert(sizeof(size_t) == sizeof(void*), 
              "size_t and pointer size mismatch");
```
