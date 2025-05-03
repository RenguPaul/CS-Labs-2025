#ifndef TERM_H
#define TERM_H

#include <iostream>
#include <stdexcept>

class Term {
private:
    int coefficient;
    int exponent;

public:
    Term();
    Term(int coeff);
    Term(int coeff, int exp);

    int getCoefficient() const;
    int getExponent() const;
    void setCoefficient(int coeff);
    void setExponent(int exp);

    Term operator+(const Term& other) const;
    Term operator*(const Term& other) const;
    bool operator==(const Term& other) const;
    bool operator!=(const Term& other) const;
    bool operator<(const Term& other) const;

    friend std::ostream& operator<<(std::ostream& os, const Term& term);
    friend std::istream& operator>>(std::istream& is, Term& term);

    friend class Polynomial;
};

#endif // TERM_H
