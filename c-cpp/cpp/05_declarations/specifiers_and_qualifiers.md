# Specifiers and qualifiers

## Specifiers and qualifiers

### [inline specifier](https://en.cppreference.com/w/cpp/language/inline.html)

**Code-related Keywords:**
- `inline int func() { }` - Suggest inlining, allow multiple definitions
- `inline constexpr` - Often paired with [constexpr](../../04_expressions/expressions.md#constexpr)
- `inline` variable (C++17) - Inline variable definition

**Theory Keywords:**
- **ODR relaxation** - Multiple identical definitions allowed with inline
- **optimization hint** - Compiler may inline function body at call site

**Example:**
```cpp
// Header file (multiple includes allowed):
inline int square(int x) { return x * x; }  // Multiple definitions OK

inline constexpr int PI_INT = 3;  // C++17: inline variable

// Class definition (implicitly inline):
class Foo {
    int getValue() { return 42; }  // Member functions defined in class are inline
};
```

### [asm declaration](https://en.cppreference.com/w/cpp/language/asm.html)

**Code-related Keywords:**
- `asm("instruction");` - Embed assembly code
- `asm volatile` - Prevent optimization

**Theory Keywords:**
- **inline assembly** - Platform-specific low-level code
- **compiler-specific** - Syntax varies by compiler

**Example:**
```cpp
int result;
asm("mov eax, 1\n\t"    // Move 1 into eax register
    "mov %0, eax"       // Move eax to result
    : "=r"(result));    // Output operand
```

### [volatile qualifier](https://en.cppreference.com/w/cpp/language/cv.html)

**Code-related Keywords:**
- `volatile int var;` - Prevent optimization of reads/writes
- `volatile` pointer - Points to volatile data

**Theory Keywords:**
- **hardware register** - Common use: memory-mapped I/O
- **no optimization** - Compiler must read/write every access

**Example:**
```cpp
volatile int* ioPort = reinterpret_cast<volatile int*>(0x40000000);  // Memory-mapped I/O
*ioPort = 0xFF;         // Write: not optimized away
int status = *ioPort;   // Read: always fetched from memory
```

### [const/cv (const and volatile) type qualifiers](https://en.cppreference.com/w/cpp/language/cv.html)

**Code-related Keywords:**
- `const int x = 10;` - Immutable variable
- `const int* ptr;` - Pointer to const data
- `int* const ptr;` - Const pointer
- `const int& ref = x;` - Const [reference](compound_types.md)
- `mutable` - Allow modification in const context

**Theory Keywords:**
- **immutability** - Value cannot change after initialization
- **const-correctness** - Design principle for safer code

**Example:**
```cpp
const int x = 10;             // x is immutable
// x = 20;                    // ERROR

const int* p1 = &x;           // Pointer to const int (can't modify *p1)
// *p1 = 20;                  // ERROR
p1++;                         // OK: pointer itself is mutable

int y = 5;
int* const p2 = &y;           // Const pointer (can't reassign p2)
*p2 = 20;                     // OK: pointee is mutable
// p2++;                      // ERROR

const int* const p3 = &x;     // Const pointer to const int

class Cache {
    mutable int accessCount = 0;  // mutable: modifiable in const methods
public:
    int getValue() const {
        ++accessCount;        // OK: mutable allows modification
        return 42;
    }
};
```

### [constexpr specifier](https://en.cppreference.com/w/cpp/language/constexpr.html) (C++11)

**Code-related Keywords:**
- `constexpr int x = 10;` - Compile-time constant
- `constexpr int func() { }` - Compile-time evaluable [function](../../07_functions/functions.md)
- `if constexpr` (C++17) - Compile-time conditional

**Theory Keywords:**
- **compile-time evaluation** - Computed at compile time when possible
- **constant expression** - Usable in contexts requiring constants (array sizes, [template](../../10_templates/templates.md) arguments)

**Example:**
```cpp
constexpr int factorial(int n) {  // Evaluated at compile time if possible
    return n <= 1 ? 1 : n * factorial(n - 1);
}

constexpr int f5 = factorial(5);  // Compile-time: f5 = 120
int arr[factorial(4)];            // Array size must be constant: arr[24]

int runtime_val = 5;
int f_runtime = factorial(runtime_val);  // Runtime evaluation (not constexpr context)

template<typename T>
auto getSize(T value) {
    if constexpr (sizeof(T) > 4) {  // C++17: compile-time branch
        return "large";
    } else {
        return "small";
    }
}
```

### [consteval specifier](https://en.cppreference.com/w/cpp/language/consteval.html) (C++20)

**Code-related Keywords:**
- `consteval int func() { }` - Must evaluate at compile time

**Theory Keywords:**
- **immediate function** - Always produces compile-time constants (C++20)
- **constexpr vs consteval** - consteval stricter (no runtime fallback)

**Example:**
```cpp
consteval int square(int x) {  // MUST be compile-time
    return x * x;
}

constexpr int s1 = square(5);  // OK: compile-time (25)
// int runtime = 5;
// int s2 = square(runtime);   // ERROR: consteval requires compile-time argument
```

### [constinit specifier](https://en.cppreference.com/w/cpp/language/constinit.html) (C++20)

**Code-related Keywords:**
- `constinit int x = 10;` - Constant initialization required (C++20)

**Theory Keywords:**
- **static initialization** - Ensures no runtime initialization overhead
- **non-const constinit** - Unlike constexpr, variable remains mutable

**Example:**
```cpp
constinit int globalCounter = 0;  // Initialized at compile time, but mutable
// constinit int bad = rand();    // ERROR: rand() not constant expression

void increment() {
    ++globalCounter;  // OK: constinit doesn't imply const (unlike constexpr)
}
```

### [alignas specifier](https://en.cppreference.com/w/cpp/language/alignas.html) (C++11)

**Code-related Keywords:**
- `alignas(16) int x;` - Specify alignment requirement
- `alignof(T)` - Query alignment of [type](../../02_types_and_objects/types.md)

**Theory Keywords:**
- **memory alignment** - Address must be multiple of specified bytes
- **SIMD optimization** - Aligned data for vector instructions

**Example:**
```cpp
#include <iostream>

alignas(16) int aligned;         // Align to 16-byte boundary
alignas(64) char cache_line[64]; // Cache line alignment

struct alignas(32) Vec4 {        // Struct aligned to 32 bytes
    float x, y, z, w;
};

std::cout << alignof(Vec4) << '\n';        // 32
std::cout << alignof(int) << '\n';         // 4 (typical)
std::cout << alignof(double) << '\n';      // 8 (typical)
```
