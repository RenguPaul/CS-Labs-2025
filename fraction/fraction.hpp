#ifndef FRACTION_HPP
#define FRACTION_HPP

#include <iostream>
#include <stdexcept>

class Fraction {
private:
    int numerator;
    int denominator;

    int gcd(int a, int b);
    void reduce();

public:
    Fraction(int num = 0, int denom = 1);
    Fraction(const char* fractionStr);

    int getNumerator() const;
    int getDenominator() const;

    Fraction operator+(const Fraction& other) const;
    Fraction operator-(const Fraction& other) const;
    Fraction operator*(const Fraction& other) const;
    Fraction operator/(const Fraction& other) const;

    bool operator==(const Fraction& other) const;
    bool operator!=(const Fraction& other) const;
    bool operator<(const Fraction& other) const;
    bool operator>(const Fraction& other) const;
    bool operator<=(const Fraction& other) const;
    bool operator>=(const Fraction& other) const;

    friend std::istream& operator>>(std::istream& in, Fraction& frac);
    friend std::ostream& operator<<(std::ostream& out, const Fraction& frac);
};

#endif // FRACTION_HPP
