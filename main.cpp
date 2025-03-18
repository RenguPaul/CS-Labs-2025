#include "MyStack/MyStack.h"
#include <iostream>

int main() {
    char continueExecution = 'y';
    while (continueExecution == 'y') {
        std::cout << "Введите число, которое нужно разложить на множители. Заметьте - оно должно быть натуральным и больше 1\n";
        int N;
        std::cin >> N;
        MyStack<int> stack;
        Multipliers(N, stack);

    std::cout << N << "=";
    while (!stack.empty()) {
        std::cout << stack.top_inf();
        stack.pop();
        if (!stack.empty()) {
            std::cout << " * ";
        }
    }
    std::cout << std::endl;
    std::cout << "Хотите продолжить выполнение программы? (y/n)" << std::endl;
    std::cin >> continueExecution;
    }
    MyStack<char> stack1;
    stack1.push('A');
    stack1.push('B');
    stack1.push('C');
    MyStack<char> stack2(stack1);
    MyStack<char> stack3;
    stack3 = stack2;
    std::cout << stack1 << ' ' << stack2 << ' ' << stack3 << std::endl;

    return 0;

}
