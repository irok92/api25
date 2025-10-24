# Advanced template features

## Advanced template features

### [Parameter packs](https://en.cppreference.com/w/cpp/language/parameter_pack.html) (C++11)

**Code-related Keywords:**
- `template<typename... Args>` - Variadic template (C++11)
- `Args...` - Pack expansion
- `sizeof...(Args)` - Number of parameters
- Recursion - Process pack elements

**Theory Keywords:**
- **variadic template** - Accept any number of arguments
- **pack expansion** - Unpack arguments
- **template recursion** - Process one argument at a time

**Example:**
```cpp
// Variadic template:
template<typename... Args>
void print(Args... args) {
    (std::cout << ... << args) << '\n';  // C++17 fold expression
}

print(1, 2.5, "hello");   // Prints: 12.5hello

// sizeof... operator:
template<typename... Args>
void printCount(Args... args) {
    std::cout << "Count: " << sizeof...(Args) << '\n';
}

printCount(1, 2, 3, 4);   // "Count: 4"

// Recursive expansion (pre-C++17):
template<typename T>
void printRecursive(T value) {
    std::cout << value << '\n';  // Base case
}

template<typename T, typename... Args>
void printRecursive(T first, Args... rest) {
    std::cout << first << ' ';
    printRecursive(rest...);     // Recursive call
}

printRecursive(1, 2, 3, 4);  // "1 2 3 4"

// Perfect forwarding with pack:
template<typename... Args>
auto makeUnique(Args&&... args) {
    return std::make_unique<MyClass>(std::forward<Args>(args)...);
}

// Variadic class template:
template<typename... Types>
class Tuple;              // Declaration

template<>
class Tuple<> { };        // Empty tuple

template<typename Head, typename... Tail>
class Tuple<Head, Tail...> : Tuple<Tail...> {
    Head value;
public:
    Tuple(Head h, Tail... t) : Tuple<Tail...>(t...), value(h) {}
};
```

### [sizeof...](https://en.cppreference.com/w/cpp/language/sizeof....html) (C++11)

**Code-related Keywords:**
- `sizeof...(pack)` - Count elements in parameter pack (C++11)

**Theory Keywords:**
- **compile-time count** - Number of template arguments
- **pack size** - Variadic template argument count

**Example:**
```cpp
template<typename... Args>
constexpr size_t count(Args...) {
    return sizeof...(Args);   // Count arguments
}

constexpr size_t n = count(1, 2, 3, 4, 5);  // 5

// Use in static_assert:
template<typename T, typename... Args>
void checkCount(T first, Args... rest) {
    static_assert(sizeof...(Args) >= 2, "Need at least 3 arguments");
}

// Array size from pack:
template<typename... Args>
class Tuple {
    static constexpr size_t size = sizeof...(Args);
    
public:
    size_t getSize() const { return size; }
};

Tuple<int, double, char> t;
std::cout << t.getSize();  // 3
```

### [Fold expressions](https://en.cppreference.com/w/cpp/language/fold.html) (C++17)

**Code-related Keywords:**
- `(... op pack)` - Left fold (C++17)
- `(pack op ...)` - Right fold
- `(init op ... op pack)` - Fold with initial value
- [Operators](../../04_expressions/operators.md): `+`, `-`, `*`, `/`, `&&`, `||`, `,`, etc.

**Theory Keywords:**
- **fold expression** - Apply binary operator to pack (C++17)
- **variadic simplification** - Avoid recursion

**Example:**
```cpp
// Sum with fold (C++17):
template<typename... Args>
auto sum(Args... args) {
    return (args + ...);      // Right fold: ((a1 + a2) + a3) + ...
}

auto s = sum(1, 2, 3, 4, 5);  // 15

// Logical AND fold:
template<typename... Args>
bool allTrue(Args... args) {
    return (args && ...);     // Right fold
}

bool b = allTrue(true, true, false);  // false

// Print with comma operator:
template<typename... Args>
void print(Args... args) {
    (std::cout << ... << args) << '\n';  // Left fold
}

print(1, ' ', 2, ' ', 3);  // "1 2 3"

// With initial value:
template<typename... Args>
auto product(Args... args) {
    return (1 * ... * args);  // Fold with init: 1 * (a1 * a2 * ...)
}

auto p = product(2, 3, 4);  // 24

// Complex example: checking all types:
template<typename... Args>
bool allIntegers() {
    return (std::is_integral_v<Args> && ...);  // AND fold
}

static_assert(allIntegers<int, char, short>());      // true
static_assert(!allIntegers<int, double, char>());    // false
```
