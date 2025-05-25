#ifndef MANAGER_H
#define MANAGER_H

#include "Employee.h"

class Manager : public Employee {
private:
    double baseSalary;
    double bonus;

public:
    // Constructor
    Manager(const std::string& name, int id, double baseSalary, double bonus);

    // Destructor
    virtual ~Manager();

    // Override pure virtual function
    double calculateSalary() const override;

    // Override display function
    void displayInfo() const override;

    // Accessors
    double getBaseSalary() const;
    double getBonus() const;
};

#endif // MANAGER_H

