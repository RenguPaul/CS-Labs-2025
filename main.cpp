#include "fraction/fraction.hpp"
#include <iostream>

// Демо-режим
void demoMode() {
    std::cout << "\n=== Демо-режим ===\n";

    Fraction f1("2 3/4");
    Fraction f2("1/2");

    std::cout << "f1 = " << f1 << std::endl;
    std::cout << "f2 = " << f2 << std::endl;

    std::cout << "Сумма: " << f1 + f2 << std::endl;
    std::cout << "Разность: " << f1 - f2 << std::endl;
    std::cout << "Произведение: " << f1 * f2 << std::endl;
    std::cout << "Частное: " << f1 / f2 << std::endl;

    std::cout << "f1 == f2: " << (f1 == f2 ? "Да" : "Нет") << std::endl;
    std::cout << "f1 != f2: " << (f1 != f2 ? "Да" : "Нет") << std::endl;
    std::cout << "f1 < f2: " << (f1 < f2 ? "Да" : "Нет") << std::endl;
    std::cout << "f1 > f2: " << (f1 > f2 ? "Да" : "Нет") << std::endl;
    std::cout << "f1 <= f2: " << (f1 <= f2 ? "Да" : "Нет") << std::endl;
    std::cout << "f1 >= f2: " << (f1 >= f2 ? "Да" : "Нет") << std::endl;
}

// Интерактивный режим
void interactiveMode() {
    char continueExecution = 'y';
    while (continueExecution == 'y') {
    std::cout << "\n=== Интерактивный режим ===\n";

    Fraction f1, f2;

    std::cout << "Введите первую дробь (например, 2 3/4 или -3/5): ";
    std::cin >> f1;

    std::cout << "Введите вторую дробь (например, 7 2/3 или -4/-7): ";
    std::cin >> f2;

    std::cout << "Первая дробь: " << f1 << std::endl;
    std::cout << "Вторая дробь: " << f2 << std::endl;

    std::cout << "Сумма: " << f1 + f2 << std::endl;
    std::cout << "Разность: " << f1 - f2 << std::endl;
    std::cout << "Произведение: " << f1 * f2 << std::endl;
    std::cout << "Частное: " << f1 / f2 << std::endl;

    std::cout << "f1 == f2: " << (f1 == f2 ? "Да" : "Нет") << std::endl;
    std::cout << "f1 != f2: " << (f1 != f2 ? "Да" : "Нет") << std::endl;
    std::cout << "f1 < f2: " << (f1 < f2 ? "Да" : "Нет") << std::endl;
    std::cout << "f1 > f2: " << (f1 > f2 ? "Да" : "Нет") << std::endl;
    std::cout << "f1 <= f2: " << (f1 <= f2 ? "Да" : "Нет") << std::endl;
    std::cout << "f1 >= f2: " << (f1 >= f2 ? "Да" : "Нет") << std::endl;

    std::cout << "Хотите продолжить? (y/n)\n\n\n";
    std::cin >> continueExecution;
    }
}

int main() {
    int choice;
    std::cout << "Выберите режим:\n";
    std::cout << "1. Интерактивный режим\n";
    std::cout << "2. Демо-режим\n";
    std::cout << "Ваш выбор: ";
    std::cin >> choice;
    std::cin.ignore(); // Игнорируем оставшийся символ новой строки

    try {
        if (choice == 1) {
            interactiveMode();
        } else if (choice == 2) {
            demoMode();
        } else {
            std::cout << "Неверный выбор.\n";
        }
    } catch (const std::invalid_argument& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    }

    return 0;
}
