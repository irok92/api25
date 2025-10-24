# Conversion functions

## Conversion functions

### [Converting constructor](https://en.cppreference.com/w/cpp/language/converting_constructor.html)

**Code-related Keywords:**
- Single-parameter constructor - Enables implicit [conversion](../../04_expressions/conversions.md)
- `explicit` - Disable implicit conversion

**Theory Keywords:**
- **implicit conversion** - Automatic [type](../../02_types_and_objects/types.md) conversion
- **constructor as converter** - From parameter type to class type

**Example:**
```cpp
class String {
    std::string data;
    
public:
    String(const char* s) : data(s) {}  // Converting constructor
    
    void print() const { std::cout << data; }
};

void process(String s) {
    s.print();
}

process("hello");         // Implicit: const char* -> String
String s = "world";       // Implicit conversion

// Explicit disables implicit:
class ExplicitString {
    std::string data;
    
public:
    explicit ExplicitString(const char* s) : data(s) {}
};

// ExplicitString es = "hi";  // ERROR: no implicit conversion
ExplicitString es("hi");  // OK: direct initialization
// process(ExplicitString("test"));  // Would need explicit construction
```

### [Conversion function](https://en.cppreference.com/w/cpp/language/cast_operator.html)

**Code-related Keywords:**
- `operator Type() const` - Conversion to Type
- `explicit operator Type()` (C++11) - Explicit conversion only

**Theory Keywords:**
- **user-defined conversion** - From class type to other type
- **implicit vs explicit** - Without/with explicit keyword

**Example:**
```cpp
class Fraction {
    int num, den;
    
public:
    Fraction(int n, int d) : num(n), den(d) {}
    
    // Conversion to double:
    operator double() const {
        return static_cast<double>(num) / den;
    }
    
    // Conversion to bool:
    explicit operator bool() const {  // C++11: explicit
        return num != 0;
    }
};

Fraction f(3, 4);

double d = f;             // Implicit: Fraction -> double (0.75)
d = static_cast<double>(f);  // Explicit also works

// bool b = f;            // ERROR: explicit conversion
if (f) {                  // OK: explicit conversion in boolean context
    std::cout << "Non-zero\n";
}
bool b = static_cast<bool>(f);  // OK: explicit cast

// Real-world example: smart pointers
class SmartPtr {
    int* ptr;
    
public:
    explicit operator bool() const {  // Check if valid
        return ptr != nullptr;
    }
};
```

### [explicit specifier](https://en.cppreference.com/w/cpp/language/explicit.html)

**Code-related Keywords:**
- `explicit Constructor(Type)` - Disable implicit conversion
- `explicit operator Type()` (C++11) - Explicit conversion function
- `explicit(bool)` (C++20) - Conditionally explicit

**Theory Keywords:**
- **prevent surprises** - No unexpected conversions
- **safety** - Require intentional conversions
- **boolean context** - explicit operator bool common pattern

**Example:**
```cpp
// Explicit constructor:
class Size {
    int value;
    
public:
    explicit Size(int v) : value(v) {}
    
    int get() const { return value; }
};

Size s1(100);             // OK: direct initialization
// Size s2 = 100;         // ERROR: no implicit conversion
// void func(Size s);
// func(50);              // ERROR: no implicit conversion

// Explicit conversion operator:
class Wrapper {
    int value;
    
public:
    Wrapper(int v) : value(v) {}
    
    explicit operator int() const {
        return value;
    }
};

Wrapper w(42);
// int x = w;             // ERROR: explicit conversion
int y = static_cast<int>(w);  // OK: explicit cast

// C++20 conditionally explicit:
template<typename T>
class Optional {
    T value;
    bool hasValue;
    
public:
    // Explicit only if T is not convertible to bool:
    explicit(!std::is_convertible_v<T, bool>) 
    operator bool() const {
        return hasValue;
    }
};
```
