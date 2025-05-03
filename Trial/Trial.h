#ifndef TRIAL_H
#define TRIAL_H

#include "/home/pavel/BAUMAN_PROJECTS/CS-2025-PR/CS-Labs-2025/Test/Test.h"

class Trial : public Test {
    int attemptsAllowed;

public:
    Trial(const char* name, int questions, int attempts);
    ~Trial() override;

    void show() const override;
    const char* getType() const override { return "Trial"; }
};

#endif // TRIAL_H
