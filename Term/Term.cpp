#include "Term.h"
#include <cctype>
#include <cstring>
#include <cstdlib>

Term::Term(int coeff, int exp) : coefficient(coeff), exponent(exp) {}

int Term::getCoefficient() const { return coefficient; }
int Term::getExponent() const { return exponent; }

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

std::istream& operator>>(std::istream& is, Term& term) {
    const int MAX_TERM_LENGTH = 50;
    char buffer[MAX_TERM_LENGTH] = {0};
    char* ptr = buffer;
    int coeff = 1;
    int exp = 0;

    int ch;
    while ((ch = is.peek()) != EOF && !isspace(ch) && (ptr - buffer) < MAX_TERM_LENGTH - 1) {
        *ptr++ = is.get();
    }
    *ptr = '\0';

    // Парсим коэффициент
    ptr = buffer;
    bool negative = false;

    if (*ptr == '-') {
        negative = true;
        ptr++;
    } else if (*ptr == '+') {
        ptr++;
    }

    if (isdigit(*ptr)) {
        coeff = atoi(ptr);
        while (isdigit(*ptr)) ptr++;
    }

    if (negative) coeff = -coeff;

    if (*ptr == 'x') {
        ptr++;
        exp = 1;

        if (*ptr == '^') {
            ptr++;
            exp = atoi(ptr);
        }
    } else {
        exp = 0;
    }

    term.coefficient = coeff;
    term.exponent = exp;

    return is;
}

std::ostream& operator<<(std::ostream& os, const Term& term) {
    if (term.coefficient == 0) {
        os << '0';
        return os;
    }

    if (term.coefficient < 0) {
        os << '-';
        if (term.coefficient != -1 || term.exponent == 0) {
            os << -term.coefficient;
        }
    } else if (term.coefficient != 1 || term.exponent == 0) {
        os << term.coefficient;
    }

    if (term.exponent > 0) {
        os << 'x';
        if (term.exponent > 1) {
            os << '^' << term.exponent;
        }
    }

    return os;
}
