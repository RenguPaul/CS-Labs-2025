#include "fraction.hpp"
#include <cstring> // для работы с функциями strchr, strtok, atoi
#include <cstdlib> // для abs

// Конструктор по умолчанию
Fraction::Fraction() : numerator(0), denominator(1) {}

// Конструктор с параметрами
Fraction::Fraction(int num, int den) : numerator(num), denominator(den) {
    reduce();
}

// Конструктор из строки (массива char)
Fraction::Fraction(const char* fractionStr) {
    char buffer[50]; // Буфер для копирования строки
    strcpy(buffer, fractionStr);

    // Обработка смешанной дроби (например, "2 3/4")
    char* spacePos = strchr(buffer, ' ');
    if (spacePos != nullptr) {
        // Если есть пробел, это смешанная дробь
        int wholePart = atoi(buffer); // Целая часть
        char* fractionPart = spacePos + 1; // Дробная часть

        // Обработка дробной части
        char* slashPos = strchr(fractionPart, '/');
        if (slashPos != nullptr) {
            numerator = atoi(fractionPart);
            denominator = atoi(slashPos + 1);
            numerator += wholePart * denominator; // Преобразуем в неправильную дробь
        } else {
            // Если дробной части нет, то это целое число
            numerator = wholePart;
            denominator = 1;
        }
    } else {
        // Если нет пробела, это простая дробь (например, "3/4" или "3/-4")
        char* slashPos = strchr(buffer, '/');
        if (slashPos != nullptr) {
            numerator = atoi(buffer);
            denominator = atoi(slashPos + 1);
        } else {
            // Если нет слэша, это целое число
            numerator = atoi(buffer);
            denominator = 1;
        }
    }
    reduce();
}

// Метод для вычисления НОД (алгоритм Евклида)
int Fraction::gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Метод для сокращения дроби
void Fraction::reduce() {
    int commonDivisor = gcd(abs(numerator), abs(denominator));
    numerator /= commonDivisor;
    denominator /= commonDivisor;
    if (denominator < 0) {
        numerator *= -1;
        denominator *= -1;
    }
}

// Перегрузка оператора вывода
std::ostream& operator<<(std::ostream& out, const Fraction& frac) {
    out << frac.numerator << "/" << frac.denominator;
    return out;
}

// Перегрузка оператора ввода
std::istream& operator>>(std::istream& in, Fraction& frac) {
    char input[50];
    in >> input;
    frac = Fraction(input);
    return in;
}

// Геттеры
int Fraction::getNumerator() const {
    return numerator;
}

int Fraction::getDenominator() const {
    return denominator;
}
