#include <iostream>  // Include the standard input-output stream library

int main() {
    // Declaring two integer variables
    int x;
    int y;

    // Asking the user to input the first number
    std::cout << "Enter first number:  x = ";
    std::cin >> x;  // Taking input from the user and storing it in x

    // Asking the user to input the second number
    std::cout << "Enter second number: y = ";
    std::cin >> y;  // Taking input from the user and storing it in y

    // Performing arithmetic operations and displaying the results
    std::cout << "x + y = " << x + y << std::endl;  // Addition
    std::cout << "x * y = " << x * y << std::endl;  // Multiplication
    std::cout << "x - y = " << x - y << std::endl;  // Subtraction
    std::cout << "x / y = " << x / y << std::endl;  // Division (integer division)

    return 0;  // Exit the program successfully
}
