#include "MyVector.h"
#include <cstring>
#include <algorithm>
#include <stdexcept>

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

MyVector<char*>::MyVector(size_t initial_max_size)
    : max_size(initial_max_size), size(0), pdata(new char*[max_size]()) {}

void MyVector<char*>::resize(size_t new_size) {
    char** new_pdata = new char*[new_size]();
    for(size_t i = 0; i < size; ++i) {
        new_pdata[i] = pdata[i];
    }
    delete[] pdata;
    pdata = new_pdata;
    max_size = new_size;
}

MyVector<char*>::MyVector(const MyVector& other)
    : max_size(other.max_size), size(other.size), pdata(new char*[max_size]()) {
    for(size_t i = 0; i < size; ++i) {
        if(other.pdata[i]) {
            pdata[i] = new char[strlen(other.pdata[i]) + 1];
            strcpy(pdata[i], other.pdata[i]);
        }
    }
}

MyVector<char*>::~MyVector() {
    for(size_t i = 0; i < size; ++i) {
        delete[] pdata[i];
    }
    delete[] pdata;
}

void MyVector<char*>::add_element(const char* element) {
    if(size == max_size) {
        resize(max_size ? max_size * 2 : 1);
    }
    pdata[size] = new char[strlen(element) + 1];
    strcpy(pdata[size], element);
    ++size;
}

void MyVector<char*>::delete_element(const char* element) {
    int index = find(element);
    if(index == -1) return;

    delete[] pdata[index];
    for(size_t i = index; i < size - 1; ++i) {
        pdata[i] = pdata[i + 1];
    }
    --size;

    if(size < max_size / 4 && max_size > 1) {
        resize(max_size / 2);
    }
}

int MyVector<char*>::find(const char* element) const {
    if(element == nullptr) {
        for(size_t i = 0; i < size; ++i) {
            if(pdata[i] == nullptr) {
                return static_cast<int>(i);
            }
        }
    } else {
        for(size_t i = 0; i < size; ++i) {
            if(pdata[i] && strcmp(element, pdata[i]) == 0) {
                return static_cast<int>(i);
            }
        }
    }
    return -1;
}

int MyVector<char*>::partition(char** array, int left, int right) {
    const char* pivot = array[(left + right) / 2];
    int i = left;
    int j = right;

    while(i <= j) {
        while(strcmp(array[i], pivot) < 0) ++i;
        while(strcmp(array[j], pivot) > 0) --j;
        if(i <= j) std::swap(array[i++], array[j--]);
    }
    return j;
}

void MyVector<char*>::quickSort(char** array, int left, int right) {
    if(left < right) {
        int q = partition(array, left, right);
        quickSort(array, left, q);
        quickSort(array, q + 1, right);
    }
}

void MyVector<char*>::sort() {
    if(size > 1) {
        quickSort(pdata, 0, static_cast<int>(size) - 1);
    }
}

char*& MyVector<char*>::operator[](size_t index) {
    if(index >= size) {
        throw std::out_of_range("Index out of range");
    }
    return pdata[index];
}

const char* MyVector<char*>::operator[](size_t index) const {
    if(index >= size) {
        throw std::out_of_range("Index out of range");
    }
    return pdata[index];
}

MyVector<char*>& MyVector<char*>::operator=(const MyVector& other) {
    if(this != &other) {
        for(size_t i = 0; i < size; ++i) {
            delete[] pdata[i];
        }
        delete[] pdata;

        max_size = other.max_size;
        size = other.size;
        pdata = new char*[max_size]();

        for(size_t i = 0; i < size; ++i) {
            if(other.pdata[i]) {
                pdata[i] = new char[strlen(other.pdata[i]) + 1];
                strcpy(pdata[i], other.pdata[i]);
            }
        }
    }
    return *this;
}
