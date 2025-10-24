# Functions

## Overview
### [Functions](https://en.cppreference.com/w/c/language/functions.html)
Self-contained blocks of code with parameters and return value.

Functions are reusable code blocks that take parameters and return a value (or `void` for no return value).
Declare functions with prototypes before use, and define them with an implementation body.

```c
int add(int a, int b) { return a + b; }
void print_hello(void) { printf("Hello\n"); }
int (*fp)(int, int) = add; // Function pointer
```

## Function Declarations and Definitions
### [Function declaration](https://en.cppreference.com/w/c/language/function_declaration.html)
Prototype specifying name, parameters, and return type.

Function declarations (prototypes) tell the compiler about a function's signature before its definition - include return type, name, and parameter types (parameter names optional).
Use `void` in the parameter list (`int f(void)`) to explicitly indicate no parameters.

- **Prototype**: Informs compiler about function signature before definition.
- **Parameter names**: Optional in declaration but required in definition.
- **void parameter**: int f(void) means no parameters; int f() is old-style (avoid).
- **Multiple declarations**: Can declare same function multiple times (must match).
```c
int max(int a, int b);         // Declaration (prototype)
int max(int, int);             // Parameter names optional
extern int helper(void);       // Explicit extern
```

### [Function definition](https://en.cppreference.com/w/c/language/function_definition.html)
Complete implementation with body.

Function definitions provide the actual implementation with a body (`{ }` containing statements) - parameter names are required in definitions.
Each function can only be defined once (one definition rule), but can be declared multiple times.

```c
int max(int a, int b) {        // Definition
  return a > b ? a : b;
}
static void local(void) { }    // Internal linkage
```

## Function Specifiers
### [inline (C99)](https://en.cppreference.com/w/c/language/inline.html)
Hint to compiler to expand function at call site.
- **Optimization**: Replaces function call with actual code (eliminates call overhead).
- **Just a hint**: Compiler may ignore inline suggestion (especially for large functions).
- **Definition in header**: Often defined in header files with static inline.
- **Trade-off**: Reduces call overhead but increases code size (duplicates function body).
```c
inline int square(int x) { return x * x; }
static inline int fast(void) { return 42; }
// May avoid function call overhead
```

### [_Noreturn (C11) (deprecated in C23)](https://en.cppreference.com/w/c/language/noreturn.html)
Function never returns to caller (exits or loops forever).
```c
_Noreturn void fatal_error(const char *msg) {
  fprintf(stderr, "Error: %s\n", msg);
  exit(1);
}
```

## Variable Arguments
### [Variadic arguments](https://en.cppreference.com/w/c/language/variadic.html)
Functions accepting variable number of arguments.
- **... notation**: Indicates function accepts variable arguments (printf, scanf).
- **va_list**: Type for accessing variable arguments.
- **va_start**: Initialize va_list with last fixed parameter.
- **va_arg**: Retrieve next argument (must specify type).
- **va_end**: Clean up va_list (required before function returns).
- **Type safety**: No type checking; wrong type in va_arg causes undefined behavior.
```c
#include <stdarg.h>
int sum(int count, ...) {
  va_list args; va_start(args, count); int s = 0;
  for (int i = 0; i < count; i++) s += va_arg(args, int);
  va_end(args); return s;
}
```
