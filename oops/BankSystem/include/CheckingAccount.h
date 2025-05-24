#ifndef CHECKINGACCOUNT_H
#define CHECKINGACCOUNT_H

#include "Account.h"

class CheckingAccount : public Account {
private:
    double overdraftLimit;

public:
    CheckingAccount(double init_balance = 0.0, double overdraft = 0.0);
    virtual ~CheckingAccount();

    // Overridden methods
    bool withdraw(double amount) override;

    // Additional functionality
    void setOverdraftLimit(double limit);
    double getOverdraftLimit() const;
};

#endif // CHECKINGACCOUNT_H

