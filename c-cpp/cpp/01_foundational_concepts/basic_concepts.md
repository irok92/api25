# Basic concepts

## [Basic concepts](https://en.cppreference.com/w/cpp/language/basics.html)

### Code-related Keywords
- `main()` - Entry point function where program execution begins
- `return` - Exits a [function](../../07_functions/functions.md) and returns a value
- `//` - Single-line comment
- `/* */` - Multi-line comment
- `\n`, `\t`, `\"`, `\'`, `\\` - Common [escape sequences](https://en.cppreference.com/w/cpp/language/escape.html) for special characters
- `identifiers` - Names for variables, functions, [classes](../../09_classes/classes.md), etc.

### Theory Keywords
- **translation phases** - Steps (preprocessing, compilation, linking) that transform source code to executable
- **identifier rules** - Must start with letter or underscore, can contain letters, digits, underscores
- **reserved words** - [Keywords](../../03_keywords_and_preprocessor/keywords.md) cannot be used as identifiers

### Example

```cpp
// Single-line comment: main function is program entry point
/* Multi-line comment:
   main returns int (0 = success, non-zero = error) */
int main() {  // { } are punctuators defining scope
    int myVariable_123 = 42;  // Valid identifier with letters, digits, underscore
    char newline = '\n';      // Escape sequence for newline character
    char tab = '\t';          // Tab escape sequence
    char quote = '\'';        // Escaped single quote
    char backslash = '\\';    // Escaped backslash
    // int 123invalid;        // ERROR: identifier cannot start with digit
    // int class;             // ERROR: 'class' is a keyword, cannot be used as identifier
    return 0;                 // Return success status to operating system
}  // As-if rule: compiler may optimize this code but preserve observable behavior
```

### [The as-if rule](https://en.cppreference.com/w/cpp/language/as_if.html)

### Program structure

#### [Translation phases](https://en.cppreference.com/w/cpp/language/translation_phases.html)

**Code-related Keywords:**
- `#include` - [Preprocessor](../../03_keywords_and_preprocessor/preprocessor.md) directive to include header files
- `#define` - Define macros during preprocessing
- `.cpp`, `.h` - Common source and header file extensions

**Theory Keywords:**
- **preprocessing** - First phase where `#include`, `#define` directives are processed
- **compilation** - Source code is translated to object code
- **linking** - Object files are combined into executable

**Example:**
```cpp
// file: math.h
int add(int a, int b);  // Declaration in header

// file: math.cpp
#include "math.h"       // Preprocessing: includes header content
int add(int a, int b) { // Compilation: translates to object code
    return a + b;
}

// file: main.cpp
#include "math.h"       // Includes add declaration
int main() {
    return add(2, 3);   // Linking: resolves add() call to math.cpp definition
}
```

#### [main function](https://en.cppreference.com/w/cpp/language/main_function.html)

**Code-related Keywords:**
- `int main()` - Standard main signature with no arguments
- `int main(int argc, char* argv[])` - Main with command-line arguments
- `argc` - Argument count (number of command-line arguments)
- `argv` - Argument vector (array of C-strings containing arguments)

**Theory Keywords:**
- **entry point** - Where program execution begins
- **return code** - `0` means success, non-zero indicates error
- **command-line arguments** - Values passed to program when launched

**Example:**
```cpp
#include <iostream>
int main(int argc, char* argv[]) {  // argc = count, argv = array of arguments
    std::cout << "Program name: " << argv[0] << '\n';  // argv[0] is program name
    for (int i = 1; i < argc; ++i) {  // Loop through command-line arguments
        std::cout << "Arg " << i << ": " << argv[i] << '\n';
    }
    return 0;  // Return 0 to indicate success (can omit - implicit return 0)
}  // Running as: ./program arg1 arg2 → argc=3, argv={"./program","arg1","arg2",nullptr}
```

### [Comments](https://en.cppreference.com/w/cpp/comments.html)

**Code-related Keywords:**
- `//` - Single-line comment (everything after `//` on line is ignored)
- `/* */` - Multi-line comment (everything between `/*` and `*/` is ignored)

**Theory Keywords:**
- **ignored by compiler** - Comments don't affect compilation or execution

**Example:**
```cpp
int x = 5;  // Single-line comment: variable initialization
/* Multi-line comment:
   This explains a complex algorithm
   across multiple lines */
int y = /* inline comment */ 10;  // Comments can appear mid-line
// int z = 15;  // This line is commented out (code won't execute)
```

### Character sets and encoding

#### [Character sets and encodings](https://en.cppreference.com/w/cpp/language/charset.html)

**Code-related Keywords:**
- `char` - Character [type](../../02_types_and_objects/types.md) (typically 1 byte)
- `'A'` - Character [literal](../../04_expressions/literals.md) (single character in single quotes)
- UTF-8, UTF-16, UTF-32 - Unicode encoding schemes

**Theory Keywords:**
- **ASCII** - 7-bit character set (values 0-127)
- **Unicode** - Universal character set supporting all writing systems
- **encoding** - How characters are represented as bytes

**Example:**
```cpp
char letter = 'A';        // ASCII character (value 65)
char digit = '0';         // Character '0' (ASCII 48, not integer 0)
char newline = '\n';      // Escape sequence (see next section)
// wchar_t wide = L'א';   // Wide character for non-ASCII (Hebrew letter)
```

#### [Escape sequences](https://en.cppreference.com/w/cpp/language/escape.html)

**Code-related Keywords:**
- `\n` - Newline
- `\t` - Tab
- `\\` - Backslash
- `\'` - Single quote
- `\"` - Double quote
- `\0` - Null character (string terminator)
- `\xHH` - Hex value (e.g., `\x41` = 'A')

**Theory Keywords:**
- **special characters** - Characters that need escaping to be represented

**Example:**
```cpp
char newline = '\n';      // Line feed character
char tab = '\t';          // Horizontal tab
char quote = '\'';        // Single quote (must escape inside '')
char backslash = '\\';    // Backslash (must escape \ itself)
char null = '\0';         // Null terminator for C-strings
char hex = '\x41';        // 'A' using hex notation (0x41 = 65)
// Use in strings:
std::cout << "Line1\nLine2\t\tTabbed\n";  // Output: Line1
                                           //         Line2		Tabbed
```

### [ASCII chart](https://en.cppreference.com/w/cpp/language/ascii.html)

**Code-related Keywords:**
- `'0'` to `'9'` - Digit characters (ASCII 48-57)
- `'A'` to `'Z'` - Uppercase letters (ASCII 65-90)
- `'a'` to `'z'` - Lowercase letters (ASCII 97-122)

**Theory Keywords:**
- **ASCII values** - Numeric representation of characters (0-127)

**Example:**
```cpp
char upper = 'A';         // ASCII 65
char lower = 'a';         // ASCII 97 (upper + 32)
char zero = '0';          // ASCII 48 (NOT integer 0!)
int diff = lower - upper; // Difference is 32
char toLower = 'A' + 32;  // Convert to 'a' using ASCII math
bool isDigit = (zero >= '0' && zero <= '9');  // Check if character is digit
```

### [Punctuation](https://en.cppreference.com/w/cpp/language/punctuators.html)

**Code-related Keywords:**
- `{ }` - Braces (define [scope](../../02_types_and_objects/object.md))
- `( )` - Parentheses ([function](../../07_functions/functions.md) calls, grouping)
- `[ ]` - Brackets ([arrays](../../05_declarations/compound_types.md), subscript)
- `;` - Semicolon ([statement](../../08_statements/statements.md) terminator)
- `,` - Comma (separator)
- `.` - Member access
- `::` - Scope resolution

**Example:**
```cpp
int arr[5] = {1, 2, 3, 4, 5};  // [] brackets, {} braces, , commas, ; semicolon
int x = (2 + 3) * 4;            // () parentheses for grouping
std::cout << arr[0];            // :: scope resolution, [] subscript, . (implicit in <<)
```

### [Names and identifiers](https://en.cppreference.com/w/cpp/language/name.html)

**Code-related Keywords:**
- Valid: `myVariable`, `_private`, `value123`, `CamelCase`
- Invalid: `123invalid`, `class` (keyword), `my-var` (hyphen not allowed)

**Theory Keywords:**
- **naming rules** - Must start with letter/underscore, contain only letters/digits/underscores
- **reserved names** - [Keywords](../../03_keywords_and_preprocessor/keywords.md) and names starting with `__` or `_` + uppercase are reserved
- **case-sensitive** - `myVar` and `myvar` are different identifiers

**Example:**
```cpp
int myVariable = 42;      // Valid: starts with letter
int _private = 10;        // Valid: starts with underscore
int value123 = 5;         // Valid: contains digits (but doesn't start with one)
// int 123invalid;        // ERROR: cannot start with digit
// int class;             // ERROR: 'class' is a keyword
// int my-var;            // ERROR: hyphen not allowed (use _ instead)
int myVar = 1, myvar = 2; // Valid: different identifiers (case-sensitive)
```
