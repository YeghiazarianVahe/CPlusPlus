#include <cassert>
#include <iostream>
#include "fraction.hpp"

void test_constructors() {
    Fraction f1;  // Default
    Fraction f2(3, 6);  // Should reduce to 1/2
    Fraction f3(f2);    // Copy constructor

    assert(f2 == Fraction(1, 2));
    assert(f3 == Fraction(1, 2));
}

void test_assignment_operator() {
    Fraction a(2, 4);  // should become 1/2
    Fraction b;
    b = a;

    assert(b == Fraction(1, 2));
}

void test_addition() {
    Fraction a(1, 3);
    Fraction b(1, 6);
    Fraction c = a + b;

    assert(c == Fraction(1, 2));
}

void test_subtraction() {
    Fraction a(3, 4);
    Fraction b(1, 4);
    Fraction c = a - b;

    assert(c == Fraction(1, 2));
}

void test_multiplication() {
    Fraction a(2, 3);
    Fraction b(3, 4);
    Fraction c = a * b;

    assert(c == Fraction(1, 2));
}

void test_division() {
    Fraction a(3, 5);
    Fraction b(6, 10);
    Fraction c = a / b;

    assert(c == Fraction(1, 1));  // 3/5 ÷ 6/10 = (3/5)*(10/6) = 30/30 = 1/1
}

void test_negative_handling() {
    Fraction a(-2, 4); // should reduce to -1/2
    Fraction b(2, -4); // should reduce to -1/2
    Fraction c(-2, -4); // should reduce to 1/2

    assert(a == b);
    assert(c == Fraction(1, 2));
}

int main() {
    test_constructors();
    test_assignment_operator();
    test_addition();
    test_subtraction();
    test_multiplication();
    test_division();
    test_negative_handling();

    std::cout << "All tests passed!\n";
    return 0;
}
