#include <iostream>
#include "mymath/mymath.h"

int interactive() {
    char continueExecution = 'y';
    while (continueExecution == 'y' || continueExecution == 'Y') {
        int a, b;
        char operation;

        std::cout << "Введите первое число (a): ";
        std::cin >> a;
        std::cout << "Введите второе число (b): ";
        std::cin >> b;
        std::cout << "Выберите операцию (+, -, *, /, ^): ";
        std::cin >> operation;

        switch (operation) {
            case '+':
                std::cout << "Sum(a, b) = " << mymath::Sum(a, b) << std::endl;
                break;
            case '-':
                std::cout << "Substraction(a, b) = " << mymath::Substraction(a, b) << std::endl;
                break;
            case '*':
                std::cout << "Product(a, b) = " << mymath::Product(a, b) << std::endl;
                break;
            case '/':
                if (b != 0) {
                    std::cout << "Division(a, b) = " << mymath::Division(a, b) << std::endl;
                } else {
                    std::cout << "Ошибка: деление на ноль!" << std::endl;
                }
                break;
            case '^':
                std::cout << "RaisingToPower(a, b) = " << mymath::RaisingToPower(a, b) << std::endl;
                break;
            default:
                std::cout << "Неизвестная операция!" << std::endl;
                break;
        }

        std::cout << "Хотите продолжить? (y/n): ";
        std::cin >> continueExecution;
    }

    std::cout << "Программа завершена." << std::endl;
    return 0;
}

int demo() {
    int a = 2;
    int b = 3;
    std::cout << "Пусть a, b - некоторые переменные, равные 2, 3\n";
    std::cout << "Вы можете использовать следующие функции:\n";
    std::cout << mymath::Sum(a, b) << " " << "Sum(a, b) - сумма a и b\n";
    std::cout << mymath::Substraction(a, b) << " " << "Substraction(a, b) - разность a и b\n";
    std::cout << mymath::Product(a, b) << " " << "Product(a, b) - умножение a на b\n";
    std::cout << mymath::Division(a, b) << " " << "Division(a, b) - деление a на b\n";
    std::cout << mymath::RaisingToPower(a, b) << " " << "RaisingToPower(a, b) - возведение  в степень a на b\n";
    return 0;
}

int main(int argc, char *argv[]) {
    bool isInteractive = false;    // по умолчанию демо-режим.

    // Если i передается в качестве аргумента, то программу
    // необходимо запустить в интерактивном режиме
    if ((argc == 2) && std::string(argv[1]) == "i") {
        isInteractive = true;
    }

    if (isInteractive) {
        return interactive();
    } else {
        return demo();
    }
}
