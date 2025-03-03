#include <iostream>
#include <cstring>
#include <stdexcept>

class Fraction {
public:
    int numerator;
    int denominator;

    // Функция для нахождения наибольшего общего делителя (НОД)
    int gcd(int a, int b) {
        while (b != 0) {
            int temp = b;
            b = a % b;
            a = temp;
        }
        return a;
    }

    // Функция для сокращения дроби
    void reduce() {
        int commonDivisor = gcd(numerator, denominator);
        numerator /= commonDivisor;
        denominator /= commonDivisor;
        if (denominator < 0) { // Убедимся, что знаменатель всегда положительный
            numerator = -numerator;
            denominator = -denominator;
        }
    }

    Fraction(int num = 0, int denom = 1) : numerator(num), denominator(denom) {
        if (denominator == 0) {
            throw std::invalid_argument("Знаменатель не может быть равен нулю.");
        }
        reduce();
    }

    Fraction(const char* fractionStr) {
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
                if (denominator == 0) {
                    throw std::invalid_argument("Знаменатель не может быть равен нулю.");
                }
                numerator += wholePart * denominator; // Преобразуем в неправильную дробь
            } else {
                // Если дробной части нет, то это целое число
                numerator = wholePart;
                denominator = 1;
            }
        } else {
            // Если нет пробела, это простая дробь (например, "3/4", "-3/4", "3/-4")
            char* slashPos = strchr(buffer, '/');
            if (slashPos != nullptr) {
                numerator = atoi(buffer);
                denominator = atoi(slashPos + 1);
                if (denominator == 0) {
                    throw std::invalid_argument("Знаменатель не может быть равен нулю.");
                }
            } else {
                // Если нет слэша, это целое число
                numerator = atoi(buffer);
                denominator = 1;
            }
        }
        reduce(); // Сокращаем дробь
    }

    friend std::istream& operator>>(std::istream& in, Fraction& frac);
};

// Перегрузка оператора ввода
std::istream& operator>>(std::istream& in, Fraction& frac) {
    char input[50];
    in.getline(input, 50); // Считываем всю строку
    frac = Fraction(input); // Создаем Fraction из C-строки
    return in;
}

// Перегрузка оператора вывода для удобства
std::ostream& operator<<(std::ostream& out, const Fraction& frac) {
    out << frac.numerator << "/" << frac.denominator;
    return out;
}

int main() {
    try {
        Fraction f1, f2;

        std::cout << "Введите первую дробь (например, 2 3/4): ";
        std::cin >> f1;

        std::cin.ignore(); // Игнорируем оставшийся символ новой строки

        std::cout << "Введите вторую дробь (например, 7 2/3): ";
        std::cin >> f2;

        std::cout << "Первая дробь: " << f1 << std::endl;
        std::cout << "Вторая дробь: " << f2 << std::endl;
    } catch (const std::invalid_argument& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    }

    return 0;
}
