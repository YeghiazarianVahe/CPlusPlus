# Phase 4: Memory Management & Smart Pointers

This repository contains the implementation and tests for **Phase 4** of our C++ learning roadmap, focusing on memory management techniques—from manual allocation to smart pointers. The project is organized under the `memory/` folder and includes:

```
memory/
├── include/
│   ├── Arena.hpp
│   ├── Logger.hpp
│   ├── MyUnique.hpp
│   └── MyShared.hpp
├── src/
│   ├── Arena.cpp
│   └── Logger.cpp
├── tests/
│   └── test_memory.cpp
└── Makefile
```

## 📁 Project Structure

* **include/**: Header files.

  * `Arena.hpp` – A simple "arena" memory manager using `malloc`/`free`, tracking allocations for automatic cleanup.
  * `Logger.hpp` – A `Logger` class that wraps a `FILE*` in a `std::unique_ptr` with a custom deleter, writing log messages to a file.
  * `MyUnique.hpp` – A minimal, header-only implementation of a `std::unique_ptr`-like class (`MyUnique<T>`) with exclusive ownership and move semantics.
  * `MyShared.hpp` – A minimal, header-only, non-thread-safe implementation of a `std::shared_ptr`-like class (`MyShared<T>`) with reference counting.

* **src/**: Implementation files.

  * `Arena.cpp` – (Empty; all `Arena` methods are implemented inline in `Arena.hpp`.)
  * `Logger.cpp` – Definitions for `Logger::Logger(const std::string&)` and `Logger::log(const std::string&)`.
  * **Note**: `MyUnique` and `MyShared` are header-only, so no corresponding `.cpp` files.

* **tests/**: Combined test suite.

  * `test_memory.cpp` – Verifies all functionality:

    1. **Arena**: allocation, read/write, `release_all()`, move semantics.
    2. **Logger**: writing to a file, reading back log contents, cleanup.
    3. **MyUnique**: construction, `release()`, `reset()`, move construction/assignment, `operator->`.
    4. **MyShared**: reference counting, copy/move constructors and assignments, `use_count()`, nullptr state.

* **Makefile**: Simplifies building and running tests.

## 🛠️ Build & Run Tests

Ensure you have a C++ compiler that supports C++17. From the `memory/` root directory, run:

```bash
# Build everything and run the combined tests
make test
```

* `make test` will:

  1. Create the `bin/` directory (if it doesn’t exist).
  2. Compile all source files (`Arena.cpp`, `Logger.cpp`) and the combined test file (`test_memory.cpp`) into `bin/`.
  3. Link all object files into the `bin/test_memory` executable.
  4. Run `bin/test_memory`, printing `All tests passed!` on success.

To clean up build artifacts, run:

```bash
make clean
```

This removes the entire `bin/` directory.

## 📝 Overview of Components

### 1. Arena (Manual Memory Manager)

* **Header**: `include/Arena.hpp`

* **Key Functionality**:

  * `void* allocate(std::size_t bytes)` – Calls `std::malloc(bytes)`; tracks the returned pointer in an internal `std::vector<void*>`.
  * `void release_all() noexcept` – Iterates over tracked pointers and calls `std::free(ptr)` for each, then clears the list.
  * **Rule of 3/5 Compliance**: Copy disabled; move constructor and move assignment transfer ownership of tracked pointers.
  * **Destructor**: Calls `release_all()`.

* **Tests** (in `test_memory.cpp`):

  1. Allocate an `int` array, write and read elements.
  2. Allocate a `char` buffer, copy a C-string in, and verify with `std::strcmp`.
  3. Call `release_all()`, then allocate again and verify new data.
  4. Test move semantics by moving one `Arena` into another and verifying old allocations are gone.

### 2. Logger (unique\_ptr with Custom Deleter)

* **Header**: `include/Logger.hpp`

* **Implementation**: `src/Logger.cpp`

* **Key Functionality**:

  * Wraps a `FILE*` in a `std::unique_ptr<FILE, int(*)(FILE*)>` using `std::fclose` as the deleter.
  * Throws `std::runtime_error` if `fopen` fails.
  * `void log(const std::string& msg)` writes `msg` plus newline via `std::fprintf`.
  * Destructor of `std::unique_ptr` guarantees `fclose` on scope exit.

* **Tests** (in `test_memory.cpp`):

  1. Create `Logger("test_log.txt")`, write two lines.
  2. Close logger (upon destruction) and reopen file with `std::ifstream`.
  3. Verify the two lines were written correctly and no extra content exists.
  4. Delete the `test_log.txt` file.

### 3. MyUnique<T> (Minimal unique\_ptr-like)

* **Header**: `include/MyUnique.hpp`

* **Key Functionality** (all inline/member-defined):

  * Exclusive ownership of a raw `T*`.
  * **Constructor**: `explicit MyUnique(T* ptr = nullptr)`
  * **Destructor**: `delete ptr_` if not null.
  * **Move Constructor**: `MyUnique(MyUnique&& other) noexcept` steals `other.ptr_`, sets `other.ptr_ = nullptr`.
  * **Move Assignment**: deletes current, steals from `other`, sets `other.ptr_ = nullptr`.
  * **Copy**: Disabled (`delete`).
  * `T* release() noexcept` – Returns raw pointer and sets internal `ptr_ = nullptr`.
  * `void reset(T* new_ptr = nullptr) noexcept` – Deletes current and assigns `new_ptr`.
  * Observers: `T* get()`, `T& operator*()`, `T* operator->()`, `explicit operator bool()`.

* **Tests** (in `test_memory.cpp`):

  1. Construct with `new int(10)`, dereference and verify.
  2. `release()`, confirm old pointer is returned, internal pointer null, delete raw.
  3. `reset(new int(20))`, `*u1 == 20`.
  4. Move constructor: `MyUnique<int> u2(std::move(u1))`; confirm `u1` is null, `u2` owns the value.
  5. `reset()` to null, confirm `get() == nullptr`.
  6. Use `operator->` on a small `struct Foo`.
  7. Move assignment: `fu3 = std::move(fu2)`, confirm ownership transfer.

### 4. MyShared<T> (Minimal shared\_ptr-like)

* **Header**: `include/MyShared.hpp`

* **Key Functionality** (all inline/member-defined):

  * **Constructor**: `explicit MyShared(T* raw_ptr)` sets `ptr_ = raw_ptr`, allocates `count_ = new std::size_t(1)` if `raw_ptr != nullptr`.
  * **Default Constructor**: `MyShared()` sets both pointers to `nullptr`.
  * **Copy Constructor**: Increments `(*count_)` if `count_ != nullptr`.
  * **Move Constructor**: Steals `ptr_` and `count_`, sets other to `nullptr`.
  * **Copy Assignment**: Decrements old count (delete if zero), then shares/increments from `other`.
  * **Move Assignment**: Decrements old count, then steals pointers, sets other to `nullptr`.
  * **Destructor**: If `count_` decremented to zero, deletes `ptr_` and `count_`.
  * `std::size_t use_count() const noexcept` returns `*count_` or `0` if null.
  * Observers: `T* get()`, `T& operator*()`, `T* operator->()`, `explicit operator bool()`.

* **Tests** (in `test_memory.cpp`):

  1. Construct `MyShared<int> s1(new int(42))`, check `use_count() == 1`.
  2. Copy `s2(s1)`, confirm `use_count() == 2`.
  3. Nested copy to `s3`, confirm `use_count() == 3`, then let `s3` go out of scope (back to 2).
  4. Move constructor: `MyShared<int> s4(std::move(s1))`, confirm `s1.get() == nullptr`, `s4.use_count() == 1`.
  5. Move assignment: `s5 = MyShared<int>(new int(200))`, confirm `s5.use_count() == 1`, `*s5 == 200`.
  6. Copy assignment: `s6 = s5`, confirm `use_count() == 2`.
  7. Self-copy assignment: `s6 = s6`, confirm stable `use_count() == 2`.
  8. Default `MyShared<int> sEmpty`, confirm `get() == nullptr` and `use_count() == 0`.
  9. Chaining with `std::string` to confirm copy/move semantics and `use_count()`.

## 🚀 Getting Started

1. Clone or download this repository.
2. Navigate to the `memory/` folder.
3. Run `make test`.
4. Observe that output ends with `All tests passed!`.
5. (Optional) Use `make clean` to remove the `bin/` directory.









