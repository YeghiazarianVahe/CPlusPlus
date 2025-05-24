#include "../include/CheckingAccount.h"

CheckingAccount::CheckingAccount(double init_balance, double overdraft) :
	Account(init_balance), overdraftLimit(overdraft) {};

CheckingAccount::~CheckingAccount() {};

//Withdraw with overdraft protection
bool CheckingAccount::withdraw(double amount) {
	if (balance + overdraftLimit >= amount) {
		balance -= amount;
		return true;
	}
	else {
		std::cerr << "Withdrawal denied: exceeds overdraft limit of $"<< overdraftLimit << ".\n";
		return false;
	}
}

// Setter for overdraft limit
void CheckingAccount::setOverdraftLimit(double limit) {
    if (limit >= 0.0) {
        overdraftLimit = limit;
    } else {
        std::cerr << "Invalid overdraft limit. Must be non-negative.\n";
    }
}

// Getter for overdraft limit
double CheckingAccount::getOverdraftLimit() const {
    return overdraftLimit;
}
