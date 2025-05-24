#ifndef SAVINGSACCOUNT_H
#define SAVINGSACCOUNT_H

#include "Account.h"

class SavingsAccount : public Account {
private:
    double interestRate;

public:
    SavingsAccount(double, double);
    virtual ~SavingsAccount();

    void applyInterest();

    // Method overriding
    bool withdraw(double) override;
};

#endif // SAVINGSACCOUNT_H

