# Iteration statements (Loops)

## Iteration statements (Loops)

### [for](https://en.cppreference.com/w/cpp/language/for.html)

**Code-related Keywords:**
- `for (init; condition; increment) { }` - Traditional for loop
- `for (;;)` - Infinite loop

**Theory Keywords:**
- **loop control** - init, condition, increment
- **scope** - init variable scoped to loop

**Example:**
```cpp
// Standard for loop:
for (int i = 0; i < 5; ++i) {  // i scoped to loop
    std::cout << i << '\n';    // Prints 0, 1, 2, 3, 4
}

// Multiple variables:
for (int i = 0, j = 10; i < j; ++i, --j) {
    std::cout << i << ", " << j << '\n';
}

// Infinite loop:
for (;;) {
    // break or return to exit
}

// Empty parts:
int x = 0;
for (; x < 5; ) {         // No init or increment
    std::cout << x++;
}
```

### [range-for](https://en.cppreference.com/w/cpp/language/range-for.html) (C++11)

**Code-related Keywords:**
- `for (auto elem : container) { }` - Iterate over range (C++11)
- `for (auto& elem : container)` - Modify elements
- `const auto&` - Avoid copies for large elements

**Theory Keywords:**
- **range-based loop** - Simpler iteration over containers
- **begin/end** - Requires `.begin()` and `.end()` methods

**Example:**
```cpp
std::vector<int> v = {1, 2, 3, 4, 5};

// By value (copy):
for (auto elem : v) {
    std::cout << elem << '\n';
}

// By reference (modify):
for (auto& elem : v) {
    elem *= 2;            // v becomes {2, 4, 6, 8, 10}
}

// By const reference (efficient, no copy, read-only):
std::vector<std::string> words = {"hello", "world"};
for (const auto& word : words) {  // Avoid copying strings
    std::cout << word << '\n';
}

// With arrays:
int arr[] = {10, 20, 30};
for (int x : arr) {
    std::cout << x << '\n';
}

// C++20 init statement:
for (auto vec = getVector(); const auto& elem : vec) {  // vec scoped to loop
    std::cout << elem;
}
```

### [while](https://en.cppreference.com/w/cpp/language/while.html)

**Code-related Keywords:**
- `while (condition) { }` - Loop while condition true
- Condition checked before body

**Theory Keywords:**
- **pre-test loop** - Condition evaluated before each iteration
- **zero iterations** - Body may never execute

**Example:**
```cpp
int i = 0;
while (i < 5) {           // Check before body
    std::cout << i << '\n';
    ++i;
}

// Infinite loop:
while (true) {
    // break to exit
}

// Read until EOF:
std::string line;
while (std::getline(std::cin, line)) {  // Read line until EOF
    std::cout << line << '\n';
}
```

### [do-while](https://en.cppreference.com/w/cpp/language/do.html)

**Code-related Keywords:**
- `do { } while (condition);` - Loop, check condition after
- Body executes at least once

**Theory Keywords:**
- **post-test loop** - Condition evaluated after each iteration
- **minimum one iteration** - Body always executes at least once

**Example:**
```cpp
int i = 0;
do {
    std::cout << i << '\n';
    ++i;
} while (i < 5);          // Check after body

// Always executes once:
int x = 10;
do {
    std::cout << "Runs once\n";  // Executes even though condition false
} while (x < 0);

// Menu pattern:
int choice;
do {
    std::cout << "Enter choice (0 to quit): ";
    std::cin >> choice;
    // Process choice
} while (choice != 0);
```
