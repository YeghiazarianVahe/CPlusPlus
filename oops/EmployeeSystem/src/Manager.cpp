#include "../include/Manager.h"

Manager::Manager(const std::string& name, int id, double baseSalary, double bonus) 
	: Employee(name, id), baseSalary(baseSalary), bonus(bonus) {};

Manager::~Manager() {}

double Manager::calculateSalary() const {
	return baseSalary + bonus;
}

void Manager::displayInfo() const {
    std::cout << "[Manager] " << name
              << " (ID: " << id << ") - Salary: $"
              << calculateSalary() << "\n";
}

double Manager::getBaseSalary() const {
	return baseSalary;
}

double Manager::getBonus() const {
	return bonus;
}
