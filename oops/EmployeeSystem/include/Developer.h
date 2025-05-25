#ifndef DEVELOPER_H
#define DEVELOPER_H

#include "Employee.h"

class Developer : public Employee {
private:
    double baseSalary;
    double overtimeHours;
    double overtimeRate;

public:
    // Constructor
    Developer(const std::string& name, int id,
              double baseSalary, double overtimeHours, double overtimeRate);

    // Destructor
    virtual ~Developer();

    // Override salary calculation
    double calculateSalary() const override;

    // Override display function
    void displayInfo() const override;

    // Accessors
    double getBaseSalary() const;
    void getOvertime() const;
};

#endif // DEVELOPER_H

