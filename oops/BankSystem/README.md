# 🏦 Bank System

This project implements a simple bank account system using modern C++ Object-Oriented Programming concepts such as inheritance, polymorphism, and operator overloading.

---

## 📌 Project Overview

The system provides three types of bank accounts:

* **General Account**: Basic operations (deposit, withdraw, balance inquiry).
* **Savings Account**: Interest calculation and minimum balance protection.
* **Checking Account**: Overdraft protection allowing withdrawals beyond the available balance up to a limit.

---

## 📂 Project Structure

```
BankSystem/
├── include/
│   ├── Account.h
│   ├── SavingsAccount.h
│   └── CheckingAccount.h
│
├── src/
│   ├── Account.cpp
│   ├── SavingsAccount.cpp
│   └── CheckingAccount.cpp
│
├── tests/
│   └── test_bank_system.cpp
│
├── main.cpp
├── Makefile
└── README.md
```

---

## 🛠️ Compilation

### Compile the main program:

```bash
make clean
make
```

### Run the application:

```bash
./bank_system
```

### Compile and run unit tests:

```bash
./test_bank_system
```

---

## 🚀 Features

* **Operator Overloading**: Easily print account details, compare balances.
* **Inheritance & Polymorphism**: Clearly defined class hierarchies with specialized account behaviors.
* **Robust Error Handling**: Withdrawals checked for overdraft, minimum balance enforcement.

---

## ✅ Testing

Unit tests validate critical functionalities:

* Deposit and withdrawal operations
* Overdraft protection in checking accounts
* Interest calculations in savings accounts

Run tests regularly to ensure correctness:

```bash
./test_bank_system
```

---

## 📚 Usage Examples

Basic demonstration of creating and operating bank accounts:

```cpp
SavingsAccount sa(1000.0, 0.05);  // initial balance $1000, interest rate 5%
CheckingAccount ca(500.0, 200.0); // initial balance $500, overdraft limit $200

sa.deposit(200);
sa.applyInterest();
ca.withdraw(600); // uses overdraft
```

---

## ⚙️ Technologies

* **Language**: C++17
* **Tools**: GNU Make, g++

---

## 📃 License

This project is open-source under the MIT License. You are free to modify and redistribute the code as per the license terms.

