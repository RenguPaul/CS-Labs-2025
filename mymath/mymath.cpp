#include "mymath.h"

namespace mymath {
    int Sum(int a, int b) {
        return a + b;
    }

    int Substraction(int a, int b) {
        return a - b;
    }

    int Product(int a, int b) {
        return a * b;
    }

    int Division(int a, int b) {
        return a / b;
    }

    int RaisingToPower(int a, int b) {
        int number = 1;
        for(int i=0; i<b; ++i) {
            number *= a;
        }
        return number;
    }
}
