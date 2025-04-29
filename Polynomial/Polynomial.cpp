#include <cctype>
#include <cstring>
#include <cstdlib>
#include "Polynomial.h"

namespace {
    bool compareTerms(const Term& a, const Term& b, bool ascending) {
        return ascending ?
            (a.getExponent() < b.getExponent()) :
            (a.getExponent() > b.getExponent());
    }
}

Polynomial::Polynomial() : degree(0), order(false) {}

Polynomial::Polynomial(int constant) : degree(0), order(false) {
    if (constant != 0) {
        terms.add_element(Term(constant, 0));
    }
}

Polynomial::Polynomial(const Term& term) : degree(term.getExponent()), order(false) {
    if (term.getCoefficient() != 0) {
        terms.add_element(term);
    }
}

Polynomial::Polynomial(const Polynomial& other)
    : terms(other.terms), degree(other.degree), order(other.order) {}

Polynomial& Polynomial::operator=(const Polynomial& other) {
    if (this != &other) {
        terms = other.terms;
        degree = other.degree;
        order = other.order;
    }
    return *this;
}

void Polynomial::combineLikeTerms() {
    if (terms.get_size() == 0) {
        degree = 0;
        return;
    }

    sortTerms();
    MyVector<Term> newTerms;

    for (size_t i = 0; i < terms.get_size(); ) {
        Term current = terms[i];
        size_t j = i + 1;

        while (j < terms.get_size() && terms[j].getExponent() == current.getExponent()) {
            current = current + terms[j];
            j++;
        }

        if (current.getCoefficient() != 0) {
            newTerms.add_element(current);
        }

        i = j;
    }

    terms = newTerms;
    degree = terms.get_size() > 0 ? terms[0].getExponent() : 0;
}

void Polynomial::sortTerms() {
    for (size_t i = 0; i < terms.get_size(); ++i) {
        for (size_t j = i + 1; j < terms.get_size(); ++j) {
            if (compareTerms(terms[j], terms[i], order)) {
                Term temp = terms[i];
                terms[i] = terms[j];
                terms[j] = temp;
            }
        }
    }
}

Polynomial& Polynomial::operator+=(const Polynomial& other) {
    for (size_t i = 0; i < other.terms.get_size(); i++) {
        terms.add_element(other.terms[i]);
    }
    combineLikeTerms();
    return *this;
}

Polynomial& Polynomial::operator*=(const Polynomial& other) {
    Polynomial result;

    for (size_t i = 0; i < terms.get_size(); i++) {
        for (size_t j = 0; j < other.terms.get_size(); j++) {
            Term t1 = terms[i];
            Term t2 = other.terms[j];

            int coeff = t1.getCoefficient() * t2.getCoefficient();
            int exp = t1.getExponent() + t2.getExponent();

            if (coeff != 0) {
                result.terms.add_element(Term(coeff, exp));
            }
        }
    }

    result.combineLikeTerms();
    *this = result;
    return *this;
}

Polynomial& Polynomial::operator+=(const Term& term) {
    if (term.getCoefficient() != 0) {
        terms.add_element(term);
        combineLikeTerms();
    }
    return *this;
}

Polynomial& Polynomial::operator*=(const Term& term) {
    if (term.getCoefficient() == 0) {
        terms.delete_element(terms[0]);
        degree = 0;
        return *this;
    }

    for (size_t i = 0; i < terms.get_size(); i++) {
        Term& t = terms[i];
        t = Term(t.getCoefficient() * term.getCoefficient(),
                 t.getExponent() + term.getExponent());
    }

    combineLikeTerms();
    return *this;
}

Polynomial operator+(const Polynomial& lhs, const Polynomial& rhs) {
    Polynomial result(lhs);
    result += rhs;
    return result;
}

Polynomial operator*(const Polynomial& lhs, const Polynomial& rhs) {
    Polynomial result(lhs);
    result *= rhs;
    return result;
}

Polynomial operator+(const Polynomial& p, const Term& t) {
    Polynomial result(p);
    result += t;
    return result;
}

Polynomial operator*(const Polynomial& p, const Term& t) {
    Polynomial result(p);
    result *= t;
    return result;
}

std::istream& operator>>(std::istream& is, Polynomial& poly) {
    const int BUFFER_SIZE = 256;
    char buffer[BUFFER_SIZE];
    is.getline(buffer, BUFFER_SIZE);

    poly = Polynomial();

    char* token = strtok(buffer, " \t\n+-");
    while (token != nullptr) {

        bool negative = false;
        if (token[0] == '-') {
            negative = true;
            token++;
        } else if (token[0] == '+') {
            token++;
        }


        Term term;
        char* ptr = token;


        int coeff = 1;
        if (isdigit(*ptr)) {
            coeff = atoi(ptr);
            while (isdigit(*ptr)) ptr++;
        }
        if (negative) coeff = -coeff;


        int exp = 0;
        if (*ptr == 'x') {
            ptr++;
            exp = 1;
            if (*ptr == '^') {
                ptr++;
                exp = atoi(ptr);
            }
        }

        if (coeff != 0) {
            poly.terms.add_element(Term(coeff, exp));
        }

        token = strtok(nullptr, " \t\n+-");
    }

    poly.combineLikeTerms();
    return is;
}

std::ostream& operator<<(std::ostream& os, const Polynomial& poly) {
    if (poly.terms.get_size() == 0) {
        os << '0';
        return os;
    }

    for (size_t i = 0; i < poly.terms.get_size(); i++) {
        const Term& term = poly.terms[i];

        if (i > 0) {
            if (term.getCoefficient() > 0) {
                os << " + ";
            } else {
                os << " - ";
            }
        }

        if (term.getCoefficient() < 0) {
            Term temp(-term.getCoefficient(), term.getExponent());
            os << temp;
        } else {
            os << term;
        }
    }

    return os;
}
