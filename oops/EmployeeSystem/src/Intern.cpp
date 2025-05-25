#include "../include/Intern.h"

Intern::Intern(const std::string& name, int id, double stipend) 
	: Employee(name, id), stipend(stipend) {};

Intern::~Intern() {};

double Intern::calculateSalary() const {
	return stipend;
};

void Intern::displayInfo() const {
    std::cout << "[Intern] " << name
              << " (ID: " << id << ") - Stipend: $"
              << calculateSalary() << "\n";
}

double Intern::getStipend() const {
	return stipend;
};

