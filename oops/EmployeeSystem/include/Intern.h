#ifndef INTERN_H
#define INTERN_H

#include "Employee.h"

class Intern : public Employee {
private:
    double stipend;

public:
    // Constructor
    Intern(const std::string& name, int id, double stipend);

    // Destructor
    virtual ~Intern();

    // Override salary calculation
    double calculateSalary() const override;

    // Override display function
    void displayInfo() const override;

    // Accessor
    double getStipend() const;
};

#endif // INTERN_H

