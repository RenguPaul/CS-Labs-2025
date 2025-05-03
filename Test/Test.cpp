#include "Test.h"

Test::Test(const char* name, int questions)
    : name(copyString(name)), questionsCount(questions) {
    //std::cout << "Test()" << std::endl;
}

Test::~Test() {
    //std::cout << "~Test()" << std::endl;
    delete[] name;
}
