#include "MyVector.h"
#include <cstring>

template <typename T>
MyVector<T>::MyVector(size_t initial_max_size) : max_size(initial_max_size), size(0) {
    pdata = new T[max_size];
}

template <typename T>
void MyVector<T>::resize(size_t new_size) {
    T* newPdata = new T[new_size];
    for(size_t i=0; i<size; ++i) {
        newPdata[i] = pdata[i];
    }
    delete[] pdata;
    pdata = newPdata;
    max_size = new_size;
}

template <typename T>
MyVector<T>::MyVector(const MyVector& other) : max_size(other.max_size), size(other.size) {
    pdata = new T[max_size];
    for (size_t i=0; i<size; ++i) {
        pdata[i] = other.pdata[i];
    }
}

template <typename T>
MyVector<T>::~MyVector() {
    delete[] pdata;
}

template<>
MyVector<const char*>::~MyVector() {
    for(int i=0; i<size; ++i) {
        delete[] pdata[i];
    }
    delete[] pdata;
}

template <typename T>
void MyVector<T>::add_element(const T& element){
    if (size == max_size) {
        resize(max_size * 2);
    }
    pdata[size++] = element;
    return;
}

template<>
void MyVector<char*>::add_element(const char* element) {
    if (size == max_size) {
        resize(max_size * 2);
    }
    pdata[size] = new char[strlen(element) + 1];
    strcpy(pdata[size], element);
    ++size;
    return;

}

template <typename T>
void MyVector<T>::delete_element(const T& element) {
    int index = find(element);

    for(size_t i=static_cast<size_t>(index); i<size - 1; ++i) {
        pdata[i] = pdata[i + 1];
    }

    --size;

    if (size < max_size / 4) {
        max_size /= 2;
    }

    return;
}

template <>
void MyVector<char*>::delete_element(const char* element){
    int index = find(element);

    if(index == 1) return;

    delete[] pdata[index];

    for(size_t i=static_cast<size_t>(index); i < size - 1; ++i) {
        pdata[i] = pdata[i + 1];
    }

    --size;

    if (size < max_size / 4) {
        max_size /= 2;
    }

    return;
}

template <typename T>
int MyVector<T>::find(const T& element) {
    for(size_t i = 0; i < size; ++i) {
        if (pdata[i] == element) {
            return static_cast<int>(i);
        }
    }
    return -1;
}

template <>
int MyVector<const char*>::find(const char* element) {
    if (element == nullptr) {
        for(size_t i = 0; i < size; ++i) {
            if (pdata[i] == nullptr) {
                return static_cast<int>(i);
            }
        }
    } else {
        for(size_t i = 0; i < size; ++i) {
            if (pdata[i] != nullptr && strcmp(element, pdata[i]) == 0) {
                return static_cast<int>(i);
            }
        }
    }
    return -1;
}

template <typename T>
int partition(T* array, int left, int right) {
    T pivot = array[(left + right) / 2];
    int i = left;
    int j = right;

    while (i <= j) {
        while (array[i] < pivot) {
            ++i;
        }
        while (array[j] > pivot) {
            --j;
        }

        if (i <= j) {
            std::swap(array[i++], array[j--]);
        }
    }
    return j;
}

template<>
int partition(const char** array, int left, int right) {
    const char* pivot = array[(left + right) / 2];
    int i = left;
    int j = right;
    while (i <= j) {
        while(strcmp(array[i], pivot) < 0) {
            ++i;
        }
        while(strcmp(array[j], pivot) > 0) {
            --j;
        }
        if (i <= j) {
            std::swap(array[i++], array[j--]);
        }
    }
    return j;

}

template <typename T>
void quickSort(T* array, int left, int right) {
    if (left < right) {
        int q = partition(array, left, right);
        quickSort(array, left, q);
        quickSort(array, q + 1, right);
    }
}

template <typename T>
void MyVector<T>::sort() {
    if (size > 1) {
        quickSort(pdata, 0, static_cast<int>(size) - 1);
    }
}


template <typename T>
T& MyVector<T>::operator[](size_t index) const {
    if (index > max_size) {
        throw std::runtime_error("Индекс больше размера вектора");
    }
    return pdata[index];
}

template <typename T>
MyVector<T>& MyVector<T>::operator=(const MyVector& other) {
    if (this != &other) {
        delete[] pdata;
        max_size = other.max_size;
        size = other.size;
        pdata = new T[max_size]{};
        for(int i=0; i<size; ++i) {
            pdata[i] = other.pdata[i];
        }
    }
    return *this;
}
