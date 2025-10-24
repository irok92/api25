# Operators

## [Operators](https://en.cppreference.com/w/cpp/language/expressions.html#Operators)

### [Assignment operators](https://en.cppreference.com/w/cpp/language/operator_assignment.html)

**Code-related Keywords:**
- `=` - Assignment
- `+=`, `-=`, `*=`, `/=`, `%=` - Compound assignment
- `&=`, `|=`, `^=`, `<<=`, `>>=` - Bitwise compound assignment

**Example:**
```cpp
int x = 10;                    // Simple assignment
x += 5;                        // x = x + 5 (now 15)
x *= 2;                        // x = x * 2 (now 30)
x /= 3;                        // x = x / 3 (now 10)
x %= 3;                        // x = x % 3 (now 1)
int y = x = 5;                 // Right-to-left: x=5, then y=x (both 5)
```

### [Arithmetic operators](https://en.cppreference.com/w/cpp/language/operator_arithmetic.html)

**Code-related Keywords:**
- `+`, `-` - Addition, subtraction
- `*`, `/` - Multiplication, division
- `%` - Modulo (remainder, integers only)
- Unary: `+x`, `-x` - Positive, negative

**Example:**
```cpp
int a = 10 + 5;                // 15: addition
int b = 10 - 5;                // 5: subtraction
int c = 10 * 5;                // 50: multiplication
int d = 10 / 3;                // 3: integer division (truncates)
int e = 10 % 3;                // 1: remainder
float f = 10.0f / 3.0f;        // 3.333...: float division
int neg = -a;                  // -15: unary minus
```

### [Increment and decrement](https://en.cppreference.com/w/cpp/language/operator_incdec.html)

**Code-related Keywords:**
- `++x` - Pre-increment (increment, then return new value)
- `x++` - Post-increment (return old value, then increment)
- `--x` - Pre-decrement
- `x--` - Post-decrement

**Example:**
```cpp
int x = 5;
int a = ++x;                   // x becomes 6, a = 6 (pre-increment)
int b = x++;                   // b = 6, x becomes 7 (post-increment)
int c = --x;                   // x becomes 6, c = 6 (pre-decrement)
int d = x--;                   // d = 6, x becomes 5 (post-decrement)

// Prefer pre-increment when value not used (more efficient for objects)
for (int i = 0; i < 10; ++i) {}  // ++i slightly better than i++
```

### [Logical operators](https://en.cppreference.com/w/cpp/language/operator_logical.html)

**Code-related Keywords:**
- `&&` - Logical AND (short-circuit)
- `||` - Logical OR (short-circuit)
- `!` - Logical NOT

**Theory Keywords:**
- **short-circuit** - Right side not evaluated if left determines result

**Example:**
```cpp
bool a = true, b = false;
bool c = a && b;               // false: AND (both must be true)
bool d = a || b;               // true: OR (at least one true)
bool e = !a;                   // false: NOT (inverts)

if (ptr != nullptr && ptr->value > 0) {}  // Safe: ptr checked first (short-circuit)
if (x > 0 || expensive_check()) {}        // expensive_check() skipped if x > 0
```

### [Comparison operators](https://en.cppreference.com/w/cpp/language/operator_comparison.html)

**Code-related Keywords:**
- `==`, `!=` - Equal, not equal
- `<`, `>` - Less than, greater than
- `<=`, `>=` - Less or equal, greater or equal
- `<=>` - Three-way comparison spaceship (C++20)

**Example:**
```cpp
int a = 5, b = 10;
bool eq = (a == b);            // false
bool ne = (a != b);            // true
bool lt = (a < b);             // true
bool gt = (a > b);             // false
bool le = (a <= b);            // true
bool ge = (a >= b);            // false

auto cmp = a <=> b;            // C++20: returns ordering (less, equal, greater)
```

### [Member access operators](https://en.cppreference.com/w/cpp/language/operator_member_access.html)

**Code-related Keywords:**
- `.` - Member access (object)
- `->` - Member access ([pointer](../../05_declarations/compound_types.md))
- `.*` - Pointer-to-member (object)
- `->*` - Pointer-to-member (pointer)

**Example:**
```cpp
struct Point { int x, y; };
Point p = {1, 2};
Point* ptr = &p;

int x1 = p.x;                  // 1: access member via object
int y1 = ptr->y;               // 2: access member via pointer
// Same as: (*ptr).y

int Point::*pmember = &Point::x;  // Pointer-to-member
int val = p.*pmember;          // 1: access via pointer-to-member (object)
int val2 = ptr->*pmember;      // 1: access via pointer-to-member (pointer)
```

### [Other operators](https://en.cppreference.com/w/cpp/language/operator_other.html)

**Code-related Keywords:**
- `()` - Function call
- `,` - Comma (sequence, returns rightmost)
- `?:` - Ternary conditional
- `[]` - Subscript ([array](../../05_declarations/compound_types.md) access)

**Example:**
```cpp
int max = (a > b) ? a : b;     // Ternary: if a>b then a, else b
int arr[5] = {1,2,3,4,5};
int val = arr[2];              // 3: subscript operator
int result = (a++, b++, a+b);  // Comma: evaluates all, returns last (a+b)
func(x, y);                    // Function call operator (parentheses)
```

### Special operators

#### [sizeof](https://en.cppreference.com/w/cpp/language/sizeof.html)

**Code-related Keywords:**
- `sizeof(type)` - Size of [type](../../02_types_and_objects/types.md) in bytes
- `sizeof expr` - Size of expression's type

**Example:**
```cpp
int size1 = sizeof(int);       // 4 (typically): size of int type
int arr[10];
int size2 = sizeof(arr);       // 40: size of entire array
int count = sizeof(arr) / sizeof(arr[0]);  // 10: number of elements
int x = 5;
int size3 = sizeof(x);         // 4: size of int (x not evaluated!)
int size4 = sizeof x;          // Same (parentheses optional for expressions)
```

#### [alignof](https://en.cppreference.com/w/cpp/language/alignof.html) (C++11)

**Code-related Keywords:**
- `alignof(type)` - Alignment requirement in bytes
- `alignas(N)` - Specify alignment ([specifier](../../05_declarations/specifiers_and_qualifiers.md))

**Example:**
```cpp
int align1 = alignof(char);    // 1: char aligned to 1-byte boundary
int align2 = alignof(int);     // 4: int typically aligned to 4-byte boundary
int align3 = alignof(double);  // 8: double typically aligned to 8-byte boundary

struct alignas(16) Aligned {   // Force 16-byte alignment
    int data;
};
```

#### [typeid](https://en.cppreference.com/w/cpp/language/typeid.html)

**Code-related Keywords:**
- `typeid(type)` - Get type information
- `typeid(expr)` - Get runtime type info (for [polymorphic](../../09_classes/inheritance_and_derived_classes.md) types)
- `std::type_info` - Type information class

**Example:**
```cpp
#include <typeinfo>
int x = 5;
const std::type_info& ti = typeid(x);       // Type info for int
bool same = (typeid(int) == typeid(x));     // true

struct Base { virtual ~Base() {} };         // Polymorphic (has virtual)
struct Derived : Base {};
Base* ptr = new Derived();
bool isDerived = (typeid(*ptr) == typeid(Derived));  // true: runtime type check
```

#### [new](https://en.cppreference.com/w/cpp/language/new.html)

**Code-related Keywords:**
- `new type` - Allocate single object
- `new type[n]` - Allocate array
- `new (ptr) type` - Placement new (construct at address)

**Example:**
```cpp
int* p1 = new int;             // Allocate single int (undefined value)
int* p2 = new int(42);         // Allocate int with value 42
int* arr = new int[10];        // Allocate array of 10 ints
int* p3 = new int{5};          // C++11: uniform initialization

char buffer[sizeof(int)];
int* p4 = new (buffer) int(10);  // Placement new: construct at buffer address
```

#### [delete](https://en.cppreference.com/w/cpp/language/delete.html)

**Code-related Keywords:**
- `delete ptr` - Deallocate single object
- `delete[] ptr` - Deallocate array

**Theory Keywords:**
- **memory leak** - Forgetting to delete allocated memory
- **dangling pointer** - Using pointer after delete

**Example:**
```cpp
int* p = new int(42);
delete p;                      // Deallocate single object
// delete p;                   // UNDEFINED: double delete!

int* arr = new int[10];
delete[] arr;                  // Deallocate array (use [] for arrays!)
// delete arr;                 // WRONG: undefined behavior (missing [])

p = nullptr;                   // Good practice: set to nullptr after delete
```

#### [throw](https://en.cppreference.com/w/cpp/language/throw.html)

**Code-related Keywords:**
- `throw expression` - Throw [exception](../../11_exceptions/exceptions.md)
- `throw;` - Re-throw current exception

**Example:**
```cpp
void func() {
    if (error_condition)
        throw std::runtime_error("Error message");  // Throw exception
}

try {
    func();
} catch (const std::exception& e) {
    std::cerr << e.what();
    throw;                     // Re-throw caught exception
}
```

#### [noexcept operator](https://en.cppreference.com/w/cpp/language/noexcept.html) (C++11)

**Code-related Keywords:**
- `noexcept(expr)` - Check if expression doesn't throw
- `noexcept` - Function [specifier](../../11_exceptions/exception_specification.md) (doesn't throw)

**Example:**
```cpp
void safe() noexcept {}        // Function guaranteed not to throw

void check() {
    bool b1 = noexcept(1 + 1); // true: arithmetic doesn't throw
    bool b2 = noexcept(safe()); // true: safe() is noexcept
    bool b3 = noexcept(throw 1); // false: throw expression may throw
}

template <typename T>
void func() noexcept(noexcept(T())) {  // Conditionally noexcept
    T obj;                     // noexcept if T() doesn't throw
}
```
