#include <iostream>
#include <string>

template <typename T>
void my_swap_ref(T& first, T& second){
    T temp = first;
    first = second;
    second = temp;
}

template <typename T>
void my_swap_ptr(T* first, T* second){
    if(first == nullptr || second == nullptr) return;
    T temp = *first;
    *first = *second;
    *second = temp;
}

int main() {
    std::cout << "=== Testing my_swap_ref ===\n";

    int a = 10, b = 20;
    my_swap_ref(a, b);
    std::cout << "int: a = " << a << ", b = " << b << "\n";

    double x = 1.5, y = 3.5;
    my_swap_ref(x, y);
    std::cout << "double: x = " << x << ", y = " << y << "\n";

    std::string s1 = "Hello", s2 = "World";
    my_swap_ref(s1, s2);
    std::cout << "string: s1 = " << s1 << ", s2 = " << s2 << "\n";

    std::cout << "\n=== Testing my_swap_ptr ===\n";

    int m = 100, n = 200;
    my_swap_ptr(&m, &n);
    std::cout << "int: m = " << m << ", n = " << n << "\n";

    double p = 2.71, q = 3.14;
    my_swap_ptr(&p, &q);
    std::cout << "double: p = " << p << ", q = " << q << "\n";

    std::string str1 = "C++", str2 = "Rocks";
    my_swap_ptr(&str1, &str2);
    std::cout << "string: str1 = " << str1 << ", str2 = " << str2 << "\n";

    return 0;
}