#include "../include/SavingsAccount.h"

SavingsAccount::SavingsAccount(double init_balance, double rate) :
	Account(init_balance), interestRate(rate) {};

SavingsAccount::~SavingsAccount() {};

void SavingsAccount::applyInterest() {
	balance += balance * interestRate;
}

bool SavingsAccount::withdraw(double amount) {
	const double min_balance = 50.0; // Minimum balance required for SavingsAccount

    // Check if withdrawal maintains minimum balance
    if (balance - amount >= min_balance) {
        balance -= amount;
        return true;
    } 
    else {
        std::cerr << "Withdrawal denied: must maintain minimum balance of $"
                  << min_balance << ".\n";
        return false;
    }
}

