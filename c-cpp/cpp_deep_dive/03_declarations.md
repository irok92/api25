# C++ Deep Dive: Declarations

A declaration introduces names and their types into a C++ program. A **definition** is a declaration that also provides the full implementation or value.

## 1. Specifiers

Specifiers modify the type or linkage of a declared entity.

- **Storage class specifiers**:
    - **`static`**:
        - Inside a function: The variable retains its value between calls.
        - At global/namespace scope: The variable or function has internal linkage (visible only within the current file).
        - Inside a class: The member is shared among all instances of the class.
    - **`extern`**: Declares an entity that is defined in another translation unit. It specifies external linkage.
    - **`thread_local` (C++11)**: The variable has a unique instance for each thread.
    - **`register`**: A hint to the compiler to store a variable in a CPU register. Mostly deprecated and ignored by modern compilers.
- **Function specifiers**:
    - **`inline`**: A hint to the compiler to perform inline expansion of a function, avoiding a function call.
    - **`virtual`**: For member functions, indicates that the function can be overridden by a derived class.
    - **`explicit`**: For constructors or conversion operators, prevents their use in implicit conversions.
- **Type specifiers**:
    - **`const`**: The object cannot be modified.
    - **`volatile`**: The object's value can be changed by means outside the program's control. Prevents compiler optimizations on that variable.
    - **`constexpr`**: Specifies that a variable or function can be evaluated at compile time.

## 2. Type Aliases

- **`typedef`**: Creates an alias for a type.
    ```cpp
    typedef unsigned long ulong;
    typedef void (*FuncPtr)(int);
    ```
- **`using` (C++11)**: A more modern and flexible way to create type aliases, especially with templates.
    ```cpp
    using ulong = unsigned long;
    using IntVector = std::vector<int>;

    template<typename T>
    using Ptr = T*;
    Ptr<double> p_double; // Same as double*
    ```

## 3. `using` Declarations and Directives

- **`using` declaration**: Brings a specific name from a namespace into the current scope.
    ```cpp
    #include <iostream>
    using std::cout; // Bring only std::cout into scope
    cout << "Hello";
    ```
- **`using` directive**: Brings *all* names from a namespace into the current scope. Often discouraged in header files to avoid name collisions.
    ```cpp
    using namespace std;
    cout << "Hello";
    ```

## 4. Namespaces

A namespace provides a scope to prevent name conflicts.

- **Defining a namespace**:
    ```cpp
    namespace MyMath {
        int add(int a, int b) { return a + b; }
    }
    int result = MyMath::add(2, 3);
    ```
- **Nested namespaces**:
    ```cpp
    namespace MyLib::Utils { // C++17 nested syntax
        void helper() {}
    }
    ```
- **Anonymous namespaces**: A namespace without a name. Its members have internal linkage, making them accessible only within the current file. This is a superior alternative to using `static` for global variables/functions.
    ```cpp
    namespace {
        void internal_helper() { /* ... */ }
    }
    ```
- **Namespace alias**:
    ```cpp
    namespace fs = std::filesystem;
    ```

## 5. Enumerations

- **Unscoped enumeration (`enum`)**: The enumerators are in the same scope as the enum itself and can implicitly convert to integers.
    ```cpp
    enum Color { RED, GREEN, BLUE };
    Color c = RED;
    int i = BLUE; // i is 2
    ```
- **Scoped enumeration (`enum class` or `enum struct`) (C++11)**: Strongly typed and scoped. The enumerators are not implicitly converted to integers. This is the preferred modern approach.
    ```cpp
    enum class Status { Ok, Error };
    Status s = Status::Ok;
    // int i = s; // Error: no implicit conversion
    int i = static_cast<int>(s); // OK: explicit conversion
    ```
- **Underlying type**: You can specify the underlying integral type for an enumeration.
    ```cpp
    enum class Code : uint8_t { Success = 0, Fail = 1 };
    ```

## 6. `auto` and `decltype`

- **`auto` (C++11)**: Deduces the type of a variable from its initializer.
    ```cpp
    auto i = 42; // i is int
    auto s = "hello"; // s is const char*
    auto& v = my_vector; // v is a reference to my_vector
    ```
- **`decltype` (C++11)**: Inspects the declared type of an entity or expression.
    ```cpp
    int x = 0;
    decltype(x) y = 5; // y is int

    std::vector<int> vec;
    decltype(vec.begin()) it = vec.begin(); // it has the type of the iterator
    ```

## 7. `static_assert`

A declaration that performs an assertion at compile time. If the condition is false, the compilation fails.

```cpp
template<typename T>
void process(T val) {
    static_assert(std::is_integral_v<T>, "process() only works with integral types.");
    // ...
}
```
