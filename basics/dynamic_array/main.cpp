#include "Vector.h"

int main() {
    Vector vec;

    std::cout << "Initial size: " << vec.get_size() << "\n";
    std::cout << "Initial capacity: " << vec.get_capacity() << "\n\n";

    // Push elements
    for (int i = 0; i < 10; ++i) {
        vec.push_back(i * 10);
        std::cout << "Pushed: " << i * 10 
                  << ", Size: " << vec.get_size() 
                  << ", Capacity: " << vec.get_capacity() << "\n";
    }

    std::cout << "\nCurrent Elements:\n";
    for (std::size_t i = 0; i < vec.get_size(); ++i) {
        std::cout << "vec[" << i << "] = " << vec[i] << "\n";
    }

    // Pop a few elements
    std::cout << "\nPopping 3 elements...\n";
    vec.pop_back();
    vec.pop_back();
    vec.pop_back();

    std::cout << "Size after popping: " << vec.get_size() << "\n";

    std::cout << "\nElements after popping:\n";
    for (std::size_t i = 0; i < vec.get_size(); ++i) {
        std::cout << "vec[" << i << "] = " << vec[i] << "\n";
    }

    return 0;
}
