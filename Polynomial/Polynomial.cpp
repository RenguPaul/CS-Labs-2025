#include "Polynomial.h"
#include <cstdlib>
#include <cstring>
#include <cmath>

Polynomial::Polynomial() : degree(0), order_asc(false) {}

Polynomial::Polynomial(int constant) : degree(0), order_asc(false) {
    if (constant != 0) {
        terms.add_element(Term(constant, 0));
    }
}

Polynomial::Polynomial(const Term& term) : degree(term.exponent), order_asc(false) {
    if (term.coefficient != 0) {
        terms.add_element(term);
    }
}

Polynomial::Polynomial(const Polynomial& other)
    : terms(other.terms), degree(other.degree), order_asc(other.order_asc) {}

Polynomial& Polynomial::operator=(const Polynomial& other) {
    if (this != &other) {
        terms = other.terms;
        degree = other.degree;
        order_asc = other.order_asc;
    }
    return *this;
}

void Polynomial::combineLikeTerms() {
    if (terms.get_size() <= 1) return;

    sortTerms();

    MyVector<Term> combined;
    Term current = terms[0];

    for (size_t i = 1; i < terms.get_size(); ++i) {
        if (terms[i].exponent == current.exponent) {
            current.coefficient += terms[i].coefficient;
        } else {
            if (current.coefficient != 0) {
                combined.add_element(current);
            }
            current = terms[i];
        }
    }

    if (current.coefficient != 0) {
        combined.add_element(current);
    }

    terms = combined;
    updateDegree();
}

void Polynomial::sortTerms() {
    if (terms.get_size() <= 1) return;

    for (size_t i = 0; i < terms.get_size() - 1; ++i) {
        for (size_t j = i + 1; j < terms.get_size(); ++j) {
            bool shouldSwap = order_asc ?
                (terms[i].exponent > terms[j].exponent) :
                (terms[i].exponent < terms[j].exponent);

            if (shouldSwap) {
                Term temp = terms[i];
                terms[i] = terms[j];
                terms[j] = temp;
            }
        }
    }
}

void Polynomial::updateDegree() {
    degree = 0;
    for (size_t i = 0; i < terms.get_size(); ++i) {
        if (terms[i].coefficient != 0 &&
            (terms.get_size() == 1 || abs(terms[i].exponent) > abs(degree))) {
            degree = terms[i].exponent;
        }
    }
}

Polynomial& Polynomial::operator+=(const Term& term) {
    if (term.coefficient == 0) return *this;

    for (size_t i = 0; i < terms.get_size(); ++i) {
        if (terms[i].exponent == term.exponent) {
            terms[i].coefficient += term.coefficient;
            if (terms[i].coefficient == 0) {
                terms.delete_element(terms[i]);
            }
            updateDegree();
            return *this;
        }
    }

    terms.add_element(term);
    sortTerms();
    updateDegree();
    return *this;
}

Polynomial& Polynomial::operator-=(const Term& term) {
    if (term.coefficient == 0) return *this;

    for (size_t i = 0; i < terms.get_size(); ++i) {
        if (terms[i].exponent == term.exponent) {
            terms[i].coefficient -= term.coefficient;
            if (terms[i].coefficient == 0) {
                terms.delete_element(terms[i]);
            }
            updateDegree();
            return *this;
        }
    }

    terms.add_element(term);
    sortTerms();
    updateDegree();
    return *this;
}

Polynomial& Polynomial::operator-=(const Polynomial& other) {
    for (size_t i = 0; i < other.terms.get_size(); ++i) {
        *this -= other.terms[i];
    }
    return *this;
}

Polynomial& Polynomial::operator+=(const Polynomial& other) {
    for (size_t i = 0; i < other.terms.get_size(); ++i) {
        *this += other.terms[i];
    }
    return *this;
}

Polynomial& Polynomial::operator*=(const Term& term) {
    if (term.coefficient == 0) {
        terms = MyVector<Term>();
        degree = 0;
        return *this;
    }

    for (size_t i = 0; i < terms.get_size(); ++i) {
        terms[i].coefficient *= term.coefficient;
        terms[i].exponent += term.exponent;
    }
    combineLikeTerms();
    return *this;
}

Polynomial& Polynomial::operator*=(const Polynomial& other) {
    Polynomial result;
    for (size_t i = 0; i < terms.get_size(); ++i) {
        Polynomial temp;
        for (size_t j = 0; j < other.terms.get_size(); ++j) {
            Term product;
            product.coefficient = terms[i].coefficient * other.terms[j].coefficient;
            product.exponent = terms[i].exponent + other.terms[j].exponent;
            temp.terms.add_element(product);
        }
        result += temp;
    }
    *this = result;
    return *this;
}

int Polynomial::getDegree() const {
    return degree;
}

bool Polynomial::isOrderAsc() const {
    return order_asc;
}

void Polynomial::setOrderAsc(bool asc) {
    order_asc = asc;
    if (terms.get_size() > 0) {
        combineLikeTerms();
    }
}

Polynomial operator+(const Polynomial& p1, const Polynomial& p2) {
    Polynomial result(p1);
    result += p2;
    return result;
}

Polynomial operator-(const Polynomial& p1, const Polynomial& p2) {
    Polynomial result(p1);
    result -= p2;
    return result;
}

Polynomial operator*(const Polynomial& p1, const Polynomial& p2) {
    Polynomial result;
    for (size_t i = 0; i < p1.terms.get_size(); ++i) {
        for (size_t j = 0; j < p2.terms.get_size(); ++j) {
            Term product;
            product.setCoefficient(p1.terms[i].getCoefficient() * p2.terms[j].getCoefficient());
            product.setExponent(p1.terms[i].getExponent() + p2.terms[j].getExponent());
            result += product;
        }
    }
    return result;
}

std::istream& operator>>(std::istream& is, Polynomial& poly) {
    poly.terms = MyVector<Term>();
    poly.degree = 0;

    while (is.peek() == ' ' || is.peek() == '\t') is.get();

    while (is.peek() != '\n' && is.peek() != EOF) {
        Term term;
        is >> term;

        if (term.getCoefficient() != 0) {
            poly.terms.add_element(term);
        }

        while (is.peek() == ' ' || is.peek() == '\t') is.get();
    }

    if (is.peek() == '\n') is.get();

    poly.combineLikeTerms();
    return is;
}

std::ostream& operator<<(std::ostream& os, const Polynomial& poly) {
    if (poly.terms.get_size() == 0) {
        os << '0';
        return os;
    }

    for (size_t i = 0; i < poly.terms.get_size(); ++i) {
        const Term& term = poly.terms[i];

        if (i != 0) {
            os << (term.getCoefficient() > 0 ? " + " : " - ");
        } else if (term.getCoefficient() < 0) {
            os << '-';
        }

        int abs_coeff = abs(term.getCoefficient());
        if (abs_coeff != 1 || term.getExponent() == 0) {
            os << abs_coeff;
        }

        if (term.getExponent() != 0) {
            os << 'x';
            if (term.getExponent() != 1) {
                os << '^';
                if (term.getExponent() < 0) {
                    os << '(' << term.getExponent() << ')';
                } else {
                    os << term.getExponent();
                }
            }
        }
    }

    return os;
}
