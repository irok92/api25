# Declarations

## [Declarations](https://en.cppreference.com/w/cpp/language/declarations.html)

**Code-related Keywords:**
- Variable: `int x;` `int x = 5;`
- Function: `void func();` `int add(int, int);`
- [Class](../../09_classes/classes.md): `class MyClass;` `struct Point {};`
- [Type alias](./type_aliases.md): `using MyInt = int;`

**Theory Keywords:**
- **declaration** - Introduces name into scope
- **definition** - Declaration that provides implementation/storage
- **forward declaration** - Declare before defining

**Example:**
```cpp
// Declarations:
int x;                         // Variable declaration (also definition - allocates storage)
void func();                   // Function declaration (no body)
class MyClass;                 // Forward declaration

// Definitions:
int x = 42;                    // Definition with initialization
void func() { /*body*/ }       // Function definition
class MyClass { int data; };   // Class definition

extern int global;             // Declaration only (defined elsewhere)
```

### [Conflicting declarations](https://en.cppreference.com/w/cpp/language/conflicting_declarations.html)

**Theory Keywords:**
- **conflicting** - Same name, incompatible types
- **redeclaration** - Same name, compatible types (allowed)

**Example:**
```cpp
int func();                    // Declaration 1
int func();                    // OK: redeclaration (same type)
// float func();               // ERROR: conflicting declaration (different return type)

extern int x;                  // Declaration
extern int x;                  // OK: same declaration
// extern float x;             // ERROR: conflicting type

namespace NS {
    int value;
}
// int NS::value;              // ERROR: redeclaration outside namespace
```
