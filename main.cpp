#include "fraction/fraction.hpp"
#include <iostream>

void demoMode() {
    /*std::cout << "\n=== Демо-режим ===\n";

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
    std::cout << "f1 >= f2: " << (f1 >= f2 ? "Да" : "Нет") << std::endl;*/
    std::cout << "Введите дробь: \n";
    Fraction z;
    std::cin >> z;
    std::cout << "z=" << z << std::endl;
    // проверка конструкторов
    Fraction fr1(10, 0), fr2;
    std::cout << "fr2=" << fr2 << std::endl;
    std::cout << "fr1=" << fr1 << std::endl;
    Fraction fr = "-1 4/8";
    std::cout << "fr=" << fr << std::endl;
    Fraction x(z), y;
    std::cout << "x=" << x << std::endl;
    double dbl = -1.25;
    Fraction f = dbl;
    std::cout << "f=" << f << std::endl;
    // проверка перегруженной операции "+"
    y = x + z;
    std::cout << "y=" << y << std::endl;
    y += x;
    f += dbl / 2;
    std::cout << "f=" << f << std::endl;
    y = x + dbl;
    std::cout << "y=" << y << std::endl;
    y = dbl + y;
    std::cout << "y=" << y << std::endl;
    y += dbl;
    std::cout << "y=" << y << std::endl;
    int i = 5;
    y += i;
    std::cout << "y=" << y << std::endl;
    y = i + x;
    std::cout << "y=" << y << std::endl;
    y = x + i;
    std::cout << "y=" << y << std::endl;
    y += dbl + i + x;
    std::cout << "y=" << y << std::endl;
}

void interactiveMode() {
    char continueExecution = 'y';
    while (continueExecution == 'y') {
    std::cout << "\n=== Интерактивный режим ===\n";

    Fraction f1, f2;

    std::cout << "Введите первую дробь (например, 2 3/4 или -3/5 или 1.25): ";
    std::cin >> f1;

    std::cout << "Введите вторую дробь (в таких же форматах): ";
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

    std::cout << "Хотите продолжить? (y/n)\n";
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
    std::cin.ignore();

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
