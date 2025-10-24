# Templates

## [Templates](https://en.cppreference.com/w/cpp/language/templates.html)

**Code-related Keywords:**
- `template<typename T>` - Template parameter
- `template<class T>` - Same as typename
- `template<int N>` - Non-type parameter
- `template<ConceptName T>` - Constrained parameter (C++20)
- Instantiation - Create concrete type/function from template

**Theory Keywords:**
- **generic programming** - Code that works with any [type](../../02_types_and_objects/types.md)
- **compile-time polymorphism** - Type-specific code generated at compile time
- **code generation** - Compiler generates code for each used type
- **template vs macro** - Templates are type-safe, macros are text replacement
- **SFINAE** - Substitution Failure Is Not An Error
- **concepts** - Named constraints on template parameters (C++20)

**Example:**
```cpp
// Function template:
template<typename T>
T max(T a, T b) {
    return a > b ? a : b;
}

int i = max(3, 5);        // max<int> instantiated
double d = max(1.5, 2.7); // max<double> instantiated

// Class template:
template<typename T>
class Stack {
    std::vector<T> data;
    
public:
    void push(T value) { data.push_back(value); }
    T pop() { T v = data.back(); data.pop_back(); return v; }
    bool empty() const { return data.empty(); }
};

Stack<int> intStack;      // Stack instantiated for int
intStack.push(10);
intStack.push(20);

Stack<std::string> strStack;  // Different instantiation
strStack.push("hello");

// Non-type template parameter:
template<typename T, int Size>
class Array {
    T data[Size];
    
public:
    T& operator[](int i) { return data[i]; }
    int size() const { return Size; }
};

Array<int, 10> arr;       // 10-element int array
arr[0] = 42;

// === C++20: Concepts (constraints on templates) ===
#include <concepts>

template<std::integral T>  // T must be an integral type
T add(T a, T b) {
    return a + b;
}

add(1, 2);                // OK: int is integral
// add(1.5, 2.5);         // Error: double is not integral

// See constraints_and_concepts.md for full coverage of C++20 concepts
```
