#ifndef EXAM_H
#define EXAM_H

#include "/home/pavel/BAUMAN_PROJECTS/CS-2025-PR/CS-Labs-2025/Test/Test.h"

class Exam : public Test {
protected:
    char* subject;
    int duration;

public:
    Exam(const char* name, int questions, const char* subject, int duration);
    ~Exam() override;

    void show() const override;
    const char* getType() const override { return "Exam"; }
};

#endif // EXAM_H
