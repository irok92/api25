# Template specialization

## Template specialization

### [Explicit specialization](https://en.cppreference.com/w/cpp/language/template_specialization.html)

**Code-related Keywords:**
- `template<> class Name<Type> { };` - Full specialization for class
- `template<> ReturnType func<Type>() { }` - Full specialization for function
- Override generic - Provide custom implementation

**Theory Keywords:**
- **template specialization** - Custom version for specific [type](../../02_types_and_objects/types.md)
- **optimization** - Type-specific efficient implementation
- **full specialization** - All template parameters specified

**Example:**
```cpp
// Generic template:
template<typename T>
class Storage {
    T value;
    
public:
    Storage(T v) : value(v) {}
    void print() { std::cout << value << '\n'; }
};

// Explicit specialization for bool:
template<>
class Storage<bool> {
    bool value;
    
public:
    Storage(bool v) : value(v) {}
    void print() { 
        std::cout << (value ? "true" : "false") << '\n';
    }
};

Storage<int> s1(42);      // Uses generic template
s1.print();               // "42"

Storage<bool> s2(true);   // Uses specialization
s2.print();               // "true"

// Function template specialization:
template<typename T>
T max(T a, T b) {
    return a > b ? a : b;
}

// Specialization for const char*:
template<>
const char* max<const char*>(const char* a, const char* b) {
    return strcmp(a, b) > 0 ? a : b;  // Compare strings, not pointers
}

auto m1 = max(3, 5);      // Generic: 5
auto m2 = max("abc", "xyz");  // Specialization: "xyz"
```

### [Partial specialization](https://en.cppreference.com/w/cpp/language/partial_specialization.html)

**Code-related Keywords:**
- `template<typename T> class Name<T*> { };` - Specialize for [pointers](../../05_declarations/compound_types.md)
- Only for classes - Function templates can't be partially specialized
- Pattern matching - More specific template

**Theory Keywords:**
- **partial specialization** - Specialize subset of parameters
- **pointer specialization** - Common pattern
- **const specialization** - Handle const types differently

**Example:**
```cpp
// Primary template:
template<typename T, typename U>
class Pair {
public:
    void print() { std::cout << "Generic pair\n"; }
};

// Partial specialization: same types
template<typename T>
class Pair<T, T> {
public:
    void print() { std::cout << "Same type pair\n"; }
};

// Partial specialization: pointer types
template<typename T, typename U>
class Pair<T*, U*> {
public:
    void print() { std::cout << "Pointer pair\n"; }
};

Pair<int, double> p1;     // Generic
p1.print();               // "Generic pair"

Pair<int, int> p2;        // Same type specialization
p2.print();               // "Same type pair"

Pair<int*, double*> p3;   // Pointer specialization
p3.print();               // "Pointer pair"

// Real-world: std::vector<bool> specialization
template<typename T>
class MyVector {
    T* data;
    // ...
};

// Specialization for bool (space-efficient bit packing):
template<>
class MyVector<bool> {
    unsigned char* bits;  // Pack 8 bools per byte
    // ...
};

// Another example: remove_const
template<typename T>
struct RemoveConst {
    using type = T;
};

template<typename T>
struct RemoveConst<const T> {  // Partial specialization for const T
    using type = T;
};

RemoveConst<int>::type x = 5;        // int
RemoveConst<const int>::type y = 10;  // int (const removed)
```
