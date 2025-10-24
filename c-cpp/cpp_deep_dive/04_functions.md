# C++ Deep Dive: Functions

This document explores various aspects of functions in C++.

## 1. Function Declaration and Definition

- **Declaration (Prototype)**: Tells the compiler about a function's name, return type, and parameters.
    ```cpp
    int add(int a, int b);
    ```
- **Definition**: Provides the actual body of the function.
    ```cpp
    int add(int a, int b) {
        return a + b;
    }
    ```

## 2. Parameters and Arguments

- **Pass-by-value**: A copy of the argument is passed to the function. Changes inside the function do not affect the original argument.
    ```cpp
    void func(int x) { x = 10; }
    int a = 5;
    func(a); // a is still 5
    ```
- **Pass-by-reference**: A reference to the argument is passed. This is efficient and allows the function to modify the original argument.
    - **`&`**: Modifiable reference.
    - **`const &`**: Non-modifiable reference. Avoids a copy but prevents modification.
    ```cpp
    void modify(int& x) { x = 10; }
    void print(const std::string& s) { /* ... */ }

    int a = 5;
    modify(a); // a is now 10
    ```
- **Pass-by-pointer**: The memory address of the argument is passed. Allows modification and can be `nullptr`.
    ```cpp
    void modify_ptr(int* p) {
        if (p) { *p = 10; }
    }
    ```

## 3. Default Arguments

Function parameters can have default values. They must be at the end of the parameter list.

```cpp
void log(const std::string& msg, int level = 0) {
    // ...
}
log("Error"); // level is 0
log("Debug", 1); // level is 1
```

## 4. Function Overloading

Multiple functions can have the same name as long as they have different numbers or types of parameters. The compiler resolves which function to call based on the arguments.

```cpp
void print(int i) { /* ... */ }
void print(const std::string& s) { /* ... */ }

print(42);       // Calls the int version
print("hello");  // Calls the string version
```

## 5. `main` Function

The entry point of every C++ program. It has two standard forms:

```cpp
int main() { /* ... */ }
int main(int argc, char* argv[]) { /* ... */ }
```
- `argc`: The number of command-line arguments.
- `argv`: An array of C-style strings representing the arguments. `argv[0]` is the program name.

## 6. `inline` Functions

A hint to the compiler to insert the function's code directly at the call site, potentially avoiding the overhead of a function call. Often used for small, frequently called functions defined in header files.

```cpp
inline int max(int a, int b) {
    return a > b ? a : b;
}
```

## 7. `constexpr` and `consteval` Functions (C++11/C++20)

- **`constexpr`**: A function that *can* be evaluated at compile time if given compile-time constant arguments.
    ```cpp
    constexpr int factorial(int n) {
        return n <= 1 ? 1 : n * factorial(n - 1);
    }
    int arr[factorial(4)]; // Evaluated at compile time
    ```
- **`consteval`**: A function that *must* be evaluated at compile time. It's an "immediate function".
    ```cpp
    consteval int get_compile_time_value() { return 42; }
    ```

## 8. `noexcept` Specifier and Operator (C++11)

- **Specifier**: Declares that a function will not throw exceptions. This allows for compiler optimizations (e.g., with move semantics).
    ```cpp
    void process() noexcept { /* ... */ }
    ```
- **Operator**: A compile-time check to see if an expression is declared as non-throwing.
    ```cpp
    static_assert(noexcept(process()), "process() should be noexcept");
    ```

## 9. Trailing Return Type (C++11)

Allows specifying the return type after the parameter list. This is particularly useful when the return type depends on the types of the function's parameters, especially in templates.

```cpp
template<typename T, typename U>
auto add(T t, U u) -> decltype(t + u) {
    return t + u;
}
```
