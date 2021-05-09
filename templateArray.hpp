#pragma once
#include <ostream>
#include <cassert>

//The whole code is put in the header because template classes have to be forced to compile, or else will not resolve

template <class T> class Array;
template <class T> std::ostream& operator << (std::ostream &os, const Array<T> &array);

template <class T> class Array {
private:
    T *array;
public:
    const int length;

    Array (int length);
    ~Array();

    friend std::ostream& operator << <> (std::ostream &os, const Array<T> &array);
    T operator[] (int index) const;
    T& operator[] (int index);
};

template <class T> std::ostream& operator << (std::ostream &os, const Array<T> &array) {
    os << "[";
    for (int i = 0; i < array.length; i++) {
        os << array.array[i];

        if (i + 1 < array.length) os << "; ";
    }
    os << "]";

    return os;
}

template <class T> Array<T>::Array(int length) : length(length) {
    array = new T[length];
}

template <class T> Array<T>::~Array() {
    delete[] this->array;
}

template <class T> T Array<T>::operator[](int index) const {
    //assert(index < this->length && index > -1);
    return this->array[index];
}

template <class T> T& Array<T>::operator[](int index) {
    //assert(index < this->length && index > -1);
    return this->array[index];
}
