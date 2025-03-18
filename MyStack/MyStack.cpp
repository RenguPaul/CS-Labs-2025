#include "MyStack.h"
#include <stdexcept>

void Multipliers(int n, MyStack<int> &stack) {
    if (n < 0) {
        throw std::invalid_argument("Ошибка, вы ввели число < 0. Числа должны быть больше 1");
    }
    if (n == 0 || n == 1) {
        throw std::invalid_argument("Ошибка, числа должны быть больше 1");
    }
    int d = 2;
    while (n > 1) {
        while (n % d == 0) {
            stack.push(d);
            n /= d;
        }
        d++;
    }
}
