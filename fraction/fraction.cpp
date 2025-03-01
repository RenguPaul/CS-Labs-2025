#include <iostream>
#include <algorithm>
#include <stdexcept>
#include <cctype> // для isdigit

class Fraction {
private:
    int numerator;
    int denominator;

    // Функция для нахождения наибольшего общего делителя (НОД)
    int gcd(int a, int b) const {
        while (b != 0) {
            int temp = b;
            b = a % b;
            a = temp;
        }
        return a;
    }

    // Функция для сокращения дроби
    void reduce() {
        int commonDivisor = gcd(std::abs(numerator), std::abs(denominator));
        numerator /= commonDivisor;
        denominator /= commonDivisor;
        // Убедимся, что знаменатель всегда положительный
        if (denominator < 0) {
            numerator *= -1;
            denominator *= -1;
        }
    }

    // Вспомогательная функция для парсинга числа из строки
    int parseNumber(const char*& str) const {
        int result = 0;
        int sign = 1;

        // Обработка знака
        if (*str == '-') {
            sign = -1;
            str++;
        }

        // Чтение цифр
        while (isdigit(*str)) {
            result = result * 10 + (*str - '0');
            str++;
        }

        return result * sign;
    }

public:
    // Конструктор по умолчанию
    Fraction() : numerator(0), denominator(1) {}

    // Конструктор с числителем и знаменателем
    Fraction(int num, int denom) : numerator(num), denominator(denom) {
        if (denominator == 0) {
            throw std::invalid_argument("Denominator cannot be zero.");
        }
        reduce();
    }

    // Конструктор из строки
    Fraction(const char* fractionStr) {
        int whole = 0, num = 0, denom = 1;
        const char* ptr = fractionStr;

        // Парсим целую часть
        whole = parseNumber(ptr);

        // Пропускаем пробелы
        while (*ptr == ' ') ptr++;

        // Если есть дробная часть
        if (*ptr == '/') {
            num = whole;
            whole = 0;
            ptr++;
            denom = parseNumber(ptr);
        } else if (isdigit(*ptr) || *ptr == '-') {
            // Если есть целая часть и дробная часть (например, "2 3/4")
            num = parseNumber(ptr);
            if (*ptr == '/') {
                ptr++;
                denom = parseNumber(ptr);
            } else {
                denom = 1;
            }
        }

        // Вычисляем числитель и знаменатель
        numerator = whole * denom + (whole >= 0 ? num : -num);
        denominator = denom;

        if (denominator == 0) {
            throw std::invalid_argument("Denominator cannot be zero.");
        }
        reduce();
    }

    // Перегрузка оператора вывода
    friend std::ostream& operator<<(std::ostream& out, const Fraction& fraction) {
        int whole = fraction.numerator / fraction.denominator;
        int num = fraction.numerator % fraction.denominator;
        int denom = fraction.denominator;

        if (whole != 0) {
            out << whole;
            if (num != 0) {
                out << " " << std::abs(num) << "/" << denom;
            }
        } else {
            if (num != 0) {
                out << num << "/" << denom;
            } else {
                out << 0;
            }
        }
        return out;
    }

    // Перегрузка оператора сложения
    Fraction operator+(const Fraction& other) const {
        int num = numerator * other.denominator + other.numerator * denominator;
        int denom = denominator * other.denominator;
        return Fraction(num, denom);
    }

    // Перегрузка оператора вычитания
    Fraction operator-(const Fraction& other) const {
        int num = numerator * other.denominator - other.numerator * denominator;
        int denom = denominator * other.denominator;
        return Fraction(num, denom);
    }

    // Перегрузка оператора умножения
    Fraction operator*(const Fraction& other) const {
        int num = numerator * other.numerator;
        int denom = denominator * other.denominator;
        return Fraction(num, denom);
    }

    // Перегрузка оператора деления
    Fraction operator/(const Fraction& other) const {
        if (other.numerator == 0) {
            throw std::invalid_argument("Cannot divide by zero.");
        }
        int num = numerator * other.denominator;
        int denom = denominator * other.numerator;
        return Fraction(num, denom);
    }
};

int main() {
    try {
        // Примеры с дробями в формате строки
        Fraction a("2 3/4");  // 2 3/4
        Fraction b("-3/5");   // -3/5
        Fraction c("3/-5");   // -3/5
        Fraction d("7/3");    // 7/3 (неправильная дробь)
        Fraction e("-2 1/2"); // -2 1/2

        std::cout << "a = " << a << std::endl;
        std::cout << "b = " << b << std::endl;
        std::cout << "c = " << c << std::endl;
        std::cout << "d = " << d << std::endl;
        std::cout << "e = " << e << std::endl;

        Fraction sum = a + b;
        std::cout << "a + b = " << sum << std::endl;

        Fraction difference = a - e;
        std::cout << "a - e = " << difference << std::endl;

        Fraction product = b * c;
        std::cout << "b * c = " << product << std::endl;

        Fraction quotient = d / e;
        std::cout << "d / e = " << quotient << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
