# Namespaces

## Namespaces

### [Namespace declaration](https://en.cppreference.com/w/cpp/language/namespace.html)

**Code-related Keywords:**
- `namespace Name { }` - Define namespace
- `using namespace Name;` - Using directive (imports all names)
- `using Name::member;` - Using declaration (imports specific name)
- `namespace alias = Original;` - Namespace alias
- Anonymous: `namespace { }` - Unnamed namespace

**Theory Keywords:**
- **namespace** - Scope for grouping related names
- **avoid name conflicts** - Separate identifiers from different libraries
- **nested namespaces** - Namespaces within namespaces

**Example:**
```cpp
namespace Math {
    int add(int a, int b) { return a + b; }
    int sub(int a, int b) { return a - b; }
    
    namespace Advanced {       // Nested namespace
        double sqrt(double x);
    }
}

// C++17: nested namespace shorthand
namespace Math::Advanced {     // Same as namespace Math { namespace Advanced { }}
    double pow(double x, int n);
}

// Usage:
int x = Math::add(1, 2);       // Qualified name
using namespace Math;          // Import all from Math
int y = add(3, 4);             // Unqualified (now finds Math::add)

using Math::sub;               // Import specific name
int z = sub(5, 1);             // OK: sub imported

namespace { 
    int hidden = 42;           // Unnamed namespace: internal linkage
}
```

### [Namespace alias](https://en.cppreference.com/w/cpp/language/namespace_alias.html)

**Code-related Keywords:**
- `namespace short = very::long::namespace::name;`

**Theory Keywords:**
- **alias** - Shorter name for long namespace

**Example:**
```cpp
namespace VeryLongLibraryName {
    namespace Subsystem {
        namespace Component {
            void func();
        }
    }
}

// Create alias:
namespace VLLN = VeryLongLibraryName;
namespace Comp = VeryLongLibraryName::Subsystem::Component;

// Use alias:
Comp::func();                  // Instead of VeryLongLibraryName::Subsystem::Component::func()
```
