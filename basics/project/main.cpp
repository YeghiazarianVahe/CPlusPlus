#include <iostream>

int main(){
    std::cout << "Welcome to mini scientific toolbox.\n";
    std::cout << "/================================\\\n";
    std::cout << "|===== 1. Matrix operations =====|\n";
    std::cout << "|===== 2. Vector operations =====|\n";
    std::cout << "|===== 3. String operations =====|\n";
    std::cout << "|======== 4.  Calculator ========|\n";
    std::cout << "|========  5.  Swap demo  =======|\n";
    std::cout << "\\===============================/\n";
    std::cout << "||==>>  Choose an option: =>  \n";
    
    int choice;
    std::cin >> choice;

    // TODO: Dispatch to the appropriate module

    return 0;
}