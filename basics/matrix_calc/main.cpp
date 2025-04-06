#include "Matrix.h"
#include <iostream>

void printMenu() {
    std::cout << "\n=== Matrix Calculator ===\n";
    std::cout << "Available operations:\n";
    std::cout << "1. Add (A + B)\n";
    std::cout << "2. Subtract (A - B)\n";
    std::cout << "3. Multiply (A * B)\n";
    std::cout << "4. Transpose A\n";
    std::cout << "5. Transpose B\n";
    std::cout << "0. Exit\n";
    std::cout << "Choose option: ";
}

Matrix getMatrixInput(const std::string& name) {
    int rows, cols;
    std::cout << "\nEnter dimensions for Matrix " << name << " (rows cols): ";
    std::cin >> rows >> cols;

    Matrix M(rows, cols);
    std::cout << "Enter elements for Matrix " << name << ":\n";
    M.input();

    return M;
}

int main() {
    Matrix A = getMatrixInput("A");
    Matrix B = getMatrixInput("B");

    int choice;
    do {
        printMenu();
        std::cin >> choice;

        try {
            switch (choice) {
                case 1: {
                    Matrix result = Matrix::add(A, B);
                    std::cout << "\nResult (A + B):\n";
                    result.print();
                    break;
                }
                case 2: {
                    Matrix result = Matrix::subtract(A, B);
                    std::cout << "\nResult (A - B):\n";
                    result.print();
                    break;
                }
                case 3: {
                    Matrix result = Matrix::multiply(A, B);
                    std::cout << "\nResult (A * B):\n";
                    result.print();
                    break;
                }
                case 4: {
                    Matrix tA = Matrix::transpose(A);
                    std::cout << "\nTranspose of A:\n";
                    tA.print();
                    break;
                }
                case 5: {
                    Matrix tB = Matrix::transpose(B);
                    std::cout << "\nTranspose of B:\n";
                    tB.print();
                    break;
                }
                case 0:
                    std::cout << "Exiting...\n";
                    break;
                default:
                    std::cout << "Invalid choice.\n";
            }
        } catch (const std::exception& e) {
            std::cout << "Error: " << e.what() << '\n';
        }

    } while (choice != 0);

    return 0;
}
