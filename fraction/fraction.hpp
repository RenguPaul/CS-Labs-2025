#ifndef FRACTION_HPP
#define FRACTION_HPP

#include <iostream>
#include <stdexcept>

class Fraction {
private:
    int numerator;
    int denominator;

    int gcd(int a, int b); // Нахождение НОД
    void reduce();         // Сокращение дроби

public:
    Fraction(int num = 0, int denom = 1); // Конструктор
    Fraction(const char* fractionStr);    // Конструктор из строки

    // Геттеры
    int getNumerator() const;
    int getDenominator() const;

    // Арифметические операции
    Fraction operator+(const Fraction& other) const;
    Fraction operator-(const Fraction& other) const;
    Fraction operator*(const Fraction& other) const;
    Fraction operator/(const Fraction& other) const;

    // Операторы сравнения
    bool operator==(const Fraction& other) const;
    bool operator!=(const Fraction& other) const;
    bool operator<(const Fraction& other) const;
    bool operator>(const Fraction& other) const;
    bool operator<=(const Fraction& other) const;
    bool operator>=(const Fraction& other) const;

    // Дружественные функции для ввода/вывода
    friend std::istream& operator>>(std::istream& in, Fraction& frac);
    friend std::ostream& operator<<(std::ostream& out, const Fraction& frac);
};

#endif // FRACTION_HPP
