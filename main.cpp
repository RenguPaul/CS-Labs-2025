#include <iostream>
#include <cstring>
#include "fraction/fraction.hpp"

// Функция для демонстрации возможностей класса Fraction
void demoMode() {
    std::cout << "=== Демо-режим ===" << std::endl;

    // Создание дробей
    Fraction frac1(3, 4);
    Fraction frac2("2 1/2");
    Fraction frac3("-6/8");

    // Вывод дробей
    std::cout << "Дробь 1: " << frac1 << std::endl;
    std::cout << "Дробь 2: " << frac2 << std::endl;
    std::cout << "Дробь 3: " << frac3 << std::endl;

    // Сокращение дробей
    std::cout << "\nСокращение дробей:" << std::endl;
    std::cout << "Дробь 3 после сокращения: " << Fraction(frac3.getNumerator(), frac3.getDenominator()) << std::endl;

    // Ввод дроби с клавиатуры
    std::cout << "\nВведите дробь в формате a/b или a b/c: ";
    Fraction frac4;
    std::cin >> frac4;
    std::cout << "Вы ввели: " << frac4 << std::endl;

    std::cout << "\n=== Демо-режим завершен ===" << std::endl;
}

// Функция для интерактивного режима
void interactiveMode() {
    std::cout << "=== Интерактивный режим ===" << std::endl;

    Fraction frac;
    while (true) {
        std::cout << "\nВведите дробь (или 'exit' для выхода): ";
        char input[50];
        std::cin >> input;

        if (strcmp(input, "exit") == 0) {
            break;
        }

        frac = Fraction(input);
        std::cout << "Вы ввели: " << frac << std::endl;
        std::cout << "Числитель: " << frac.getNumerator() << std::endl;
        std::cout << "Знаменатель: " << frac.getDenominator() << std::endl;
    }

    std::cout << "\n=== Интерактивный режим завершен ===" << std::endl;
}

int main() {
    int choice;
    std::cout << "Выберите режим:\n"
              << "1. Демо-режим\n"
              << "2. Интерактивный режим\n"
              << "Ваш выбор: ";
    std::cin >> choice;

    if (choice == 1) {
        demoMode();
    } else if (choice == 2) {
        interactiveMode();
    } else {
        std::cout << "Неверный выбор. Завершение программы." << std::endl;
    }

    return 0;
}
