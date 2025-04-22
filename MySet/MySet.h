#ifndef MYSET_H
#define MYSET_H

#include "MyVector.h"

template <typename T>
class MySet : public MyVector<T> {
public:
    using MyVector<T>::MyVector;

    bool is_element(const T& element) const;
    int q_find(const T& element) const;

    void add_element(const T& element) override;
    void delete_element(const T& element) override;

    MySet<T> operator+(const MySet<T>& other) const;
    MySet<T> operator-(const MySet<T>& other) const;
    MySet<T> operator*(const MySet<T>& other) const;
    MySet<T>& operator+=(const MySet<T>& other);
    MySet<T>& operator-=(const MySet<T>& other);
    MySet<T>& operator*=(const MySet<T>& other);
    bool operator==(const MySet<T>& other) const;
};

template <>
class MySet<char*> : public MyVector<char*> {
public:
    using MyVector<char*>::MyVector;

    bool is_element(const char* element) const;
    int q_find(const char* element) const;

    void add_element(const char* element) override;
    void delete_element(const char* element) override;

    MySet<char*> operator+(const MySet<char*>& other) const;
    MySet<char*> operator-(const MySet<char*>& other) const;
    MySet<char*> operator*(const MySet<char*>& other) const;
    MySet<char*>& operator+=(const MySet<char*>& other);
    MySet<char*>& operator-=(const MySet<char*>& other);
    MySet<char*>& operator*=(const MySet<char*>& other);
    bool operator==(const MySet<char*>& other) const;
};

#endif // MYSET_H
