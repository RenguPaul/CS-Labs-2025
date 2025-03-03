#ifndef FRACTION_H
#define FRACTION_H

#include <iostream>

class Fraction {
private:
    int numerator;   // числитель
    int denominator; // знаменатель

    void reduce();   // метод для сокращения дроби
    int gcd(int a, int b); // метод для вычисления НОД

public:
    // Конструкторы
    Fraction(); // по умолчанию
    Fraction(int num, int den); // с параметрами
    Fraction(const char* fractionStr); // из строки (массива char)

    // Перегрузка операторов ввода/вывода
    friend std::ostream& operator<<(std::ostream& out, const Fraction& frac);
    friend std::istream& operator>>(std::istream& in, Fraction& frac);

    // Геттеры
    int getNumerator() const;
    int getDenominator() const;
};

#endif // FRACTION_H
