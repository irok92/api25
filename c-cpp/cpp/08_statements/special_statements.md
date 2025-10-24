# Special statements

## Special statements

### [contract_assert](https://en.cppreference.com/w/cpp/language/contract_assert.html) (C++26)

**Code-related Keywords:**
- `contract_assert(condition);` - Runtime assertion (C++26, upcoming)

**Theory Keywords:**
- **contracts** - Specify preconditions/postconditions (C++26 proposal)
- **runtime check** - Validate assumptions at runtime
- **design by contract** - Formal interface specifications

**Example:**
```cpp
// C++26 (proposal):
void setAge(int age) {
    contract_assert(age >= 0 && age <= 150);  // Runtime check
    this->age = age;
}

// Until C++26, use assert or exceptions:
#include <cassert>
void setAgeNow(int age) {
    assert(age >= 0 && age <= 150);  // Debug-mode check
    // Or: if (age < 0 || age > 150) throw std::invalid_argument("Invalid age");
}
```

### [synchronized/atomic](https://en.cppreference.com/w/cpp/language/transactional_memory.html) (TM TS)

**Code-related Keywords:**
- `synchronized { }` - Transactional memory block (TS, experimental)
- `atomic_commit`, `atomic_cancel` - Transaction control

**Theory Keywords:**
- **transactional memory** - Atomic execution of code blocks
- **technical specification** - Not in standard yet
- **concurrency** - Alternative to locks for thread safety

**Example:**
```cpp
// Transactional Memory TS (experimental, not widely supported):
int shared = 0;

synchronized {            // Atomic block
    shared += 10;         // Executes atomically
}

// Use standard atomics instead (C++11):
#include <atomic>
std::atomic<int> counter{0};
counter += 10;            // Atomic operation

// Or use mutexes:
#include <mutex>
std::mutex mtx;
int value = 0;

{
    std::lock_guard<std::mutex> lock(mtx);  // RAII lock
    value += 10;          // Protected by mutex
}
```
