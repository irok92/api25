# Concurrency Support Library (C11)

## Overview
### [Concurrency support library](https://en.cppreference.com/w/c/thread.html)
Multithreading primitives: threads, mutexes, condition variables.

C11 added threading support with threads (independent execution sequences), mutexes (locks for protecting shared data), and condition variables (for thread coordination).
This library is optional - check for `__STDC_NO_THREADS__` to detect availability.

- **Thread**: Independent sequence of execution (program can run multiple tasks simultaneously).
- **Mutex**: Mutual exclusion lock (prevents multiple threads from accessing same data).
- **Condition variable**: Allows threads to wait for specific conditions.
- **Optional**: May not be available if __STDC_NO_THREADS__ is defined.
```c
#include <threads.h>
thrd_t t; mtx_t m; cnd_t c;
mtx_init(&m, mtx_plain);
thrd_create(&t, func, arg); thrd_join(t, NULL);
```

### [Atomic operations library](https://en.cppreference.com/w/c/atomic.html)
Lock-free thread-safe operations on atomic types.

Atomic operations are indivisible operations that complete without interruption - they're lock-free (no mutex needed) and hardware-guaranteed, making them faster than locks for simple operations.
Use atomic types for shared counters or flags between threads.

- **Atomic operation**: Indivisible operation (completes fully or not at all, no interruption).
- **Lock-free**: No mutex needed; hardware guarantees atomicity (faster than locks).
- **Use case**: Shared counters, flags between threads without explicit locking.
- **Optional**: May not be available if __STDC_NO_ATOMICS__ is defined.
```c
#include <stdatomic.h>
atomic_int counter = 0;
atomic_fetch_add(&counter, 1);
int val = atomic_load(&counter);
```

### [_Atomic type specifier and qualifier](https://en.cppreference.com/w/c/language/atomic.html)
Type qualifier for lock-free atomic operations.
- **_Atomic qualifier**: Makes type safe for concurrent access (like adding "thread-safe" to type).
- **Syntax**: _Atomic int or _Atomic(int) both create atomic integer.
- **Operations**: Standard operations (++, =, etc.) become atomic automatically.
- **Size**: May be larger than non-atomic version (padding for atomicity).
```c
_Atomic int x = 0;           // Atomic integer
_Atomic(int*) ptr = NULL;    // Atomic pointer
x++;                         // Atomic increment
```

## Threads
### [thrd_create](https://en.cppreference.com/w/c/thread/thrd_create.html)
Create and start new thread.
```c
int thread_func(void *arg) { return 0; }
thrd_t thread;
if (thrd_create(&thread, thread_func, arg) == thrd_success)
  thrd_join(thread, NULL);
```

### [thrd_equal](https://en.cppreference.com/w/c/thread/thrd_equal.html)
Compare two thread identifiers for equality.
```c
thrd_t t1, t2;
if (thrd_equal(t1, t2))
  printf("Same thread\n");
```

### [thrd_current](https://en.cppreference.com/w/c/thread/thrd_current.html)
Get identifier of calling thread.
```c
thrd_t current = thrd_current();
if (thrd_equal(current, main_thread))
  printf("Main thread\n");
```
### [thrd_sleep](https://en.cppreference.com/w/c/thread/thrd_sleep.html)
Suspend execution for specified duration.
```c
struct timespec duration = {.tv_sec=1, .tv_nsec=500000000}; // 1.5s
thrd_sleep(&duration, NULL);  // Sleep for duration
```

### [thrd_yield](https://en.cppreference.com/w/c/thread/thrd_yield.html)
Give up time slice to allow other threads to run.
```c
while (waiting) {
  thrd_yield();  // Let other threads execute
}
```

### [thrd_exit](https://en.cppreference.com/w/c/thread/thrd_exit.html)
Terminate calling thread with return value.
```c
int thread_func(void *arg) {
  if (error) thrd_exit(1);  // Exit with code 1
  return 0;
}
```

### [thrd_detach](https://en.cppreference.com/w/c/thread/thrd_detach.html)
Detach thread so resources free automatically when done.
```c
thrd_t t;
thrd_create(&t, func, arg);
thrd_detach(t);  // No need to join
```

### [thrd_join](https://en.cppreference.com/w/c/thread/thrd_join.html)
Wait for thread to finish and get return value.
```c
thrd_t t; int result;
thrd_create(&t, func, arg);
thrd_join(t, &result);  // Wait and get return value
```

## Mutual Exclusion
### [mtx_init](https://en.cppreference.com/w/c/thread/mtx_init.html)
Initialize mutex for synchronization.
```c
mtx_t mutex;
mtx_init(&mutex, mtx_plain);      // Plain mutex
mtx_init(&mutex, mtx_recursive);  // Recursive mutex
```

### [mtx_lock](https://en.cppreference.com/w/c/thread/mtx_lock.html)
Block until mutex is acquired.
- **Critical section**: Code region where only one thread can execute at a time.
- **Blocking**: If locked, thread waits (sleeps) until mutex becomes available.
- **Must unlock**: Always unlock after critical section (prefer RAII pattern or cleanup labels).
- **Deadlock risk**: Two threads waiting for each other's locks (careful with multiple mutexes).
```c
mtx_lock(&mutex);
// Critical section
mtx_unlock(&mutex);
```

### [mtx_timedlock](https://en.cppreference.com/w/c/thread/mtx_timedlock.html)
Try to lock mutex with timeout.
```c
struct timespec timeout = {.tv_sec=1};
if (mtx_timedlock(&mutex, &timeout) == thrd_success) {
  /* Got lock */ mtx_unlock(&mutex);
}
```
### [mtx_trylock](https://en.cppreference.com/w/c/thread/mtx_trylock.html)
Try to lock mutex without blocking.
```c
if (mtx_trylock(&mutex) == thrd_success) {
  /* Got lock */ mtx_unlock(&mutex);
} else { /* Locked by another thread */ }
```

### [mtx_unlock](https://en.cppreference.com/w/c/thread/mtx_unlock.html)
Release mutex lock.
```c
mtx_lock(&mutex);
shared_data++;
mtx_unlock(&mutex);
```

### [mtx_destroy](https://en.cppreference.com/w/c/thread/mtx_destroy.html)
Destroy mutex and release resources.
```c
mtx_t mutex;
mtx_init(&mutex, mtx_plain);
// Use mutex...
mtx_destroy(&mutex);
```

### [call_once](https://en.cppreference.com/w/c/thread/call_once.html)
Ensure function is called exactly once across all threads.
- **Use case**: Thread-safe lazy initialization (create singleton, load config once).
- **Guarantee**: Even if multiple threads call simultaneously, function runs exactly once.
- **once_flag**: Tracks whether function was called (must be initialized with ONCE_FLAG_INIT).
- **Blocking**: Other threads wait if first call is still executing.
```c
once_flag flag = ONCE_FLAG_INIT;
void init_func(void) { /* Initialize once */ }
call_once(&flag, init_func);  // Thread-safe initialization
```

## Condition Variables
### [cnd_init](https://en.cppreference.com/w/c/thread/cnd_init.html)
Initialize condition variable.
```c
cnd_t cond;
cnd_init(&cond);
```

### [cnd_signal](https://en.cppreference.com/w/c/thread/cnd_signal.html)
Wake one waiting thread.
```c
mtx_lock(&mutex); ready = 1; mtx_unlock(&mutex);
cnd_signal(&cond);  // Wake one waiter
```

### [cnd_broadcast](https://en.cppreference.com/w/c/thread/cnd_broadcast.html)
Wake all waiting threads.
```c
mtx_lock(&mutex); ready = 1; mtx_unlock(&mutex);
cnd_broadcast(&cond);  // Wake all waiters
```
### [cnd_wait](https://en.cppreference.com/w/c/thread/cnd_wait.html)
Wait for condition variable signal.
- **Atomicity**: Unlocks mutex and waits as single operation (prevents missed signals).
- **Spurious wakeup**: May wake without signal (always check condition in loop).
- **Pattern**: while (!condition) cnd_wait() is correct idiom (not if).
- **Relocks**: Automatically relocks mutex before returning to caller.
```c
mtx_lock(&mutex);
while (!ready) cnd_wait(&cond, &mutex);  // Atomically unlock/wait/lock
// Process... 
mtx_unlock(&mutex);
```

### [cnd_timedwait](https://en.cppreference.com/w/c/thread/cnd_timedwait.html)
Wait for condition variable with timeout.
```c
struct timespec timeout = {.tv_sec=1};
mtx_lock(&mutex);
int r = cnd_timedwait(&cond, &mutex, &timeout);
mtx_unlock(&mutex);
```

### [cnd_destroy](https://en.cppreference.com/w/c/thread/cnd_destroy.html)
Destroy condition variable.
```c
cnd_t cond;
cnd_init(&cond);
// Use...
cnd_destroy(&cond);
```

## Thread-Local Storage
### [thread_local (C11, removed in C23)](https://en.cppreference.com/w/c/thread/thread_local.html)
Storage duration specifier for per-thread variables.
```c
_Thread_local int tls_var = 0;  // Each thread has own copy
thread_local int var2 = 0;      // C11 macro (removed C23)
```

### [tss_create](https://en.cppreference.com/w/c/thread/tss_create.html)
Create thread-specific storage key.
- **Thread-specific storage (TSS)**: Each thread gets its own separate value for same variable.
- **Key**: Handle used to access per-thread data (like a map key, but per-thread).
- **Destructor**: Optional cleanup function called when thread exits.
- **Use case**: errno, thread-local buffers, per-thread caches.
```c
tss_t key;
void destructor(void *p) { free(p); }
tss_create(&key, destructor);
```

### [tss_get](https://en.cppreference.com/w/c/thread/tss_get.html)
Get thread-specific value.
```c
void *value = tss_get(key);
if (!value) { /* Not set yet */ }
```
### [tss_set](https://en.cppreference.com/w/c/thread/tss_set.html)
Set thread-specific value.
```c
void *data = malloc(100);
tss_set(key, data);  // Store per-thread
```

### [tss_delete](https://en.cppreference.com/w/c/thread/tss_delete.html)
Delete thread-specific storage key.
```c
tss_t key;
tss_create(&key, NULL);
// Use...
tss_delete(key);
```

## Atomic Operations
### [atomic_is_lock_free](https://en.cppreference.com/w/c/atomic/atomic_is_lock_free.html)
Check if atomic type uses lock-free operations.
```c
atomic_int x; 
if (atomic_is_lock_free(&x))
  printf("Lock-free\n");
```

### [atomic_store](https://en.cppreference.com/w/c/atomic/atomic_store.html)
Atomically store value.
```c
atomic_int counter;
atomic_store(&counter, 42);
atomic_store_explicit(&counter, 42, memory_order_release);
```

### [atomic_load](https://en.cppreference.com/w/c/atomic/atomic_load.html)
Atomically load value.
```c
atomic_int counter;
int val = atomic_load(&counter);
int val2 = atomic_load_explicit(&counter, memory_order_acquire);
```

### [atomic_exchange](https://en.cppreference.com/w/c/atomic/atomic_exchange.html)
Atomically swap value and return old value.
```c
atomic_int x;
int old = atomic_exchange(&x, 10);  // Set to 10, get old value
```
### [atomic_compare_exchange](https://en.cppreference.com/w/c/atomic/atomic_compare_exchange.html)
Atomically compare and swap if equal (CAS operation).
- **Compare-and-swap (CAS)**: Fundamental operation for lock-free algorithms.
- **Strong vs weak**: Strong never spuriously fails; weak may (but faster, use in loops).
- **Updates expected**: If comparison fails, expected is updated with current value.
- **Use case**: Lock-free data structures, atomic updates based on old value.
```c
atomic_int x = 5; int expected = 5;
if (atomic_compare_exchange_strong(&x, &expected, 10))
  printf("Swapped\n");  // x is now 10
```

### [atomic_fetch_add](https://en.cppreference.com/w/c/atomic/atomic_fetch_add.html)
Atomically add and return old value.
```c
atomic_int counter = 0;
int old = atomic_fetch_add(&counter, 5);  // counter += 5
```

### [atomic_fetch_sub](https://en.cppreference.com/w/c/atomic/atomic_fetch_sub.html)
Atomically subtract and return old value.
```c
atomic_int counter = 10;
int old = atomic_fetch_sub(&counter, 3);  // counter -= 3
```

### [atomic_fetch_or](https://en.cppreference.com/w/c/atomic/atomic_fetch_or.html)
Atomically OR bits and return old value.
```c
atomic_int flags = 0;
int old = atomic_fetch_or(&flags, 0x04);  // Set bit 2
```

### [atomic_fetch_xor](https://en.cppreference.com/w/c/atomic/atomic_fetch_xor.html)
Atomically XOR bits and return old value.
```c
atomic_int mask = 0xFF;
int old = atomic_fetch_xor(&mask, 0x0F);  // Toggle low bits
```

### [atomic_fetch_and](https://en.cppreference.com/w/c/atomic/atomic_fetch_and.html)
Atomically AND bits and return old value.
```c
atomic_int flags = 0xFF;
int old = atomic_fetch_and(&flags, 0x0F);  // Clear high bits
```

## Atomic Flag Operations
### [atomic_flag_test_and_set](https://en.cppreference.com/w/c/atomic/atomic_flag_test_and_set.html)
Atomically set flag to true and return old value.
```c
atomic_flag lock = ATOMIC_FLAG_INIT;
while (atomic_flag_test_and_set(&lock));  // Spinlock
```

### [atomic_flag_clear](https://en.cppreference.com/w/c/atomic/atomic_flag_clear.html)
Atomically set flag to false.
```c
atomic_flag lock;
atomic_flag_clear(&lock);  // Release spinlock
```

## Atomic Initialization
### [atomic_init](https://en.cppreference.com/w/c/atomic/atomic_init.html)
Initialize atomic object (non-atomic operation).
```c
atomic_int counter;
atomic_init(&counter, 0);  // Initialize before use
```

### [ATOMIC_VAR_INIT (deprecated in C17, removed in C23)](https://en.cppreference.com/w/c/atomic/ATOMIC_VAR_INIT.html)
Macro for static atomic initialization (deprecated).
```c
atomic_int x = ATOMIC_VAR_INIT(42);  // Old style (deprecated)
atomic_int y = 42;                   // Direct init (C17+)
```

### [ATOMIC_FLAG_INIT](https://en.cppreference.com/w/c/atomic/ATOMIC_FLAG_INIT.html)
Initialize atomic_flag to cleared state.
```c
atomic_flag flag = ATOMIC_FLAG_INIT;  // Cleared/false state
```

## Memory Ordering
### [memory_order](https://en.cppreference.com/w/c/atomic/memory_order.html)
Constraints on memory access ordering for synchronization.
- **Memory ordering**: Controls how CPU/compiler reorders memory operations.
- **seq_cst**: Sequentially consistent (default, strongest, slowest).
- **acquire/release**: Establishes synchronization between threads (read/write pairing).
- **relaxed**: No ordering constraints (fastest, no synchronization).
- **Advanced topic**: Most code can use defaults; optimization requires deep understanding.
```c
atomic_store_explicit(&x, 1, memory_order_release);
int v = atomic_load_explicit(&x, memory_order_acquire);
// relaxed, consume, acquire, release, acq_rel, seq_cst
```

### [kill_dependency](https://en.cppreference.com/w/c/atomic/kill_dependency.html)
Break dependency chain for memory_order_consume.
```c
int *p = atomic_load_explicit(&ptr, memory_order_consume);
int val = kill_dependency(p);  // Break dependency
```

### [atomic_thread_fence](https://en.cppreference.com/w/c/atomic/atomic_thread_fence.html)
Memory barrier for synchronization between threads.
- **Memory fence/barrier**: Prevents reordering of operations across the fence.
- **Synchronization**: Ensures one thread's writes are visible to another thread.
- **Use case**: Coordinating non-atomic operations around atomic flag.
- **Release fence**: Paired with acquire fence/load ensures memory visibility.
```c
data = 42;
atomic_thread_fence(memory_order_release);
atomic_store(&flag, 1);
```

### [atomic_signal_fence](https://en.cppreference.com/w/c/atomic/atomic_signal_fence.html)
Memory barrier between thread and signal handler.
```c
data = 42;
atomic_signal_fence(memory_order_release);
raise(SIGUSR1);
```

## Atomic Types
### [atomic_flag](https://en.cppreference.com/w/c/atomic/atomic_flag.html)
Lock-free boolean atomic flag type.
```c
atomic_flag flag = ATOMIC_FLAG_INIT;
atomic_flag_test_and_set(&flag);  // Set to true
atomic_flag_clear(&flag);         // Set to false
```

### [Atomic type aliases (atomic_bool, atomic_int, etc.)](https://en.cppreference.com/w/c/atomic.html#Types)
Convenient typedefs for atomic types.
```c
atomic_int count = 0;         // _Atomic int
atomic_bool ready = false;    // _Atomic bool
atomic_ulong size = 0;        // _Atomic unsigned long
```
