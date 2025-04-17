#include <iostream>
#include "Fraction.hpp"

Fraction::Fraction() : numerator(0), denominator(1) {}

Fraction::Fraction(int x, int y) : numerator(x), denominator(y) {
    if(denominator == 0){
        std::cerr << "Error: Denominator cannot be zero.\n";
        denominator = 1;
    }
    reduce();
}

Fraction::Fraction(const Fraction& other) 
    :   numerator(other.numerator), denominator(other.denominator) {}

Fraction& Fraction::operator=(const Fraction& other) {
    if(this != &other) {
        numerator = other.numerator;
        denominator = other.denominator;
    }

    return *this;
}

Fraction::~Fraction() {}

Fraction Fraction::operator+(const Fraction& other) const {
    return Fraction(numerator * other.denominator + 
        other.numerator * denominator, denominator * other.denominator);
}

Fraction Fraction::operator-(const Fraction& other) const {
    return Fraction(numerator * other.denominator -
        other.numerator * denominator, denominator * other.denominator);
}

Fraction Fraction::operator*(const Fraction& other) const {
    return Fraction(numerator * other.numerator, denominator * other.denominator);
}

Fraction Fraction::operator/(const Fraction& other) const {
    return Fraction(numerator * other.denominator, denominator * other.numerator);
}

bool Fraction::operator==(const Fraction& other) const {
    return numerator == other.numerator && denominator == other.denominator;
}

void Fraction::print() const {
    std::cout << numerator << " / " << denominator << '\n';
}

void Fraction::reduce(){
    int d = gcd(numerator, denominator);
    numerator /= d;
    denominator /= d;
    if (denominator < 0) {
        numerator *= -1;
        denominator *= -1;
    }
}

int Fraction::gcd(int a, int b) {
    while (b != 0) {
        int t = b;
        b = a % b;
        a = t;
    }
    return a < 0 ? -a : a;
}