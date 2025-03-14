#include <iostream>

int main(){
    int random = rand() % 101;
    int guest;
    while(1){
        std::cout << "Guest number between 0 and 100: ";
        std::cin >> guest;
        if(guest > random){
            std::cout << "Try again! Your number is bigger.\n";
        }
        if(guest < random){
            std::cout << "Try again! Your number is smaller.\n";
        }
        if(guest == random){
            std::cout << "Congratulations !!! YOU WIN !!!\n";
            break;
        }
    }
    return 0;
}