# Class members

## Class members

### [Data members](https://en.cppreference.com/w/cpp/language/data_members.html)

**Code-related Keywords:**
- Class member variables - State/data
- `static` member - Shared across all instances
- `const` member - Immutable after [initialization](../../06_initialization/initialization.md)
- Default member initializer (C++11) - `int x = 0;`

**Theory Keywords:**
- **instance variable** - Each [object](../../02_types_and_objects/object.md) has own copy
- **static variable** - Single shared copy

**Example:**
```cpp
class Account {
    std::string owner;         // Instance member
    double balance = 0.0;      // C++11: default initializer
    const int id;              // Must initialize in constructor
    static int nextId;         // Static: shared by all instances
    
public:
    Account(std::string o) : owner(o), id(nextId++) {}
    
    static int getNextId() { return nextId; }
};

// Static member definition (outside class):
int Account::nextId = 1000;

Account a1("Alice");      // a1.id = 1000
Account a2("Bob");        // a2.id = 1001
std::cout << Account::getNextId();  // 1002
```

### [Bit-fields](https://en.cppreference.com/w/cpp/language/bit_field.html)

**Code-related Keywords:**
- `int x : bits;` - Specify bit width for member

**Theory Keywords:**
- **memory optimization** - Pack multiple fields in single word
- **hardware registers** - Map to hardware bit layouts

**Example:**
```cpp
struct Flags {
    unsigned int flag1 : 1;   // 1 bit
    unsigned int flag2 : 1;   // 1 bit
    unsigned int value : 6;   // 6 bits (total: 8 bits = 1 byte)
};

Flags f;
f.flag1 = 1;              // 0 or 1
f.flag2 = 0;
f.value = 42;             // 0-63 (6 bits)
```

### [Member functions](https://en.cppreference.com/w/cpp/language/member_functions.html)

**Code-related Keywords:**
- Methods - [Functions](../../07_functions/functions.md) inside class
- `const` method - Doesn't modify object
- `static` method - No `this` pointer
- `&`, `&&` qualifiers (C++11) - Lvalue/rvalue overloading

**Theory Keywords:**
- **const-correctness** - Const methods callable on const objects
- **method overloading** - Different parameters or cv-qualifiers

**Example:**
```cpp
class String {
    char* data;
    
public:
    // Regular method:
    void print() const {      // const: doesn't modify object
        std::cout << data;
    }
    
    // Non-const method:
    void clear() {
        delete[] data;
        data = nullptr;
    }
    
    // Static method (no this):
    static String create(const char* s) {
        return String(s);
    }
    
    // Ref-qualifiers (C++11):
    String& get() & { return *this; }        // Called on lvalue
    String&& get() && { return std::move(*this); }  // Called on rvalue
};

String s("hello");
s.print();                // Regular call
String::create("world");  // Static call (no object)
```

### [The this pointer](https://en.cppreference.com/w/cpp/language/this.html)

**Code-related Keywords:**
- `this` - [Pointer](../../05_declarations/compound_types.md) to current object
- `*this` - Dereference to object
- Return `*this` - Enable chaining

**Theory Keywords:**
- **implicit parameter** - Every non-static method receives `this`
- **method chaining** - Return `*this` for fluent API

**Example:**
```cpp
class Builder {
    int value = 0;
    
public:
    Builder& setValue(int v) {
        this->value = v;      // this-> to access member
        return *this;         // Return reference for chaining
    }
    
    Builder& add(int n) {
        value += n;
        return *this;         // Chaining
    }
    
    int get() const { return value; }
};

Builder b;
b.setValue(10).add(5).add(3);  // Chaining: value = 18
std::cout << b.get();     // 18
```

### [Static members](https://en.cppreference.com/w/cpp/language/static.html)

**Code-related Keywords:**
- `static` member variable - Shared by all instances
- `static` member function - No `this` pointer
- Definition outside class - `Type Class::member = value;`

**Theory Keywords:**
- **class-level data** - Not per-instance
- **no object required** - Access via `Class::member`

**Example:**
```cpp
class Counter {
    static int count;         // Declaration
    
public:
    Counter() { ++count; }
    ~Counter() { --count; }
    
    static int getCount() {   // Static method
        return count;         // Can access static members only
        // return value;      // ERROR: no this pointer
    }
};

// Definition (required for static data members):
int Counter::count = 0;

Counter c1;               // count = 1
Counter c2;               // count = 2
std::cout << Counter::getCount();  // 2 (no object needed)
```

### [Nested classes](https://en.cppreference.com/w/cpp/language/nested_classes.html)

**Code-related Keywords:**
- Class inside class - Nested type
- `Outer::Inner` - Access nested class
- Access to outer - Needs [reference](../../05_declarations/compound_types.md)/pointer

**Theory Keywords:**
- **logical grouping** - Helper classes
- **access control** - Can be private

**Example:**
```cpp
class Outer {
    int outerValue = 10;
    
public:
    // Nested class:
    class Inner {
        Outer& outer;         // Reference to outer object
        
    public:
        Inner(Outer& o) : outer(o) {}
        
        void printOuter() {
            std::cout << outer.outerValue;  // Access outer's members
        }
    };
    
    Inner createInner() {
        return Inner(*this);  // Pass reference to outer
    }
};

Outer o;
Outer::Inner inner = o.createInner();  // Create nested object
inner.printOuter();       // 10
```
