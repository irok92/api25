# Statements

## [Statements](https://en.cppreference.com/w/cpp/language/statements.html)

**Code-related Keywords:**
- `{ }` - Compound statement (block)
- `;` - Empty statement
- [Expression](../../04_expressions/expressions.md) statement - `expr;`
- [Declaration](../../05_declarations/declarations.md) statement - Variable/type declaration

**Theory Keywords:**
- **statement** - Unit of execution (ends with `;` or `{}`)
- **control flow** - if, switch, loops, jump statements
- **scope** - Braces create new scope

**Example:**
```cpp
// Empty statement:
;                         // Does nothing

// Expression statement:
x = 42;                   // Assignment
func();                   // Function call

// Declaration statement:
int y = 10;

// Compound statement (block):
{
    int local = 5;        // local scope
    std::cout << local;
}
// local not accessible here

// Control flow:
if (x > 0) {              // Conditional
    return x;
}

for (int i = 0; i < 10; ++i) {  // Loop
    std::cout << i;
}
```
