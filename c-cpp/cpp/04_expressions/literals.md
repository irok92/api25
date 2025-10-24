# Literals

## [Literals](https://en.cppreference.com/w/cpp/language/expressions.html#Literals)

### [Integer literals](https://en.cppreference.com/w/cpp/language/integer_literal.html)

**Code-related Keywords:**
- Decimal: `42`, `123`
- Hex: `0x2A`, `0xFF`
- Octal: `042`, `0755`
- Binary: `0b101010`, `0b11111111` (C++14)
- Suffixes: `42u` (unsigned), `42L` (long), `42LL` (long long), `42UL`

**Example:**
```cpp
int dec = 42;                  // Decimal
int hex = 0x2A;                // Hexadecimal (same as 42)
int oct = 052;                 // Octal (same as 42)
int bin = 0b101010;            // Binary (same as 42, C++14)

unsigned u = 42u;              // Unsigned
long l = 42L;                  // Long
long long ll = 42LL;           // Long long
unsigned long ul = 42UL;       // Unsigned long

int big = 1'000'000;           // C++14: digit separator (1 million)
int hex2 = 0xFF'FF'FF'FF;      // Can use in any base
```

### [Floating-point literals](https://en.cppreference.com/w/cpp/language/floating_literal.html)

**Code-related Keywords:**
- Decimal: `3.14`, `.5`, `2.`
- Scientific: `1.5e10`, `3.14E-5`
- Hex float: `0x1.2p3` (C++17)
- Suffixes: `f` (float), `l` (long double), none (double)

**Example:**
```cpp
double d1 = 3.14;              // Double (default)
double d2 = 3.14159265359;     // High precision
float f1 = 3.14f;              // Float (f suffix required to avoid narrowing)
long double ld = 3.14L;        // Long double

double sci = 1.5e10;           // Scientific: 1.5 × 10^10
double tiny = 3.14e-5;         // 0.0000314

double hex_float = 0x1.2p3;    // C++17: hex float (1.125 × 2^3 = 9.0)
```

### [Character literals](https://en.cppreference.com/w/cpp/language/character_literal.html)

**Code-related Keywords:**
- `'c'` - char literal
- `L'c'` - wchar_t literal
- `u'c'` - char16_t (C++11)
- `U'c'` - char32_t (C++11)
- `u8'c'` - char8_t (C++20)

**Example:**
```cpp
char c1 = 'A';                 // Character literal
char c2 = '\n';                // Escape sequence (newline)
char c3 = '\x41';              // Hex escape ('A')
char c4 = '\'';                // Escaped quote

wchar_t wc = L'あ';            // Wide character (Japanese hiragana)
char16_t c16 = u'€';           // UTF-16 (Euro sign)
char32_t c32 = U'😀';          // UTF-32 (emoji)
char8_t c8 = u8'A';            // UTF-8 (C++20)

// Multi-byte sequences:
int multi = 'abcd';            // Implementation-defined: multiple chars
```

### [String literals](https://en.cppreference.com/w/cpp/language/string_literal.html)

**Code-related Keywords:**
- `"text"` - C-string (null-terminated)
- `L"text"` - Wide string
- `u8"text"` - UTF-8 (C++11)
- `u"text"` - UTF-16 (C++11)
- `U"text"` - UTF-32 (C++11)
- `R"(raw)"` - Raw string (C++11)
- Adjacent concatenation: `"ab" "cd"` → `"abcd"`

**Example:**
```cpp
const char* str = "Hello";     // C-string (type: const char[6], null-terminated)
const char* multi = "Line1\n"
                    "Line2";   // Adjacent strings concatenated

const char* raw = R"(C:\path\to\file.txt)";  // Raw string: no escape needed
const char* raw2 = R"delim(String with "quotes" and )stuff)delim";  // Custom delimiter

const wchar_t* wide = L"Wide text";     // Wide string
const char8_t* utf8 = u8"UTF-8 text";   // UTF-8
const char16_t* utf16 = u"UTF-16 text"; // UTF-16
const char32_t* utf32 = U"UTF-32 text"; // UTF-32

// String contains: 'H' 'e' 'l' 'l' 'o' '\0'
```

### [Boolean literals](https://en.cppreference.com/w/cpp/language/bool_literal.html)

**Code-related Keywords:**
- `true` - Boolean true
- `false` - Boolean false

**Example:**
```cpp
bool b1 = true;                // Boolean true
bool b2 = false;               // Boolean false

if (true) {}                   // Always executes
while (false) {}               // Never executes

bool b3 = 1;                   // Converts to true (non-zero)
bool b4 = 0;                   // Converts to false (zero)
```

### [nullptr](https://en.cppreference.com/w/cpp/language/nullptr.html) (C++11)

**Code-related Keywords:**
- `nullptr` - Null [pointer](../../05_declarations/compound_types.md) literal (C++11)
- Replaces `NULL` macro

**Theory Keywords:**
- **type-safe** - Has type `std::nullptr_t`
- **not convertible to int** - Unlike `NULL` which is 0

**Example:**
```cpp
int* p1 = nullptr;             // C++11: null pointer (preferred)
int* p2 = NULL;                // C-style: actually 0 (avoid)
int* p3 = 0;                   // Also null, but ambiguous

void func(int);                // Overload 1
void func(int*);               // Overload 2

// func(NULL);                 // AMBIGUOUS: NULL is 0 (could be either overload)
func(nullptr);                 // OK: calls func(int*) - unambiguous

if (p1 == nullptr) {}          // Check for null (clear intent)
if (!p1) {}                    // Also valid (implicit bool conversion)
```

### [User-defined literals](https://en.cppreference.com/w/cpp/language/user_literal.html) (C++11)

**Code-related Keywords:**
- `operator""_suffix(type)` - Define custom literal suffix
- Must start with `_` (or use standard suffixes like `s`, `ms`, `h`)

**Theory Keywords:**
- **suffix notation** - Natural syntax for units, types

**Example:**
```cpp
#include <chrono>
#include <string>

// Standard library UDLs:
using namespace std::literals;
auto str = "hello"s;           // std::string (not const char*)
auto dur1 = 100ms;             // std::chrono::milliseconds
auto dur2 = 5min;              // std::chrono::minutes

// Custom UDL:
constexpr long double operator""_km(long double km) {
    return km * 1000;          // Convert kilometers to meters
}

constexpr long double operator""_m(long double m) {
    return m;
}

int main() {
    double dist1 = 5.0_km;     // 5000.0 meters
    double dist2 = 100.0_m;    // 100.0 meters
    double total = dist1 + dist2;  // 5100.0 meters
}
```
