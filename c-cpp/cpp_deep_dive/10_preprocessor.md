# C++ Deep Dive: Preprocessor

The C++ preprocessor is a program that processes the source code *before* it is passed to the compiler. It operates on directives, which are lines starting with `#`. The preprocessor is a powerful tool for conditional compilation, macro definitions, and including files, but it is purely text-based and has no knowledge of C++ syntax.

## 1. `#include`

This directive tells the preprocessor to insert the contents of another file into the current file.

- **`#include <header>`**: Searches for the file in the standard system directories. Used for standard library and third-party library headers.
    ```cpp
    #include <iostream>
    #include <vector>
    ```
- **`#include "header"`**: Searches for the file first in the same directory as the current file, and then in the standard system directories. Used for your own project's header files.
    ```cpp
    #include "my_class.h"
    ```

## 2. `#define` and `#undef`

- **`#define`**: Defines a preprocessor macro.
    - **Object-like macros**: Replaces an identifier with a token string.
        ```cpp
        #define PI 3.14159
        double circumference = 2 * PI * radius;
        ```
    - **Function-like macros**: Can take arguments, making them look like functions.
        ```cpp
        #define MAX(a, b) ((a) > (b) ? (a) : (b))
        int largest = MAX(x, y);
        ```
        **Warning**: Always wrap macro arguments and the entire macro body in parentheses to avoid operator precedence issues.
- **`#undef`**: Undefines a macro.
    ```cpp
    #undef PI
    ```

## 3. Conditional Compilation

These directives allow you to include or exclude parts of the code from a compilation based on certain conditions. This is commonly used for platform-specific code, debugging builds, or managing different feature sets.

- **`#if`, `#elif`, `#else`, `#endif`**: General conditional compilation based on a constant expression.
    ```cpp
    #define VERSION 2

    #if VERSION > 2
        // Code for versions > 2
    #elif VERSION == 2
        // Code for version 2
    #else
        // Code for older versions
    #endif
    ```
- **`#ifdef` and `#ifndef`**: Checks if a macro is defined (`#ifdef`) or not defined (`#ifndef`).
    ```cpp
    #define DEBUG

    #ifdef DEBUG
        std::cerr << "Debugging info" << std::endl;
    #endif

    #ifndef RELEASE
        // This code is compiled only if RELEASE is not defined
    #endif
    ```
- **`defined()` operator**: Can be used within an `#if` or `#elif` to check for macro definitions. It's more flexible than `#ifdef`.
    ```cpp
    #if defined(WINDOWS) && defined(X64)
        // Code for 64-bit Windows
    #endif
    ```

## 4. `#error` and `#warning`

- **`#error`**: Generates a fatal compilation error with a specified message.
    ```cpp
    #if !defined(__cplusplus)
        #error "A C++ compiler is required."
    #endif
    ```
- **`#warning`**: Generates a compiler warning with a specified message (non-standard but widely supported).
    ```cpp
    #warning "This feature is deprecated."
    ```

## 5. `#pragma`

Provides additional information to the compiler for implementation-specific features. Its behavior is compiler-dependent.

- **`#pragma once`**: A non-standard but widely used directive that serves as an include guard, ensuring a header file is included only once per compilation unit.
    ```cpp
    #pragma once

    // Header file content
    ```
- **Other pragmas**: Can control optimizations, packing alignment, and other compiler-specific behaviors (e.g., `#pragma pack(1)`).

## 6. Predefined Macros

C++ specifies several predefined macros that provide useful information.

- **`__cplusplus`**: An integer literal representing the version of the C++ standard (e.g., `202002L` for C++20).
- **`__FILE__`**: A string literal for the name of the current source file.
- **`__LINE__`**: An integer literal for the current line number.
- **`__DATE__`**: A string literal for the compilation date.
- **`__TIME__`**: A string literal for the compilation time.

```cpp
std::cout << "Compiled on " << __DATE__ << " at " << __TIME__ << std::endl;
```
