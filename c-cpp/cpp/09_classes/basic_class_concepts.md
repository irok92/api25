# Basic class concepts

## Basic class concepts

### [Class types](https://en.cppreference.com/w/cpp/language/class.html)

**Code-related Keywords:**
- `class Name { };` - Class definition
- `struct Name { };` - Struct (class with public default)
- `Name obj;` - Create instance
- Member access - `.` for object, `->` for pointer

**Theory Keywords:**
- **user-defined type** - Custom [type](../../02_types_and_objects/types.md)
- **class vs struct** - struct defaults public, class private
- **member layout** - Implementation-defined order

**Example:**
```cpp
// Class:
class Circle {
    double radius;        // private by default
public:
    Circle(double r) : radius(r) {}
    double area() const { return 3.14159 * radius * radius; }
};

Circle c(5.0);
std::cout << c.area();    // 78.54

// Struct:
struct Rectangle {        // public by default
    double width, height;
    
    double area() const { return width * height; }
};

Rectangle r{4.0, 3.0};
std::cout << r.width;     // Direct access: 4.0
```

### [Union types](https://en.cppreference.com/w/cpp/language/union.html)

**Code-related Keywords:**
- `union Name { };` - Union definition
- All members share memory - Only one active at a time
- `std::variant` (C++17) - Type-safe alternative

**Theory Keywords:**
- **overlapping storage** - All members at same address
- **type punning** - Reinterpret memory as different type (unsafe)
- **active member** - Last written member is active

**Example:**
```cpp
// Union (legacy, use std::variant in modern C++):
union Data {
    int i;
    double d;
    char c;
};

Data data;
data.i = 42;              // i is active
std::cout << data.i;      // 42
data.d = 3.14;            // Now d is active, i no longer valid
std::cout << data.d;      // 3.14

// Modern alternative (C++17):
#include <variant>
std::variant<int, double, char> v;
v = 42;                   // Holds int
v = 3.14;                 // Now holds double
std::cout << std::get<double>(v);  // 3.14, type-safe
```

### [injected-class-name](https://en.cppreference.com/w/cpp/language/injected-class-name.html)

**Code-related Keywords:**
- Class name as member - Refers to itself

**Theory Keywords:**
- **self-reference** - Class name available inside class scope
- **[template](../../10_templates/templates.md) contexts** - Used in template member [declarations](../../05_declarations/declarations.md)

**Example:**
```cpp
class MyClass {
    MyClass* clone();     // Returns pointer to same class
    
    // Constructor using injected name:
    MyClass(const MyClass& other) { }  // Copy constructor
};

// Template example:
template<typename T>
class Container {
    Container<T>* next;   // Injected name: Container refers to Container<T>
    Container* prev;      // Same: Container is shorthand for Container<T> inside class
};
```
