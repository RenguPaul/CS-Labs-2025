#include "Trial.h"
#include <iostream>

Trial::Trial(const char* name, int questions, int attempts)
    : Test(name, questions), attemptsAllowed(attempts) {
    //std::cout << "Trial()" << std::endl;
}

Trial::~Trial() {
    //std::cout << "~Trial()" << std::endl;
}

void Trial::show() const {
    std::cout << "Trial: " << name << "\n"
              << "  Questions: " << questionsCount << "\n"
              << "  Attempts allowed: " << attemptsAllowed << std::endl;
}
