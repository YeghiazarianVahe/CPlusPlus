#include <cassert>
#include <sstream>
#include <iostream>
#include "../include/Manager.h"
#include "../include/Developer.h"
#include "../include/Intern.h"

// Utility function to capture displayInfo() output
std::string captureDisplayInfo(const Employee& emp) {
    std::ostringstream oss;
    std::streambuf* oldCout = std::cout.rdbuf(); // Save old buffer
    std::cout.rdbuf(oss.rdbuf());                // Redirect std::cout to oss

    emp.displayInfo();

    std::cout.rdbuf(oldCout); // Restore old buffer
    return oss.str();
}

// Test Manager functionality
void testManager() {
    Manager m("Alice", 101, 5000.0, 1500.0);

    assert(m.getBaseSalary() == 5000.0);
    assert(m.getBonus() == 1500.0);
    assert(m.calculateSalary() == 6500.0);

    std::string output = captureDisplayInfo(m);
    assert(output.find("Manager") != std::string::npos);
    assert(output.find("Alice") != std::string::npos);
}

// Test Developer functionality and edge cases
void testDeveloper() {
    Developer d("Bob", 102, 4000.0, 0, 100.0);
    assert(d.calculateSalary() == 4000.0); // No overtime

    d = Developer("Bob", 102, 4000.0, 10, 100.0);
    assert(d.calculateSalary() == 5000.0); // 4000 + 10 * 100

    std::string output = captureDisplayInfo(d);
    assert(output.find("Developer") != std::string::npos);
    assert(output.find("Bob") != std::string::npos);
}

// Test Intern functionality and edge cases
void testIntern() {
    Intern i("Charlie", 103, 0.0);
    assert(i.calculateSalary() == 0.0); // Free intern!

    i = Intern("Charlie", 103, 1000.0);
    assert(i.getStipend() == 1000.0);
    assert(i.calculateSalary() == 1000.0);

    std::string output = captureDisplayInfo(i);
    assert(output.find("Intern") != std::string::npos);
    assert(output.find("Charlie") != std::string::npos);
    assert(output.find("Stipend") != std::string::npos);
}

// Test polymorphism
void testPolymorphism() {
    Employee* emp1 = new Manager("Anna", 111, 6000, 1000);
    Employee* emp2 = new Developer("Dan", 112, 3500, 5, 80);
    Employee* emp3 = new Intern("Eva", 113, 900);

    assert(emp1->calculateSalary() == 7000);
    assert(emp2->calculateSalary() == 3500 + 5 * 80);
    assert(emp3->calculateSalary() == 900);

    std::string out1 = captureDisplayInfo(*emp1);
    std::string out2 = captureDisplayInfo(*emp2);
    std::string out3 = captureDisplayInfo(*emp3);

    assert(out1.find("Manager") != std::string::npos);
    assert(out2.find("Developer") != std::string::npos);
    assert(out3.find("Intern") != std::string::npos);

    delete emp1;
    delete emp2;
    delete emp3;
}

int main() {
    std::cout << "Running deep employee system tests...\n";

    testManager();
    std::cout << "✔ Manager tests passed.\n";

    testDeveloper();
    std::cout << "✔ Developer tests passed.\n";

    testIntern();
    std::cout << "✔ Intern tests passed.\n";

    testPolymorphism();
    std::cout << "✔ Polymorphism tests passed.\n";

    std::cout << "✅ All tests passed successfully.\n";
    return 0;
}

