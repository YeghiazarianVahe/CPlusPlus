#include <iostream>
#include <cassert>
#include <cstring>
#include "../include/MyString.h"

void testConstructors() {
    MyString a("Hello");
    assert(std::strcmp(a.c_str(), "Hello") == 0);

    MyString b;  // default
    assert(std::strcmp(b.c_str(), "") == 0);

    MyString c = a;  // copy constructor
    assert(c == a);

    MyString d = MyString("Temp");  // move constructor
    assert(std::strcmp(d.c_str(), "Temp") == 0);

    std::cout << "[✓] Constructors passed\n";
}

void testAssignment() {
    MyString a("Hello");
    MyString b;
    b = a;  // copy assignment
    assert(b == a);

    MyString c;
    c = MyString("World");  // move assignment
    assert(std::strcmp(c.c_str(), "World") == 0);

    std::cout << "[✓] Assignment operators passed\n";
}

void testOperators() {
    MyString a("Hi");
    MyString b("There");
    MyString c = a + b;
    assert(std::strcmp(c.c_str(), "HiThere") == 0);

    assert(!(a == b));
    assert(a == MyString("Hi"));

    MyString d("Test");
    d[0] = 'B';
    assert(d[0] == 'B');
    assert(d == MyString("Best"));

    const MyString e("ConstTest");
    assert(e[1] == 'o');

    std::cout << "[✓] Operators passed\n";
}

void testMethods() {
    MyString a("Methods");
    assert(a.size() == 7);
    assert(std::strcmp(a.c_str(), "Methods") == 0);

    MyString sub = a.substr(1, 3);  // "eth"
    assert(sub == MyString("eth"));

    a.clear();
    assert(a.size() == 0);
    assert(std::strcmp(a.c_str(), "") == 0);

    std::cout << "[✓] Extra methods passed\n";
}

void testIO() {
    MyString input;
    std::cout << "Enter a word for input test: ";
    std::cin >> input;
    std::cout << "You entered: " << input << "\n";

    // Just basic I/O shown; no assertion for this part
}

int main() {
    testConstructors();
    testAssignment();
    testOperators();
    testMethods();
    // testIO(); // Uncomment for interactive testing

    std::cout << "\nAll tests passed successfully ✅\n";
    return 0;
}

