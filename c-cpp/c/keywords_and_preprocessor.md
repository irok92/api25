# Keywords and Preprocessor

## Keywords
### [Keywords](https://en.cppreference.com/w/c/keyword.html)
Reserved words with special meaning: if, while, int, struct, etc.

Keywords are reserved words that have special meaning in C and cannot be used as identifiers (`int`, `if`, `while`, `struct`, `return`, etc.).
Each C standard adds new keywords - C99 added `inline` and `restrict`, C11 added `_Alignas` and `_Atomic`, C23 adds `typeof`.

```c
int auto_var = 0; auto register const volatile restrict;
struct typedef enum union sizeof return break continue;
```

## Preprocessor Overview
### [Preprocessor](https://en.cppreference.com/w/c/preprocessor.html)
Text manipulation before compilation: macros, includes, conditionals.

The preprocessor performs text manipulation before compilation - it handles `#include` (file insertion), `#define` (macro expansion), and `#if` (conditional compilation).
Preprocessor directives start with `#` and are processed in translation phase 4 before the compiler sees your code.

```c
#include <stdio.h>
#define MAX 100
#if defined(DEBUG)
  #define LOG(x) printf("%s\n", x)
#endif
```

## Conditional Compilation
### [#if - #ifdef - #ifndef - #elif](https://en.cppreference.com/w/c/preprocessor/conditional.html)
Conditional code inclusion based on preprocessor expressions.

Conditional compilation allows you to include or exclude code based on compile-time conditions - `#ifdef DEBUG` compiles debug code only when `DEBUG` is defined.
Common uses include platform-specific code, debug vs. release builds, and include guards (`#ifndef HEADER_H`).

- **#ifdef**: True if macro is defined (regardless of value).
- **#ifndef**: True if macro is not defined (common for include guards).
- **#if**: Evaluates integer constant expression (can use operators).
- **#elif**: Else-if for chaining conditions.
```c
#ifdef DEBUG
  printf("Debug mode\n");
#elif defined(RELEASE)
  printf("Release\n");
#else
  #ifndef NDEBUG
    printf("Default\n");
  #endif
#endif
```

### [#elifdef - #elifndef (C23)](https://en.cppreference.com/w/c/preprocessor/conditional.html)
Shorthand for #elif defined and #elif !defined.

C23 adds `#elifdef` (shorthand for `#elif defined`) and `#elifndef` (shorthand for `#elif !defined`) to make conditional chains more readable.
These replace the verbose `#elif defined(MACRO)` pattern with the cleaner `#elifdef MACRO`.

```c
#ifdef WINDOWS
  /* Windows code */
#elifdef LINUX
  /* Linux code */
#elifndef MACOS
  /* Not macOS code */
#endif
```

## Macro Definitions
### [#define - # - ##](https://en.cppreference.com/w/c/preprocessor/replace.html)
Object-like and function-like macros with stringification and concatenation.

Macros provide text replacement - object-like macros are simple constants (`#define MAX 100`), while function-like macros take parameters (`#define SQUARE(x) ((x)*(x))`).
The `#` operator stringifies (converts to string), and `##` concatenates tokens to create new identifiers.

- **Object-like macro**: Simple text replacement (e.g., `#define MAX 100`).
- **Function-like macro**: Takes parameters (always use parentheses: `((x) * (x))`).
- **# operator**: Converts macro parameter to string literal (stringification).
- **## operator**: Concatenates tokens to create new identifier (token pasting).
```c
#define MAX 100
#define SQUARE(x) ((x) * (x))
#define STR(x) #x           // Stringification: STR(test) -> "test"
#define CONCAT(a,b) a##b    // Token pasting: CONCAT(x,1) -> x1
```

## File Inclusion
### [#include](https://en.cppreference.com/w/c/preprocessor/include.html)
Insert contents of header file: <system> or "user" headers.

`#include` inserts the contents of a header file into your source - use `<brackets>` for system headers (searched in standard locations) and `"quotes"` for user headers (searched relative to current file first).
The preprocessor literally copies the entire file's contents at the `#include` location.

```c
#include <stdio.h>      // System header
#include "myheader.h"   // User header
#define HEADER "config.h"
#include HEADER         // Macro expansion
```

## Compiler Directives
### [#pragma](https://en.cppreference.com/w/c/preprocessor/impl.html)
Implementation-defined compiler instructions.

`#pragma` provides compiler-specific directives that control implementation-defined behavior (optimization, warnings, packing, etc.).
While non-standard, many pragmas are widely supported across compilers (`#pragma once` for include guards, `#pragma pack` for struct packing).

- **#pragma once**: Non-standard but widely supported alternative to include guards.
- **#pragma pack**: Controls structure member alignment/packing (compiler-specific).
- **_Pragma operator**: Allows pragmas inside macro definitions (C99).
- Different compilers support different pragmas; check compiler documentation.
```c
#pragma once                    // Include guard
#pragma pack(1)                 // Structure packing
#pragma GCC optimize("O3")      // GCC-specific
_Pragma("GCC diagnostic ignored \"-Wunused\"") // Operator form
```

### [#line](https://en.cppreference.com/w/c/preprocessor/line.html)
Change line number and filename for error messages.

`#line` changes the values reported by `__LINE__` and `__FILE__` macros, mainly used by code generators to report errors in the original source file rather than generated code.
For example, a preprocessor tool can use `#line` to map generated C code back to the original template file.

```c
#line 100                  // Line 100
#line 200 "custom.c"       // Line 200, file "custom.c"
printf("%d %s", __LINE__, __FILE__); // Reports modified values
```

## Diagnostics
### [#error](https://en.cppreference.com/w/c/preprocessor/warning.html)
Emit compilation error with message.

`#error` causes compilation to fail with a custom message - useful for detecting unsupported configurations at compile-time (e.g., checking for required macros or incompatible platforms).
`#warning` (C23/widely supported extension) emits a warning without stopping compilation.
```c
#ifndef CONFIG_H
  #error "config.h must be included first"
#endif
#if BUFFER_SIZE < 64
  #error Buffer size too small
#endif
```

### [#warning (C23)](https://en.cppreference.com/w/c/preprocessor/warning.html)
Emit compilation warning with message.

`#warning` (standardized in C23 but widely supported earlier as extension) emits a warning without stopping compilation - useful for deprecation notices or experimental feature alerts.
Unlike `#error`, the compilation continues after the warning is displayed.

```c
#warning "This code is deprecated"
#ifdef EXPERIMENTAL
  #warning Using experimental features
#endif
```

## Resource Embedding
### [#embed (C23)](https://en.cppreference.com/w/c/preprocessor/embed.html)
Embed binary file contents as array of integers.

`#embed` (new in C23) embeds binary file contents directly as an array initializer, making it easy to include resources like images, fonts, or config files in your executable.
This replaces the old practice of using external tools to convert binary data to C arrays.

```c
const unsigned char data[] = {
  #embed "image.png"
};
const int config[] = { #embed "config.bin" };
```
