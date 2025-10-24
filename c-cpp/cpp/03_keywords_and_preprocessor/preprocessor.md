# Preprocessor

## [Preprocessor](https://en.cppreference.com/w/cpp/preprocessor.html)

**Code-related Keywords:**
- `#include` - Include header files
- `#define` - Define macros
- `#ifdef`, `#ifndef`, `#if`, `#else`, `#elif`, `#endif` - Conditional compilation
- `#pragma` - Compiler-specific directives
- `__FILE__`, `__LINE__`, `__DATE__`, `__TIME__` - Predefined macros

**Theory Keywords:**
- **preprocessor** - Processes directives before compilation
- **text substitution** - Macros are literally replaced in code
- **conditional compilation** - Include/exclude code based on conditions

**Example:**
```cpp
#include <iostream>            // Include standard library header
#include "myheader.h"          // Include local header

#define PI 3.14159             // Simple macro (text substitution)
#define MAX(a, b) ((a) > (b) ? (a) : (b))  // Function-like macro (use with care!)

#ifdef DEBUG                   // If DEBUG is defined
    #define LOG(x) std::cout << x << '\n'
#else
    #define LOG(x)             // Empty macro when not debugging
#endif

int main() {
    double radius = 5.0;
    double area = PI * radius * radius;  // PI replaced with 3.14159
    int max_val = MAX(10, 20); // Expands to ((10) > (20) ? (10) : (20))
    LOG("Debug message");      // Only prints if DEBUG defined
}
```

### Conditional compilation

#### [#if - #ifdef - #ifndef - #elif](https://en.cppreference.com/w/cpp/preprocessor/conditional.html)

**Code-related Keywords:**
- `#ifdef NAME` - If NAME is defined
- `#ifndef NAME` - If NAME is not defined
- `#if expression` - If expression is true
- `#elif expression` - Else if
- `#else` - Otherwise
- `#endif` - End conditional block

**Example:**
```cpp
#define PLATFORM_WINDOWS       // Define platform macro

#ifdef PLATFORM_WINDOWS        // Check if defined
    #include <windows.h>
    // Windows-specific code
#endif

#ifndef CONFIG_H               // Include guard pattern
#define CONFIG_H
    // Header content
#endif

#if __cplusplus >= 201703L     // Check C++ version
    // C++17 or later code
#elif __cplusplus >= 201103L
    // C++11 or later code
#else
    #error "Requires C++11 or later"
#endif
```

#### [#elifdef - #elifndef](https://en.cppreference.com/w/cpp/preprocessor/conditional.html) (C++23)

**Code-related Keywords:**
- `#elifdef NAME` - Else if NAME is defined (C++23)
- `#elifndef NAME` - Else if NAME is not defined (C++23)

**Example:**
```cpp
#ifdef FEATURE_A
    // Code for feature A
#elifdef FEATURE_B             // C++23: cleaner than #elif defined(FEATURE_B)
    // Code for feature B
#elifndef FEATURE_C
    // Code when feature C is not defined
#else
    // Default code
#endif
```

### Macro definition and expansion

#### [#define - # - ##](https://en.cppreference.com/w/cpp/preprocessor/replace.html)

**Code-related Keywords:**
- `#define NAME value` - Define object-like macro
- `#define NAME(params) replacement` - Define function-like macro
- `#` - Stringification operator (converts parameter to string)
- `##` - Token pasting operator (concatenates tokens)
- `#undef NAME` - Undefine macro

**Example:**
```cpp
#define VERSION 100            // Object-like macro
#define SQUARE(x) ((x) * (x))  // Function-like macro (note parentheses!)

#define STR(x) #x              // Stringification: STR(hello) → "hello"
#define CONCAT(a, b) a##b      // Token pasting: CONCAT(x, 123) → x123

int main() {
    int v = VERSION;           // v = 100
    int sq = SQUARE(5);        // Expands to ((5) * (5)) = 25
    // int bad = SQUARE(2+3);  // Without parens: 2+3*2+3 = 11 (wrong!)
                               // With parens: ((2+3) * (2+3)) = 25 (correct!)
    
    const char* str = STR(hello world);  // "hello world"
    int x123 = 42;
    int val = CONCAT(x, 123);  // val = x123 = 42
}

#undef VERSION                 // Undefine VERSION
```

### File inclusion

#### [#include](https://en.cppreference.com/w/cpp/preprocessor/include.html)

**Code-related Keywords:**
- `#include <header>` - Include system/standard library header
- `#include "header"` - Include local project header

**Theory Keywords:**
- **search path** - `< >` searches system paths, `" "` searches local paths first
- **include guard** - Prevents multiple inclusion

**Example:**
```cpp
// myheader.h
#ifndef MYHEADER_H             // Include guard: check if not defined
#define MYHEADER_H             // Define it

void myFunction();             // Declaration

#endif                         // End include guard

// main.cpp
#include <iostream>            // System header (angle brackets)
#include "myheader.h"          // Local header (quotes)
#include "myheader.h"          // OK: include guard prevents redefinition

int main() {
    myFunction();              // Use function from myheader.h
}
```

### Implementation-defined behavior

#### [#pragma](https://en.cppreference.com/w/cpp/preprocessor/impl.html)

**Code-related Keywords:**
- `#pragma once` - Include guard (non-standard but widely supported)
- `#pragma pack` - Control structure packing
- `#pragma warning` - Control compiler warnings

**Theory Keywords:**
- **compiler-specific** - Behavior varies by compiler
- **portability** - May not work on all compilers

**Example:**
```cpp
// Modern include guard alternative
#pragma once                   // Simpler than #ifndef guards (most compilers support)

// Compiler-specific pragmas:
#pragma pack(push, 1)          // Pack structure without padding
struct Packed {
    char c;
    int i;                     // No padding between c and i
};
#pragma pack(pop)              // Restore default packing

#ifdef _MSC_VER                // Microsoft Visual C++
    #pragma warning(disable: 4996)  // Disable specific warning
#endif
```

### Line control

#### [#line](https://en.cppreference.com/w/cpp/preprocessor/line.html)

**Code-related Keywords:**
- `#line number` - Set line number
- `#line number "filename"` - Set line number and filename
- `__LINE__`, `__FILE__` - Macros for current line and file

**Theory Keywords:**
- **debug info** - Used by code generators to map back to original source

**Example:**
```cpp
#include <iostream>

int main() {
    std::cout << "Line: " << __LINE__ << '\n';  // Current line number
    
#line 100 "generated.cpp"      // Change line number and file for error messages
    std::cout << "Line: " << __LINE__ << '\n';  // Now reports as line 100
    std::cout << "File: " << __FILE__ << '\n';  // Now reports as "generated.cpp"
    
    // Useful for code generators to map errors back to original source
}
```

### Error and warning directives

#### [#error](https://en.cppreference.com/w/cpp/preprocessor/warning.html)

**Code-related Keywords:**
- `#error message` - Emit compilation error with message

**Theory Keywords:**
- **compile-time error** - Stops compilation with custom message

**Example:**
```cpp
#if __cplusplus < 201103L
    #error "This code requires C++11 or later"  // Stop compilation with error
#endif

#ifndef REQUIRED_MACRO
    #error "REQUIRED_MACRO must be defined"
#endif

// Useful for platform checks:
#if !defined(_WIN32) && !defined(__linux__) && !defined(__APPLE__)
    #error "Unsupported platform"
#endif
```

#### [#warning](https://en.cppreference.com/w/cpp/preprocessor/warning.html) (C++23)

**Code-related Keywords:**
- `#warning message` - Emit compilation warning with message (C++23)

**Theory Keywords:**
- **compile-time warning** - Continues compilation but shows message

**Example:**
```cpp
#ifdef EXPERIMENTAL_FEATURE
    #warning "Using experimental feature - may be unstable"  // Warning, not error
#endif

#if BUFFER_SIZE < 1024
    #warning "Buffer size is small, performance may be affected"
#endif

// Deprecation warnings:
#ifdef USE_OLD_API
    #warning "USE_OLD_API is deprecated, please use new API"
#endif
```
