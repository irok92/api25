# C/C++ Summary

This document provides a concise summary of various topics related to C and C++.

## 1. Number Systems

- **Decimal (Base 10):** Our everyday number system. `123 = 1*10^2 + 2*10^1 + 3*10^0`.
- **Binary (Base 2):** Uses only 0 and 1. `1101 = 1*2^3 + 1*2^2 + 0*2^1 + 1*2^0 = 13`.
- **Hexadecimal (Base 16):** Uses 0-9 and A-F (10-15). Represents a byte (8 bits) with two characters. `0xA5`.
- **Octal (Base 8):** Uses 0-7. Rarely used.
- **Signed and Unsigned:**
    - **Unsigned:** Represents only positive numbers (and zero). An 8-bit unsigned integer is 0 to 255.
    - **Signed:** Represents positive, negative, and zero. An 8-bit signed integer is -128 to 127.
- **Integer Overflow/Underflow:** Occurs when a value exceeds the storable range, causing it to wrap around.

## 2. Modularity in Development

- **Modules:** Self-contained units with defined **Inputs**, **Outputs**, **States**, and **Signals**.
- **Circuits:** Physical implementations of modules.
- **Signaling:** How modules communicate. Grouping signals can create higher-level inputs (e.g., 8-bit adder from two 4-bit adders).
- **CPUs:**
    - **CISC (Complex Instruction Set Computer):** (e.g., x86, ARM) Focus on performance and flexibility.
        - **Cache:** Fast, small memory on the CPU (L1, L2, L3) to reduce latency to main memory.
        - **Cache Line:** The amount of data transferred between RAM and cache (e.g., 64/128 bytes). Sequential data access is faster.
        - **Hyperthreading:** Allows a single CPU core to run multiple threads concurrently.
        - **IPC (Instructions Per Cycle):** A measure of parallel efficiency.
        - **Memory Alignment:** Aligning data in memory to fit within a cache line to prevent race conditions between cores.
    - **RISC (Reduced Instruction Set Computer):** Focus on stability, low cost, and low memory usage. Often lack caches.

## 3. Programs and Memory

- **Virtual Memory:** An OS provides each program with a virtual address space, which is mapped to physical RAM. This allows for memory fragmentation, on-demand growth, and security.
- **Stack:** Memory for local variables, function arguments, and return addresses. Fast allocation/deallocation.
    - **Stack Overflow:** Occurs when the stack runs out of space, often due to deep recursion.
- **Heap:** Memory for dynamically sized data that can be allocated and freed at any time.
- **Pipes:** Standard I/O streams for inter-process communication.
    - `stdout`: Standard output.
    - `stderr`: Standard error (for logging).
    - `stdin`: Standard input.
- **Environment Variables:** Key-value pairs passed to a program on startup for configuration.

## 4. C - Building Systems & Language Basics

### 4.1 Building Systems

- **C Language:** A low-level, procedural language known for performance, portability, and requiring manual memory management.
- **Functions:** Building blocks of C programs. `return_type function_name(args);`.
    - **`static` functions:** Visible only within the file they are defined in.
    - **`extern` functions:** A declaration that a function is defined in another file.
- **Compilation & Optimization:** Compilers translate C code into machine code. They can perform optimizations like inlining (copy-pasting a function's code at the call site) to improve performance by reducing function call overhead.
- **Headers (.h) & Sources (.c):**
    - **Source files (`.c`):** Contain function and variable implementations. Each source file is compiled into an object file (`.o` or `.obj`).
    - **Header files (`.h`):** Contain shared declarations (function prototypes, type definitions, macros) so that source files can use code from other files.
- **Compilation Process:**
    1.  **Preprocessing:** Handles `#` directives. The preprocessor runs before the compiler, modifying the source code textually.
    2.  **Parsing/Compilation:** Checks for syntax errors and translates the preprocessed C code into assembly, then to a machine code object file.
    3.  **Linking:** Combines object files and libraries into a final executable. It resolves symbols (function names, global variables) between files. If a function is declared but not defined anywhere, the linker will produce an "undefined reference" error.
- **`#include`:** Pastes a header file's content. `"my_header.h"` for local project headers, `<stdio.h>` for system/standard library headers.
- **Prototypes:** Function declarations without an implementation. They tell the compiler about a function's signature (name, return type, parameters) before it's defined.
    ```c
    // In math_utils.h
    int square(int num);

    // In math_utils.c
    int square(int num) {
        return num * num;
    }
    ```
- **Include Guards:** A standard preprocessor pattern to prevent a header from being included multiple times in a single compilation unit, which would cause redefinition errors.
    ```c
    #ifndef MY_HEADER_H
    #define MY_HEADER_H
    // ... header content ...
    #endif
    ```
- **Shared Objects (DLL/.so):** Libraries that can be loaded by a program at runtime, allowing code to be shared among multiple applications.

### 4.2 Data

- **Variables:** `my_type my_var = value;`. Uninitialized local variables contain garbage data. Global and static variables are initialized to zero by default.
- **`const`:** Makes a variable read-only. `const int x = 10;`.
- **`static` variables:** When used globally, they are private to the file. Inside a function, they retain their value between function calls.
    ```c
    void counter() {
        static int count = 0; // Initialized only once
        printf("%d\n", count++); // Prints 0, 1, 2, ... on successive calls
    }
    ```
- **Data Types:**
    - **Booleans:** `#include <stdbool.h>` for `true`/`false`. Otherwise, use integers (0 is false, non-zero is true).
    - **Integers:** `char`, `short`, `int`, `long`, `long long`. Use `<stdint.h>` for fixed-size types like `int32_t`, `uint64_t`.
    - **Floating-point:** `float`, `double`, `long double`.
- **Type Casting:** Explicitly converting a value's type. `float f = (float)10;`.
- **Pointers:** A variable holding a memory address. `type* ptr;`.
    - `NULL`: An empty/invalid pointer, defined in `<stddef.h>`.
    - **Dereferencing:** `*ptr` accesses the value at the pointer's address.
    - **Address-of:** `&var` gets the memory address of a variable.
    - **Pointer Arithmetic:** Pointers can be incremented/decremented. The address changes by `n * sizeof(type)`.
        ```c
        int arr[] = {10, 20, 30};
        int* ptr = arr; // ptr points to arr[0]
        ptr++;          // Now ptr points to arr[1]
        printf("%d", *ptr); // Prints 20
        ```
    - **Function Pointers:** A pointer that holds the address of a function. `int (*my_func)(int, int);`.
    - **`void*`:** A generic pointer to an unknown data type. It must be cast to a specific type before being dereferenced.
- **Arrays:** Fixed-size collections of elements of the same type.
    - **1D Array:** `int my_array[10];`
    - **2D Array:** `int matrix[3][4];`
    - **Strings:** Are arrays of characters ending with a null terminator `\0`. `char name[] = "Alice";` is equivalent to `char name[] = {'A', 'l', 'i', 'c', 'e', '\0'};`.
- **`struct`:** A composite data type that groups variables under one name.
    ```c
    struct Point {
        int x;
        int y;
    };
    struct Point p1 = {10, 20};
    p1.x = 15;
    ```
- **`union`:** A special data type that allows storing different data types in the same memory location. Only one member can contain a value at any given time.
    ```c
    union Data {
       int i;
       float f;
    };
    union Data data;
    data.i = 10; // data.f is now invalid
    ```
- **`typedef`:** Creates an alias for an existing data type.
    ```c
    typedef unsigned char byte;
    byte b = 255;
    ```

### 4.3 Statements and Logic

- **Math Operators:** `+`, `-`, `*`, `/`, `%` (modulus), `++` (increment), `--` (decrement).
- **Bitwise Operators:** Operate on individual bits of data. `~` (NOT), `&` (AND), `|` (OR), `^` (XOR), `<<` (left shift), `>>` (right shift).
- **Logical Operators:** `&&` (AND), `||` (OR), `!` (NOT). Used in conditional logic. They use short-circuit evaluation.
- **Ternary Operator (`? :`):** A shorthand for an if-else statement.
    ```c
    int x = 10;
    int y = (x > 5) ? 1 : 0; // y will be 1
    ```
- **Control Flow:**
    - **`if-else`:** `if (condition) { ... } else if (condition2) { ... } else { ... }`
    - **`while` loop:** `while (condition) { ... }`
    - **`do-while` loop:** `do { ... } while (condition);` (always runs at least once).
    - **`for` loop:** `for (init; condition; increment) { ... }`. Any part can be omitted.
        ```c
        // Infinite loop
        for (;;) {
            // ...
        }
        ```
    - **`switch-case`:** Selects a code block to execute based on an integer value.
        - **Fall-through:** Execution continues to the next `case` if `break` is omitted.
        ```c
        switch (value) {
            case 1:
                printf("1"); // Falls through
            case 2:
                printf(" or 2");
                break;
            default:
                printf("Other");
        }
        ```
    - **`goto`:** Unconditionally transfers control to a labeled statement. Its use is highly discouraged as it can create unreadable "spaghetti code".
        ```c
        if (error) goto cleanup;
        // ...
        cleanup:
            // ... cleanup code ...
        ```

### 4.4 Preprocessors

- **`#define`:** Creates a macro, which is a text-replacement token.
    - **Object-like macro:** `#define PI 3.14159`
    - **Function-like macro:** ` #define MAX(a, b) ((a) > (b) ? (a) : (b))`
        - **Pitfall:** Arguments may be evaluated multiple times. `MAX(x++, y++)` will increment one of the variables twice. Always wrap arguments and the whole expression in parentheses to avoid operator precedence issues.
- **`#undef`:** Removes a macro definition.
- **Stringification (`#`) and Token Pasting (`##`):**
    - `#`: Turns a macro parameter into a string literal.
    - `##`: Concatenates two tokens into a single token.
    ```c
    #define PRINT_VAR(v) printf(#v " = %d\n", v)
    #define MAKE_FUNC(name) void func_##name() { printf("Hi from " #name "\n"); }

    int my_var = 10;
    PRINT_VAR(my_var); // Expands to: printf("my_var" " = %d\n", my_var);
    MAKE_FUNC(test);   // Creates: void func_test() { ... }
    ```
- **Predefined Macros:** Standard macros provided by the compiler.
    - `__FILE__`: The name of the current source file (a string).
    - `__LINE__`: The current line number in the source file (an integer).
    - `__DATE__`: The compilation date (a string).
    - `__TIME__`: The compilation time (a string).
- **Conditional Compilation:** Includes or excludes code based on compile-time conditions.
    ```c
    #ifdef DEBUG
        fprintf(stderr, "Debugging info\n");
    #endif

    #if defined(WINDOWS)
        // Windows-specific code
    #elif defined(LINUX)
        // Linux-specific code
    #endif
    ```

## 5. CMake

- **CMake:** A cross-platform build system generator. It uses `CMakeLists.txt` files to define a project.
- **`CMakeLists.txt` Example:**
    ```cmake
    cmake_minimum_required(VERSION 3.10)
    project(MyProject)

    # Find source files
    file(GLOB_RECURSE SOURCES "src/*.c")

    # Add an executable target
    add_executable(my_app ${SOURCES})

    # Add include directories
    target_include_directories(my_app PUBLIC "include")

    # Add a library
    add_library(my_lib STATIC src/my_lib.c)

    # Link the library to the executable
    target_link_libraries(my_app my_lib)
    ```

## 6. C++

C++ builds on C with many new features.

- **`struct` and `class`:** Can have member functions, constructors, and destructors. `struct` members are public by default; `class` members are private.
- **Initialization:** C++ offers more ways to initialize variables and objects, including aggregate initialization for structs. `MyStruct s = {.a=1, .b=2};`.
- **Default Initialization:** Variables are often zero-initialized by default. `int a; // is 0`.
- **`new` and `delete`:** For dynamic memory management.
    ```cpp
    MyClass* obj = new MyClass(); // Allocate and construct
    delete obj;                   // Destruct and free

    MyClass* arr = new MyClass[10]; // Allocate array
    delete[] arr;                   // Free array
    ```
- **Namespaces:** Prevent naming conflicts by grouping code. `namespace MyCode { ... }`. Access with `MyCode::my_function();`.
- **Exceptions:** A mechanism for handling runtime errors.
    ```cpp
    try {
        throw std::runtime_error("An error occurred");
    } catch (const std::exception& e) {
        // Handle error
    }
    ```
- **Iterators:** Objects that allow traversal of containers (like `std::vector`).
    ```cpp
    std::vector<int> v = {1, 2, 3};
    for (auto it = v.begin(); it != v.end(); ++it) {
        // *it is the element
    }
    // Or with a range-based for loop:
    for (int i : v) {
        // i is the element
    }
    ```
- **References (`&`):** An alias for an existing variable. Cannot be null.
    ```cpp
    void increment(int& value) {
        value++; // Modifies the original variable
    }
    ```
- **Function Overloading:** Defining multiple functions with the same name but different parameters.
- **Default Arguments:** Providing default values for function parameters. `void func(int a, int b = 10);`.
- **Lambda Functions:** Anonymous, inline functions.
    ```cpp
    // [captures](params) -> return_type { body }
    auto add = [](int a, int b) { return a + b; };
    int sum = add(2, 3); // sum is 5
    ```
- **Operator Overloading:** Customizing the behavior of operators for user-defined types.
    ```cpp
    MyVector operator+(const MyVector& a, const MyVector& b);
    ```

## 7. C++ Standard Template Library (STL)

The STL is a collection of template classes and functions providing common data structures and algorithms.

- **`<algorithm>`**: Functions for sorting, searching, and transforming elements in containers.
    ```cpp
    #include <vector>
    #include <algorithm>
    std::vector<int> v = {3, 1, 2};
    std::sort(v.begin(), v.end()); // v is now {1, 2, 3}
    ```
- **`<iostream>`, `<fstream>`, `<sstream>` (Streams)**: For input/output operations on console, files, and strings.
    ```cpp
    #include <iostream>
    #include <sstream>
    std::stringstream ss;
    ss << "Hello, " << 42;
    std::cout << ss.str(); // Prints "Hello, 42"
    ```
- **`std::unique_ptr` and `std::shared_ptr`**: Smart pointers for automatic memory management.
    - `unique_ptr`: Exclusive ownership. The object is destroyed when the pointer goes out of scope.
        ```cpp
        std::unique_ptr<int> p1 = std::make_unique<int>(10);
        ```
    - `shared_ptr`: Shared ownership with reference counting. The object is destroyed when the last `shared_ptr` is destroyed.
        ```cpp
        std::shared_ptr<int> p2 = std::make_shared<int>(20);
        std::shared_ptr<int> p3 = p2; // Both point to the same object
        ```
- **`std::string` and `std::string_view`**:
    - `string`: A dynamic character string.
        ```cpp
        std::string s = "Hello";
        s += " World";
        ```
    - `string_view`: A non-owning, read-only view of a string. Avoids copies.
        ```cpp
        std::string_view sv(s);
        ```
- **Containers**:
    - **`std::vector`**: A dynamic array.
        ```cpp
        std::vector<int> v;
        v.push_back(1);
        ```
    - **`std::array`**: A fixed-size array.
        ```cpp
        std::array<int, 3> a = {1, 2, 3};
        ```
    - **`std::map` / `std::unordered_map` / `std::flat_map`**: Key-value pairs. `map` is sorted, `unordered_map` is hashed, `flat_map` is a sorted vector.
        ```cpp
        std::map<std::string, int> m;
        m["one"] = 1;
        ```
    - **`std::set` / `std::unordered_set` / `std::flat_set`**: Collections of unique elements.
        ```cpp
        std::set<int> s;
        s.insert(1);
        ```
    - **`std::list` / `std::forward_list` / `std::deque`**:
        - `list`: Doubly-linked list.
        - `forward_list`: Singly-linked list.
        - `deque`: Double-ended queue.
- **`std::function`**: A general-purpose polymorphic function wrapper.
    ```cpp
    #include <functional>
    std::function<int(int, int)> add = [](int a, int b) { return a + b; };
    ```
- **`std::tuple`**: A fixed-size collection of heterogeneous values.
    ```cpp
    std::tuple<int, std::string, double> t(1, "hello", 3.14);
    ```
- **`std::variant`**: A type-safe union. Can hold a value from a set of alternative types.
    ```cpp
    std::variant<int, std::string> v = "hello";
    ```
- **`std::optional`**: Represents a value that may or may not be present.
    ```cpp
    std::optional<int> opt; // Empty
    opt = 10; // Now contains a value
    ```
- **`std::span`**: A non-owning view over a contiguous sequence of objects.
    ```cpp
    #include <span>
    int arr[] = {1, 2, 3};
    std::span<int> s(arr);
    ```

## 8. Modern C++ Features (C++11 and later)

- **Ranges**: A feature for composing operations on sequences of elements.
    ```cpp
    #include <vector>
    #include <ranges>
    std::vector<int> v = {1, 2, 3, 4, 5, 6};
    auto result = v | std::views::filter([](int i){ return i % 2 == 0; })
                    | std::views::transform([](int i){ return i * 2; });
    // result is a view containing {4, 8, 12}
    ```
- **`auto`**: Deduces the type of a variable from its initializer.
    ```cpp
    auto x = 5; // x is int
    auto s = "hello"; // s is const char*
    ```
- **`constexpr`, `consteval`, `constinit`**: For compile-time computation.
    - `constexpr`: Specifies that a function or variable can be evaluated at compile time.
    - `consteval`: Enforces that a function must be evaluated at compile time.
    - `constinit`: Asserts that a variable has static initialization (initialized at compile time).
- **Structured Bindings**: Unpack elements from a `struct`, `class`, `tuple`, or `array`.
    ```cpp
    std::pair<int, int> p = {1, 2};
    auto [x, y] = p; // x is 1, y is 2
    ```
- **Concepts**: Define constraints on template parameters, improving error messages.
    ```cpp
    #include <concepts>
    template<std::integral T>
    T add(T a, T b) { return a + b; }
    ```
- **Scoped Enums (`enum class`)**: Strongly-typed enums where enumerators are scoped to the enum.
    ```cpp
    enum class Color { Red, Green, Blue };
    Color c = Color::Red;
    ```
- **`decltype`**: Yields the type of an expression.
    ```cpp
    int x = 0;
    decltype(x) y = 1; // y is int
    ```
- **`#pragma once`**: A non-standard but widely supported directive to prevent a header from being included multiple times.
    ```c
    #pragma once
    // ... header content ...
    ```
- **Coroutines**: Functions that can be suspended and resumed, for cooperative multitasking.
    ```cpp
    // Requires a coroutine library/framework for full use
    generator<int> range(int n) {
        for (int i = 0; i < n; ++i) {
            co_yield i;
        }
    }
    ```
- **Modules**: An alternative to header files for organizing code, intended to improve compilation times (still gaining full support).
    ```cpp
    // math.cppm
    export module math;
    export int add(int a, int b) { return a + b; }

    // main.cpp
    import math;
    int main() { return add(1, 2); }
    ```
- **User-Defined Literals**: Create custom suffixes for literals.
    ```cpp
    long double operator"" _deg(long double d) {
        return d * 3.141592 / 180.0;
    }
    auto angle = 90.0_deg; // angle is in radians
    ```
- **`<regex>`**: For regular expression-based text searching and manipulation.
    ```cpp
    #include <regex>
    std::string s = "Hello World";
    std::regex r("(\\w+)");
    std::smatch m;
    std::regex_search(s, m, r); // Finds "Hello"
    ```

## 9. Additional C++ Language Features

This section covers more features of the C++ language, expanding on previous topics.

### Keywords and Type System

- **`using` Alias**: A modern alternative to `typedef` for creating type aliases.
    ```cpp
    using byte = unsigned char;
    using IntVector = std::vector<int>;
    IntVector v;
    ```
- **`static_assert`**: Performs an assertion at compile time.
    ```cpp
    static_assert(sizeof(int) >= 4, "int must be at least 32-bit");
    ```
- **`noexcept` Specifier and Operator**:
    - Specifier: Declares that a function will not throw exceptions.
    - Operator: Checks if an expression is declared to not throw.
    ```cpp
    void func() noexcept; // This function promises not to throw
    bool b = noexcept(func()); // b is true
    ```
- **Type Casts**: C++ introduces more specific and safer casting operators.
    - **`static_cast`**: For safe, compile-time checked conversions (e.g., numeric types, pointers in a class hierarchy).
        ```cpp
        double d = 3.14;
        int i = static_cast<int>(d);
        ```
    - **`dynamic_cast`**: For safely downcasting pointers/references in a class hierarchy. Requires RTTI and returns `nullptr` on failure.
        ```cpp
        struct Base { virtual ~Base() = default; };
        struct Derived : Base {};
        Base* b = new Derived;
        if (Derived* d = dynamic_cast<Derived*>(b)) { /* success */ }
        ```
    - **`reinterpret_cast`**: For low-level, unsafe type conversions (e.g., pointer to integer).
        ```cpp
        int i = 0x12345678;
        char* p = reinterpret_cast<char*>(&i);
        ```
    - **`const_cast`**: Used to add or remove `const` or `volatile` qualifiers. Use with extreme caution.
        ```cpp
        const int c = 10;
        int* non_const_ptr = const_cast<int*>(&c);
        *non_const_ptr = 20; // Undefined behavior
        ```
- **`typeid` Operator**: Returns run-time type information (RTTI) about an object.
    ```cpp
    #include <typeinfo>
    if (typeid(int) == typeid(float)) { /* false */ }
    ```

### Classes

- **Member Initializer List**: The preferred way to initialize class members in a constructor, as it avoids default construction followed by assignment.
    ```cpp
    class MyClass {
        int x;
        std::string s;
    public:
        MyClass(int val, const char* str) : x(val), s(str) {} // Initializer list
    };
    ```
- **`explicit` Specifier**: Prevents a constructor from being used for implicit type conversions.
    ```cpp
    struct A { explicit A(int) {} };
    void func(A a) {}
    // func(10); // Error: implicit conversion is disallowed
    func(A(10)); // OK: explicit conversion
    ```
- **Copy and Move Semantics**:
    - **Copy Constructor/Assignment**: Creates a new copy of an object's data.
    - **Move Constructor/Assignment**: "Steals" the resources (like heap memory) from a temporary object, avoiding expensive copies.
    ```cpp
    // Move constructor example
    MyClass(MyClass&& other) noexcept : data(other.data) {
        other.data = nullptr; // Leave the source object in a valid but empty state
    }
    ```
- **`friend` Keyword**: Allows an external function or class to access the `private` and `protected` members of a class.
    ```cpp
    class A {
        int x = 10;
        friend void show(const A& a);
    };
    void show(const A& a) { std::cout << a.x; } // Can access private member x
    ```
- **Virtual Functions and Polymorphism**:
    - **`virtual`**: Declares a member function that can be overridden in derived classes.
    - **`override`**: Ensures a function is overriding a base class virtual function.
    - **`final`**: Prevents a virtual function from being overridden further, or a class from being inherited.
    - **Abstract Class**: A class with at least one pure virtual function (`= 0`), which cannot be instantiated.
    ```cpp
    struct Base {
        virtual void draw() const = 0; // Pure virtual function
        virtual ~Base() = default;
    };
    struct Circle final : Base {
        void draw() const override { /* draw circle */ }
    };
    ```

### Templates

- **Variadic Templates**: Templates that can take a variable number of arguments.
    ```cpp
    template<typename... Args>
    void print(Args... args) {
        ( (std::cout << args << " "), ... ); // C++17 fold expression
    }
    print(1, "hello", 3.14);
    ```
- **Template Specialization**: Provides a specific implementation for a template when instantiated with a particular type.
    ```cpp
    template<typename T> struct Hasher { /* generic version */ };
    template<> struct Hasher<std::string> { // Specialization for string
        size_t operator()(const std::string& s) { return s.length(); }
    };
    ```
- **Variable Templates (C++14)**: Defines a family of variables or static data members.
    ```cpp
    template<typename T>
    constexpr T pi = T(3.1415926535897932385);
    double d_pi = pi<double>;
    float  f_pi = pi<float>;
    ```

### Attributes

Attributes provide standardized syntax for compiler-specific extensions.

- **`[[nodiscard]]`**: Encourages the compiler to issue a warning if the return value of a function is ignored.
    ```cpp
    [[nodiscard]] bool is_ok() { return true; }
    is_ok(); // Compiler warning
    ```
- **`[[deprecated]]`**: Indicates that a feature is discouraged and may be removed in the future, causing a compile-time warning.
    ```cpp
    [[deprecated("Use new_func instead")]]
    void old_func() {}
    ```
- **`[[fallthrough]]`**: Suppresses compiler warnings about implicit fall-through in a `switch` statement.
    ```cpp
    switch(n) {
        case 1:
            // ...
            [[fallthrough]];
        case 2:
            // ...
            break;
    }
    ```

## 10. Further C++ Topics

### Concurrency and Parallelism

C++ provides a rich library for managing concurrent threads of execution.

- **`std::thread`**: Represents a single thread of execution.
    ```cpp
    #include <thread>
    void task() { /* ... */ }
    std::thread my_thread(task);
    my_thread.join(); // Wait for the thread to finish
    ```
- **Mutexes (`std::mutex`, `std::lock_guard`)**: Mutual exclusion objects to protect shared data from being simultaneously accessed by multiple threads.
    ```cpp
    #include <mutex>
    std::mutex mtx;
    void safe_increment(int& counter) {
        std::lock_guard<std::mutex> lock(mtx); // Lock is acquired on construction, released on destruction
        counter++;
    }
    ```
- **Atomics (`std::atomic`)**: Provides lock-free atomic operations on types, suitable for simple, low-level synchronization.
    ```cpp
    #include <atomic>
    std::atomic<int> counter = 0;
    counter++; // This is an atomic operation
    ```
- **Futures and Promises (`std::future`, `std::promise`, `std::async`)**: A mechanism to get a result from an asynchronous task.
    ```cpp
    #include <future>
    int slow_calculation() { /* ... returns 42 ... */ return 42; }
    // std::async runs the function asynchronously (potentially in a new thread)
    std::future<int> result_future = std::async(std::launch::async, slow_calculation);
    // ... do other work ...
    int result = result_future.get(); // Waits for the result and retrieves it
    ```

### Filesystem (`<filesystem>`)

A standard way to manipulate files and directories.

- **`std::filesystem::path`**: Represents a path on a filesystem.
    ```cpp
    #include <filesystem>
    namespace fs = std::filesystem;
    fs::path p = "/path/to/file.txt";
    std::cout << "Filename: " << p.filename() << std::endl;
    ```
- **Directory Operations**:
    ```cpp
    fs::create_directory("my_dir");
    for (const auto& entry : fs::directory_iterator(".")) {
        std::cout << entry.path() << std::endl;
    }
    ```

### Advanced Memory Management

- **Placement `new`**: Constructs an object on a pre-allocated buffer of memory. It does not allocate memory itself.
    ```cpp
    #include <new>
    alignas(MyClass) char buffer[sizeof(MyClass)];
    MyClass* obj = new (buffer) MyClass(); // Construct MyClass in 'buffer'
    obj->~MyClass(); // Manually call destructor
    ```

### More Utilities

- **`std::chrono`**: A library for working with time durations and clocks.
    ```cpp
    #include <chrono>
    #include <thread>
    auto start = std::chrono::high_resolution_clock::now();
    std::this_thread::sleep_for(std::chrono::seconds(1));
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> elapsed = end - start;
    std::cout << "Elapsed time: " << elapsed.count() << " ms\n";
    ```
- **`std::any`**: A type-safe container for single values of any type.
    ```cpp
    #include <any>
    std::any val;
    val = 5;
    val = "hello";
    if (val.has_value() && val.type() == typeid(const char*)) {
        std::cout << std::any_cast<const char*>(val) << std::endl;
    }
    ```

### Three-Way Comparison (C++20)

The spaceship operator (`<=>`) simplifies comparison logic by determining if `a < b`, `a == b`, or `a > b` in a single operation.

```cpp
#include <compare>
struct Point {
    int x, y;
    // Defaulted three-way comparison
    auto operator<=>(const Point&) const = default;
};
Point p1{1, 1}, p2{1, 2};
auto result = p1 <=> p2; // result is std::strong_ordering::less
```

### `volatile` Qualifier

The `volatile` keyword tells the compiler that a variable's value can be changed at any time by something outside of the program's control (e.g., hardware, another thread). It prevents the compiler from applying optimizations that might assume the variable's value doesn't change unexpectedly.

```cpp
// 'mmio_status' is a memory-mapped I/O register
volatile uint32_t* mmio_status = (uint32_t*)0x12345678;

// Wait for a hardware device to be ready
// The compiler will not optimize this loop away
while (*mmio_status != 1) {
    // do nothing
}
```

## 11. Assorted Advanced C++ Features

### Value Categories (lvalues, rvalues)

Understanding value categories is crucial for advanced C++ like move semantics.

- **lvalue** (locator value): An expression that refers to a memory location and can appear on the left-hand side of an assignment. Variables are lvalues.
- **rvalue** (right value): An expression that is temporary and cannot have an assignment made to it. Literals (`10`, `"hello"`) and temporary objects are rvalues.
- **xvalue** (eXpiring value): An object near the end of its lifetime, typically as a result of a move. It's a "movable" lvalue.
- **prvalue** (pure rvalue): An rvalue that is not an xvalue.
- **glvalue** (generalized lvalue): An lvalue or an xvalue.

```cpp
int x = 10; // x is an lvalue
int y = x;  // x is an lvalue
int z = x + y; // (x + y) is an rvalue

std::string s = "hi"; // s is an lvalue
std::string s2 = std::move(s); // std::move(s) is an xvalue
```

### Bit-fields

Bit-fields allow you to specify the number of bits a member of a `struct` or `class` should occupy. This is useful for packing data tightly, often for hardware interaction.

```cpp
struct Register {
    unsigned int is_enabled : 1; // Use 1 bit
    unsigned int mode       : 2; // Use 2 bits
    unsigned int reserved   : 5; // Use 5 bits
}; // Total size is 8 bits (1 byte)
```

### Linkage Specification (`extern "C"`)

To link C++ code with C code, you must tell the C++ compiler to use C-style name mangling for a function, which is typically just the function's name.

```cpp
// In a C++ file, to make a function callable from C code
extern "C" void my_cpp_func() { /* ... */ }

// In a C++ file, to call a C function
extern "C" {
    #include "c_header.h"
}
```

### More Attributes

- **`[[likely]]` and `[[unlikely]]` (C++20)**: Hints to the compiler about the likelihood of a code path, allowing it to optimize for the common case (e.g., by arranging branch prediction).
    ```cpp
    if (x > 0) [[likely]] {
        // This path is expected to be taken most of the time
    } else [[unlikely]] {
        // This path is rare
    }
    ```

### `if consteval` (C++23)

A statement that checks if the evaluation is happening within a constant evaluation context (i.e., at compile time).

```cpp
auto get_value() {
    if consteval {
        return 42; // Compile-time value
    } else {
        return 10; // Runtime value
    }
}
```

### `using enum` (C++20)

Brings the enumerators of a scoped enum into the local scope, avoiding the need to qualify them.

```cpp
enum class Color { Red, Green, Blue };
void set_color(Color c) {
    using enum Color;
    switch(c) {
        case Red:   /* ... */ break; // No Color:: needed
        case Green: /* ... */ break;
        case Blue:  /* ... */ break;
    }
}
```

### `std::source_location` (C++20)

A utility to capture information about the source code location (file name, line number, function name) where it is evaluated. Useful for logging and debugging.

```cpp
#include <iostream>
#include <source_location>

void log(const std::string& msg, const std::source_location& loc = std::source_location::current()) {
    std::cout << loc.file_name() << ":" << loc.line() << " " << msg << std::endl;
}

// log("Something happened"); // Prints file:line Something happened
```

### `std::jthread` (C++20)

An improvement over `std::thread` that automatically joins on destruction (preventing accidental termination) and supports cooperative cancellation.

```cpp
#include <thread> // for jthread
#include <chrono>

void task(std::stop_token token) {
    while (!token.stop_requested()) {
        // ... do work ...
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    // Cleanup
}

std::jthread jt(task);
// ... after some time ...
jt.request_stop(); // Ask the thread to stop
// jt automatically joins in its destructor
```

### `std::format` (C++20)

A modern, safe, and extensible way to format strings, similar to Python's f-strings or C#'s string interpolation.

```cpp
#include <format>
#include <string>

std::string s = std::format("Hello, {}! You are {} years old.", "world", 42);
// s is "Hello, world! You are 42 years old."
```

### `std::expected` (C++23)

A type that can hold either an expected value or an unexpected error value. It's an alternative to using exceptions or error codes for functions that can fail.

```cpp
#include <expected>
#include <string>

std::expected<int, std::string> parse_int(const std::string& s) {
    try {
        return std::stoi(s);
    } catch(...) {
        return std::unexpected("Failed to parse");
    }
}

auto result = parse_int("123");
if (result) { // Check if it has a value
    std::cout << "Value: " << *result << std::endl;
} else {
    std::cout << "Error: " << result.error() << std::endl;
}
```
