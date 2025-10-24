# Miscellaneous

## C Language History and Standards
### [History of C](https://en.cppreference.com/w/c/language/history.html)
Evolution from K&R C through C89, C99, C11, C17, C23.

C has evolved through several standards: C89 (ANSI C, original standard), C99 (VLAs, `//` comments, `inline`), C11 (threads, `_Generic`, `_Static_assert`), and C23 (`nullptr`, `true`/`false`, `#embed`).
Each version adds features while maintaining backward compatibility.

```c
// C89: Original standard
// C99: inline, restrict, // comments, VLAs
// C11: _Generic, _Static_assert, threads
// C23: nullptr, true/false, #embed, [[attributes]]
```

### [Conformance](https://en.cppreference.com/w/c/language/conformance.html)
Standard compliance categories: strictly conforming, conforming, hosted/freestanding.

C implementations can be hosted (full standard library with `printf`, `malloc`) or freestanding (minimal library for embedded systems).
Strictly conforming programs use only standard features and work on any conforming implementation.

```c
// Strictly conforming: uses only standard features
// Hosted: full standard library (printf, malloc)
// Freestanding: minimal library (stddef.h, limits.h)
```

## Advanced Features
### [Inline assembly](https://en.cppreference.com/w/c/language/asm.html)
Embed assembly instructions directly in C code.

Inline assembly lets you write CPU-specific assembly instructions within C code - useful for hardware access or performance-critical sections, but non-portable and architecture-specific.
Modern compilers optimize well, so inline assembly is rarely needed.

- **Use cases**: Hardware access, performance-critical sections, CPU-specific instructions.
- **Non-portable**: Assembly code is architecture-specific (x86, ARM, etc.).
- **volatile**: Prevents compiler from optimizing away assembly.
- **Constraints**: Specify how C variables map to registers (complex syntax).
- **Last resort**: Usually unnecessary; modern compilers optimize well.
```c
// GCC/Clang syntax
__asm__("nop");                    // Single instruction
asm volatile("cli" ::: "memory");  // Disable interrupts
int result; asm("addl %1, %0" : "=r"(result) : "r"(5));
```

### [Signal handling](https://en.cppreference.com/mwiki/index.php?title=c/language/signal&action=edit&redlink=1)
Asynchronous event handling (SIGINT, SIGSEGV, etc.).
```c
#include <signal.h>
void handler(int sig) { /* handle signal */ }
signal(SIGINT, handler);     // Register handler
raise(SIGINT);               // Raise signal
```

### [Analyzability (C11)](https://en.cppreference.com/w/c/language/analyzability.html)
Features enabling static analysis: bounds-checking, annotations.
```c
// Enables static analysis tools to verify:
// - Array bounds, pointer validity, undefined behavior
// __STDC_ANALYZABLE__ macro indicates support
```
