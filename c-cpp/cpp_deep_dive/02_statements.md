# C++ Deep Dive: Statements

This document covers the various types of statements in C++.

## 1. Labeled Statements

A label provides an identifier that can be the target of a `goto` statement.

- **`case` and `default` labels**: Used inside `switch` statements.
- **Identifier labels**: Used as a target for `goto`.
    ```cpp
    goto my_label;
    // ... some code ...
    my_label: // This is a label
        // Execution jumps here
    ```

## 2. Expression Statements

An expression statement is simply an expression followed by a semicolon. Most work in C++ is done by expression statements.

```cpp
int x = 5; // Declaration statement
x = x + 1; // Expression statement
my_function(x); // Expression statement (function call)
```

## 3. Compound Statements (Blocks)

A compound statement, or block, groups zero or more statements into a single unit. It's enclosed in curly braces `{}` and introduces a new scope.

```cpp
if (x > 0) { // Start of a block
    int y = 5; // y is local to this block
    x += y;
} // End of block, y is destroyed
```

## 4. Selection Statements

These statements control which part of the code is executed based on a condition.

- **`if` statement**: Executes code if a condition is true. Can be followed by `else if` and `else`.
    ```cpp
    if (condition) {
        // ...
    } else {
        // ...
    }
    ```
- **`switch` statement**: Selects a block of code to execute based on the value of an integral or enum type.
    ```cpp
    switch (value) {
        case 1:
            // ...
            break;
        case 2:
            // ...
            break;
        default:
            // ...
    }
    ```

## 5. Iteration Statements (Loops)

These statements execute a block of code repeatedly.

- **`while` loop**: Executes as long as a condition is true. The condition is checked *before* each iteration.
    ```cpp
    while (condition) {
        // ...
    }
    ```
- **`do-while` loop**: Executes a block of code once, and then continues as long as a condition is true. The condition is checked *after* each iteration.
    ```cpp
    do {
        // ...
    } while (condition);
    ```
- **`for` loop**: A compact way to create a loop with an initializer, a condition, and a post-iteration step.
    ```cpp
    for (int i = 0; i < 10; i++) {
        // ...
    }
    ```
- **Range-based `for` loop (C++11)**: Iterates over all elements of a range (e.g., an array, a container).
    ```cpp
    std::vector<int> v = {1, 2, 3};
    for (int element : v) {
        // ...
    }
    ```

## 6. Jump Statements

These statements unconditionally transfer control flow.

- **`break`**: Exits the nearest enclosing loop (`while`, `do-while`, `for`) or `switch` statement.
- **`continue`**: Skips the remainder of the current loop iteration and proceeds to the next one.
- **`return`**: Exits the current function and optionally returns a value to the caller.
- **`goto`**: Transfers control to a labeled statement within the same function. Its use is generally discouraged in favor of structured control flow.
- **`co_return`**: Exits a coroutine and returns a value.

## 7. Declaration Statements

A declaration introduces one or more names into the program. If it also specifies a value or function body, it's a definition.

```cpp
int x; // A declaration (and definition, as it's zero-initialized)
extern int y; // A pure declaration (y is defined elsewhere)
struct Point { int x, y; }; // A declaration and definition of a type
void my_func(); // A function declaration (prototype)
```

## 8. `try...catch` Blocks

Handles exceptions. The `try` block contains code that might throw an exception, and the `catch` block(s) handle the exception if it occurs.

```cpp
try {
    // Code that might throw
} catch (const std::exception& e) {
    // Handle the exception
} catch (...) {
    // Catch any other type of exception
}
```
