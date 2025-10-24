# C++ Deep Dive: Templates

Templates are a powerful feature of C++ that allow you to write generic code that works with any data type. They enable you to define functions and classes without specifying the exact types they will operate on, deferring that decision until the template is instantiated.

## 1. Function Templates

A function template is a blueprint for creating a function. The compiler generates a specific version of the function whenever you call it with a different data type.

```cpp
template<typename T> // or template<class T>
T max(T a, T b) {
    return a > b ? a : b;
}

int i = max(3, 7);          // Instantiates max<int>(int, int)
double d = max(3.14, 2.71); // Instantiates max<double>(double, double)
std::string s = max(std::string("hello"), std::string("world")); // Instantiates max<std::string>(...)
```

- **Template Argument Deduction**: In most cases, the compiler can deduce the template arguments from the function call arguments.
- **Explicit Specialization**: You can provide a specific implementation for a function template for a particular type.
    ```cpp
    // A specialized template for comparing C-style strings
    template<>
    const char* max<const char*>(const char* a, const char* b) {
        return std::strcmp(a, b) > 0 ? a : b;
    }
    ```

## 2. Class Templates

A class template is a blueprint for creating a class. It's commonly used for creating generic container classes.

```cpp
template<typename T>
class Box {
    T value;
public:
    Box(T val) : value(val) {}
    T get_value() const { return value; }
};

Box<int> int_box(42);             // Creates a Box that holds an int
Box<std::string> str_box("hello"); // Creates a Box that holds a string
```

- **Member Functions**: Member functions of a class template are themselves function templates. They are only instantiated if they are actually used.

## 3. Template Parameters

- **Type Template Parameters**: The most common type, representing a type (e.g., `typename T`, `class C`).
- **Non-Type Template Parameters**: Integral types, pointers, references, and more can be used as template parameters. This is often used for fixed-size arrays or compile-time values.
    ```cpp
    template<typename T, int Size>
    class FixedArray {
        T data[Size];
    public:
        int get_size() const { return Size; }
    };

    FixedArray<double, 10> my_array; // An array of 10 doubles
    ```
- **Template Template Parameters**: A template can take another template as a parameter. This is an advanced feature used for high-level generic programming.
    ```cpp
    template<typename T, template<typename> class Container>
    class MyContainer {
        Container<T> c;
    };

    // MyContainer can be instantiated with std::vector, std::list, etc.
    MyContainer<int, std::vector> my_vec_container;
    ```

## 4. Variadic Templates (C++11)

A variadic template is a template that can take a variable number of arguments. The arguments are packed into a **template parameter pack**.

```cpp
// A function that prints any number of arguments
template<typename T>
void print(const T& arg) {
    std::cout << arg << std::endl; // Base case for recursion
}

template<typename T, typename... Args>
void print(const T& first, const Args&... rest) {
    std::cout << first << ", ";
    print(rest...); // Recursive call with the rest of the arguments
}

print(1, "hello", 3.14); // Prints: 1, hello, 3.14
```
- **Fold Expressions (C++17)**: A more concise way to work with parameter packs.
    ```cpp
    template<typename... Args>
    auto sum(Args... args) {
        return (args + ...); // Unary right fold
    }
    int total = sum(1, 2, 3, 4, 5); // total is 15
    ```

## 5. `auto` as a Template Parameter (C++17/C++20)

You can use `auto` to declare non-type template parameters, and the compiler will deduce the type.

```cpp
template<auto Value>
void print_value() {
    std::cout << Value << std::endl;
}

print_value<42>();    // Instantiates with int
print_value<'c'>(); // Instantiates with char
```

## 6. Concepts (C++20)

Concepts are a major addition that allows you to place constraints on template parameters. They define requirements for a type, making templates safer and producing much clearer error messages.

```cpp
#include <concepts>

// This function will only compile if T is an integral type
template<std::integral T>
T add(T a, T b) {
    return a + b;
}

// Defining a custom concept
template<typename T>
concept HasDraw = requires(T t) {
    { t.draw() } -> std::same_as<void>;
};

template<HasDraw T>
void render(const T& object) {
    object.draw();
}
```
