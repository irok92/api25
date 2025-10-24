# Expressions and Operators

## Overview
### [Expressions](https://en.cppreference.com/w/c/language/operators.html)
Sequence of operators and operands that compute a value.

Expressions combine operators and operands to compute values - they include arithmetic (`2 + 3`), comparisons (`x > 10`), assignments (`x = 5`), and function calls (`printf()`).
Every expression has a type and produces a value (or has side effects like modifying memory).

```c
int x = 2 + 3 * 4;        // Arithmetic
int *p = &x;              // Address-of
int y = *p > 10 ? 1 : 0;  // Dereference, comparison, conditional
```

## Expression Properties
### [Value categories](https://en.cppreference.com/w/c/language/value_category.html)
Lvalue (addressable) vs rvalue (temporary value).

Lvalues refer to memory locations and can appear on the left of assignments (like variables), while rvalues are temporary values like literals or computation results.
Understanding this matters because only lvalues can have their address taken with `&`, and some operations require lvalues.

- **Lvalue**: Expression that refers to memory location (can appear on left of assignment).
- **Rvalue**: Temporary value not associated with memory location (literals, computed results).
- Lvalues can be converted to rvalues (reading value), but not vice versa.
- Only lvalues can have their address taken with & operator.
```c
int x = 5;     // x is lvalue, 5 is rvalue
int *p = &x;   // OK: x is lvalue
// int *q = &5; // Error: 5 is rvalue, no address
```

### [Evaluation order and sequencing](https://en.cppreference.com/w/c/language/eval_order.html)
Order of side effects and sequence points.

Evaluation order determines when side effects (modifications, I/O) happen - sequence points (`;`, `&&`, `||`, `,`) guarantee all previous side effects complete before continuing.
Modifying the same variable twice between sequence points (like `i = i++`) causes undefined behavior, and function argument evaluation order is unspecified.

- **Side effect**: Modification of object or I/O operation (assignment, `++`, `--`, function calls).
- **Sequence point**: Point where all previous side effects are complete (;, &&, ||, ?:, comma).
- **Undefined behavior**: Modifying same variable twice between sequence points.
- **Unspecified order**: Function argument evaluation order is not defined by standard.
```c
int i = 0;
i = i++;              // Undefined behavior
int a = (i++, i++, i); // Comma: left-to-right, a = 2
f(i++, i++);          // Unspecified order of arguments
```

## Constants and Literals
### [Constants and literals](https://en.cppreference.com/w/c/language/operators.html#Constants_and_literals)
Fixed values in source code: integer, float, char, string.

Literals are fixed values written directly in code - integers (`42`, `0x1F`), floating-point (`3.14`, `1e-3`), characters (`'A'`, `L'€'`), and strings (`"text"`, `u8"UTF-8"`).
Each literal has a type determined by its form and optional suffix.

```c
42; 3.14; 'A'; "text"; 0x1F; 077; 1e-3; L'€'; u8"UTF-8";
```

### [Integer constants](https://en.cppreference.com/w/c/language/integer_constant.html)
Decimal, octal, hexadecimal, binary with optional suffix.

Integer literals can be decimal (`42`), octal (`052` - starts with `0`), hexadecimal (`0x2A` - starts with `0x`), or binary (`0b101010` - C23 only).
Suffixes (`L` for `long`, `U` for `unsigned`, `LL` for `long long`) specify the type explicitly.

- **Decimal**: Starts with non-zero digit (42, 100).
- **Octal**: Starts with 0 followed by octal digits 0-7 (052 = 42 decimal).
- **Hexadecimal**: Starts with 0x or 0X followed by digits 0-9, A-F (0x2A = 42 decimal).
- **Binary**: Starts with 0b or 0B (C23 only, 0b101010 = 42 decimal).
- **Suffixes**: L/l for long, U/u for unsigned, LL/ll for long long (can combine: ULL).
```c
int d = 42; long l = 42L; unsigned u = 42U;
int h = 0x2A; int o = 052; int b = 0b101010; // (C23)
```

### [Floating constants](https://en.cppreference.com/w/c/language/floating_constant.html)
Decimal or hexadecimal floating-point with optional suffix.
- **Decimal form**: Digits with decimal point and/or exponent (3.14, 1e-3, .5).
- **Hexadecimal form**: 0x prefix, binary exponent with p (0x1.5p2 = 1.5 × 2² = 6.0).
- **Suffixes**: f/F for float, l/L for long double, no suffix is double.
- **Scientific notation**: Use e or E for decimal exponent (1e-3 = 0.001).
```c
float f = 3.14f; double d = 2.718; long double ld = 1.0L;
double e = 1e-3; double h = 0x1.5p2; // 0x1.5 * 2^2 = 5.25
```
### [Character constants](https://en.cppreference.com/w/c/language/character_constant.html)
Single character in quotes with escape sequences.
```c
char c = 'A'; char n = '\n'; char h = '\x41'; // 'A'
wchar_t w = L'€'; char16_t c16 = u'α'; char32_t c32 = U'🙂';
```

### [true/false (C23)](https://en.cppreference.com/w/c/language/bool_constant.html)
Boolean literal constants true and false.
```c
bool b1 = true;  // bool is a keyword in C23
bool b2 = false;
if (b1) printf("true\n");
```

### [nullptr (C23)](https://en.cppreference.com/w/c/language/nullptr.html)
Null pointer constant literal.
```c
int *p = nullptr;         // C23: type-safe null pointer
void *v = nullptr;
if (p == nullptr) { /* ... */ }
```

### [String literals](https://en.cppreference.com/w/c/language/string_literal.html)
Null-terminated character arrays in quotes.
- **Null terminator**: '\0' automatically added at end (not counted in strlen).
- **Storage**: String literals have static storage duration (exist entire program).
- **Modifiable**: Writing to string literal is undefined behavior (may crash).
- **Prefixes**: L for wide strings, u8 for UTF-8, u for UTF-16, U for UTF-32.
- **Concatenation**: Adjacent string literals automatically merged: "ab" "cd" → "abcd".
```c
char *s = "hello";  // Type: char[6] (includes '\0')
wchar_t *w = L"wide"; char *u8 = u8"UTF-8";
char m[] = "line1\n" "line2"; // Concatenation
```

### [Compound literals (C99)](https://en.cppreference.com/w/c/language/compound_literal.html)
Unnamed objects created in-place with type and initializer.
- **Lifetime**: Automatic in block scope, static at file scope.
- **Lvalue**: Can take address with & operator.
- **Use case**: Creating temporary arrays/structs to pass to functions.
- **Syntax**: (type){initializer-list} creates unnamed object of specified type.
```c
int *p = (int[]){1, 2, 3};
struct Point {int x, y;} *pt = &(struct Point){.x=1, .y=2};
f((int[]){1, 2, 3}); // Pass array to function
```

## Type Conversions
### [Constant expressions](https://en.cppreference.com/w/c/language/constant_expression.html)
Expressions evaluated at compile-time.
```c
enum { SIZE = 10 * 20 };      // Constant expression
int arr[5 + 3];               // Array size must be constant
static int x = sizeof(int);   // OK: sizeof is constant
```

### [Implicit conversions](https://en.cppreference.com/w/c/language/conversion.html)
Automatic type conversions: promotion, usual arithmetic conversions.
- **Integer promotion**: Small integer types (char, short) promoted to int in expressions.
- **Usual arithmetic conversions**: Both operands converted to common type (e.g., int + float → float).
- **Narrowing**: Converting larger type to smaller may lose data (double → int truncates decimal).
- **Sign conversions**: Mixing signed/unsigned can produce unexpected results.
```c
int i = 3.14;      // float to int (truncation)
double d = 5;      // int to double (promotion)
char c = 300;      // Overflow: value wrapped
```

### [Cast operator](https://en.cppreference.com/w/c/language/cast.html)
Explicit type conversion with (type) syntax.
```c
int i = (int)3.14;
void *v = malloc(10); int *p = (int*)v;
char c = (char)((int)'A' + 1); // 'B'
```

## Operators
### [Operator precedence](https://en.cppreference.com/w/c/language/operator_precedence.html)
Order and associativity of operator evaluation.
- **Precedence**: Determines which operators execute first (*, / before +, -).
- **Associativity**: For same precedence, left-to-right or right-to-left (= is right-to-left).
- **Parentheses**: Override precedence (always use when unsure for clarity).
- **Common mistake**: Bitshift operators have lower precedence than arithmetic (+, -).
```c
int x = 2 + 3 * 4;    // * before +: x = 14
int y = 1 << 2 + 1;   // + before <<: y = 8
int z = (2 + 3) * 4;  // Parentheses: z = 20
```

### [Member access and indirection](https://en.cppreference.com/w/c/language/operator_member_access.html)
Access struct/union members and array elements.
```c
struct S { int x; } s = {5}, *p = &s;
int a = s.x;        // Direct member access
int b = p->x;       // Indirect member ((*p).x)
int arr[3] = {1,2,3}; int c = arr[1]; // Subscript
```

### [Logical operators](https://en.cppreference.com/w/c/language/operator_logical.html)
Boolean logic: && (and), || (or), ! (not), with short-circuit.
```c
int x = 1, y = 0;
if (x && y) { } // False: y not evaluated if x is false
if (x || y) { } // True: y not evaluated
if (!y) { }     // True: logical NOT
```

### [Comparison operators](https://en.cppreference.com/w/c/language/operator_comparison.html)
Relational: <, <=, >, >=; Equality: ==, !=.
```c
int a = 5, b = 10;
if (a < b) { }    // True
if (a == b) { }   // False
if (a != b) { }   // True
```

### [Arithmetic operators](https://en.cppreference.com/w/c/language/operator_arithmetic.html)
Math operations: +, -, *, /, % (modulo for integers).
```c
int x = 10 + 5; int y = 10 - 5; int z = 10 * 5;
int q = 10 / 3; // 3 (integer division)
int r = 10 % 3; // 1 (remainder)
```
### [Assignment operators](https://en.cppreference.com/w/c/language/operator_assignment.html)
Simple and compound assignment: =, +=, -=, *=, /=, %=, <<=, >>=, &=, ^=, |=.
```c
int x = 5;     // Simple assignment
x += 3;        // x = x + 3
x *= 2;        // x = x * 2
x &= 0x0F;     // x = x & 0x0F
```

### [Increment/decrement](https://en.cppreference.com/w/c/language/operator_incdec.html)
Pre/post increment (++) and decrement (--).
```c
int i = 5;
int a = i++;   // a = 5, i = 6 (post-increment)
int b = ++i;   // i = 7, b = 7 (pre-increment)
int c = i--;   // c = 7, i = 6 (post-decrement)
```

### [sizeof](https://en.cppreference.com/w/c/language/sizeof.html)
Size in bytes of type or object at compile-time.
```c
size_t s1 = sizeof(int);           // Size of type
int arr[10]; size_t s2 = sizeof(arr); // Size of object: 40
size_t s3 = sizeof arr[0];         // No parentheses needed
```

### [_Alignof (C11)](https://en.cppreference.com/w/c/language/alignof.html)
Alignment requirement of type in bytes.
```c
size_t a1 = _Alignof(char);     // Usually 1
size_t a2 = _Alignof(int);      // Usually 4
size_t a3 = _Alignof(double);   // Usually 8
```

### [Generic selection (C11)](https://en.cppreference.com/w/c/language/generic.html)
Type-generic expression selection at compile-time.
- **Type-safe macros**: Selects expression based on argument type.
- **Compile-time**: Type selection happens during compilation (no runtime overhead).
- **Use case**: Creating type-generic math functions or type-checking macros.
- **Syntax**: _Generic(expr, type1: result1, type2: result2, default: result).
```c
#define abs(x) _Generic((x), \
  int: abs, \
  float: fabsf, \
  double: fabs)(x)
int i = abs(-5); float f = abs(-3.14f);
```
