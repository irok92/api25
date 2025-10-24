# Initialization and Declarations

## Initialization
### [Initialization](https://en.cppreference.com/w/c/language/initialization.html)
Setting initial value when object is created.

Initialization sets an object's initial value when it's created - you can initialize scalars (`int x = 5`), arrays (`int arr[] = {1,2,3}`), and structs (`struct S s = {10}`).
Uninitialized local variables contain garbage values, so always initialize them.

```c
int x = 5;                    // Direct initialization
int arr[3] = {1, 2, 3};      // Aggregate initialization
struct S { int a; } s = {10}; // Struct initialization
```

### [Scalar](https://en.cppreference.com/w/c/language/scalar_initialization.html)
Initialize arithmetic, pointer, or enum with single value.

Scalar initialization sets a single value for arithmetic types (`int`, `float`), pointers, or enums.
Use `= value` syntax, and for pointers, `NULL` or `0` represents the null pointer.

```c
int i = 42;
float f = 3.14f;
int *p = NULL;
enum E { A, B } e = A;
```

### [Array](https://en.cppreference.com/w/c/language/array_initialization.html)
Initialize array elements with brace-enclosed list.

Array initialization uses brace-enclosed lists `{1, 2, 3}` - if you provide fewer values than the array size, remaining elements are zero-initialized.
C99+ supports designated initializers `[3] = 5` to initialize specific indices.

- **Partial initialization**: Unspecified elements are zero-initialized.
- **Size inference**: Omitting size `[]` makes compiler calculate from initializer.
- **Designated initializers**: Specify index with [index]=value syntax (C99+).
- **String initialization**: char arrays can be initialized with string literals.
```c
int a[5] = {1, 2, 3};        // Remaining elements: 0
int b[] = {1, 2, 3};         // Size inferred: 3
int c[10] = {[3]=5, [7]=9};  // Designated initializers (C99)
```

### [Structure/Union](https://en.cppreference.com/w/c/language/struct_initialization.html)
Initialize aggregate members with brace-enclosed list.
- **Order matters**: Without designators, values assigned in member declaration order.
- **Designated initializers**: Use .member=value to initialize by name (C99+).
- **Partial initialization**: Unspecified members are zero-initialized.
- **Union initialization**: Only one member can be initialized (first by default, or designated).
```c
struct S { int x, y; char *s; } s1 = {1, 2, "text"};
struct S s2 = {.y=5, .x=3}; // Designated (C99)
union U { int i; float f; } u = {.f=3.14};
```

## Declarations Overview
### [Declarations](https://en.cppreference.com/w/c/language/declarations.html)
Introduce names with type and storage class.
```c
int x;                // Declaration
extern int y;         // Declaration (defined elsewhere)
int f(int);           // Function declaration
typedef int Int;      // Type alias declaration
```

## Pointer and Array Types
### [Pointers](https://en.cppreference.com/w/c/language/pointer.html)
Variables holding memory addresses of other objects.
- **& operator**: Takes address of variable (int *p = &x means "p points to x").
- **\* operator**: Dereferences pointer to access pointed-to value (*p reads x's value).
- **NULL/nullptr**: Special pointer value indicating "points to nothing".
- **void\***: Generic pointer type that can point to any object type.
- **Pointer arithmetic**: Adding/subtracting moves by element size (p+1 advances sizeof(*p) bytes).
```c
int x = 5, *p = &x;       // p points to x
int **pp = &p;            // Pointer to pointer
void *v = p;              // Generic pointer
int (*fp)(int) = func;    // Function pointer
```

### [Arrays](https://en.cppreference.com/w/c/language/array.html)
Contiguous sequence of elements of same type.
- **Zero-indexed**: First element is [0], last is [size-1].
- **No bounds checking**: Accessing out-of-bounds is undefined behavior (no error).
- **Array decay**: Arrays automatically convert to pointer in most contexts (loses size info).
- **sizeof on array**: Returns total bytes (sizeof(int[10]) = 40), but decayed pointer loses this.
- **Multidimensional**: Actually array of arrays (int[3][4] is 3 arrays of 4 ints).
```c
int a[10];                // Array of 10 ints
int m[3][4];              // 2D array (3 rows, 4 cols)
int *p = a;               // Array decays to pointer
sizeof(a);                // Total size: 40 bytes
```

## Enumeration Types
### [Enumerations](https://en.cppreference.com/w/c/language/enum.html)
Named integer constants forming a distinct type.
```c
enum Color { RED, GREEN, BLUE };    // RED=0, GREEN=1, BLUE=2
enum Status { OK=0, ERROR=-1, PENDING=100 };
enum Color c = RED;
```

## Storage and Linkage
### [Storage duration and Linkage](https://en.cppreference.com/w/c/language/storage_class_specifiers.html)
Lifetime and visibility: auto, static, extern, register, thread_local.
- **auto**: Default for local variables (rarely written explicitly).
- **static**: Internal linkage (file-only) or persistent local variable (retains value).
- **extern**: Declares variable defined in another file (doesn't allocate storage).
- **register**: Hint to store in CPU register (mostly obsolete, compilers ignore).
- **Linkage**: External (visible across files), internal (file-only), none (local only).
```c
int global;              // External linkage, static duration
static int file_scope;   // Internal linkage
void f() {
  auto int local;        // Automatic duration
  static int persistent = 0; // Static duration, no linkage
}
```

## Type Qualifiers
### [const](https://en.cppreference.com/w/c/language/const.html)
Declare object as read-only (cannot be modified).
- **const int x**: x cannot be changed (compiler enforces).
- **const int \*p**: p points to const int (can't change \*p, but can change p).
- **int \*const p**: const pointer (can't change p, but can change \*p).
- **const int \*const p**: Both pointer and pointee are const.
- **Read rule right-to-left**: "const int \*" is "pointer to const int".
```c
const int x = 5;         // x cannot be changed
const int *p = &x;       // Pointer to const int
int *const cp = &x;      // Const pointer to int
const char *str = "text"; // Read-only string
```

### [volatile](https://en.cppreference.com/w/c/language/volatile.html)
Prevent optimization, object may change unexpectedly.
- **Use cases**: Hardware registers, signal handlers, multithreading (pre-C11).
- **Prevents optimization**: Compiler must read/write actual memory location (no caching in register).
- **Not atomic**: volatile does not guarantee thread-safety (use atomic types for that).
- **Memory-mapped I/O**: Essential for accessing hardware that changes value independently.
```c
volatile int sensor;     // Hardware register
volatile sig_atomic_t flag; // Modified by signal handler
volatile int *hw = (volatile int*)0x40000000;
```

### [restrict (C99)](https://en.cppreference.com/w/c/language/restrict.html)
Pointer optimization hint: no aliasing with other pointers.
- **Aliasing**: Two pointers pointing to same or overlapping memory.
- **Optimization**: Tells compiler this pointer is only way to access the memory.
- **Contract**: Programmer promises no aliasing; compiler can optimize more aggressively.
- **Violation**: Using restrict with aliased pointers is undefined behavior.
- **Common use**: memcpy (restrict) vs memmove (no restrict, handles overlap).
```c
void copy(int *restrict dst, const int *restrict src, size_t n) {
  for (size_t i = 0; i < n; i++) dst[i] = src[i];
} // Compiler knows dst and src don't overlap
```

## Aggregate Types
### [struct](https://en.cppreference.com/w/c/language/struct.html)
Compound type grouping variables of different types.
```c
struct Point { int x, y; };
struct Point p = {10, 20};
p.x = 30;
struct Point *pp = &p; pp->y = 40;
```

### [union](https://en.cppreference.com/w/c/language/union.html)
Type where all members share same memory location.
- **Memory overlay**: All members start at same address (size = largest member).
- **One active member**: Only last-written member is valid to read (type punning).
- **Use cases**: Save memory, type punning, variant types (with discriminator tag).
- **Undefined behavior**: Reading wrong member (write as int, read as float) technically undefined.
```c
union Data { int i; float f; char c[4]; };
union Data d;
d.i = 42;        // Write as int
d.f = 3.14f;     // Overwrites i, write as float
```

### [Bit-fields](https://en.cppreference.com/w/c/language/bit_field.html)
Struct members with specified bit width.
- **Space saving**: Pack multiple values into single integer (hardware registers, flags).
- **Width**: Colon followed by bit count (max is bits in underlying type).
- **Limitations**: Cannot take address of bit-field (&field invalid).
- **Padding**: Compiler may add padding between bit-fields for alignment.
- **Portability**: Bit order is implementation-defined (endianness issues).
```c
struct Flags {
  unsigned int a : 1;  // 1 bit
  unsigned int b : 3;  // 3 bits
  unsigned int c : 4;  // 4 bits
} f = {1, 5, 12};
```

## Type Specifiers
### [alignas (C11)](https://en.cppreference.com/w/c/language/alignas.html)
Specify alignment requirement for variable.
```c
_Alignas(16) char buffer[64];    // 16-byte aligned
_Alignas(double) int x;          // Align like double
struct S { _Alignas(8) char c; };
```

### [typedef](https://en.cppreference.com/w/c/language/typedef.html)
Create type alias for existing type.
- **Readability**: Makes complex types easier to understand (typedef int\* IntPtr).
- **Portability**: Hide platform differences (typedef long size_t on some systems).
- **Not new type**: Just an alias; typedef'd types are interchangeable with original.
- **With struct**: Can eliminate need to write "struct" keyword repeatedly.
```c
typedef unsigned long ulong;
typedef int* IntPtr;
typedef struct { int x, y; } Point;
Point p = {1, 2};
```

## Compile-time Assertions
### [static_assert (C11)](https://en.cppreference.com/w/c/language/static_assert.html)
Compile-time assertion with optional message.
```c
_Static_assert(sizeof(int) == 4, "int must be 4 bytes");
_Static_assert(sizeof(void*) >= 4, "pointer size");
#define MAX 100
_Static_assert(MAX > 0, "MAX must be positive");
```

## Attributes
### [Attributes (C23)](https://en.cppreference.com/w/c/language/attributes.html)
Compiler hints: [[deprecated]], [[nodiscard]], [[fallthrough]], etc.
- **[[deprecated]]**: Warns when using obsolete functions/types.
- **[[nodiscard]]**: Warns if return value is ignored (important for error codes).
- **[[fallthrough]]**: Suppresses warning about intentional switch fallthrough.
- **[[maybe_unused]]**: Suppresses unused variable/parameter warnings.
- **Standard attributes**: C23 standardizes what were compiler extensions (__attribute__).
```c
[[deprecated]] void old_func(void);
[[nodiscard]] int important(void);
switch(x) { case 1: f(); [[fallthrough]]; case 2: g(); }
```
