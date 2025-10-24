# Miscellaneous

## Miscellaneous

### [History of C++](https://en.cppreference.com/w/cpp/language/history.html)

**Theory Keywords:**
- **C++98/03** - First ISO standard
- **C++11** - Major update (move semantics, [lambdas](../../07_functions/functions.md), auto)
- **C++14** - Refinements (generic lambdas, variable [templates](../../10_templates/templates.md))
- **C++17** - Structured bindings, if constexpr, CTAD
- **C++20** - Concepts, ranges, [coroutines](../../07_functions/advanced_function_types.md), modules
- **C++23/26** - Ongoing evolution

**Example:**
```cpp
// C++98: verbose
std::vector<int>::iterator it = v.begin();

// C++11: auto
auto it = v.begin();

// C++11: lambda
std::sort(v.begin(), v.end(), [](int a, int b) { return a > b; });

// C++17: structured bindings
auto [x, y] = std::make_pair(1, 2);

// C++20: concepts
template<std::integral T>
T add(T a, T b) { return a + b; }
```

### [Extending the namespace std](https://en.cppreference.com/w/cpp/language/extending_std.html)

**Code-related Keywords:**
- `namespace std { }` - Standard [namespace](../../05_declarations/namespaces.md)
- Specialization - Allowed for user [types](../../02_types_and_objects/types.md)
- Adding - Generally forbidden

**Theory Keywords:**
- **undefined behavior** - Adding to std (except specializations)
- **allowed** - Template specializations for user types
- **forbidden** - New names in std

**Example:**
```cpp
// ALLOWED: specialize std templates for user types
struct MyType { int value; };

namespace std {
    // OK: specialize std::hash for MyType
    template<>
    struct hash<MyType> {
        size_t operator()(const MyType& t) const {
            return std::hash<int>{}(t.value);
        }
    };
}

std::unordered_map<MyType, std::string> map;  // Uses custom hash

// FORBIDDEN (undefined behavior):
// namespace std {
//     void myFunc() { }  // ERROR: adding to std
// }
```

### Acronyms

#### [AFO - Algorithm function objects](https://en.cppreference.com/w/cpp/algorithm/ranges.html#Algorithm_function_objects)

**Theory Keywords:**
- **C++20 ranges** - Algorithm objects (not [functions](../../07_functions/functions.md))

#### [CPO - Customization Point Objects](https://en.cppreference.com/w/cpp/ranges/cpo.html)

**Theory Keywords:**
- **C++20** - Objects for customizing behavior

#### [IFNDR - Ill-formed, No Diagnostic Required](https://en.cppreference.com/w/cpp/ndr.html)

**Theory Keywords:**
- **ill-formed** - Invalid code, compiler not required to error

#### [NDR - No Diagnostic Required](https://en.cppreference.com/w/cpp/ndr.html)

**Theory Keywords:**
- **optional diagnostic** - Compiler may or may not warn

#### [NTBS - Null-Terminated Byte String](https://en.cppreference.com/w/cpp/string/byte.html)

**Code-related Keywords:**
- `const char*` - C-style string ending with `\0`

**Example:**
```cpp
const char* ntbs = "hello";  // Null-terminated: "hello\0"
```

#### [NTTP - Non-Type Template Parameter](https://en.cppreference.com/w/cpp/language/template_parameters.html#Constant_template_parameter)

**Code-related Keywords:**
- `template<int N>` - Template parameter is value, not type

**Example:**
```cpp
template<int Size>
class Array { int data[Size]; };

Array<10> arr;            // Size = 10 (non-type parameter)
```

#### [RAO - Range Adaptor Objects](https://en.cppreference.com/w/cpp/ranges.html#Range_adaptor_objects)

**Theory Keywords:**
- **C++20 ranges** - Pipeline-style range transformation

**Example:**
```cpp
// C++20:
// auto result = v | std::views::filter(pred) | std::views::transform(func);
```

#### [SOCCC - select_on_container_copy_construction](https://en.cppreference.com/w/cpp/memory/allocator_traits/select_on_container_copy_construction.html)

**Theory Keywords:**
- **allocator trait** - How allocator copied with container

#### [TMP - Template Metaprogramming](https://en.cppreference.com/w/cpp/language/templates.html)

**Theory Keywords:**
- **compile-time computation** - Using templates for computation

**Example:**
```cpp
// Compile-time factorial:
template<int N>
struct Factorial {
    static constexpr int value = N * Factorial<N-1>::value;
};

template<>
struct Factorial<0> { static constexpr int value = 1; };

constexpr int f5 = Factorial<5>::value;  // 120 at compile time
```
