# Statements

## Overview
### [Statements](https://en.cppreference.com/w/c/language/statements.html)
Execution units: expression, compound, selection, iteration, jump.

Statements are the building blocks of C programs - they include expression statements (ending with `;`), compound statements (code blocks in `{}`), selection statements (`if`, `switch`), iteration statements (loops), and jump statements (`return`, `break`, `continue`, `goto`).
Every statement either performs an action or controls program flow.

```c
int x = 5;        // Expression statement
{ int y = 0; }    // Compound statement
if (x) return;    // Selection, jump
while (x--);      // Iteration
```

## Conditional Statements
### [if](https://en.cppreference.com/w/c/language/if.html)
Execute code based on boolean condition.

The `if` statement executes code conditionally - if the condition (any expression) evaluates to non-zero (true), the first block executes; otherwise, the optional `else` block executes.
You can chain multiple conditions using `else if` to test multiple cases sequentially.

```c
if (x > 0) printf("positive");
else if (x < 0) printf("negative");
else printf("zero");
```

### [switch](https://en.cppreference.com/w/c/language/switch.html)
Multi-way branch based on integer value.

The `switch` statement provides multi-way branching based on an integer value - each `case` label must be a compile-time constant, and execution jumps to the matching case (or `default` if no match).
Don't forget `break` to exit the switch; without it, execution "falls through" to the next case (usually unintended).

- **case labels**: Must be compile-time constant integer expressions.
- **break**: Exits switch (without it, execution falls through to next case).
- **default**: Optional catch-all for values not matching any case.
- **fallthrough**: When break is omitted, execution continues to next case (often unintended).
```c
switch (x) {
  case 1: case 2: printf("1 or 2"); break;
  case 3: printf("3"); // fallthrough
  default: printf("other");
}
```

## Loop Statements
### [for](https://en.cppreference.com/w/c/language/for.html)
Loop with initialization, condition, and increment.

The `for` loop has three parts: initialization (once before loop), condition (checked before each iteration), and increment (after each iteration).
All three parts are optional - `for(;;)` creates an infinite loop, and C99+ allows declaring the loop variable in the initialization.

- **Initialization**: Executed once before loop starts (can declare variable in C99+).
- **Condition**: Checked before each iteration; loop continues if true.
- **Increment**: Executed after each iteration (despite name, can be any expression).
- All three parts are optional; `for(;;)` creates infinite loop.
```c
for (int i = 0; i < 10; i++) printf("%d ", i);
for (;;) { break; } // Infinite loop with break
```

### [while](https://en.cppreference.com/w/c/language/while.html)
Loop while condition is true (test before body).

The `while` loop tests the condition *before* executing the body - if the condition is false initially, the body never executes.
It's simpler than `for` when you don't need initialization and increment in one place.

```c
int i = 0;
while (i < 10) { printf("%d ", i++); }
while (getchar() != '\n'); // Skip to newline
```

### [do-while](https://en.cppreference.com/w/c/language/do.html)
Loop at least once, then test condition.

The `do-while` loop tests the condition *after* executing the body, guaranteeing at least one execution even if the condition is false.
Use this when the loop body must run at least once (e.g., menu systems, input validation).

```c
int i = 0;
do { printf("%d ", i++); } while (i < 10);
do { /* ... */ } while (0); // Run exactly once
```

## Jump Statements
### [continue](https://en.cppreference.com/w/c/language/continue.html)
Skip rest of loop body and continue with next iteration.

The `continue` statement skips the rest of the current loop iteration and jumps to the next iteration (checking the condition again).
Use it to skip processing for certain items without exiting the entire loop.

```c
for (int i = 0; i < 10; i++) {
  if (i % 2 == 0) continue; // Skip even numbers
  printf("%d ", i);
}
```

### [break](https://en.cppreference.com/w/c/language/break.html)
Exit innermost loop or switch statement.

The `break` statement immediately exits the innermost `for`, `while`, `do-while`, or `switch` statement.
Use it to exit a loop early when a condition is met (e.g., finding what you're looking for, or error conditions).

```c
while (1) {
  int c = getchar();
  if (c == '\n') break; // Exit loop
}
switch (x) { case 1: break; } // Exit switch
```

### [goto](https://en.cppreference.com/w/c/language/goto.html)
Jump to labeled statement (forward or backward).

The `goto` statement jumps unconditionally to a labeled statement within the same function - generally discouraged but useful for cleanup code or breaking out of nested loops.
Labels are identifiers followed by a colon (e.g., `cleanup:`), and you can only jump within the same function.

- **Label**: Identifier followed by colon (e.g., `cleanup:`).
- **Scope**: Can only jump within same function (not across functions).
- **Use cases**: Error handling, breaking out of nested loops (use sparingly).
- **Warning**: Overuse can create "spaghetti code" that's hard to follow.
```c
for (int i = 0; i < 10; i++)
  for (int j = 0; j < 10; j++)
    if (error) goto cleanup; // Exit nested loops
cleanup: printf("Done\n");
```

### [return](https://en.cppreference.com/w/c/language/return.html)
Exit function with optional value.

The `return` statement exits the current function immediately - for non-`void` functions, it must provide a value of the function's return type.
For `void` functions, you can use `return;` (no value) to exit early, or omit it entirely to return at the end.

```c
int max(int a, int b) {
  return a > b ? a : b;
}
void f(void) { return; } // No value for void
```
