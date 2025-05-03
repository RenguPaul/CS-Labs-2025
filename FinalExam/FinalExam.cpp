#include "FinalExam.h"
#include <iostream>

FinalExam::FinalExam(const char* name, int questions, const char* subject,
                     int duration, bool isThesis)
    : Exam(name, questions, subject, duration), isThesis(isThesis) {
    //std::cout << "FinalExam()" << std::endl;
}

FinalExam::~FinalExam() {
    //std::cout << "~FinalExam()" << std::endl;
}

void FinalExam::show() const {
    std::cout << "Final Exam: " << name << " (" << subject << ")\n"
              << "  Questions: " << questionsCount << "\n"
              << "  Duration: " << duration << " minutes\n"
              << "  " << (isThesis ? "Includes" : "No") << " thesis defense" << std::endl;
}
