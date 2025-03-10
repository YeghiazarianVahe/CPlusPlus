#include <iostream>  // Include the iostream library for input and output

int main() {
    float cels;  // Variable to store temperature in Celsius
    float fahr;  // Variable to store temperature in Fahrenheit

    // Prompt the user to enter a temperature in Celsius
    std::cout << "Enter temperature in Celsius: ";
    std::cin >> cels;  // Read user input into the 'cels' variable

    // Convert Celsius to Fahrenheit using the formula: F = C * 1.8 + 32
    std::cout << "Temperature in Fahrenheit: " << cels * 1.8 + 32 << "F\n";

    // Prompt the user to enter a temperature in Fahrenheit
    std::cout << "Enter temperature in Fahrenheit: ";
    std::cin >> fahr;  // Read user input into the 'fahr' variable

    // Convert Fahrenheit to Celsius using the formula: C = (F - 32) / 1.8
    std::cout << "Temperature in Celsius: " << (fahr - 32) / 1.8 << "C\n";

    return 0;  // Indicate that the program executed successfully
}
