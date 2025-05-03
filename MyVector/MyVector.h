#ifndef MYVECTOR_H
#define MYVECTOR_H

#include <cstring>
#include <stdexcept>
#include <algorithm>
#include <iostream>

template <typename T> class MyVector;
template <typename T> std::ostream& operator<<(std::ostream& os, const MyVector<T>& vec);

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
    explicit MyVector(const T& element);
    ~MyVector();

    virtual void add_element(const T& element);
    virtual void delete_element(const T& element);
    int find(const T& element) const;
    size_t get_max_size() const { return max_size; }
    size_t get_size() const { return size; }

    void sort();

    T& operator[](size_t index);
    const T& operator[](size_t index) const;
    MyVector& operator=(const MyVector& other);

    friend std::ostream& operator<< <T>(std::ostream& os, const MyVector<T>& vec);
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
    explicit MyVector(const char* element);
    ~MyVector();

    size_t get_max_size() const { return max_size; }
    size_t get_size() const { return size; }

    virtual void add_element(const char* element);
    virtual void delete_element(const char* element);
    int find(const char* element) const;

    void sort();

    char*& operator[](size_t index);
    const char* operator[](size_t index) const;
    MyVector& operator=(const MyVector& other);

    friend std::ostream& operator<<(std::ostream& os, const MyVector<char*>& vec);
};


template <typename T>
MyVector<T>::MyVector(size_t initial_max_size)
    : max_size(initial_max_size), size(0), pdata(new T[max_size]) {}

template <typename T>
void MyVector<T>::resize(size_t new_size) {
    T* new_pdata = new T[new_size];
    for(size_t i = 0; i < size; ++i) {
        new_pdata[i] = pdata[i];
    }
    delete[] pdata;
    pdata = new_pdata;
    max_size = new_size;
}

template <typename T>
MyVector<T>::MyVector(const MyVector& other)
    : max_size(other.max_size), size(other.size), pdata(new T[max_size]) {
    for(size_t i = 0; i < size; ++i) {
        pdata[i] = other.pdata[i];
    }
}

template <typename T>
MyVector<T>::MyVector(const T& element)
    : max_size(1), size(1), pdata(new T[1]) {
    pdata[0] = element;
}

template <typename T>
MyVector<T>::~MyVector() {
    delete[] pdata;
}

template <typename T>
void MyVector<T>::add_element(const T& element) {
    if(size == max_size) {
        resize(max_size ? max_size * 2 : 1);
    }
    pdata[size++] = element;
}

template <typename T>
void MyVector<T>::delete_element(const T& element) {
    int index = find(element);
    if(index == -1) return;

    for(size_t i = index; i < size - 1; ++i) {
        pdata[i] = pdata[i + 1];
    }
    --size;

    if(size < max_size / 4 && max_size > 1) {
        resize(max_size / 2);
    }
}

template <typename T>
int MyVector<T>::find(const T& element) const {
    for(size_t i = 0; i < size; ++i) {
        if(pdata[i] == element) {
            return static_cast<int>(i);
        }
    }
    return -1;
}

template <typename T>
void MyVector<T>::sort() {
    if(size > 1) {
        std::sort(pdata, pdata + size);
    }
}

template <typename T>
T& MyVector<T>::operator[](size_t index) {
    if(index >= size) {
        throw std::out_of_range("Index out of range");
    }
    return pdata[index];
}

template <typename T>
const T& MyVector<T>::operator[](size_t index) const {
    if(index >= size) {
        throw std::out_of_range("Index out of range");
    }
    return pdata[index];
}

template <typename T>
MyVector<T>& MyVector<T>::operator=(const MyVector& other) {
    if(this != &other) {
        delete[] pdata;
        max_size = other.max_size;
        size = other.size;
        pdata = new T[max_size];
        for(size_t i = 0; i < size; ++i) {
            pdata[i] = other.pdata[i];
        }
    }
    return *this;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const MyVector<T>& vec) {
    os << "[";
    for(size_t i = 0; i < vec.size; ++i) {
        if(i != 0) os << ", ";
        os << vec.pdata[i];
    }
    os << "]";
    return os;
}


#endif // MYVECTOR_H
