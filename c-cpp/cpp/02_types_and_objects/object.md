# Object

## [Object](https://en.cppreference.com/w/cpp/language/objects.html)

**Code-related Keywords:**
- [Variable declaration](../../05_declarations/declarations.md): `int x;`
- Object creation: `MyClass obj;`
- [Pointer](../../05_declarations/compound_types.md): `int* ptr = &x;`
- [Reference](../../05_declarations/compound_types.md): `int& ref = x;`

**Theory Keywords:**
- **object** - Region of storage with a type
- **variable** - Named object
- **instance** - Specific object of a [class](../../09_classes/classes.md) type

**Example:**
```cpp
int x = 42;                    // Object of type int, named x
int* ptr = &x;                 // ptr is object holding address of x
int& ref = x;                  // ref is reference (alias) to object x, not a separate object
MyClass obj;                   // Object of user-defined type
int arr[5];                    // Array object containing 5 int objects
```

### [Scope](https://en.cppreference.com/w/cpp/language/scope.html)

**Code-related Keywords:**
- `{ }` - Block scope delimiters
- `::` - Scope resolution operator
- `namespace` - [Namespace scope](../../05_declarations/namespaces.md)
- Global scope - Outside all blocks

**Theory Keywords:**
- **scope** - The region of code where you can "see" and use a name
- **block scope** - Name only visible inside the `{ }` curly braces where it's declared
- **function scope** - Name visible anywhere inside the function body
- **global scope** - Name visible throughout the entire file (after you declare it)
- **namespace scope** - Name visible within a specific namespace

**Example:**
```cpp
int global = 100;              // Global scope: visible everywhere after this line

void func() {
    int local = 10;            // Function scope: visible only in func()
    {
        int block = 5;         // Block scope: visible only in this block
        local = 20;            // OK: can access outer scope
    }
    // block = 10;             // ERROR: block is out of scope
}

namespace MyNS {
    int value = 42;            // Namespace scope
}

int main() {
    int x = MyNS::value;       // Access namespace scope with ::
    int y = ::global;          // Access global scope with ::
    // int z = local;          // ERROR: local is not in scope here
}
```

### [Lifetime](https://en.cppreference.com/w/cpp/language/lifetime.html)

**Code-related Keywords:**
- `static` - Static storage duration ([storage class](../../05_declarations/storage_and_linkage.md))
- `new` / `delete` - Dynamic lifetime control ([operators](../../04_expressions/operators.md))
- Automatic lifetime - Local variables in blocks
- Temporary objects - Created by compiler, destroyed at end of expression

**Theory Keywords:**
- **lifetime** - How long an object exists in memory (from creation to destruction)
- **automatic lifetime** - Object created when you declare it, destroyed when scope ends
- **static lifetime** - Object lives for the entire program (created at start, destroyed at end)
- **dynamic lifetime** - You control when it's created (`new`) and destroyed (`delete`)
- **temporary lifetime** - Very short-lived object, only exists for one expression

**Example:**
```cpp
int global = 1;                // Static lifetime: exists for entire program

void func() {
    int local = 2;             // Automatic lifetime: created here, destroyed at }
    static int persistent = 3; // Static lifetime: initialized once, persists across calls
    
    int* dynamic = new int(4); // Dynamic lifetime: exists until delete
    // ... use dynamic
    delete dynamic;            // End of dynamic lifetime
    
    int temp = 5 + 6;          // Temporary for (5 + 6) created and destroyed
}  // local destroyed here, persistent remains

int main() {
    func();
    func();                    // persistent retains value from first call
}
```

### [Memory model](https://en.cppreference.com/w/cpp/language/memory_model.html)

**Code-related Keywords:**
- `std::atomic` - Atomic operations for thread safety
- `volatile` - Prevent optimization for special memory ([qualifier](../../05_declarations/specifiers_and_qualifiers.md))
- Memory order: `memory_order_relaxed`, `memory_order_acquire`, `memory_order_release`

**Theory Keywords:**
- **memory location** - Scalar object or maximal sequence of adjacent bit-fields
- **thread** - Execution sequence
- **data race** - Concurrent access to same memory where at least one is a write
- **synchronization** - Ordering guarantees between threads
- **undefined behavior** - Programs with data races have undefined behavior

**Example:**
```cpp
#include <atomic>
#include <thread>

int non_atomic = 0;            // NOT thread-safe
std::atomic<int> atomic_val{0}; // Thread-safe atomic operations

void increment() {
    for (int i = 0; i < 1000; ++i) {
        non_atomic++;          // DATA RACE: unsafe with multiple threads
        atomic_val++;          // Safe: atomic increment
    }
}

int main() {
    std::thread t1(increment);
    std::thread t2(increment); // Two threads accessing same data
    t1.join();
    t2.join();
    // non_atomic may not be 2000 (race condition)
    // atomic_val will always be 2000 (thread-safe)
}

volatile int hardware_reg;     // volatile: prevents compiler optimization for memory-mapped I/O
```
