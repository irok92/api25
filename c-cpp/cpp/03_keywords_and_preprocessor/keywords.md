# Keywords

## [Keywords](https://en.cppreference.com/w/cpp/keywords.html)

**Code-related Keywords:**
- Control flow: `if`, `else`, `switch`, `case`, `default`, `for`, `while`, `do`, `break`, `continue`, `return`
- [Types](../../02_types_and_objects/types.md): `int`, `float`, `double`, `char`, `bool`, `void`, `auto`, `decltype`
- Character types (C++11/20): `char8_t`, `char16_t`, `char32_t`, `wchar_t`
- [Classes](../../09_classes/classes.md): `class`, `struct`, `union`, `enum`, `public`, `private`, `protected`, `friend`
- Storage: `static`, `extern`, `const`, `constexpr`, `consteval` (C++20), `constinit` (C++20), `volatile`, `mutable`, `thread_local` (C++11)
- [Templates](../../10_templates/templates.md): `template`, `typename`, `concept` (C++20), `requires` (C++20)
- Coroutines (C++20): `co_await`, `co_return`, `co_yield`
- [Modules](../../03a_modules/modules.md) (C++20): `import`, `export`, `module`
- Other: `namespace`, `using`, `sizeof`, `alignof` (C++11), `new`, `delete`, `this`, `nullptr` (C++11), `noexcept` (C++11)

**Theory Keywords:**
- **reserved words** - Cannot be used as identifiers (see full list at [cppreference](https://en.cppreference.com/w/cpp/keyword))
- **context-sensitive** - Some keywords (like `override`, `final`, `import`, `module`) only keywords in specific contexts
- **alternative operators** - `and`, `or`, `not`, `xor`, `bitand`, `bitor`, etc. (alternative representations of operators)

**Example:**
```cpp
// Keywords in action:
class MyClass {                // class keyword
public:                        // public keyword
    int value;                 // int keyword
    static const int MAX = 100; // static, const keywords
    
    void func() {              // void keyword
        if (value > 0) {       // if keyword
            return;            // return keyword
        }
        for (int i = 0; i < 10; ++i) {  // for, int keywords
            break;             // break keyword
        }
    }
};

template <typename T>          // template, typename keywords
T add(T a, T b) {
    return a + b;
}

// auto x = class;             // ERROR: 'class' is keyword, can't be identifier
```
