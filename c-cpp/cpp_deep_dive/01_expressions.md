# C++ Deep Dive: Expressions

This document covers various C++ expressions in more detail.

## 1. Primary Expressions

These are the most basic building blocks of expressions.

- **Literals**: Fixed values directly in the source code.
    - *Integer literals*: `42`, `0x2A`, `0b101010`
    - *Floating-point literals*: `3.14`, `6.022e23`
    - *Character literals*: `'a'`, `'\n'`
    - *String literals*: `"hello"`
    - *Boolean literals*: `true`, `false`
    - *Pointer literal*: `nullptr`
- **`this` keyword**: Within a non-static member function, `this` is a pointer to the object for which the function was called.
    ```cpp
    class MyClass {
        int value;
    public:
        void set_value(int value) {
            this->value = value; // 'this' disambiguates member from parameter
        }
    };
    ```
- **Parenthesized expression**: An expression enclosed in parentheses, which has the same value and type as the original expression but can be used to control evaluation order.
    ```cpp
    int x = (2 + 3) * 4; // x is 20, not 14
    ```

## 2. Postfix Expressions

These expressions consist of a primary expression followed by an operator.

- **Subscript operator `[]`**: Accesses an element of an array or a container that overloads it.
    ```cpp
    int arr[] = {10, 20, 30};
    int x = arr[1]; // x is 20
    ```
- **Function call operator `()`**: Calls a function.
    ```cpp
    int add(int a, int b) { return a + b; }
    int sum = add(5, 3); // sum is 8
    ```
- **Member access operators `.` and `->`**: Access members of a `struct`, `class`, or `union`.
    ```cpp
    struct Point { int x, y; };
    Point p1 = {1, 2};
    p1.x = 10; // Access with . for objects

    Point* p2 = &p1;
    p2->y = 20; // Access with -> for pointers to objects
    ```
- **Postfix increment/decrement `++` and `--`**: Increments or decrements the value of the operand, but the expression evaluates to the value *before* the operation.
    ```cpp
    int i = 5;
    int j = i++; // j is 5, i becomes 6
    ```

## 3. Unary Expressions

These expressions consist of an operator followed by an operand.

- **Prefix increment/decrement `++` and `--`**: Increments or decrements the value of the operand, and the expression evaluates to the value *after* the operation.
    ```cpp
    int i = 5;
    int j = ++i; // j is 6, i is 6
    ```
- **`sizeof` and `sizeof...`**:
    - `sizeof`: Returns the size in bytes of a type or an object.
        ```cpp
        size_t s = sizeof(int); // s is typically 4 or 8
        ```
    - `sizeof...`: Returns the number of elements in a template parameter pack.
        ```cpp
        template<typename... Args>
        size_t count() {
            return sizeof...(Args);
        }
        // count<int, double, char>() returns 3
        ```
- **`co_await`**: Suspends a coroutine and awaits the result of an awaitable object.
    ```cpp
    // Conceptual example
    async_task<int> my_task = get_result_async();
    int result = co_await my_task; // Suspends until my_task is ready
    ```

## 4. `new` and `delete` Expressions

- **`new` expression**: Allocates memory on the heap and constructs an object.
    ```cpp
    int* p_int = new int(42);
    MyClass* p_obj = new MyClass();
    ```
- **`delete` expression**: Destructs an object and deallocates memory.
    ```cpp
    delete p_int;
    delete p_obj;
    ```
- **Array `new[]` and `delete[]`**: For allocating and deallocating arrays.
    ```cpp
    int* p_arr = new int[10];
    delete[] p_arr; // Must use delete[] for arrays
    ```

## 5. `throw`-expression

Throws an exception, which can be caught by a `try...catch` block.

```cpp
if (value < 0) {
    throw std::runtime_error("Value cannot be negative");
}
```

## 6. Assignment Operators

- **Simple assignment `=`**: Assigns the value of the right operand to the left operand.
- **Compound assignment**: Combines an arithmetic/bitwise operation with assignment (e.g., `+=`, `-=`, `*=`, `/=`, `%=`, `&=`, `|=`, `^=`, `<<=`, `>>=`).
    ```cpp
    int x = 10;
    x += 5; // Equivalent to x = x + 5; x is now 15
    ```

## 7. Comma Operator `,`

Evaluates its left operand (and discards the result), then evaluates its right operand and returns the result of the right operand. It's often used to sequence operations in a single line, like in a `for` loop.

```cpp
int a = 1, b = 2, c = 3;
int result = (a++, b += a, c += b); // result is 6 (value of c)
// a becomes 2, b becomes 4, c becomes 6
```
