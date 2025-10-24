# Basic Concepts

## General Reference
### [Basic concepts](https://en.cppreference.com/w/c/language/basic_concepts.html)
Core language fundamentals and terminology.

A C program is built from declarations (telling the compiler what exists), definitions (providing actual implementation), and statements (instructions to execute).
Think of declarations as a table of contents, definitions as the actual chapters, and statements as the sentences within those chapters.

- **Declaration**: Introduces a name and its type to the compiler.
- **Definition**: Provides the actual implementation or allocates storage.
- **Statement**: A complete instruction that performs an action.
```c
// Programs consist of declarations, definitions, statements
int main(void) { return 0; } // Simplest valid program
```

## Comments
### [Comments](https://en.cppreference.com/w/c/comment.html)
Single-line and multi-line comment syntax.

Comments are notes for humans that the compiler completely ignores - use `//` for single-line comments and `/* */` for multi-line comments.
Use them to explain *why* you did something, not *what* the code does (good code should be self-explanatory).

```c
// Single-line comment
/* Multi-line
   comment */
int x = 5; // Inline comment
```

## Character Sets and Encoding
### [ASCII chart](https://en.cppreference.com/w/c/language/ascii.html)
7-bit ASCII character encoding table.

ASCII maps each character to a number from 0 to 127 (e.g., `'A'` is 65, `'a'` is 97, `'0'` is 48).
C stores characters as these numeric values, which is why you can do arithmetic with them (`'A' + 1` gives `'B'`).

```c
char a = 'A';     // 65
char newline = '\n'; // 10
char null = '\0'; // 0 (string terminator)
```

### [Character sets and encodings](https://en.cppreference.com/w/c/language/charset.html)
Source and execution character sets.

Character encodings determine how characters are represented in memory - `char` typically uses ASCII, while `wchar_t` and Unicode prefixes (`u8""`, `u""`, `U""`) handle international characters.
Understanding these encodings matters when your program needs to work with text in multiple languages or display international characters correctly.

```c
char c = 'x';           // Basic character
wchar_t w = L'€';       // Wide character
char u8[] = u8"UTF-8";  // UTF-8 string (C11)
```

## Translation
### [Translation phases](https://en.cppreference.com/w/c/language/translation_phases.html)
Eight phases from source to executable: preprocessing, compilation, linking.

Converting your C source code into a running program happens in three main steps: **preprocessing** (expands `#include` and `#define`), **compilation** (translates C to machine code), and **linking** (combines your code with libraries like `printf`).
Understanding these phases helps you debug errors - a preprocessing error is different from a compilation error, which is different from a linker error.

- **Preprocessing**: Handles `#include`, `#define`, and other directives before compilation.
- **Compilation**: Converts C source code into assembly or machine code.
- **Linking**: Combines compiled object files and libraries into final executable.
```c
#include <stdio.h>  // Phase 4: preprocessing
#define MAX 100     // Phase 4: macro expansion
int main(void) { printf("%d", MAX); } // Phases 5-8: compile/link
```

## Syntax Elements
### [Punctuation](https://en.cppreference.com/w/c/language/punctuators.html)
Symbols with syntactic meaning: brackets, operators, delimiters.

Punctuators are special symbols that structure your code: `{ }` group statements into blocks, `( )` group expressions, `[ ]` access array elements, `;` ends statements, `.` accesses struct members, and `->` accesses members through a pointer.
Getting punctuation wrong is a common source of syntax errors for beginners.

```c
int a[5] = {1, 2, 3};  // [] {} , ;
struct S { int x; } s; // . ->
int *p = &a[0];        // * & []
```

## Identifiers and Naming
### [Identifier](https://en.cppreference.com/w/c/language/identifiers.html)
Names for variables, functions, types: letters, digits, underscore.

Identifiers are names for variables, functions, and other entities - they must start with a letter or underscore and can contain letters, digits, and underscores (no spaces or special characters).
C is case-sensitive (`total`, `Total`, and `TOTAL` are different), and you should choose meaningful names like `student_count` instead of cryptic ones like `sc`.

- **Must start with letter or underscore (not digit).
- Case-sensitive: `count` and `Count` are different identifiers.
- Cannot be a reserved keyword like `int`, `if`, `while`.
```c
int count, _private, value123; // Valid
// int 2bad, my-var; // Invalid: starts with digit, contains hyphen
```

### [Scope](https://en.cppreference.com/w/c/language/scope.html)
Visibility regions: block, file, function, function-prototype scope.

Scope determines where in your code you can use a particular variable - variables declared inside `{ }` braces (block scope) only exist within those braces, while variables declared outside all functions (file scope) are accessible throughout the file.
Inner scopes can "shadow" outer variables by declaring a new variable with the same name (usually confusing and best avoided).

- **Block scope**: Variable visible only within `{ }` braces where declared.
- **File scope**: Variable visible throughout entire source file.
- **Function-prototype scope**: Parameter names in function declarations (optional).
```c
int global;        // File scope
void f(int param) {// param: function-prototype/block scope
  int local;       // Block scope
  { int nested; }  // Nested block scope
}
```
### [Lifetime](https://en.cppreference.com/w/c/language/lifetime.html)
Duration of object existence: automatic, static, allocated, thread.

Lifetime defines how long a variable's memory exists - local variables have automatic lifetime (created and destroyed each time their block executes), while `static` variables exist for the entire program run and retain their values between function calls.
Dynamically allocated memory (from `malloc`) exists until you explicitly `free` it, giving you full control but also full responsibility.

- **Automatic**: Created when block entered, destroyed when exited (local variables).
- **Static**: Exists for entire program execution, initialized once.
- **Allocated**: Created with malloc/calloc, destroyed with free (manual control).
- **Thread**: Separate instance per thread (C11 with _Thread_local).
```c
static int s;       // Static lifetime: entire program
void f(void) {
  int auto_var;     // Automatic: function scope
  static int persistent = 0; // Static: persists across calls
}
```

### [Lookup and Name Spaces](https://en.cppreference.com/w/c/language/name_space.html)
Four separate namespaces: labels, tags, members, ordinary identifiers.

C has four separate namespaces, meaning the same name can be used for different things without conflict (e.g., you can have a `struct point`, a variable `point`, a goto label `point`, and a member `point` - they don't interfere).
This is why you can write `struct student student;` - the first `student` is a tag, the second is a variable name.

- **Label namespace**: Names for `goto` targets.
- **Tag namespace**: Names following struct, union, enum keywords.
- **Member namespace**: Struct/union member names (separate per struct/union).
- **Ordinary namespace**: Variables, functions, typedefs, enum constants.
```c
struct tag { int member; };  // tag: tag namespace
int tag;                     // tag: ordinary namespace (no conflict)
void f() { label: tag = 0; } // label: label namespace
```

## Type System
### [Type](https://en.cppreference.com/w/c/language/compatible_type.html)
Type compatibility rules for assignments and function calls.

Every variable has a type that determines valid operations and memory usage - type compatibility defines when two types can be used interchangeably (e.g., two structs are compatible only if they have the same members in the same order).
This matters when compiling files separately: a function declaration must be compatible with its definition, or the linker will connect them incorrectly.

- **Compatible types**: Two types that can be used interchangeably (same type structure).
- **Composite type**: Type formed when two compatible types are combined.
- Important for separate compilation and linking across translation units.
```c
int *p1;
int *p2;           // Compatible: same type
int (*f)(void);    // Function pointer type
int (*g)(void);    // Compatible with f
```

### [Arithmetic types](https://en.cppreference.com/w/c/language/arithmetic_types.html)
Integer (char, int, long) and floating-point (float, double) types.

Arithmetic types include integers (`char`, `short`, `int`, `long`, `long long`) for whole numbers and floating-point (`float`, `double`, `long double`) for decimals.
Signed overflow is undefined behavior, while unsigned overflow wraps around predictably (0 - 1 = maximum value).

- **Signed integers**: Can represent negative values (`char`, `short`, `int`, `long`, `long long`).
- **Unsigned integers**: Only non-negative values, wraps on overflow (unsigned int, size_t).
- **Floating-point**: Represents real numbers with decimal point (float, double, long double).
- **_Bool**: Boolean type, holds 0 (false) or 1 (true), spelled `bool` in C23.
```c
char c = 'A'; int i = -42; long l = 1000000L;
float f = 3.14f; double d = 2.718; _Bool b = 1;
unsigned u = 42u; size_t s = sizeof(int);
```

## Objects and Memory
### [Objects and Alignment](https://en.cppreference.com/w/c/language/object.html)
Region of storage with type, value, and alignment requirements.

In C, an "object" simply means a region of memory that stores a value - every variable is an object, and arrays/structs contain multiple objects as sub-objects.
Alignment refers to memory address requirements (e.g., `int` often needs 4-byte boundaries), and the compiler adds padding to satisfy these constraints, which is why `sizeof(struct)` might exceed the sum of its members' sizes.

- **Object**: Named region of memory that contains a value of a particular type.
- **Alignment**: Memory address requirement (e.g., int may need 4-byte boundary).
- **Sub-objects**: Members of structs/unions/arrays are objects themselves.
- Proper alignment improves CPU access speed and prevents crashes on some architectures.
```c
int obj = 42;              // Object with value
_Alignas(16) char buf[64]; // Object with specific alignment (C11)
struct S { char c; int i; } s; // Object with sub-objects
```

## Program Structure
### [The main function](https://en.cppreference.com/w/c/language/main_function.html)
Program entry point with optional arguments and return value.

The `main` function is where your program starts executing - it can accept command-line arguments through `argc` (count) and `argv` (array of strings).
The return value tells the OS whether your program succeeded (0) or failed (non-zero), which shell scripts can check.

- **argc**: Argument count (number of command-line arguments including program name).
- **argv**: Argument vector (array of strings containing the arguments).
- **Return value**: 0 indicates success, non-zero indicates error to operating system.
- `main(void)` for no arguments, `main(int argc, char *argv[])` for command-line args.
```c
int main(void) { return 0; }
int main(int argc, char *argv[]) { 
  return argc > 1 ? 1 : 0; // argc: count, argv: argument strings
}
```

### [As-if rule](https://en.cppreference.com/w/c/language/as_if.html)
Compiler may optimize as long as observable behavior is unchanged.

The as-if rule allows compilers to optimize your code (calculate at compile-time, reorder operations, eliminate unused code) as long as the program behaves "as if" it followed your source exactly.
What matters is "observable behavior" (I/O, `volatile` accesses, program termination) - anything the outside world can see must be preserved.

- **Observable behavior**: I/O operations, `volatile` accesses, program termination.
- Compiler can reorder, eliminate, or combine operations if results are identical.
- `volatile` prevents optimization to ensure memory access actually occurs.
- Allows aggressive optimizations while maintaining program correctness.
```c
int x = 1 + 2 * 3;    // May compute at compile-time
volatile int v = x;   // Must read/write (observable)
printf("%d", x + 0);  // May remove "+ 0" optimization
```
