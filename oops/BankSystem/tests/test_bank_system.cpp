#include <cassert>
#include <iostream>
#include "Account.h"
#include "SavingsAccount.h"
#include "CheckingAccount.h"

void testAccount() {
    Account acc(100.0);
    acc.deposit(50.0);
    assert(acc.getBalance() == 150.0);

    assert(acc.withdraw(100.0));
    assert(acc.getBalance() == 50.0);

    assert(!acc.withdraw(100.0)); // Insufficient funds
}

void testSavingsAccount() {
    SavingsAccount sa(1000.0, 0.10); // 10% interest
    sa.applyInterest();
    assert(sa.getBalance() == 1100.0);

    assert(sa.withdraw(1050.0));
    assert(sa.getBalance() == 50.0);

    assert(!sa.withdraw(50.0)); // Fails, below min balance
}

void testCheckingAccount() {
    CheckingAccount ca(500.0, 100.0); // overdraft $100
    assert(ca.withdraw(550.0)); // within overdraft
    assert(ca.getBalance() == -50.0);

    assert(!ca.withdraw(100.1)); // exceeds overdraft limit
}

int main() {
    std::cout << "Running tests...\n";

    testAccount();
    std::cout << "Account tests passed.\n";

    testSavingsAccount();
    std::cout << "SavingsAccount tests passed.\n";

    testCheckingAccount();
    std::cout << "CheckingAccount tests passed.\n";

    std::cout << "All tests passed successfully.\n";
    return 0;
}

