# Structured bindings and enumerations

## Structured bindings and enumerations

### [Structured bindings](https://en.cppreference.com/w/cpp/language/structured_binding.html) (C++17)

**Code-related Keywords:**
- `auto [a, b, c] = tuple;` - Decompose tuple/struct/array
- `auto& [x, y] = pair;` - Bind by reference
- `const auto& [...]` - Const reference binding
- `auto [...pack] = expr;` - Structured binding pack (C++26)
- `[[attr]] auto [x, y]` - Attributes on bindings (C++26)
- `static auto [...]` - Static storage duration (C++20)

**Theory Keywords:**
- **structured binding** - Unpack multiple values at once (C++17)
- **decomposition** - Break apart aggregates into individual variables
- **binding process** - Three cases: arrays, tuple-like types, data members
- **referenced type** - Type returned by decltype on binding

**Example:**
```cpp
#include <tuple>
#include <map>

// === Basic decomposition (C++17) ===
std::tuple<int, double, std::string> getTuple() {
    return {42, 3.14, "hello"};
}

auto [i, d, s] = getTuple();   // Decompose: i=42, d=3.14, s="hello"

struct Point { int x, y; };
Point p = {10, 20};
auto [px, py] = p;             // Decompose struct: px=10, py=20

int arr[3] = {1, 2, 3};
auto [a, b, c] = arr;          // Decompose array: a=1, b=2, c=3

// Reference bindings:
auto& [rx, ry] = p;            // References to p.x and p.y
rx = 30;                       // Modifies p.x
std::cout << p.x;              // 30

// Const reference (extends lifetime of temporary):
const auto& [ti, td, ts] = getTuple();  // OK, temporary lifetime extended

// === With containers ===
std::map<int, std::string> m = {{1, "one"}, {2, "two"}};
for (const auto& [key, value] : m) {  // Decompose pair in range-for
    std::cout << key << ": " << value << '\n';
}

// === Three binding cases ===

// Case 1: Array binding
double values[2] = {1.5, 2.5};
auto [v1, v2] = values;        // v1 and v2 are copies

// Case 2: Tuple-like (requires std::tuple_size and std::tuple_element)
std::pair<int, float> pr{42, 3.14f};
auto [first, second] = pr;     // Uses get<0> and get<1>

// Case 3: Public data members
struct Data {
    int a;
    double b;
    std::string c;
};
Data d{1, 2.0, "test"};
auto [da, db, dc] = d;         // Binds to a, b, c in declaration order

// === C++20: Static storage duration ===
static auto [sx, sy] = Point{100, 200};  // Static lifetime

// === C++26: Structured binding packs (proposed) ===
// auto [first, ...rest] = getTuple();     // first=42, rest contains {3.14, "hello"}
// auto [...all] = getTuple();             // all is empty or contains all elements

// === decltype on bindings ===
auto [x, y] = Point{5, 10};
// decltype(x) is int (referenced type)
// decltype((x)) is int& (lvalue expression)

// === Bit-fields ===
struct Flags {
    unsigned int a : 4;
    unsigned int b : 4;
};
Flags f{3, 5};
auto [fa, fb] = f;             // fa=3, fb=5 (copies of bit-fields)
```

### [Enumerations and enumerators](https://en.cppreference.com/w/cpp/language/enum.html)

**Code-related Keywords:**
- `enum Name { A, B, C };` - Unscoped enum
- `enum class Name { A, B };` - Scoped enum (C++11)
- `enum Name : int { };` - Specify underlying [type](../../02_types_and_objects/types.md)

**Theory Keywords:**
- **enumeration** - Named integer constants
- **scoped** - Enumerators in enum's scope (C++11, safer)
- **unscoped** - Enumerators in enclosing scope (legacy, implicit conversion)

**Example:**
```cpp
// Unscoped enum (old style):
enum Color { Red, Green, Blue };  // Red=0, Green=1, Blue=2
Color c = Red;                 // Enumerator in enclosing scope
int val = Green;               // Implicit conversion to int (1)

// Scoped enum (C++11, preferred):
enum class Status { Ok, Error, Pending };
Status s = Status::Ok;         // Must use Status:: prefix
// int x = Status::Error;      // ERROR: no implicit conversion
int y = static_cast<int>(Status::Pending);  // Explicit cast: 2

// Custom values and underlying type:
enum class Priority : char {   // Underlying type: char
    Low = 1,
    Medium = 5,
    High = 10
};

// Use in switch:
switch (s) {
    case Status::Ok: break;
    case Status::Error: break;
    case Status::Pending: break;
}
```
