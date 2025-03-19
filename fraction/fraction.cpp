#include "fraction.hpp"
#include <cstring>
#include <stdexcept>
#include <cctype>
#include <cmath>

int Fraction::gcd(int a, int b) const {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

void Fraction::reduce() {
    int commonDivisor = gcd(numerator, denominator);
    numerator /= commonDivisor;
    denominator /= commonDivisor;
    if (denominator < 0) {
        numerator = -numerator;
        denominator = -denominator;
    }
}

Fraction::Fraction() : numerator(0), denominator(1) {}

Fraction::Fraction(int num, int denom) : numerator(num), denominator(denom) {
    if (denominator == 0) {
        throw std::invalid_argument("Знаменатель не может быть равен нулю.");
    }
    reduce();
}

Fraction::Fraction(double value) {
    const double epsilon = 1.0e-6;
    double integral = std::floor(value);
    double fractional = value - integral;

    denominator = 1;
    while (std::fabs(fractional - std::round(fractional)) > epsilon) {
        fractional *= 10;
        denominator *= 10;
    }
    numerator = static_cast<int>(std::round(integral * denominator + fractional));
    reduce();
}

Fraction::Fraction(const char* fractionStr) {
    char buffer[50];
    strcpy(buffer, fractionStr);

    char* start = buffer;
    while (*start == ' ') start++;
    char* end = start + strlen(start) - 1;
    while (end > start && *end == ' ') end--;
    *(end + 1) = '\0';

    for (char* p = start; *p; ++p) {
        if (!isdigit(*p) && *p != '-' && *p != '/' && *p != ' ' && *p != '.') {
            throw std::invalid_argument("Строка содержит недопустимые символы.");
        }
    }

    bool isNegative = false;
    if (*start == '-') {
        isNegative = true;
        start++;
    }

    char* spacePos = strchr(start, ' ');
    if (spacePos != nullptr) {
        int wholePart = atoi(start);
        char* fractionPart = spacePos + 1;
        while (*fractionPart == ' ') fractionPart++;

        char* slashPos = strchr(fractionPart, '/');
        if (slashPos != nullptr) {
            numerator = atoi(fractionPart);
            denominator = atoi(slashPos + 1);
            if (denominator == 0) {
                throw std::invalid_argument("Знаменатель не может быть равен нулю.");
            }
            numerator += wholePart * denominator;
        } else {
            numerator = wholePart;
            denominator = 1;
        }
    } else {
        char* slashPos = strchr(start, '/');
        if (slashPos != nullptr) {
            numerator = atoi(start);
            denominator = atoi(slashPos + 1);
            if (denominator == 0) {
                throw std::invalid_argument("Знаменатель не может быть равен нулю.");
            }
        } else {
            char* dotPos = strchr(start, '.');
            if (dotPos != nullptr) {
                int decimalPlaces = strlen(dotPos + 1);
                numerator = atoi(start) * pow(10, decimalPlaces) + atoi(dotPos + 1);
                denominator = pow(10, decimalPlaces);
            } else {
                numerator = atoi(start);
                denominator = 1;
            }
        }
    }

    if (isNegative) {
        numerator = -numerator;
    }

    reduce();
}

Fraction::Fraction(const Fraction& other)
    : numerator(other.numerator), denominator(other.denominator) {}

int Fraction::getNumerator() const { return numerator; }
int Fraction::getDenominator() const { return denominator; }

Fraction operator+(const Fraction& lhs, const Fraction& rhs) {
    int newNumerator = lhs.numerator * rhs.denominator + rhs.numerator * lhs.denominator;
    int newDenominator = lhs.denominator * rhs.denominator;
    return Fraction(newNumerator, newDenominator);
}

Fraction Fraction::operator-(const Fraction& other) const {
    int newNumerator = numerator * other.denominator - other.numerator * denominator;
    int newDenominator = denominator * other.denominator;
    return Fraction(newNumerator, newDenominator);
}

Fraction Fraction::operator*(const Fraction& other) const {
    int newNumerator = numerator * other.numerator;
    int newDenominator = denominator * other.denominator;
    return Fraction(newNumerator, newDenominator);
}

Fraction Fraction::operator/(const Fraction& other) const {
    if (other.numerator == 0) {
        throw std::invalid_argument("Деление на ноль невозможно.");
    }
    int newNumerator = numerator * other.denominator;
    int newDenominator = denominator * other.numerator;
    return Fraction(newNumerator, newDenominator);
}

Fraction Fraction::operator+(int value) const {
    return *this + Fraction(value);
}

Fraction Fraction::operator-(int value) const {
    return *this - Fraction(value);
}

Fraction Fraction::operator*(int value) const {
    return *this * Fraction(value);
}

Fraction Fraction::operator/(int value) const {
    if (value == 0) {
        throw std::invalid_argument("Деление на ноль невозможно.");
    }
    return *this / Fraction(value);
}

Fraction Fraction::operator+(double value) const {
    return *this + Fraction(value);
}

Fraction Fraction::operator-(double value) const {
    return *this - Fraction(value);
}

Fraction Fraction::operator*(double value) const {
    return *this * Fraction(value);
}

Fraction Fraction::operator/(double value) const {
    if (value == 0) {
        throw std::invalid_argument("Деление на ноль невозможно.");
    }
    return *this / Fraction(value);
}

Fraction& Fraction::operator+=(const Fraction& other) {
    *this = *this + other;
    return *this;
}

Fraction& Fraction::operator-=(const Fraction& other) {
    *this = *this - other;
    return *this;
}

Fraction& Fraction::operator*=(const Fraction& other) {
    *this = *this * other;
    return *this;
}

Fraction& Fraction::operator/=(const Fraction& other) {
    *this = *this / other;
    return *this;
}

Fraction& Fraction::operator+=(int value) {
    *this = *this + Fraction(value);
    return *this;
}

Fraction& Fraction::operator-=(int value) {
    *this = *this - Fraction(value);
    return *this;
}

Fraction& Fraction::operator*=(int value) {
    *this = *this * Fraction(value);
    return *this;
}

Fraction& Fraction::operator/=(int value) {
    *this = *this / Fraction(value);
    return *this;
}

Fraction& Fraction::operator+=(double value) {
    *this = *this + Fraction(value);
    return *this;
}

Fraction& Fraction::operator-=(double value) {
    *this = *this - Fraction(value);
    return *this;
}

Fraction& Fraction::operator*=(double value) {
    *this = *this * Fraction(value);
    return *this;
}

Fraction& Fraction::operator/=(double value) {
    *this = *this / Fraction(value);
    return *this;
}

bool Fraction::operator==(const Fraction& other) const {
    return numerator == other.numerator && denominator == other.denominator;
}

bool Fraction::operator!=(const Fraction& other) const {
    return !(*this == other);
}

bool Fraction::operator<(const Fraction& other) const {
    return numerator * other.denominator < other.numerator * denominator;
}

bool Fraction::operator>(const Fraction& other) const {
    return numerator * other.denominator > other.numerator * denominator;
}

bool Fraction::operator<=(const Fraction& other) const {
    return *this < other || *this == other;
}

bool Fraction::operator>=(const Fraction& other) const {
    return *this > other || *this == other;
}

Fraction::operator double() const {
    return static_cast<double>(numerator) / denominator;
}

std::istream& operator>>(std::istream& in, Fraction& frac) {
    char input[50];
    in.getline(input, 50);
    frac = Fraction(input);
    return in;
}

std::ostream& operator<<(std::ostream& out, const Fraction& frac) {
    if (frac.denominator == 1) {
        out << frac.numerator;
    } else if (frac.numerator > frac.denominator) {
        int wholePart = frac.numerator / frac.denominator;
        int remainder = frac.numerator % frac.denominator;
        out << wholePart << " " << remainder << "/" << frac.denominator;
    } else {
        out << frac.numerator << "/" << frac.denominator;
    }
    return out;
}

Fraction operator+(int value, const Fraction& frac) {
    return Fraction(value) + frac;
}


Fraction operator+(double value, const Fraction& frac) {
    return Fraction(value) + frac;
}
