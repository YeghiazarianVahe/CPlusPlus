# 👵 MyString — Custom C++ String Class

This project implements a custom string class `MyString` in C++ that mimics the behavior of `std::string`. It is designed for deep learning and practice with memory management, rule of three/five, operator overloading, and custom class design.

---

## 📌 Features

* ✅ Deep copy & dynamic memory allocation
* ✅ Copy and move constructors
* ✅ Copy and move assignment operators
* ✅ Rule of Three / Rule of Five (optional)
* ✅ Operator overloading:

  * `+` (concatenation)
  * `==` (equality comparison)
  * `[]` (index access, const and non-const)
  * `<<` and `>>` (stream insertion/extraction)
* ✅ Utility methods:

  * `size()`
  * `c_str()`
  * `substr(pos, len)`
  * `clear()`

---

## 📂 Project Structure

```
MyStringProject/
├── include/
│   └── MyString.h             # Class declaration
├── src/
│   └── MyString.cpp           # Class implementation
├── tests/
│   └── test_mystring.cpp     # Full test suite using assert
├── bin/
│   └── test_string            # Compiled test executable
└── Makefile                   # Build system
```

---

## ▶️ Build & Run

### Compile

```bash
make
```

### Run Tests

```bash
make run
```

### Clean Build Artifacts

```bash
make clean
```

---

## ⚖️ Example Usage

```cpp
MyString a("Hello");
MyString b("World");
MyString c = a + b;
std::cout << c << std::endl; // HelloWorld

if (c == MyString("HelloWorld")) {
    std::cout << "Strings match!" << std::endl;
}
```

---

## 📃 License

This project is for educational purposes only. No license required.

