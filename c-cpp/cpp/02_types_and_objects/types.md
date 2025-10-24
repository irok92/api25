# Types

## [Types](https://en.cppreference.com/w/cpp/language/type-id.html)

**Code-related Keywords:**
- `int`, `float`, `double`, `char`, `bool` - Fundamental types
- `void` - Type representing absence of value
- `signed`, `unsigned` - Type modifiers for integers
- `short`, `long`, `long long` - Size modifiers for integers
- `sizeof(type)` - [Operator](../../04_expressions/operators.md) to get type size in bytes

**Theory Keywords:**
- **type system** - Rules for classifying values and expressions
- **type safety** - Prevention of type errors at compile time
- **type category** - Fundamental, compound, or user-defined

**Example:**
```cpp
int i = 42;                    // Signed integer (typically 4 bytes)
unsigned int ui = 100u;        // Unsigned integer (no negative values)
short s = 10;                  // Short integer (typically 2 bytes)
long l = 1000L;                // Long integer (at least 4 bytes)
long long ll = 1000000LL;      // Long long (at least 8 bytes)
float f = 3.14f;               // Single precision (typically 4 bytes)
double d = 3.14159;            // Double precision (typically 8 bytes)
char c = 'A';                  // Character (1 byte)
bool b = true;                 // Boolean (true or false)
void* ptr = &i;                // void pointer (type-erased pointer)
int size = sizeof(int);        // Get size of type (typically 4)
```

### [Fundamental types](https://en.cppreference.com/w/cpp/language/types.html)

**Code-related Keywords:**
- Integer types: `int`, `short`, `long`, `long long`
- Floating-point: `float`, `double`, `long double`
- Character: `char`, `wchar_t`, `char8_t`, `char16_t`, `char32_t` (C++11/20)
- Boolean: `bool`
- Void: `void`

**Theory Keywords:**
- **integer types** - Whole numbers (positive, negative, zero)
- **floating-point types** - Numbers with decimal points
- **precision** - Number of significant digits (float < double < long double)
- **range** - Minimum and maximum values a type can hold

**Example:**
```cpp
// Integer types
char c = 127;                  // Smallest: -128 to 127 (or 0 to 255 unsigned)
short s = 32767;               // Typically -32768 to 32767
int i = 2147483647;            // Typically ±2.1 billion
long l = 2147483647L;          // At least same as int
long long ll = 9223372036854775807LL;  // At least 64 bits

// Floating-point types
float f = 3.14f;               // ~7 decimal digits precision
double d = 3.14159265359;      // ~15 decimal digits precision
long double ld = 3.14159265359L;  // Extended precision (platform-dependent)

// Character types
char ascii = 'A';              // Basic character
wchar_t wide = L'한';          // Wide character (for Unicode)

// Boolean
bool flag = true;              // Only true or false values
```

### [Incomplete type](https://en.cppreference.com/w/cpp/language/incomplete_type.html)

**Code-related Keywords:**
- Forward [declaration](../../05_declarations/declarations.md): `class MyClass;`
- `void` - Incomplete type (cannot create variables of type void)
- Array with unknown bound: `int arr[];`

**Theory Keywords:**
- **incomplete type** - Type that is declared but not fully defined
- **forward declaration** - Declaring a type exists before defining it
- **use cases** - Pointers/references to incomplete types, breaking circular dependencies

**Example:**
```cpp
class Forward;                 // Forward declaration - incomplete type
class MyClass {
    Forward* ptr;              // OK: pointer to incomplete type
    // Forward obj;            // ERROR: cannot create object of incomplete type
    Forward& ref;              // OK: reference to incomplete type
};

class Forward {                // Now complete type (definition provided)
    int data;
};

extern int arr[];              // Incomplete: array of unknown size
// int x = sizeof(arr);        // ERROR: cannot use sizeof on incomplete type
int arr[10];                   // Now complete: size is known

void func(int param[]);        // OK: incomplete array type in parameter (treated as pointer)
```
