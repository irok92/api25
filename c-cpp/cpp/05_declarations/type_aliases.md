# Type aliases

## Type aliases

### [typedef declaration](https://en.cppreference.com/w/cpp/language/typedef.html)

**Code-related Keywords:**
- `typedef OldType NewName;` - Create [type](../../02_types_and_objects/types.md) alias (legacy)
- `typedef int* IntPtr;` - Alias for pointer type

**Theory Keywords:**
- **type synonym** - Alternative name for existing type
- **legacy syntax** - Prefer `using` in modern C++

**Example:**
```cpp
typedef unsigned long ulong;  // ulong is alias for unsigned long
ulong x = 42;

typedef int* IntPtr;          // IntPtr is alias for int*
IntPtr p = &x;

typedef void (*FuncPtr)(int); // Function pointer type
FuncPtr callback = nullptr;

// Complex: array of 10 int pointers
typedef int* IntPtrArray[10];
IntPtrArray arr;              // arr is int*[10]
```

### [Type alias, alias template](https://en.cppreference.com/w/cpp/language/type_alias.html) (C++11)

**Code-related Keywords:**
- `using NewName = OldType;` - Type alias (C++11, preferred)
- `template<typename T> using` - Alias [template](../../10_templates/templates.md) (C++11)

**Theory Keywords:**
- **modern syntax** - Clearer than typedef
- **template aliases** - Parameterized type aliases (C++11)

**Example:**
```cpp
// Basic aliases:
using ulong = unsigned long;  // Clearer than typedef
using IntPtr = int*;

using FuncPtr = void(*)(int); // Function pointer
FuncPtr callback = nullptr;

// Template alias (not possible with typedef):
template<typename T>
using Vec = std::vector<T>;   // Vec<int> = std::vector<int>

Vec<int> v = {1, 2, 3};

template<typename T>
using StrMap = std::map<std::string, T>;  // Partial specialization
StrMap<int> scores = {{"Alice", 100}, {"Bob", 95}};

// Complex example:
template<typename T>
using Callback = std::function<void(T)>;  // Generic callback type

Callback<int> onValue = [](int x) { std::cout << x; };
onValue(42);                  // Prints: 42
```
