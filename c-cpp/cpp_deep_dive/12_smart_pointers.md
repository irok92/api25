# C++ Deep Dive: Smart Pointers

Smart pointers are class templates in the C++ standard library that act like raw pointers but provide automatic memory management. They help prevent common programming errors like memory leaks and dangling pointers by ensuring that an object is destroyed (and its memory deallocated) when it is no longer needed. This is a cornerstone of the **RAII (Resource Acquisition Is Initialization)** idiom.

## 1. The Problem with Raw Pointers

Raw pointers (`T*`) require manual memory management using `new` and `delete`.

- **Memory Leaks**: Forgetting to call `delete` causes the memory to be lost for the duration of the program.
- **Dangling Pointers**: Accessing a pointer after the memory it points to has been deleted leads to undefined behavior.
- **Double Deletion**: Calling `delete` twice on the same pointer leads to undefined behavior.

```cpp
void unsafe_function() {
    MyClass* ptr = new MyClass();
    if (some_condition) {
        // If we return here, 'delete ptr' is never called -> memory leak
        return;
    }
    delete ptr;
}
```

## 2. `std::unique_ptr` (C++11)

`std::unique_ptr` represents **exclusive ownership**. It is a lightweight smart pointer that owns the object it points to and ensures that the object is deleted when the `unique_ptr` goes out of scope.

- **No Copying**: A `unique_ptr` cannot be copied, because that would violate exclusive ownership.
- **Moving**: Ownership can be transferred from one `unique_ptr` to another using `std::move`.

```cpp
#include <memory>

void process_widget(std::unique_ptr<Widget> w) {
    // ... use w ...
} // w goes out of scope here, and the Widget is automatically deleted.

int main() {
    // Creation using std::make_unique (preferred method, C++14+)
    auto ptr1 = std::make_unique<Widget>();

    // ptr2 cannot be a copy of ptr1
    // auto ptr2 = ptr1; // Error: copy constructor is deleted

    // Ownership can be moved
    auto ptr3 = std::move(ptr1); // Now ptr3 owns the Widget, ptr1 is empty (nullptr)

    // Pass ownership to a function
    process_widget(std::move(ptr3));
    // After the call, ptr3 is empty.
}
```

## 3. `std::shared_ptr` (C++11)

`std::shared_ptr` represents **shared ownership**. Multiple `shared_ptr` instances can point to the same object. The object is only destroyed when the *last* `shared_ptr` pointing to it is destroyed or reset.

- **Reference Counting**: It maintains a "control block" that keeps a reference count of how many `shared_ptr`s are pointing to the object.
- **Copying is Allowed**: Copying a `shared_ptr` increases the reference count.
- **Thread-Safe**: The reference count itself is modified atomically, making it safe to share `shared_ptr`s between threads. (Note: Access to the managed object itself is *not* automatically thread-safe).

```cpp
#include <memory>

void use_widget(std::shared_ptr<Widget> w) {
    // ... use w ...
    // Ref count is increased when w is created, decreased when it goes out of scope.
}

int main() {
    // Creation using std::make_shared (preferred method)
    auto sp1 = std::make_shared<Widget>();
    std::cout << "Use count: " << sp1.use_count() << std::endl; // Prints 1

    {
        auto sp2 = sp1; // Copying increases the ref count
        std::cout << "Use count: " << sp1.use_count() << std::endl; // Prints 2
        use_widget(sp2);
    } // sp2 goes out of scope, ref count decreases to 1

    std::cout << "Use count: " << sp1.use_count() << std::endl; // Prints 1
} // sp1 goes out of scope, ref count becomes 0, Widget is deleted.
```

## 4. `std::weak_ptr` (C++11)

`std::weak_ptr` is a non-owning smart pointer that holds a "weak" reference to an object managed by a `std::shared_ptr`. It is used to break circular references.

- **Circular References**: If two objects hold `shared_ptr`s to each other, their reference counts will never drop to zero, creating a memory leak.
- **Usage**: A `weak_ptr` does not affect the reference count. To access the object, you must convert the `weak_ptr` to a `shared_ptr` using the `lock()` method. If the object has already been destroyed, `lock()` returns an empty `shared_ptr`.

```cpp
struct B;
struct A {
    std::shared_ptr<B> b_ptr;
};
struct B {
    // Using weak_ptr breaks the cycle
    std::weak_ptr<A> a_ptr;
};

auto a = std::make_shared<A>();
auto b = std::make_shared<B>();
a->b_ptr = b;
b->a_ptr = a;

// When a and b go out of scope, they are correctly deleted because
// the weak_ptr from B to A did not keep A alive.
```
