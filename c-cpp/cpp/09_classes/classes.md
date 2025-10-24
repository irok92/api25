# Classes

## [Classes](https://en.cppreference.com/w/cpp/language/classes.html)

**Code-related Keywords:**
- `class Name { };` - Define class
- `struct Name { };` - Class with public default access
- `public:`, `private:`, `protected:` - Access specifiers
- Member variables - Data members
- Member [functions](../../07_functions/functions.md) - Methods
- Constructor/destructor - Special member functions

**Theory Keywords:**
- **encapsulation** - Bundle data and methods
- **access control** - Restrict member visibility
- **struct vs class** - struct defaults to public, class to private
- **member access** - dot (`.`) for [objects](../../02_types_and_objects/object.md), arrow (`->`) for [pointers](../../05_declarations/compound_types.md)

**Example:**
```cpp
// Class definition:
class Person {
private:                  // Default for class
    std::string name;
    int age;
    
public:
    // Constructor:
    Person(std::string n, int a) : name(n), age(a) {}
    
    // Member function:
    void introduce() const {
        std::cout << "I'm " << name << ", age " << age << '\n';
    }
    
    // Getter:
    int getAge() const { return age; }
    
    // Setter:
    void setAge(int a) { age = a; }
};

// Usage:
Person p("Alice", 30);
p.introduce();            // "I'm Alice, age 30"
p.setAge(31);

// Struct (public by default):
struct Point {            // public: not needed
    int x, y;
    
    double distance() const {
        return std::sqrt(x*x + y*y);
    }
};

Point pt{3, 4};
std::cout << pt.x;        // Direct access: 3
std::cout << pt.distance();  // 5.0
```
