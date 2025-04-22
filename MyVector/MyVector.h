#ifndef MYVECTOR_H
#define MYVECTOR_H

#include <cstring>
#include <stdexcept>
#include <algorithm>

template <typename T>
class MyVector {
protected:
    size_t max_size;
    size_t size;
    T* pdata;

    void resize(size_t new_size);
public:
    explicit MyVector(size_t initial_max_size = 1);
    MyVector(const MyVector& other);
    ~MyVector();

    virtual void add_element(const T& element);
    virtual void delete_element(const T& element);
    int find(const T& element) const;

    void sort();

    T& operator[](size_t index);
    const T& operator[](size_t index) const;
    MyVector& operator=(const MyVector& other);
};

template <>
class MyVector<char*> {
protected:
    size_t max_size;
    size_t size;
    char** pdata;

    void resize(size_t new_size);
    static int partition(char** array, int left, int right);
    static void quickSort(char** array, int left, int right);

public:
    explicit MyVector(size_t initial_max_size = 1);
    MyVector(const MyVector& other);
    ~MyVector();

    virtual void add_element(const char* element);
    virtual void delete_element(const char* element);
    int find(const char* element) const;

    void sort();

    char*& operator[](size_t index);
    const char* operator[](size_t index) const;
    MyVector& operator=(const MyVector& other);
};

#endif // MYVECTOR_H
