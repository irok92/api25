# Access control

## Access control

### [Access specifiers](https://en.cppreference.com/w/cpp/language/access.html)

**Code-related Keywords:**
- `public:` - Accessible from anywhere
- `protected:` - Accessible from derived classes
- `private:` - Accessible only within class (default for class)

**Theory Keywords:**
- **encapsulation** - Hide implementation details
- **interface vs implementation** - public is interface, private is implementation
- **struct default** - public; **class default** - private

**Example:**
```cpp
class BankAccount {
private:                  // Default for class
    double balance;       // Hidden from outside
    std::string pin;
    
protected:                // Accessible by derived classes
    void log(std::string msg) { }
    
public:                   // Public interface
    BankAccount(double initial) : balance(initial) {}
    
    void deposit(double amount) {
        balance += amount;
    }
    
    double getBalance() const {
        return balance;   // Controlled access
    }
};

BankAccount acc(1000);
acc.deposit(500);         // OK: public
double b = acc.getBalance();  // OK: public
// acc.balance = 9999;    // ERROR: private

// Struct defaults to public:
struct Point {            // public by default
    int x, y;
};

Point p;
p.x = 10;                 // OK: public by default
```

### [friend declaration](https://en.cppreference.com/w/cpp/language/friend.html)

**Code-related Keywords:**
- `friend class ClassName;` - Grant class access to private members
- `friend ReturnType func();` - Grant function access
- Non-member functions - Common for operators

**Theory Keywords:**
- **break encapsulation** - Controlled access to internals
- **symmetric operations** - Friend operators for commutative ops
- **not inherited** - Friendship not transitive

**Example:**
```cpp
class Complex {
    double real, imag;
    
public:
    Complex(double r, double i) : real(r), imag(i) {}
    
    // Friend function (non-member):
    friend Complex operator+(const Complex& a, const Complex& b);
    
    // Friend class:
    friend class ComplexPrinter;
    
    // Friend method from another class:
    friend void Analyzer::analyze(const Complex& c);
};

// Friend function can access private members:
Complex operator+(const Complex& a, const Complex& b) {
    return Complex(a.real + b.real, a.imag + b.imag);  // Access private
}

// Friend class can access all private members:
class ComplexPrinter {
public:
    void print(const Complex& c) {
        std::cout << c.real << " + " << c.imag << "i";  // Access private
    }
};

Complex c1(1, 2), c2(3, 4);
Complex c3 = c1 + c2;     // (4, 6)

ComplexPrinter printer;
printer.print(c3);        // "4 + 6i"
```
