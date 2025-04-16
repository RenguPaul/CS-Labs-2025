#ifndef MYVECTOR_H
#define MYVECTOR_H

#include <iostream>
#include <algorithm>
#include <cstring>

template <typename T>
class MyVector {
    protected:
        size_t max_size;
        size_t size;
        T* pdata;

        void resize(size_t new_size);
    public:
        MyVector(size_t initial_max_size=1);
        MyVector(const MyVector& other);
        virtual ~MyVector();

        virtual void add_element(const T& element);
        virtual void add_element(const char* element);
        virtual void delete_element(const T& element);
        virtual void delete_element(const char* element);

        int find(const T& element);
        int find(const char* element);
        void sort();

        T& operator[](size_t index) const;
        MyVector& operator=(const MyVector& other);

};

#endif // MYVECTOR_H
