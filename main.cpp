#include <iostream>
#include "mymath/mymath.h"

int interactive() {
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
    if ((argc == 2) && argv[1] == "i") {
        isInteractive = true;
    }

    if (isInteractive) {
        return interactive();

    } else {
        return demo();
    }
}
