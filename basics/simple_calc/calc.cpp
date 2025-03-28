#include <iostream>
#include <stdexcept>
// #include <format>  // Uncomment if you want to use std::format in C++20

int calculator(int first, int second, char operand);

int main() {
    int x, y;
    char operand;

    std::cout << "Enter expression (e.g. 5 + 3): ";
    if (!(std::cin >> x >> operand >> y)) {
        std::cerr << "Invalid input format!\n";
        return 1;
    }

    try {
        int result = calculator(x, y, operand);
        std::cout << "Result is: " << result << '\n';
        // std::cout << std::format("Result is: {}", result);  // If using C++20
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << '\n';
        return 1;
    }

    return 0;
}

int calculator(int first, int second, char operand) {
    switch (operand) {
        case '+': return first + second;
        case '-': return first - second;
        case '*': return first * second;
        case '/':
            if (second == 0)
                throw std::runtime_error("Math error! Can't divide by zero!");
            return first / second;
        default:
            throw std::invalid_argument("Invalid operand! Use +, -, *, or /.");
    }
}
