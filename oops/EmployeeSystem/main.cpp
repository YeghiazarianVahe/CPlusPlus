#include <iostream>
#include <vector>
#include <memory>
#include "include/Manager.h"
#include "include/Developer.h"
#include "include/Employee.h"
#include "include/Intern.h"

int main() {
    std::vector<std::unique_ptr<Employee>> employees;

    // Creating employees using polymorphic pointers
    employees.push_back(std::make_unique<Manager>("Alice", 1001, 5000.0, 1500.0));
    employees.push_back(std::make_unique<Developer>("Bob", 1002, 4000.0, 10, 75.0));
    employees.push_back(std::make_unique<Intern>("Charlie", 1003, 1200.0));

    std::cout << "=== Employee Payroll ===\n";
    for (const auto& emp : employees) {
        emp->displayInfo();  // Polymorphic call
    }

    return 0;
}

