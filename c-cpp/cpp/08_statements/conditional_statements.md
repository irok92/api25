# Conditional statements

## Conditional statements

### [if](https://en.cppreference.com/w/cpp/language/if.html)

**Code-related Keywords:**
- `if (condition) { }` - Conditional execution
- `else if (condition) { }` - Additional condition
- `else { }` - Default case
- `if (init; condition)` (C++17) - Init statement in if

**Theory Keywords:**
- **boolean context** - Condition converted to bool
- **short-circuit** - else not evaluated if if is true

**Example:**
```cpp
int x = 10;

// Basic if:
if (x > 0) {
    std::cout << "positive\n";
}

// if-else:
if (x > 0) {
    std::cout << "positive\n";
} else {
    std::cout << "non-positive\n";
}

// if-else if-else:
if (x > 0) {
    std::cout << "positive\n";
} else if (x < 0) {
    std::cout << "negative\n";
} else {
    std::cout << "zero\n";
}

// C++17 init statement:
if (auto it = map.find(key); it != map.end()) {  // it scoped to if
    std::cout << it->second;
}
```

#### [if constexpr](https://en.cppreference.com/w/cpp/language/if.html#Constexpr_if) (C++17)

**Code-related Keywords:**
- `if constexpr (condition) { }` - Compile-time branch (C++17)

**Theory Keywords:**
- **compile-time evaluation** - Only chosen branch compiled
- **template metaprogramming** - Common in [templates](../../10_templates/templates.md)

**Example:**
```cpp
template<typename T>
auto getValue(T value) {
    if constexpr (std::is_pointer_v<T>) {  // Compile-time check
        return *value;        // Only compiled if T is pointer
    } else {
        return value;         // Only compiled if T is not pointer
    }
}

int x = 10;
int* p = &x;

auto v1 = getValue(5);    // Returns 5 (non-pointer branch)
auto v2 = getValue(p);    // Returns 10 (pointer branch, dereferences)
```

#### [if consteval](https://en.cppreference.com/w/cpp/language/if.html#Consteval_if) (C++23)

**Code-related Keywords:**
- `if consteval { }` - Check if constant evaluation context (C++23)

**Theory Keywords:**
- **constant evaluation** - Code running at compile time
- **runtime fallback** - Different behavior for runtime vs compile-time

**Example:**
```cpp
constexpr int compute(int x) {
    if consteval {            // C++23: compile-time path
        return x * 2;
    } else {                  // Runtime path
        return x * 3;
    }
}

constexpr int a = compute(5);  // Compile-time: 10
int b = compute(5);            // Runtime: 15
```

### [switch](https://en.cppreference.com/w/cpp/language/switch.html)

**Code-related Keywords:**
- `switch (expr) { }` - Multi-way branch
- `case value:` - Match specific value
- `default:` - Fallback case
- `break;` - Exit switch
- `[[fallthrough]]` - Intentional fallthrough (C++17)

**Theory Keywords:**
- **fallthrough** - Execution continues to next case without break
- **integral types** - Switch expression must be integer/[enum](../../05_declarations/structured_bindings_and_enumerations.md)

**Example:**
```cpp
int x = 2;

switch (x) {
    case 1:
        std::cout << "one\n";
        break;              // Exit switch
    
    case 2:
        std::cout << "two\n";
        [[fallthrough]];    // C++17: intentional fallthrough
    
    case 3:
        std::cout << "two or three\n";
        break;
    
    default:
        std::cout << "other\n";
        break;
}

// C++17 init statement:
switch (auto val = getValue(); val) {  // val scoped to switch
    case 0: break;
    case 1: break;
    default: break;
}

// With enum:
enum Color { Red, Green, Blue };
Color c = Green;

switch (c) {
    case Red:   std::cout << "red\n"; break;
    case Green: std::cout << "green\n"; break;
    case Blue:  std::cout << "blue\n"; break;
}
```
