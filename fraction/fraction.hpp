#ifndef FRACTION_HPP
#define FRACTION_HPP

#include <iostream>
#include <string>

class Fraction {
private:
    int numerator;
    int denominator;


    int gcd(int a, int b) const;
    void reduce();

public:

    Fraction();
    Fraction(int num, int denom);
    Fraction(double value);
    Fraction(const char* fractionStr);
    Fraction(const Fraction& other);

    int getNumerator() const;
    int getDenominator() const;

    Fraction operator-(const Fraction& other) const;
    Fraction operator*(const Fraction& other) const;
    Fraction operator/(const Fraction& other) const;

    Fraction operator+(int value) const;
    Fraction operator-(int value) const;
    Fraction operator*(int value) const;
    Fraction operator/(int value) const;

    Fraction operator+(double value) const;
    Fraction operator-(double value) const;
    Fraction operator*(double value) const;
    Fraction operator/(double value) const;

    Fraction& operator+=(const Fraction& other);
    Fraction& operator-=(const Fraction& other);
    Fraction& operator*=(const Fraction& other);
    Fraction& operator/=(const Fraction& other);

    Fraction& operator+=(int value);
    Fraction& operator-=(int value);
    Fraction& operator*=(int value);
    Fraction& operator/=(int value);

    Fraction& operator+=(double value);
    Fraction& operator-=(double value);
    Fraction& operator*=(double value);
    Fraction& operator/=(double value);

    bool operator==(const Fraction& other) const;
    bool operator!=(const Fraction& other) const;
    bool operator<(const Fraction& other) const;
    bool operator>(const Fraction& other) const;
    bool operator<=(const Fraction& other) const;
    bool operator>=(const Fraction& other) const;

    operator double() const;

    friend Fraction operator+(const Fraction& lhs, const Fraction& rhs);
    friend std::istream& operator>>(std::istream& in, Fraction& frac);
    friend std::ostream& operator<<(std::ostream& out, const Fraction& frac);
};

Fraction operator+(const Fraction& lhs, const Fraction& rhs);

Fraction operator+(int value, const Fraction& frac);


Fraction operator+(double value, const Fraction& frac);


#endif // FRACTION_HPP
