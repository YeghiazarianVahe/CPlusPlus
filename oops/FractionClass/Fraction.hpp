#pragma once

class Fraction {
    public:
        Fraction();                            // Default constructor
        Fraction(int, int);                    // Param constructor
        Fraction(const Fraction&);             // Copy constructor
        Fraction& operator=(const Fraction&);  // Copy assignment
        ~Fraction();                           // Destructor

        Fraction operator+(const Fraction&) const;
        Fraction operator-(const Fraction&) const;
        Fraction operator*(const Fraction&) const;
        Fraction operator/(const Fraction&) const;
        bool operator==(const Fraction&) const;

        void print() const;


    private:
        int numerator;
        int denominator;
        void reduce(); // helper function
        static int gcd(int, int); // the greatest common divisor
};