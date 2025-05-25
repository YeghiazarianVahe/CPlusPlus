#include "../include/Developer.h"
#include <cstring>

Developer::Developer(const std::string& name, int id, double baseSalary,
			double overtimeHours, double overtimeRate) 
	: Employee(name, id), baseSalary(baseSalary), overtimeHours(overtimeHours),
	overtimeRate(overtimeRate) {};

Developer::~Developer() {};

double Developer::calculateSalary() const {
	return baseSalary + (overtimeHours * overtimeRate);
}

void Developer::displayInfo() const {
    std::cout << "[Developer] " << name
              << " (ID: " << id << ") - Salary: $"
              << calculateSalary() << "\n";
}

double Developer::getBaseSalary() const {
	return baseSalary;
}

void Developer::getOvertime() const {
	std::cout << "Developer works " << overtimeHours << " hours in rate "
		  << overtimeRate << ".\n";
}

