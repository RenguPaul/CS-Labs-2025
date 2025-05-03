#include "Exam.h"
#include <iostream>

Exam::Exam(const char* name, int questions, const char* subject, int duration)
    : Test(name, questions), subject(copyString(subject)), duration(duration) {
    //std::cout << "Exam()" << std::endl;
}

Exam::~Exam() {
    //std::cout << "~Exam()" << std::endl;
    delete[] subject;
}

void Exam::show() const {
    std::cout << "Exam: " << name << " (" << subject << ")\n"
              << "  Questions: " << questionsCount << "\n"
              << "  Duration: " << duration << " minutes" << std::endl;
}
