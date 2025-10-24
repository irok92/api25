# Comprehensive C Language Example

This single example demonstrates most practical C language features in a cohesive program. Each section builds upon previous concepts, showing how they work together in real code.

**Related concepts:** [Basic concepts](basic_concepts.md#basic-concepts), [The main function](basic_concepts.md#the-main-function), [Translation phases](basic_concepts.md#translation-phases)

## Complete Program

### Preprocessor and Macros

The [preprocessor](keywords_and_preprocessor.md#preprocessor) runs before compilation, handling [#include](keywords_and_preprocessor.md#include), [#define](keywords_and_preprocessor.md#define----), and [conditional compilation](keywords_and_preprocessor.md#if---ifdef---ifndef---elif).

**Related:** [Comments](basic_concepts.md#comments), [Keywords](keywords_and_preprocessor.md#keywords)

```c
// Comments: single-line documentation
/* Multi-line comments
   for longer explanations */

// Preprocessor directives
#include <stdio.h>      // Standard I/O functions
#include <stdlib.h>     // Memory allocation, exit codes
#include <stdarg.h>     // Variadic functions
#include <stdbool.h>    // bool type (C99+)
#include <stddef.h>     // NULL, size_t

// Conditional compilation
#ifdef DEBUG
  #define LOG(msg) printf("DEBUG: %s\n", msg)
#else
  #define LOG(msg)  // Empty in release builds
#endif

// Macro definitions - IMPORTANT: Always use parentheses in macro definitions!
#define MAX_SIZE 100
#define MIN(a, b) ((a) < (b) ? (a) : (b))  // Correct: fully parenthesized
#define SQUARE(x) ((x) * (x))               // Correct: SQUARE(x+1) = (x+1)*(x+1)
// Bad example: #define SQUARE(x) x*x      // WRONG: SQUARE(x+1) = x+1*x+1 (precedence issue!)

// String literals and character constants
#define WELCOME_MSG "Welcome to C Programming"
#define NEWLINE '\n'
```

### Type System: Custom Types and Qualifiers

[Typedef](initialization_and_declarations.md#typedef) creates type aliases. [Enumerations](initialization_and_declarations.md#enumerations) define named integer constants. [Structures](initialization_and_declarations.md#struct) group related data, [unions](initialization_and_declarations.md#union) share memory, and [bit-fields](initialization_and_declarations.md#bit-fields) pack data efficiently.

**Related:** [Type compatibility](basic_concepts.md#type), [Arithmetic types](basic_concepts.md#arithmetic-types), [const](initialization_and_declarations.md#const), [volatile](initialization_and_declarations.md#volatile), [Storage duration and Linkage](initialization_and_declarations.md#storage-duration-and-linkage)

```c
// Type aliases
typedef unsigned int uint;
typedef struct Point Point;  // Forward declaration for cleaner syntax

// Enumerations
enum Status {
    SUCCESS = 0,    // Explicit values
    ERROR_FILE = 1,
    ERROR_MEMORY = 2,
    ERROR_INVALID = 3
};

enum Color { RED, GREEN, BLUE };  // Implicit values: 0, 1, 2

// Structure definition
struct Point {
    int x;
    int y;
};

// Struct with bit-fields (memory optimization)
struct Flags {
    unsigned int is_active : 1;   // 1 bit
    unsigned int priority : 3;    // 3 bits (0-7)
    unsigned int reserved : 28;   // Remaining bits
};

// Union (shares memory between members)
union Data {
    int i;
    float f;
    char str[20];
};  // Size = largest member

// Type qualifiers
const int GLOBAL_CONSTANT = 42;           // Cannot be modified
static int file_scope_var = 0;            // Internal linkage (file-only)
extern int external_var;                  // Declared elsewhere
```

### Function Declarations

[Function declarations](functions.md#function-declaration) (prototypes) specify the interface before [definition](functions.md#function-definition). [Variadic arguments](functions.md#variadic-arguments) allow variable parameter counts, and [inline](functions.md#inline-c99) suggests compiler optimization.

**Related:** [Scope](basic_concepts.md#scope), [Pointers](initialization_and_declarations.md#pointers)

```c
// Function declarations (prototypes)
int add(int a, int b);
void print_array(const int *arr, size_t size);  // const prevents modification
int *allocate_array(size_t size);
void swap(int *a, int *b);                      // Pass-by-pointer for modification
void variadic_sum(int count, ...);              // Variadic function
static void helper(void);                        // Internal linkage (file-only)
inline int fast_multiply(int x) { return x * x; }  // Inline suggestion (C99)

// Function with struct parameter and return
Point create_point(int x, int y);
void move_point(Point *p, int dx, int dy);
```

### The Main Function and Variables

The [main function](basic_concepts.md#the-main-function) is the program entry point. [Arithmetic types](basic_concepts.md#arithmetic-types) are the foundation of variables, and [scalar initialization](initialization_and_declarations.md#scalar) sets their initial values.

**Related:** [Identifier](basic_concepts.md#identifier), [Objects and Alignment](basic_concepts.md#objects-and-alignment), [Lifetime](basic_concepts.md#lifetime)

```c
// Main function - program entry point
int main(int argc, char *argv[]) {  // argc: argument count, argv: argument values
    // argc is always >= 1 (program name is argv[0])
    
    // Basic arithmetic types
    // IMPORTANT: Local variables contain garbage until initialized - always initialize!
    char c = 'A';                    // Character (often 8 bits)
    int i = 42;                      // Integer (usually 32 bits)
    long l = 1000000L;              // Long integer (suffix L)
    float f = 3.14f;                // Single precision (suffix f)
    double d = 2.71828;             // Double precision
    unsigned int u = 100u;          // Unsigned (no negatives, suffix u)
    size_t sz = sizeof(int);        // Unsigned type for sizes
```

**Memory Layout (Stack):**
```
Higher addresses
┌─────────────────┐
│ sz = 4          │ (size_t, typically 8 bytes)
├─────────────────┤
│ u = 100         │ (unsigned int, 4 bytes)
├─────────────────┤
│ d = 2.71828     │ (double, 8 bytes)
├─────────────────┤
│ f = 3.14        │ (float, 4 bytes)
├─────────────────┤
│ l = 1000000     │ (long, 8 bytes on 64-bit)
├─────────────────┤
│ i = 42          │ (int, 4 bytes)
├─────────────────┤
│ c = 'A' (65)    │ (char, 1 byte)
└─────────────────┘
Lower addresses
(Stack grows downward)
```

### Literals and Constants

Different forms of [integer constants](expressions.md#integer-constants), [floating constants](expressions.md#floating-constants), [character constants](expressions.md#character-constants), and [string literals](expressions.md#string-literals) provide compile-time values.

**Related:** [Constants and literals](expressions.md#constants-and-literals), [ASCII chart](basic_concepts.md#ascii-chart)

```c
    // Integer literals in different bases
    int decimal = 42;
    int octal = 052;                // Starts with 0 (octal 52 = decimal 42)
    int hex = 0x2A;                 // Starts with 0x (hex 2A = decimal 42)
    // int binary = 0b101010;       // C23 only
```

### Operators: Arithmetic and Assignment

[Arithmetic operators](expressions.md#arithmetic-operators) perform math, while [assignment operators](expressions.md#assignment-operators) store values. [Increment/decrement](expressions.md#increment-decrement) modify variables.

**Related:** [Expressions](expressions.md#expressions), [Operator precedence](expressions.md#operator-precedence), [Evaluation order and sequencing](expressions.md#evaluation-order-and-sequencing)

```c
    // Arithmetic operators
    int sum = 10 + 5;
    int diff = 10 - 5;
    int product = 10 * 5;
    int quotient = 10 / 3;          // Integer division: 3 (not 3.333...) - common source of bugs!
    int remainder = 10 % 3;         // Modulo: 1
    
    // Assignment operators
    int x = 10;
    x += 5;                         // Equivalent to: x = x + 5
    x *= 2;                         // Equivalent to: x = x * 2
    
    // Increment/decrement
    int pre = ++x;                  // Pre-increment: increment first, then use value
    int post = x++;                 // Post-increment: use value first, then increment
    // Avoid: i = i++; (undefined behavior! Compiler can do anything - crash, wrong result, etc.)
```

### Boolean Logic and Comparisons

[Comparison operators](expressions.md#comparison-operators) test relationships, and [logical operators](expressions.md#logical-operators) combine conditions with short-circuit evaluation.

**Related:** [Value categories](expressions.md#value-categories)

```c
    // Comparison operators
    bool is_equal = (x == 10);
    bool not_equal = (x != 10);
    bool greater = (x > 10);
    bool less_eq = (x <= 10);
    
    // Logical operators (short-circuit evaluation)
    bool and_result = (x > 0 && x < 100);   // Second part not evaluated if first is false
    bool or_result = (x < 0 || x > 100);    // Second part not evaluated if first is true
    bool not_result = !(x == 0);
    // Use short-circuiting: if (ptr != NULL && *ptr > 0) - safe because *ptr only runs if ptr is valid
```

### Control Flow: Conditionals

The [if](statements.md#if) statement enables conditional execution, while the [switch](statements.md#switch) statement handles multi-way branching.

**Related:** [Statements](statements.md#statements), [Punctuation](basic_concepts.md#punctuation)

```c
    // Conditional (if-else)
    if (x > 50) {
        printf("x is large\n");
    } else if (x > 20) {
        printf("x is medium\n");
    } else {
        printf("x is small\n");
    }
    
    // Ternary operator (conditional expression)
    int max = (x > 10) ? x : 10;    // Equivalent to: if (x > 10) max = x; else max = 10;
```

```c
    // Switch statement
    enum Status status = SUCCESS;
    switch (status) {
        case SUCCESS:
            printf("Operation succeeded\n");
            break;              // Without break, falls through to next case!
        case ERROR_FILE:
        case ERROR_MEMORY:      // Multiple cases can share code
            printf("Error occurred\n");
            break;
        default:                // Optional catch-all
            printf("Unknown status\n");
    }
```

### Arrays and Indexing

[Arrays](initialization_and_declarations.md#arrays) store sequential elements with [array initialization](initialization_and_declarations.md#array) syntax. Multi-dimensional arrays extend to tables and matrices.

**Related:** [sizeof](expressions.md#sizeof)

```c
    // Arrays
    int numbers[5] = {1, 2, 3, 4, 5};           // Fixed size
    int partial[5] = {1, 2};                    // Rest initialized to 0: {1, 2, 0, 0, 0}
    int inferred[] = {1, 2, 3};                 // Size inferred: 3 elements
    
    // Array indexing (0-based)
    numbers[0] = 10;                            // First element
    int last = numbers[4];                      // Last element
    // numbers[5] = 100;                        // ERROR: out of bounds! No bounds checking - causes crashes/corruption!
    
    // Multi-dimensional arrays
    int matrix[2][3] = {
        {1, 2, 3},
        {4, 5, 6}
    };
    int element = matrix[1][2];                 // Value: 6
```

**Memory Layout:**
```
Array: int numbers[5] = {10, 2, 3, 4, 5}
       Index:  [0] [1] [2] [3] [4]
              ┌────┬────┬────┬────┬────┐
      numbers │ 10 │  2 │  3 │  4 │  5 │
              └────┴────┴────┴────┴────┘
      Address: 0x100 0x104 0x108 0x10C 0x110
               (each int = 4 bytes)

Multi-dimensional: int matrix[2][3]
       
       matrix ──► Row 0: [0][0]=1  [0][1]=2  [0][2]=3
                  Row 1: [1][0]=4  [1][1]=5  [1][2]=6
       
       Actual memory (contiguous):
       ┌───┬───┬───┬───┬───┬───┐
       │ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │
       └───┴───┴───┴───┴───┴───┘
```

### Loops: Iteration

[For](statements.md#for) loops iterate with a counter, [while](statements.md#while) loops test before execution, and [do-while](statements.md#do-while) loops test after. [Break](statements.md#break) exits loops, [continue](statements.md#continue) skips to next iteration.

**Related:** [return](statements.md#return)

```c
    // For loop
    for (int j = 0; j < 5; j++) {               // C99+: can declare variable in loop
        printf("%d ", numbers[j]);
    }
    printf("\n");
    
    // Infinite loop variations
    // for (;;) { break; }                      // Infinite loop (all parts optional)
    
    // While loop (test before body)
    int count = 0;
    while (count < 3) {
        printf("Count: %d\n", count);
        count++;
    }
    
    // Do-while loop (test after body - executes at least once)
    int n = 0;
    do {
        printf("n = %d\n", n);
        n++;
    } while (n < 3);
```

```c
    // Break and continue
    for (int k = 0; k < 10; k++) {
        if (k == 3) continue;                   // Skip rest of iteration, go to next
        if (k == 7) break;                      // Exit loop entirely
        printf("%d ", k);                       // Prints: 0 1 2 4 5 6
    }
    printf("\n");
```

### Goto and Labels

[Goto](statements.md#goto) provides unconditional jumps, mainly useful for cleanup in error handling paths.

**Related:** [Lookup and Name Spaces](basic_concepts.md#lookup-and-name-spaces)

```c
    // Goto (generally discouraged, but useful for cleanup in error handling)
    FILE *file = fopen("test.txt", "r");
    if (file == NULL) {
        printf("File open failed\n");
        goto cleanup;                           // Jump to cleanup label
    }
    // ... do work with file ...
    fclose(file);
    
cleanup:
    printf("Cleanup complete\n");
```

### Pointers and Memory Addresses

[Pointers](initialization_and_declarations.md#pointers) store memory addresses. The `&` operator gets addresses, `*` dereferences them. [Member access and indirection](expressions.md#member-access-and-indirection) use `.` and `->` operators.

**Related:** [Declarations](initialization_and_declarations.md#declarations)

```c
    // Pointers
    int value = 100;
    int *ptr = &value;                          // ptr stores the address of value
    int deref = *ptr;                           // Dereference: get value at address (100)
    *ptr = 200;                                 // Modify value through pointer
    printf("value is now: %d\n", value);        // Prints: 200
    
    // NULL pointer
    int *null_ptr = NULL;                       // NULL = 0 (no valid address)
    // *null_ptr = 5;                           // ERROR: dereferencing NULL crashes! ALWAYS check if (ptr != NULL) before *ptr
    
    // Pointer arithmetic
    int arr[5] = {10, 20, 30, 40, 50};
    int *p = arr;                               // Array name decays to pointer to first element
    printf("First: %d\n", *p);                  // 10
    printf("Second: %d\n", *(p + 1));          // 20 (moves by sizeof(int) bytes)
    p++;                                        // Move to next element
    printf("Now points to: %d\n", *p);         // 20
```

**Memory Visualization:**
```
Variable and Pointer:
        
        value = 200              ptr = 0x7FFC (stores address of value)
       ┌─────────┐              ┌────────────┐
       │   200   │◄─────────────│  0x7FFC    │
       └─────────┘              └────────────┘
     Address: 0x7FFC          Address: 0x8000

     To get value through ptr: *ptr → follows arrow → 200

Array and Pointer Arithmetic:
        
        arr[5] = {10, 20, 30, 40, 50}
        ┌────┬────┬────┬────┬────┐
        │ 10 │ 20 │ 30 │ 40 │ 50 │
        └────┴────┴────┴────┴────┘
        0x100 0x104 0x108 0x10C 0x110
          ▲
          │
          p (initially points here)
          
        p + 1 ──► 0x104 (advances by sizeof(int) = 4 bytes)
        p + 2 ──► 0x108
        *(p + 1) ──► dereference at 0x104 ──► value 20

Pointer to Pointer:
        
        val = 42        ptr1 = 0x2000       ptr2 = 0x3000
       ┌──────┐        ┌──────────┐        ┌──────────┐
       │  42  │◄───────│  0x2000  │◄───────│  0x3000  │
       └──────┘        └──────────┘        └──────────┘
      Addr: 0x2000    Addr: 0x3000       Addr: 0x4000
      
       **ptr2 means: follow ptr2 → get 0x3000 → follow 0x3000 → get 0x2000 → get 42
```

```c
    // Arrays and pointers relationship
    for (int m = 0; m < 5; m++) {
        printf("%d ", arr[m]);                  // Array notation
        printf("%d ", *(arr + m));              // Equivalent pointer notation
        printf("\n");
    }
    
    // Pointer to pointer
    int val = 42;
    int *ptr1 = &val;
    int **ptr2 = &ptr1;                         // Pointer to pointer
    printf("Value via ptr2: %d\n", **ptr2);    // Double dereference: 42
```

### Structures and Structure Access

[Structures](initialization_and_declarations.md#struct) bundle related data. [Structure/Union initialization](initialization_and_declarations.md#structure-union) sets initial values.

```c
    // Structures
    Point p1 = {10, 20};                        // Initialize with values
    Point p2 = create_point(5, 15);            // Create via function
    
    // Structure member access
    printf("p1: (%d, %d)\n", p1.x, p1.y);      // Dot operator for direct access
    
    // Pointer to structure
    Point *p_ptr = &p1;
    printf("Via pointer: (%d, %d)\n", p_ptr->x, p_ptr->y);  // Arrow operator
    // Equivalent: (*p_ptr).x but -> is cleaner
    
    move_point(&p1, 5, 5);                      // Pass by pointer to modify
    printf("After move: (%d, %d)\n", p1.x, p1.y);
```

**Memory Layout:**
```
Struct: Point p1 = {10, 20}
        
        struct Point {
            int x;  // 4 bytes
            int y;  // 4 bytes
        };
        
        p1 in memory:
        ┌─────────┬─────────┐
        │ x = 10  │ y = 20  │
        └─────────┴─────────┘
        0x1000    0x1004
        
        Total size: 8 bytes (4 + 4)

Pointer to Struct:
        
        Point *p_ptr = &p1;
        
        p_ptr ──► ┌─────────┬─────────┐
                  │ x = 10  │ y = 20  │
                  └─────────┴─────────┘
                  0x1000    0x1004
        
        p_ptr->x  means: follow pointer, access x member
        Equivalent to: (*p_ptr).x
```

### Unions and Bit-fields

[Unions](initialization_and_declarations.md#union) overlay members in the same memory. [Bit-fields](initialization_and_declarations.md#bit-fields) pack flags into minimal space.

```c
    // Unions (different interpretation of same memory)
    union Data data;
    data.i = 42;
    printf("As int: %d\n", data.i);
    data.f = 3.14f;                             // Overwrites the int value!
    printf("As float: %f\n", data.f);
    // printf("%d", data.i);                    // ERROR: i no longer valid (only last written member is)
    
    // Bit-fields
    struct Flags flags = {1, 5, 0};
    printf("Active: %u, Priority: %u\n", flags.is_active, flags.priority);
```

**Memory Visualization:**
```
Union: All members share the same memory location
        
        union Data {
            int i;        // 4 bytes
            float f;      // 4 bytes
            char str[20]; // 20 bytes
        };
        
        Same Memory Location:
        ┌──────────────────────────┐
        │      (largest: 20 bytes) │
        └──────────────────────────┘
        
        When data.i = 42:
        ┌────────┬───────────────────┐
        │   42   │  (unused space)   │
        └────────┴───────────────────┘
        
        When data.f = 3.14:
        ┌────────┬───────────────────┐
        │  3.14  │  (unused space)   │ (overwrites the 42!)
        └────────┴───────────────────┘
        
        Only ONE member is valid at a time!

Bit-fields: Pack multiple values in single bytes
        
        struct Flags {
            unsigned int is_active : 1;  // 1 bit
            unsigned int priority : 3;   // 3 bits
            unsigned int reserved : 28;  // 28 bits
        };                               // Total: 32 bits = 4 bytes
        
        Memory (32 bits total):
        ┌─┬───┬────────────────────────────┐
        │1│101│0000000000000000000000000000│
        └─┴───┴────────────────────────────┘
         │ │   │
         │ │   └─ reserved (28 bits)
         │ └───── priority = 5 (3 bits: 101 in binary)
         └─────── is_active = 1 (1 bit)
        
        Saves memory: 3 separate ints would use 12 bytes instead of 4!
```

### Type Conversions and Sizeof

[Implicit conversions](expressions.md#implicit-conversions) happen automatically, [cast operator](expressions.md#cast-operator) forces explicit conversion. [sizeof](expressions.md#sizeof) returns type or object size at compile-time.

**Related:** [Constant expressions](expressions.md#constant-expressions)

```c
    // Enumerations
    enum Color color = RED;
    if (color == RED) {
        printf("Color is red\n");
    }
    
    // Type casting
    int int_val = 10;
    double double_val = (double)int_val;        // Explicit cast
    double auto_cast = int_val;                 // Implicit conversion
    
    int truncated = (int)3.99;                  // Cast to int truncates: 3 (not 4!)
    
    // Sizeof operator (compile-time, returns size_t - use %zu format)
    printf("Size of int: %zu bytes\n", sizeof(int));
    printf("Size of Point: %zu bytes\n", sizeof(Point));
    printf("Array elements: %zu\n", sizeof(numbers) / sizeof(numbers[0]));  // Portable way to get array length
```

### Dynamic Memory Allocation

Heap memory is allocated with `malloc`/`realloc` and freed with `free`. Always check for allocation failures and free exactly once.

```c
    // Dynamic memory allocation (HEAP memory - manual management required!)
    // MEMORY MODEL: Stack = auto variables (fast, limited, auto-freed), Heap = malloc (slower, large, manual)
    int *dynamic = (int *)malloc(10 * sizeof(int));  // Allocate array of 10 ints
    if (dynamic == NULL) {                      // ALWAYS check malloc return value!
        fprintf(stderr, "Memory allocation failed!\n");
        return ERROR_MEMORY;
    }
    
    // Use allocated memory
    for (int a = 0; a < 10; a++) {
        dynamic[a] = a * 10;
    }
    
    // Resize allocation
    int *resized = (int *)realloc(dynamic, 20 * sizeof(int));  // Grow to 20 elements
    if (resized == NULL) {
        free(dynamic);                          // Free original on failure
        return ERROR_MEMORY;
    }
    dynamic = resized;
    
    // Free when done - CRITICAL: Every malloc needs exactly one free to prevent memory leaks!
    free(dynamic);                              // Memory leak if you forget this
    dynamic = NULL;                             // Best practice: set to NULL to catch use-after-free bugs
    // free(dynamic);                           // ERROR: double-free crashes!
    // *dynamic = 5;                            // ERROR: use-after-free (undefined behavior)
```

**Stack vs Heap Memory:**
```
┌─────────────────────────────────────────────────────────────┐
│                     MEMORY LAYOUT                           │
├─────────────────────────────────────────────────────────────┤
│                                                             │
│  HIGH ADDRESSES                                             │
│  ┌───────────────────────────────┐                         │
│  │         STACK                 │ ← Automatic storage     │
│  │  (local variables)            │   Fast, limited size    │
│  │                               │   Auto-freed on scope   │
│  │  int x = 10;  ┌────┐          │   exit                  │
│  │               │ 10 │          │                         │
│  │               └────┘          │                         │
│  │                               │                         │
│  │  (grows downward ▼)           │                         │
│  └───────────────────────────────┘                         │
│           ║                                                 │
│           ║  (free space)                                   │
│           ║                                                 │
│  ┌───────────────────────────────┐                         │
│  │  (grows upward ▲)             │                         │
│  │                               │                         │
│  │         HEAP                  │ ← Dynamic allocation    │
│  │  (malloc/free)                │   Slower, large size    │
│  │                               │   Manual management     │
│  │  int *p = malloc(40);         │                         │
│  │                               │                         │
│  │  p ──► ┌────┬────┬────┬────┐ │   Must free() when     │
│  │        │ 0  │ 10 │ 20 │ 30 │ │   done to prevent      │
│  │        └────┴────┴────┴────┘ │   memory leaks!        │
│  └───────────────────────────────┘                         │
│  LOW ADDRESSES                                              │
└─────────────────────────────────────────────────────────────┘

After malloc(10 * sizeof(int)):

    Stack                          Heap
    ┌────────────┐                ┌────┬────┬────┬────┬────┐
    │ dynamic ───┼───────────────►│ 0  │ 10 │ 20 │ 30 │... │
    │ (pointer)  │                └────┴────┴────┴────┴────┘
    └────────────┘                (40 bytes allocated)
    
After free(dynamic):

    Stack                          Heap
    ┌────────────┐                ┌────────────────────────┐
    │ dynamic    │                │  (memory returned to   │
    │ (dangling) │  ✗             │   system, don't use!)  │
    └────────────┘                └────────────────────────┘
    
    Set to NULL to prevent use-after-free bugs!
```

### String Handling

Strings are null-terminated character arrays. String literals are read-only. Use standard library functions for operations.

```c
    // String handling (strings are char arrays)
    char str1[] = "Hello";                      // Array: {'H','e','l','l','o','\0'}
    char *str2 = "World";                       // String literal (read-only in memory)
    // str2[0] = 'w';                           // ERROR: modifying string literal is undefined!
    
    char buffer[50];
    sprintf(buffer, "%s %s", str1, str2);       // String formatting
    printf("%s\n", buffer);
    
    // String comparison - IMPORTANT: Never use == for strings (compares addresses, not content!)
    if (strcmp(str1, "Hello") == 0) {           // Use strcmp - returns 0 if equal
        printf("Strings match\n");
    }
    // if (str1 == "Hello") { }                 // WRONG: compares addresses, always false!
```

**String Memory Layout:**
```
String: char str1[] = "Hello"
        
        Stack memory (writable):
        ┌───┬───┬───┬───┬───┬───┐
        │'H'│'e'│'l'│'l'│'o'│'\0'│ ← Null terminator (value 0)
        └───┴───┴───┴───┴───┴───┘
        [0] [1] [2] [3] [4] [5]
        
        Total size: 6 bytes (5 characters + null terminator)

String Literal: char *str2 = "World"
        
        Stack:                      Read-only Data Segment:
        ┌──────────┐               ┌───┬───┬───┬───┬───┬───┐
        │ str2 ────┼──────────────►│'W'│'o'│'r'│'l'│'d'│'\0'│
        │(pointer) │               └───┴───┴───┴───┴───┴───┘
        └──────────┘               (CANNOT modify this!)

Why == doesn't work for strings:
        
        char str1[] = "Hello";
        char str2[] = "Hello";
        
        Stack:
        str1 ──► ┌───┬───┬───┬───┬───┬───┐ Address: 0x1000
                 │'H'│'e'│'l'│'l'│'o'│'\0'│
                 └───┴───┴───┴───┴───┴───┘
        
        str2 ──► ┌───┬───┬───┬───┬───┬───┐ Address: 0x2000
                 │'H'│'e'│'l'│'l'│'o'│'\0'│ (different location!)
                 └───┴───┴───┴───┴───┴───┘
        
        str1 == str2 compares: 0x1000 == 0x2000 → false!
        strcmp(str1, str2) compares: content → 0 (equal)
```

### Const and Volatile Qualifiers

[const](initialization_and_declarations.md#const) prevents modification, [volatile](initialization_and_declarations.md#volatile) prevents optimizations for variables that may change unexpectedly.

```c
    // Const qualifier
    const int readonly = 100;
    // readonly = 200;                          // ERROR: can't modify const
    
    const int *ptr_to_const = &readonly;        // Pointer to const int
    // *ptr_to_const = 200;                     // ERROR: can't modify through pointer
    
    int normal = 50;
    int *const const_ptr = &normal;             // Const pointer (can't change address)
    *const_ptr = 60;                            // OK: can modify value
    // const_ptr = &readonly;                   // ERROR: can't change pointer itself
    
    // Volatile (tells compiler variable may change unexpectedly)
    volatile int hardware_register = 0;         // Often used for memory-mapped I/O
```

### Function Calls and Compile-Time Checks

Functions encapsulate reusable logic. [static_assert](initialization_and_declarations.md#static-assert-c11) validates assumptions at compile-time. [Compound literals](expressions.md#compound-literals-c99) create temporary objects.

```c
    // Function calls
    int result = add(10, 20);
    printf("10 + 20 = %d\n", result);
    
    print_array(numbers, 5);
    
    int a = 5, b = 10;
    printf("Before swap: a=%d, b=%d\n", a, b);
    swap(&a, &b);                               // Pass addresses to modify
    printf("After swap: a=%d, b=%d\n", a, b);
    
    // Variadic function
    variadic_sum(4, 10, 20, 30, 40);
    
    // Static assert (compile-time check, C11+)
    _Static_assert(sizeof(int) >= 4, "int must be at least 4 bytes");
    
    // Compound literals (C99+)
    Point temp = (Point){100, 200};             // Create temporary struct
    move_point(&temp, 10, 10);
```

```c
    // Command-line arguments
    printf("Program name: %s\n", argv[0]);
    if (argc > 1) {
        printf("First argument: %s\n", argv[1]);
    }
    
    // Return success - 0 means success, non-zero means error (shell scripts can check this)
    return SUCCESS;                             // 0 indicates success to OS
}
```

### Function Definitions

[Function definitions](functions.md#function-definition) provide the implementation. Pass by value copies data, pass by pointer enables modification of caller's data.

```c
// Function definitions

int add(int a, int b) {
    return a + b;
}

void print_array(const int *arr, size_t size) {  // const = promise not to modify (best practice for read-only params)
    for (size_t i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    // arr[0] = 100;                            // ERROR: can't modify const parameter
}

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

Point create_point(int x, int y) {
    Point p = {x, y};                           // Return by value (copies struct)
    return p;
    // Can also use: return (Point){x, y}; (compound literal)
}

void move_point(Point *p, int dx, int dy) {     // Pass by pointer to modify original
    p->x += dx;
    p->y += dy;
}

// Variadic function (variable number of arguments)
void variadic_sum(int count, ...) {
    va_list args;
    va_start(args, count);                      // Initialize va_list after last fixed param
    
    int sum = 0;
    for (int i = 0; i < count; i++) {
        sum += va_arg(args, int);               // Get next argument as int
    }
    
    va_end(args);                               // Cleanup (always match va_start with va_end)
    printf("Sum: %d\n", sum);
}

// Static function (internal linkage - only visible in this file)
static void helper(void) {
    LOG("Helper function called");
}
```

## Summary

This example demonstrates the core C language features in a single cohesive program. All critical concepts are shown with inline comments highlighting common errors and best practices. Key points are integrated throughout:

- **Memory safety**: Always check pointers for NULL, initialize variables, stay within array bounds
- **Memory management**: Every `malloc` needs one `free`, set pointers to NULL after freeing
- **Type awareness**: Integer division truncates, use `sizeof` for portability, cast carefully
- **String handling**: Use `strcmp` for comparison (never `==`), don't modify string literals
- **Undefined behavior**: Avoid `i = i++`, out-of-bounds access, null dereference, use-after-free
- **Best practices**: Use `const` for read-only data, parenthesize macros, check return values, prefer meaningful names

## Additional Concepts Not Demonstrated

These concepts are documented but not shown in this example:

**Advanced/Modern C:**
- [Generic selection (_Generic)](expressions.md#generic-selection-c11) - C11 type-generic macros
- [_Alignof](expressions.md#_alignof-c11) - Query alignment requirements
- [alignas](initialization_and_declarations.md#alignas-c11) - Specify alignment
- [Attributes](initialization_and_declarations.md#attributes-c23) - C23 standard attributes
- [restrict](initialization_and_declarations.md#restrict-c99) - Pointer aliasing optimization
- [_Noreturn](functions.md#_noreturn-c11-deprecated-in-c23) - Non-returning functions

**Preprocessor:**
- [#pragma](keywords_and_preprocessor.md#pragma) - Implementation-defined directives
- [#line](keywords_and_preprocessor.md#line) - Change line number reporting
- [#error](keywords_and_preprocessor.md#error) - Emit compilation error
- [#warning](keywords_and_preprocessor.md#warning-c23) - Emit compilation warning (C23)
- [#embed](keywords_and_preprocessor.md#embed-c23) - Embed binary resources (C23)
- [#elifdef/#elifndef](keywords_and_preprocessor.md#elifdef---elifndef-c23) - Shorthand conditionals (C23)

**Advanced Theory:**
- [As-if rule](basic_concepts.md#as-if-rule) - Compiler optimization freedoms
- [Character sets and encodings](basic_concepts.md#character-sets-and-encodings) - Unicode support

**Meta/Context:**
- [History of C](miscellaneous.md#history-of-c) - Language evolution
- [Conformance](miscellaneous.md#conformance) - Standards compliance
- [Inline assembly](miscellaneous.md#inline-assembly) - CPU-specific instructions
- [Signal handling](miscellaneous.md#signal-handling) - Asynchronous events
- [Analyzability](miscellaneous.md#analyzability-c11) - Static analysis support
