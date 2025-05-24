#include "../include/Account.h"

Account::Account(double init_balance = 0.0) : balance(init_balance) {};
Account::~Account() {};

void Account::deposit(double amount) {
	balance += amount;
}

bool Account::withdraw(double amount) {
	if(balance >= amount){
		balance -= amount;
		return true;
	}
	return false;
}

double Account::getBalance() const {
	return balance;
}

//Operator overloading
bool Account::operator==(const Account& other) const {
	return balance == other.balance;
}

bool Account::operator!=(const Account& other) const {
	return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const Account& acc) {
	os << "Account balance: $"<<acc.balance;
	return os;
}

