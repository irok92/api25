# Type specifiers

## Type specifiers

### [auto specifier](https://en.cppreference.com/w/cpp/language/auto.html) (C++11)

**Code-related Keywords:**
- `auto x = expr;` - Deduce [type](../../02_types_and_objects/types.md) from initializer (C++11)
- `auto& ref = x;` - Deduce reference type
- `auto*` - Deduce pointer type
- `decltype(auto)` (C++14) - Preserve exact type/value category

**Theory Keywords:**
- **type deduction** - Compiler infers type from initializer
- **template argument deduction** - Similar rules as template parameter deduction

**Example:**
```cpp
auto i = 42;              // int
auto d = 3.14;            // double
auto s = std::string("hello");  // std::string

std::vector<int> v = {1, 2, 3};
auto it = v.begin();      // std::vector<int>::iterator

auto& ref = i;            // int&: reference
ref = 100;                // Modifies i

const auto& cref = d;     // const double&

auto lambda = [](int x) { return x * 2; };  // Lambda type (unnamed)

// decltype(auto): preserves reference/cv-qualifiers
int x = 5;
int& getRef() { return x; }
auto a = getRef();        // int (copy)
decltype(auto) b = getRef();  // int& (preserves reference)
```

### [decltype specifier](https://en.cppreference.com/w/cpp/language/decltype.html) (C++11)

**Code-related Keywords:**
- `decltype(expr)` - Deduce type from [expression](../../04_expressions/expressions.md) (C++11)
- `decltype(auto)` (C++14) - Combine with auto

**Theory Keywords:**
- **unevaluated context** - Expression not executed, only analyzed
- **type query** - Get exact type including references/cv-qualifiers

**Example:**
```cpp
int x = 5;
decltype(x) y = 10;       // int y = 10

int& getRef() { return x; }
decltype(getRef()) z = x; // int& z = x

const int& cref = x;
decltype(cref) w = x;     // const int& w = x

// decltype(auto) for perfect forwarding:
template<typename F, typename... Args>
decltype(auto) wrapper(F&& f, Args&&... args) {
    return std::forward<F>(f)(std::forward<Args>(args)...);  // Preserve return type
}

// Use in trailing return type:
template<typename T, typename U>
auto add(T t, U u) -> decltype(t + u) {  // Return type of t+u
    return t + u;
}
```

### [Elaborated type specifier](https://en.cppreference.com/w/cpp/language/elaborated_type_specifier.html)

**Code-related Keywords:**
- `class ClassName` - Explicit class type specifier
- `struct StructName` - Explicit struct specifier
- `enum EnumName` - Explicit [enum](structured_bindings_and_enumerations.md) specifier
- `typename T::type` - Dependent type in [templates](../../10_templates/templates.md)

**Theory Keywords:**
- **disambiguation** - Clarify type vs variable name conflict
- **forward declaration** - Declare type before definition

**Example:**
```cpp
class MyClass;            // Forward declaration

void func(class MyClass* p);  // Elaborated: clarifies MyClass is a class

struct Point { int x, y; };
int Point = 10;           // Variable named Point (conflicts!)
struct Point p = {1, 2};  // Elaborated: refers to struct, not variable

enum Color { Red, Green };
enum Color c = Red;       // Elaborated (usually unnecessary)

// In templates (typename for dependent types):
template<typename T>
void process() {
    typename T::value_type v;  // typename: T::value_type is a type, not a value
}
```
