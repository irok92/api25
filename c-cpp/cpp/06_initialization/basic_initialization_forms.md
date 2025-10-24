# Basic initialization forms

## Basic initialization forms

### [Default-initialization](https://en.cppreference.com/w/cpp/language/default_initialization.html)

**Code-related Keywords:**
- `T obj;` - Default init (indeterminate for primitives)
- `new T;` - Dynamic default init

**Theory Keywords:**
- **indeterminate value** - Uninitialized built-in [types](../../02_types_and_objects/types.md) (undefined behavior if used)
- **default constructor** - Called for [class](../../09_classes/classes.md) types

**Example:**
```cpp
int x;                    // Indeterminate value (garbage)
std::string s;            // Calls default constructor: s = ""

struct Point { int x, y; };
Point p;                  // Members x, y indeterminate
```

### [Value-initialization](https://en.cppreference.com/w/cpp/language/value_initialization.html)

**Code-related Keywords:**
- `T obj{};` - Value init (zero for primitives)
- `T()` - Temporary value init
- `new T()` - Dynamic value init

**Theory Keywords:**
- **zero initialization** - Built-ins set to zero
- **default construction** - Classes use default constructor

**Example:**
```cpp
int x{};                  // 0
int* p = new int();       // *p = 0
std::string s{};          // "" (default constructor)
```

### [Copy-initialization](https://en.cppreference.com/w/cpp/language/copy_initialization.html)

**Code-related Keywords:**
- `T obj = value;` - Copy init syntax
- `explicit` - Prevent implicit [conversion](../../04_expressions/conversions.md)

**Theory Keywords:**
- **copy constructor** - May be called (or elided)
- **implicit conversion** - Allowed unless constructor marked explicit

**Example:**
```cpp
int x = 42;               // Copy from literal
std::string s = "hi";     // Implicit conversion from const char*

struct Foo {
    Foo(int) { }          // Allows: Foo f = 10;
};
Foo f1 = 10;              // OK: implicit conversion

struct Bar {
    explicit Bar(int) { } // Disallows: Bar b = 10;
};
// Bar b1 = 10;           // ERROR: explicit constructor
Bar b2(10);               // OK: direct init
```

### [Direct-initialization](https://en.cppreference.com/w/cpp/language/direct_initialization.html)

**Code-related Keywords:**
- `T obj(args);` - Direct init with parentheses
- `T obj{args};` - Direct list init

**Theory Keywords:**
- **explicit allowed** - Can call explicit constructors
- **narrowing allowed** - With parentheses (not braces)

**Example:**
```cpp
int x(42);                // Direct
std::string s("hello");

struct Foo {
    explicit Foo(int) { }
};
Foo f(10);                // OK: direct init allows explicit
```

### [Aggregate initialization](https://en.cppreference.com/w/cpp/language/aggregate_initialization.html)

**Code-related Keywords:**
- `T obj = {v1, v2};` - Initialize aggregate members
- `T obj{v1, v2};` - C++11 uniform syntax

**Theory Keywords:**
- **aggregate** - Array or struct with no user-declared constructors, no private/protected members
- **designated initializers** - Named member init (C++20)

**Example:**
```cpp
int arr[] = {1, 2, 3};    // Array aggregate

struct Point { int x, y; };
Point p1 = {10, 20};      // x=10, y=20
Point p2{30, 40};         // C++11

// C++20 designated initializers:
Point p3{.x = 5, .y = 15};
```

### [List-initialization](https://en.cppreference.com/w/cpp/language/list_initialization.html) (C++11)

**Code-related Keywords:**
- `T obj{args};` - Direct list init
- `T obj = {args};` - Copy list init
- `std::initializer_list<T>` - Constructor parameter for list init

**Theory Keywords:**
- **narrowing prevention** - Compile error on lossy conversions
- **uniform initialization** - Single syntax for all types

**Example:**
```cpp
int x{42};                // Direct list init
int y = {42};             // Copy list init

// Narrowing prevention:
int a = 1000;
// char c{a};             // ERROR: narrowing
char d{100};              // OK

std::vector<int> v{1, 2, 3};  // Calls constructor with initializer_list

// Custom class:
struct Foo {
    Foo(std::initializer_list<int> list) { }
};
Foo f{1, 2, 3};           // Calls initializer_list constructor
```

### [Reference initialization](https://en.cppreference.com/w/cpp/language/reference_initialization.html)

**Code-related Keywords:**
- `T& ref = obj;` - Lvalue [reference](../../05_declarations/compound_types.md) init
- `const T& ref = value;` - Bind to temporary
- `T&& ref = value;` - Rvalue reference (C++11)

**Theory Keywords:**
- **lifetime extension** - Temporary lives as long as const reference
- **lvalue vs rvalue** - Reference type determines what can bind

**Example:**
```cpp
int x = 10;
int& ref = x;             // Lvalue reference
ref = 20;                 // Modifies x

// const T& binds to temporary:
const int& cref = 42;     // Temporary lifetime extended
// cref = 10;             // ERROR: const

// Rvalue reference (C++11):
int&& rref = 42;          // Binds to temporary
rref = 100;               // OK: modifies temporary

std::string s = "hello";
// std::string&& bad = s; // ERROR: s is lvalue
std::string&& good = std::move(s);  // std::move casts to rvalue
```
