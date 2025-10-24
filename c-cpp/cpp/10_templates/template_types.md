# Template types

## Template types

### [Class template](https://en.cppreference.com/w/cpp/language/class_template.html)

**Code-related Keywords:**
- `template<typename T> class Name { };` - Class template [declaration](../../05_declarations/declarations.md)
- `Name<Type> obj;` - Instantiate template
- Member functions - Defined outside with `template<>`

**Theory Keywords:**
- **generic container** - Class for any type
- **instantiation** - Create concrete class from template
- **separate compilation** - Templates typically in headers

**Example:**
```cpp
// Class template:
template<typename T>
class Optional {
    T value;
    bool hasValue;
    
public:
    Optional() : hasValue(false) {}
    Optional(T v) : value(v), hasValue(true) {}
    
    bool has() const { return hasValue; }
    T get() const { return value; }
};

Optional<int> opt1(42);   // Optional instantiated for int
Optional<std::string> opt2("hello");  // For std::string

// Member function defined outside:
template<typename T>
class Vector {
    T* data;
    size_t sz;
    
public:
    Vector(size_t size);  // Declaration
    void push(T value);
};

template<typename T>
Vector<T>::Vector(size_t size) : sz(size), data(new T[size]) {}

template<typename T>
void Vector<T>::push(T value) { /* ... */ }

Vector<int> v(10);        // Instantiate Vector<int>
```

### [Function template](https://en.cppreference.com/w/cpp/language/function_template.html)

**Code-related Keywords:**
- `template<typename T> ReturnType func(T param)` - [Function](../../07_functions/functions.md) template
- Type deduction - Arguments infer template parameters
- `auto` return type - C++14 deduction

**Theory Keywords:**
- **generic algorithm** - Function for any type
- **overload resolution** - Templates participate in overloading

**Example:**
```cpp
// Function template:
template<typename T>
T max(T a, T b) {
    return a > b ? a : b;
}

int i = max(3, 5);        // Deduced: T = int
double d = max(1.5, 2.7); // Deduced: T = double

// Multiple type parameters:
template<typename T, typename U>
auto min(T a, U b) {      // C++14: auto return
    return a < b ? a : b;
}

auto m = min(10, 3.5);    // T = int, U = double, returns double

// Explicit template argument:
auto x = max<double>(3, 5.7);  // Force T = double

// With constraints:
template<typename Container>
void print(const Container& c) {
    for (const auto& elem : c) {
        std::cout << elem << ' ';
    }
}

std::vector<int> v = {1, 2, 3};
print(v);                 // Works with any iterable container
```

### [Variable template](https://en.cppreference.com/w/cpp/language/variable_template.html) (C++14)

**Code-related Keywords:**
- `template<typename T> constexpr T var = value;` - Variable template (C++14)

**Theory Keywords:**
- **generic constant** - Constant parameterized by type
- **type traits** - Common use case

**Example:**
```cpp
// Variable template (C++14):
template<typename T>
constexpr T pi = T(3.1415926535897932385);

float f = pi<float>;      // 3.14159f
double d = pi<double>;    // 3.1415926535897932385

// With std::is_pointer:
template<typename T>
constexpr bool is_pointer_v = std::is_pointer<T>::value;

static_assert(is_pointer_v<int*>);      // true
static_assert(!is_pointer_v<int>);      // true

// Custom variable template:
template<typename T>
constexpr size_t buffer_size = sizeof(T) * 1024;

constexpr size_t int_buf = buffer_size<int>;     // 4096 (typically)
constexpr size_t double_buf = buffer_size<double>;  // 8192 (typically)
```

### [Class member template](https://en.cppreference.com/w/cpp/language/member_template.html)

**Code-related Keywords:**
- Template member function - In non-template or template [class](../../09_classes/classes.md)
- `template<typename U>` inside class - Independent parameter

**Theory Keywords:**
- **member function template** - Generic method
- **independent instantiation** - Member instantiated separately from class

**Example:**
```cpp
// Member template in non-template class:
class Printer {
public:
    template<typename T>
    void print(T value) {
        std::cout << value << '\n';
    }
};

Printer p;
p.print(42);              // T = int
p.print("hello");         // T = const char*

// Member template in template class:
template<typename T>
class Container {
    T value;
    
public:
    Container(T v) : value(v) {}
    
    // Member template (different parameter U):
    template<typename U>
    Container(const Container<U>& other) {
        value = static_cast<T>(other.getValue());
    }
    
    T getValue() const { return value; }
};

Container<int> c1(42);
Container<double> c2(c1); // Convert int to double via member template
```
