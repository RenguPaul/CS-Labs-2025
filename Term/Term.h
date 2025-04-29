#ifndef TERM_H
#define TERM_H

#include <iostream>

class Term {
private:
    int coefficient;
    int exponent;

public:
    Term(int coeff = 0, int exp = 0) : coefficient(coeff), exponent(exp){}

    ~Term() = default;

    int getCoefficient() const {
        return coefficient;
    }
    int getExponent() const {
        return exponent;
    }

    Term operator+(const Term& other) const;
    Term operator-(const Term& other) const;

    friend std::istream& operator>>(std::istream& is, Term& term);
    friend std::ostream& operator<<(std::ostream& os, const Term& term);

    friend class Polynomial;
};

#endif // TERM_H
