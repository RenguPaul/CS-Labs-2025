#include "Term.h"
#include <cstdlib>
#include <cstring>
#include <stdexcept>
#include <cmath>

Term::Term() : coefficient(0), exponent(0) {}
Term::Term(int coeff) : coefficient(coeff), exponent(0) {}
Term::Term(int coeff, int exp) : coefficient(coeff), exponent(exp) {}

int Term::getCoefficient() const { return coefficient; }
int Term::getExponent() const { return exponent; }
void Term::setCoefficient(int coeff) { coefficient = coeff; }
void Term::setExponent(int exp) { exponent = exp; }

Term Term::operator+(const Term& other) const {
    if (exponent != other.exponent) {
        throw std::invalid_argument("Cannot add terms with different exponents");
    }
    return Term(coefficient + other.coefficient, exponent);
}

Term Term::operator-(const Term& other) const {
    if (exponent != other.exponent) {
        throw std::invalid_argument("Cannot add terms with different exponents");
    }
    return Term(coefficient - other.coefficient, exponent);
}

Term Term::operator*(const Term& other) const {
    return Term(coefficient * other.coefficient, exponent + other.exponent);
}

bool Term::operator==(const Term& other) const {
    return coefficient == other.coefficient && exponent == other.exponent;
}

bool Term::operator!=(const Term& other) const {
    return !(*this == other);
}

bool Term::operator<(const Term& other) const {
    return exponent > other.exponent;
}

std::ostream& operator<<(std::ostream& os, const Term& term) {
    if (term.coefficient == 0) {
        os << '0';
        return os;
    }

    if (term.coefficient == 1 && term.exponent != 0) {
    } else if (term.coefficient == -1 && term.exponent != 0) {
        os << '-';
    } else {
        os << term.coefficient;
    }

    if (term.exponent != 0) {
        os << 'x';
        if (term.exponent != 1 && term.exponent != -1) {
            os << '^' << term.exponent;
        } else if (term.exponent == -1) {
            os << "^(-1)";
        }
    }

    return os;
}

std::istream& operator>>(std::istream& is, Term& term) {
    term.coefficient = 1;
    term.exponent = 0;

    while (is.peek() == ' ') is.get();

    bool negative = false;
    if (is.peek() == '-') {
        negative = true;
        is.get();
    } else if (is.peek() == '+') {
        is.get();
    }

    while (is.peek() == ' ') is.get();

    if (is.peek() == 'x') {
        term.coefficient = negative ? -1 : 1;
    } else {
        is >> term.coefficient;
        if (negative) term.coefficient *= -1;

        while (is.peek() == ' ') is.get();
    }

    if (is.peek() == 'x') {
        is.get();
        term.exponent = 1;

        while (is.peek() == ' ') is.get();

        if (is.peek() == '^') {
            is.get();

            while (is.peek() == ' ') is.get();

            is >> term.exponent;
        }
    }

    return is;
}

Term& Term::operator+=(Term& other) {
    if (exponent != other.exponent) {
        throw std::invalid_argument("Cannot add terms with different exponents");
    }
    (*this).coefficient += other.getCoefficient();
    return *this;
}

Term& Term::operator-=(Term& other) {
    if (exponent != other.exponent) {
        throw std::invalid_argument("Cannot add terms with different exponents");
    }
    (*this).coefficient -= other.getCoefficient();
    return *this;
}
