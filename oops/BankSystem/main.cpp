#include <iostream>
#include "include/Account.h"
#include "include/SavingsAccount.h"
#include "include/CheckingAccount.h"

int main() {
    // Creating accounts
    SavingsAccount sa(1000.0, 0.05);      // initial balance: $1000, interest rate: 5%
    CheckingAccount ca(500.0, 200.0);     // initial balance: $500, overdraft: $200

    // Test deposits
    sa.deposit(200.0);
    ca.deposit(100.0);

    // Apply interest to savings account
    sa.applyInterest();

    // Display balances
    std::cout << "Savings Account: " << sa << "\n";
    std::cout << "Checking Account: " << ca << "\n";

    // Test withdrawals
    sa.withdraw(100.0);
    ca.withdraw(750.0); // Exceeds balance, within overdraft

    // Final balances
    std::cout << "After withdrawals:\n";
    std::cout << "Savings Account: " << sa << "\n";
    std::cout << "Checking Account: " << ca << "\n";

    return 0;
}

