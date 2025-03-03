#include "fraction.hpp"
#include <cstring>
#include <stdexcept>

// Нахождение НОД
int Fraction::gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Сокращение дроби
void Fraction::reduce() {
    int commonDivisor = gcd(numerator, denominator);
    numerator /= commonDivisor;
    denominator /= commonDivisor;
    if (denominator < 0) { // Убедимся, что знаменатель всегда положительный
        numerator = -numerator;
        denominator = -denominator;
    }
}

// Конструктор
Fraction::Fraction(int num, int denom) : numerator(num), denominator(denom) {
    if (denominator == 0) {
        throw std::invalid_argument("Знаменатель не может быть равен нулю.");
    }
    reduce();
}

// Конструктор из строки
Fraction::Fraction(const char* fractionStr) {
    char buffer[50]; // Буфер для копирования строки
    strcpy(buffer, fractionStr);

    // Удаляем лишние пробелы
    char* start = buffer;
    while (*start == ' ') start++;
    char* end = start + strlen(start) - 1;
    while (end > start && *end == ' ') end--;
    *(end + 1) = '\0';

    // Обработка смешанной дроби
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
            numerator = atoi(start);
            denominator = 1;
        }
    }
    reduce();
}

// Геттеры
int Fraction::getNumerator() const { return numerator; }
int Fraction::getDenominator() const { return denominator; }

// Арифметические операции
Fraction Fraction::operator+(const Fraction& other) const {
    int newNumerator = numerator * other.denominator + other.numerator * denominator;
    int newDenominator = denominator * other.denominator;
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

// Операторы сравнения
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

// Перегрузка оператора ввода
std::istream& operator>>(std::istream& in, Fraction& frac) {
    char input[50];
    in.getline(input, 50);
    frac = Fraction(input);
    return in;
}

// Перегрузка оператора вывода
std::ostream& operator<<(std::ostream& out, const Fraction& frac) {
    out << frac.numerator << "/" << frac.denominator;
    return out;
}
