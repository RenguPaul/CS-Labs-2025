#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include "/home/pavel/BAUMAN_PROJECTS/CS-2025-PR/CS-Labs-2025/Term/Term.h"
#include "MyVector.h"

class Polynomial {
private:
    MyVector<Term> terms;
    int degree;
    bool order;

    void combineLikeTerms();
    void sortTerms();

public:
    Polynomial();
    explicit Polynomial(int constant);
    explicit Polynomial(const Term& term);
    Polynomial(const Polynomial& other);

    Polynomial& operator=(const Polynomial& other);
    Polynomial& operator+=(const Polynomial& other);
    Polynomial& operator*=(const Polynomial& other);
    Polynomial& operator+=(const Term& term);
    Polynomial& operator*=(const Term& term);

    friend Polynomial operator+(const Polynomial& lhs, const Polynomial& rhs);
    friend Polynomial operator*(const Polynomial& lhs, const Polynomial& rhs);
    friend Polynomial operator+(const Polynomial& p, const Term& t);
    friend Polynomial operator*(const Polynomial& p, const Term& t);

    friend std::istream& operator>>(std::istream& is, Polynomial& poly);
    friend std::ostream& operator<<(std::ostream& os, const Polynomial& poly);
};

#endif // POLYNOMIAL_H
