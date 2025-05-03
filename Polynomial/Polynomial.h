#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include "/home/pavel/BAUMAN_PROJECTS/CS-2025-PR/CS-Labs-2025/Term/Term.h"
#include "/home/pavel/BAUMAN_PROJECTS/CS-2025-PR/CS-Labs-2025/MyVector/MyVector.h"

class Polynomial {
private:
    MyVector<Term> terms;
    int degree;
    bool order_asc;

    void combineLikeTerms();
    void sortTerms();
    void updateDegree();

public:
    Polynomial();
    Polynomial(int constant);
    Polynomial(const Term& term);
    Polynomial(const Polynomial& other);

    Polynomial& operator=(const Polynomial& other);
    Polynomial& operator+=(const Term& term);
    Polynomial& operator+=(const Polynomial& other);
    Polynomial& operator*=(const Term& term);
    Polynomial& operator*=(const Polynomial& other);

    int getDegree() const;
    bool isOrderAsc() const;
    void setOrderAsc(bool asc);

    friend Polynomial operator+(const Polynomial& p1, const Polynomial& p2);
    friend Polynomial operator*(const Polynomial& p1, const Polynomial& p2);
    friend std::ostream& operator<<(std::ostream& os, const Polynomial& poly);
    friend std::istream& operator>>(std::istream& is, Polynomial& poly);
};

#endif // POLYNOMIAL_H
