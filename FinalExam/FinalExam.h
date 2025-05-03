#ifndef FINALEXAM_H
#define FINALEXAM_H

#include "/home/pavel/BAUMAN_PROJECTS/CS-2025-PR/CS-Labs-2025/Exam/Exam.h"

class FinalExam : public Exam {
    bool isThesis;

public:
    FinalExam(const char* name, int questions, const char* subject,
              int duration, bool isThesis);
    ~FinalExam() override;

    void show() const override;
    const char* getType() const override { return "FinalExam"; }
};

#endif // FINALEXAM_H
