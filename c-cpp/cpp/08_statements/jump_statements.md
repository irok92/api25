# Jump statements

## Jump statements

### [continue](https://en.cppreference.com/w/cpp/language/continue.html)

**Code-related Keywords:**
- `continue;` - Skip to next loop iteration

**Theory Keywords:**
- **loop control** - Jump to loop increment/condition
- **skip iteration** - Rest of current iteration not executed

**Example:**
```cpp
for (int i = 0; i < 10; ++i) {
    if (i % 2 == 0) {
        continue;         // Skip even numbers
    }
    std::cout << i << '\n';  // Only odd: 1, 3, 5, 7, 9
}

// With while:
int x = 0;
while (x < 10) {
    ++x;
    if (x == 5) continue;  // Skip when x == 5
    std::cout << x << '\n';
}
```

### [break](https://en.cppreference.com/w/cpp/language/break.html)

**Code-related Keywords:**
- `break;` - Exit innermost loop or switch

**Theory Keywords:**
- **loop termination** - Immediately exit loop
- **switch exit** - Exit switch statement

**Example:**
```cpp
// Exit loop:
for (int i = 0; i < 100; ++i) {
    if (i == 5) {
        break;            // Exit loop when i == 5
    }
    std::cout << i << '\n';  // Prints 0, 1, 2, 3, 4
}

// Search pattern:
std::vector<int> v = {10, 20, 30, 40};
int target = 30;
bool found = false;

for (const auto& elem : v) {
    if (elem == target) {
        found = true;
        break;            // Exit early when found
    }
}

// Only breaks innermost loop:
for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
        if (j == 1) break;  // Breaks inner loop only
        std::cout << i << "," << j << '\n';
    }
}
```

### [goto](https://en.cppreference.com/w/cpp/language/goto.html)

**Code-related Keywords:**
- `goto label;` - Jump to label
- `label:` - Label definition

**Theory Keywords:**
- **unconditional jump** - Jump anywhere in [function](../../07_functions/functions.md)
- **avoid in modern C++** - Use structured control flow instead
- **error handling** - Rare legitimate use (cleanup before return)

**Example:**
```cpp
void process() {
    // Legitimate use: cleanup on error
    if (!init()) goto cleanup;
    if (!allocate()) goto cleanup;
    if (!configure()) goto cleanup;
    
    // Success path
    return;
    
cleanup:
    deallocate();         // Common cleanup code
    return;
}

// Generally avoid:
int x = 0;
loop:                     // Label
    std::cout << x << '\n';
    ++x;
    if (x < 5) goto loop;  // Jump to label (use while instead!)
```

### [return](https://en.cppreference.com/w/cpp/language/return.html)

**Code-related Keywords:**
- `return;` - Exit void function
- `return value;` - Exit function with value
- `return {};` - Return default-constructed value

**Theory Keywords:**
- **function exit** - Terminate function execution
- **return value optimization (RVO)** - Compiler avoids copies
- **multiple returns** - Early exit from function

**Example:**
```cpp
// Void function:
void print(int x) {
    if (x < 0) {
        return;           // Early exit (no value)
    }
    std::cout << x << '\n';
}

// Return value:
int add(int a, int b) {
    return a + b;         // Return value
}

// Early return pattern:
std::string validate(int age) {
    if (age < 0) return "Invalid";
    if (age < 18) return "Minor";
    return "Adult";       // Default case
}

// Return by value (RVO optimized):
std::vector<int> createVector() {
    std::vector<int> v = {1, 2, 3};
    return v;             // RVO: no copy
}

// Return temporary:
int getValue() {
    return {};            // Returns 0 (default int)
}

std::string getString() {
    return {};            // Returns "" (default string)
}
```
