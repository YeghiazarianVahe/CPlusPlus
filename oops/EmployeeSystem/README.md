# 👔 Employee Management System

A modern C++ object-oriented application that demonstrates polymorphism, abstract classes, and interface design via a payroll simulation for different types of employees.

---

## 📌 Project Overview

This system models an organization with:

* **Abstract Base Class:** `Employee`
* **Derived Classes:** `Manager`, `Developer`, `Intern`

Each employee type implements its own logic for salary calculation and display formatting, showcasing polymorphism through base class pointers.

---

## 🏗️ Class Design

| Class     | Fields                                | Salary Calculation                  |
| --------- | ------------------------------------- | ----------------------------------- |
| Employee  | `name`, `id` (abstract class)         | Pure virtual `calculateSalary()`    |
| Manager   | `baseSalary`, `bonus`                 | `baseSalary + bonus`                |
| Developer | `baseSalary`, `overtimeHours`, `rate` | `baseSalary + overtimeHours * rate` |
| Intern    | `stipend`                             | `stipend`                           |

---

## 📂 Project Structure

```
EmployeeSystem/
├── include/
│   ├── Employee.h
│   ├── Manager.h
│   ├── Developer.h
│   └── Intern.h
│
├── src/
│   ├── Manager.cpp
│   ├── Developer.cpp
│   └── Intern.cpp
│
├── tests/
│   └── test_employee_system.cpp
│
├── main.cpp
├── Makefile
└── README.md
```

---

## 🚀 How to Compile and Run

### Build and run main program:

```bash
make
./employee_system
```

### Run unit tests:

```bash
make test
./test_employee_system
```

### Clean compiled binaries:

```bash
make clean
```

---

## ✅ Features

* Full use of **inheritance**, **abstract classes**, and **polymorphism**.
* Operator overloading and dynamic dispatch for flexible employee types.
* Unit tests for salary calculation and `displayInfo()`.

---

## 🧪 Test Coverage

* Logic and edge cases for all employee types
* Output testing with `ostringstream`
* Polymorphic behavior and memory cleanup

---

## 🔧 Technologies

* **Language:** C++17
* **Build Tool:** Make
* **Testing:** assert + manual output checks

---

## 📃 License

This project is licensed under the MIT License.

