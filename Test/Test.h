#ifndef TEST_H
#define TEST_H

#include <iostream>
#include <cstring>

class Test {
protected:
    char* name;
    int questionsCount;

public:
    Test(const char* name, int questions);
    virtual ~Test();

    virtual void show() const = 0;
    virtual const char* getType() const = 0;

    const char* getName() const { return name; }
    int getQuestionsCount() const { return questionsCount; }
};

inline char* copyString(const char* src) {
    if (!src) return nullptr;
    char* dest = new char[strlen(src) + 1];
    strcpy(dest, src);
    return dest;
}

#endif // TEST_H
