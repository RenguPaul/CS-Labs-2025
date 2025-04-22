#include "MySet.h"
#include <cstring>
#include <algorithm>

template <typename T>
int MySet<T>::q_find(const T& element) const {
    int left = 0;
    int right = static_cast<int>(this->size) - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (this->pdata[mid] == element) {
            return mid;
        }
        if (this->pdata[mid] < element) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return -1;
}

template <typename T>
bool MySet<T>::is_element(const T& element) const {
    return q_find(element) != -1;
}

template <typename T>
void MySet<T>::add_element(const T& element) {
    if (!is_element(element)) {
        int index = 0;
        while (index < static_cast<int>(this->size) &&
               this->pdata[index] < element) {
            index++;
        }

        if (this->size == this->max_size) {
            this->resize(this->max_size ? this->max_size * 2 : 1);
        }
        for (int i = static_cast<int>(this->size); i > index; --i) {
            this->pdata[i] = this->pdata[i-1];
        }

        this->pdata[index] = element;
        this->size++;
    }
}

template <typename T>
void MySet<T>::delete_element(const T& element) {
    int index = q_find(element);
    if (index != -1) {
        for (size_t i = index; i < this->size - 1; ++i) {
            this->pdata[i] = this->pdata[i + 1];
        }
        this->size--;

        if (this->size < this->max_size / 4 && this->max_size > 1) {
            this->resize(this->max_size / 2);
        }
    }
}


template <typename T>
bool MySet<T>::operator==(const MySet<T>& other) const {
    if (this->size != other.size) {
        return false;
    }

    for (size_t i = 0; i < this->size; ++i) {
        if (this->pdata[i] != other.pdata[i]) {
            return false;
        }
    }
    return true;
}

template <typename T>
MySet<T> MySet<T>::operator+(const MySet<T>& other) const {
    MySet<T> newSet;

    for (size_t i = 0; i < this->size; ++i) {
        newSet.add_element(this->pdata[i]);
    }

    for (size_t i = 0; i < other.size; ++i) {
        if (!this->is_element(other.pdata[i])) {
            newSet.add_element(other.pdata[i]);
        }
    }

    return newSet;
}

template <typename T>
MySet<T> MySet<T>::operator-(const MySet<T>& other) const {
    MySet<T> newSet;

    for (size_t i = 0; i < this->size; ++i) {
        if (!other.is_element(this->pdata[i])) {
            newSet.add_element(this->pdata[i]);
        }
    }

    return newSet;
}

template <typename T>
MySet<T> MySet<T>::operator*(const MySet<T>& other) const {
    MySet<T> newSet;

    for (size_t i = 0; i < this->size; ++i) {
        if (other.is_element(this->pdata[i])) {
            newSet.add_element(this->pdata[i]);
        }
    }

    return newSet;
}

template <typename T>
MySet<T>& MySet<T>::operator*=(const MySet<T>& other) {
    *this = *this * other;
    return *this;
}

template <typename T>
MySet<T>& MySet<T>::operator+=(const MySet<T>& other) {
    *this = *this + other;
    return *this;
}

template <typename T>
MySet<T>& MySet<T>::operator-=(const MySet<T>& other) {
    *this = *this - other;
    return *this;
}

int MySet<char*>::q_find(const char* element) const {
    int left = 0;
    int right = static_cast<int>(this->size) - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        int cmp = strcmp(this->pdata[mid], element);

        if (cmp == 0) {
            return mid;
        }
        if (cmp < 0) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return -1;
}

bool MySet<char*>::is_element(const char* element) const {
    return q_find(element) != -1;
}

void MySet<char*>::add_element(const char* element) {
    if (!is_element(element)) {
        int index = 0;
        while (index < static_cast<int>(this->size) &&
               strcmp(this->pdata[index], element) < 0) {
            index++;
        }

        if (this->size == this->max_size) {
            this->resize(this->max_size ? this->max_size * 2 : 1);
        }

        for (int i = static_cast<int>(this->size); i > index; --i) {
            this->pdata[i] = this->pdata[i-1];
        }

        this->pdata[index] = new char[strlen(element) + 1];
        strcpy(this->pdata[index], element);
        this->size++;
    }
}

void MySet<char*>::delete_element(const char* element) {
    int index = q_find(element);
    if (index != -1) {
        delete[] this->pdata[index];

        for (size_t i = index; i < this->size - 1; ++i) {
            this->pdata[i] = this->pdata[i + 1];
        }
        this->size--;

        if (this->size < this->max_size / 4 && this->max_size > 1) {
            this->resize(this->max_size / 2);
        }
    }
}

bool MySet<char*>::operator==(const MySet<char*>& other) const {
    if (this->size != other.size) {
        return false;
    }

    for (size_t i = 0; i < this->size; ++i) {
        if (strcmp(this->pdata[i], other.pdata[i]) != 0) {
            return false;
        }
    }
    return true;
}

MySet<char*> MySet<char*>::operator+(const MySet<char*>& other) const {
    MySet<char*> newSet;

    for (size_t i = 0; i < this->size; ++i) {
        newSet.add_element(this->pdata[i]);
    }

    for (size_t i = 0; i < other.size; ++i) {
        if (!newSet.is_element(other.pdata[i])) {
            newSet.add_element(other.pdata[i]);
        }
    }

    return newSet;
}

MySet<char*> MySet<char*>::operator-(const MySet<char*>& other) const {
    MySet<char*> newSet;

    for (size_t i = 0; i < this->size; ++i) {
        if (!other.is_element(this->pdata[i])) {
            newSet.add_element(this->pdata[i]);
        }
    }

    return newSet;
}

MySet<char*> MySet<char*>::operator*(const MySet<char*>& other) const {
    MySet<char*> newSet;

    for (size_t i = 0; i < this->size; ++i) {
        if (other.is_element(this->pdata[i])) {
            newSet.add_element(this->pdata[i]);
        }
    }

    return newSet;
}

MySet<char*>::~MySet() {
    for (size_t i = 0; i < this->size; ++i) {
        delete[] this->pdata[i];
    }
}

MySet<char*>::MySet(const MySet<char*>& other) {
    this->size = other.size;
    this->max_size = other.max_size;
    this->pdata = new char*[this->max_size];

    for (size_t i = 0; i < this->size; ++i) {
        this->pdata[i] = new char[strlen(other.pdata[i]) + 1];
        strcpy(this->pdata[i], other.pdata[i]);
    }
}
