#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <string>
#include <iostream>

//Abstract base class
class Employee {
protected:
    std::string name;
    int id;

public:
    Employee(const std::string& name, int id);       // declared
    virtual ~Employee();                             // declared
    virtual double calculateSalary() const = 0;      // pure virtual
    virtual void displayInfo() const = 0;            // pure virtual
};



#endif
