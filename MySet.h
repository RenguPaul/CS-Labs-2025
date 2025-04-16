#ifndef MYSET_H
#define MYSET_H

#include "MyVector.h"
template <typename T>
class MySet : public MyVector<T>{

    public:

    using MyVector<T>::MyVector;

    bool is_element(const T& element);
    bool is_element(const char* element);

    int q_find(const T& element);
    int q_find(const char* element);

    void add_element(const T& element) override;
    void add_element(const char* element) override;

    void delete_element(const T& element) override;
    void delete_element(const char* element) override;


};

#endif // MYSET_H
