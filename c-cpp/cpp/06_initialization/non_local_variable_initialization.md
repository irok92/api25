# Non-local variable initialization

## Non-local variable initialization

### Static non-local initialization

#### [Zero initialization](https://en.cppreference.com/w/cpp/language/zero_initialization.html)

**Code-related Keywords:**
- `static int x;` - Zero-initialized before other inits
- Zero for primitives, [nullptr](../../04_expressions/literals.md) for [pointers](../../05_declarations/compound_types.md)

**Theory Keywords:**
- **static storage** - Before any other initialization
- **all zeros** - Primitive types set to 0, false, nullptr

**Example:**
```cpp
static int global;        // Zero-initialized: 0
static double d;          // 0.0
static char* p;           // nullptr

struct Pod { int x; double y; };
static Pod pod;           // pod.x = 0, pod.y = 0.0
```

#### [Constant initialization](https://en.cppreference.com/w/cpp/language/constant_initialization.html)

**Code-related Keywords:**
- `constexpr` global - Compile-time constant
- `constinit` (C++20) - Guarantee constant init

**Theory Keywords:**
- **compile-time evaluation** - No runtime initialization overhead
- **static initialization order** - Happens before dynamic init

**Example:**
```cpp
constexpr int SIZE = 100; // Constant init at compile time
const double PI = 3.14159;

constinit int counter = 0;  // C++20: guaranteed constant init
```

### Dynamic non-local initialization

#### [Ordered dynamic initialization](https://en.cppreference.com/w/cpp/language/initialization.html#Non-local_variables)

**Code-related Keywords:**
- Global variables in same translation unit
- Order: textual order within file

**Theory Keywords:**
- **translation unit order** - Within same file: top-to-bottom
- **initialization order fiasco** - Across files: undefined order

**Example:**
```cpp
// file.cpp
int compute() { return 42; }

int a = compute();        // Initialized first
int b = a + 1;            // Initialized second (a already ready)

// Different file.cpp: order relative to other files is UNDEFINED
```

#### [Unordered dynamic initialization](https://en.cppreference.com/w/cpp/language/initialization.html#Non-local_variables)

**Theory Keywords:**
- **cross-TU dependencies** - Globals in different files: undefined order
- **static initialization order fiasco** - Dangerous dependencies across translation units

**Example:**
```cpp
// a.cpp
extern int y;
int x = y + 1;            // UNDEFINED: y might not be initialized yet!

// b.cpp
int y = 10;               // Order relative to x is undefined
```

#### [Deferred dynamic initialization](https://en.cppreference.com/w/cpp/language/initialization.html#Non-local_variables)

**Code-related Keywords:**
- Inline variables (C++17)
- [Templates](../../10_templates/templates.md) and inline

**Theory Keywords:**
- **lazy initialization** - Delayed until first use
- **thread-safe** - Guaranteed since C++11 (for [function](../../07_functions/functions.md) statics)

**Example:**
```cpp
// Function-local static (thread-safe C++11):
int& getSingleton() {
    static int instance = expensive_init();  // Initialized on first call
    return instance;
}

// First call initializes, subsequent calls reuse
getSingleton();           // Initializes
getSingleton();           // Reuses
```
