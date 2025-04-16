#include "MySet.h"

template <typename T>
int MySet<T>::q_find(const T& element) {
    int left = 0;
    int right = static_cast<int>(this->size) - 1;
    while (left <= right) {
        int mid = (left + right) / 2;
        if (this->pdata[mid] == element) {
            return mid;
        } else if (this->pdata[mid] < element) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return -1;
}

template <>
int MySet<char*>::q_find(const char* element) {
    int left = 0;
    int right = static_cast<int>(this->size) - 1;
    while (left <= right) {
        int mid = (left + right) / 2;
        if (strcmp(this->pdata[mid], element) == 0) {
            return mid;
        } else if (strcmp(this->pdata[mid], element) < 0) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return -1;
}

template <typename T>
bool MySet<T>::is_element(const T& element) {
    return q_find(element) != -1;
}

template<>
bool MySet<char*>::is_element(const char* element) {
    return q_find(element) != -1;
}

template <typename T>
void MySet<T>::add_element(const T& element) {
    if (!is_element(element)) {
        MyVector<T>::add_element(element);
        this->sort();
    }
    return;
}

template <>
void MySet<char*>::add_element(const char* element) {
    if (!is_element(element)) {
        char* new_element = new char[strlen(element) + 1];
        strcpy(new_element, element);
        MyVector<char*>::add_element(new_element);
        this->sort();
    }
    return;
}

template <typename T>
void MySet<T>::delete_element(const T& element) {
    if (is_element(element)) {
        MyVector<T>::delete_element(element);
        this->sort();
    }
    return;
}

template <>
void MySet<char*>::delete_element(const char* element) {
    if (is_element(element)) {
        int index = find(element);
        delete[] this->pdata[index];
        MyVector<char*>::delete_element(element);
        this->sort();
    }
    return;
}
