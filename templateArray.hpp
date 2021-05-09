#pragma once
#include <ostream>
#include <cassert>
#include <functional>

//The whole code is put in the header because template classes have to be forced to compile, or else will not resolve

template <typename T> class Array;
template <typename T> std::ostream& operator << (std::ostream &os, const Array<T> &array);

template <typename T> class Array {
private:
    T *array;
public:
    const int length;

    Array (int length);
    ~Array();

    friend std::ostream& operator << <> (std::ostream &os, const Array<T> &array);
    T operator[] (int index) const;
    T& operator[] (int index);
    bool operator== (const Array<T> &b) const;

    void forEach(std::function<void(T, int)> fn) const;
    void mapSelf(std::function<T(T, int)> mapFn);
    Array<T>* map(std::function<T(T, int)> mapFn) const;
    template <typename F> F reduce(std::function<F(F, T, int)> fn, F init) const;
};

//------------ Constructor / Destructor

template <typename T> Array<T>::Array(int length) : length(length) {
    array = new T[length];
}

template <typename T> Array<T>::~Array() {
    delete[] this->array;
}

//------------ Operators

template <typename T> std::ostream& operator << (std::ostream &os, const Array<T> &array) {
    os << "[";
    for (int i = 0; i < array.length; i++) {
        os << array.array[i];

        if (i + 1 < array.length) os << "; ";
    }
    os << "]";

    return os;
}

template <typename T> T Array<T>::operator[](int index) const {
    //assert(index < this->length && index > -1);
    return this->array[index];
}

template <typename T> T& Array<T>::operator[](int index) {
    //assert(index < this->length && index > -1);
    return this->array[index];
}

template <typename T> bool Array<T>::operator==(const Array<T> &b) const {
    if (b.length != length) return false;

    for (int i = 0; i < length; i++) {
        if (array[i] != b[i]) return false;
    }

    return true;
}

//------------ Methods

template <typename T> void Array<T>::forEach(std::function<void(T, int)> fn) const {
    for (int i = 0; i < this->length; ++i) {
        fn(this->array[i], i);
    }
}

template <typename T> void Array<T>::mapSelf(std::function<T(T, int)> mapFn) {
    for (int i = 0; i < this->length; ++i) {
        this->array[i] = mapFn(this->array[i], i);
    }
}

template <typename T> Array<T>* Array<T>::map(std::function<T(T, int)> mapFn) const {
    Array<T> *mapped = new Array<T>(length);

    for (int i = 0; i < length; ++i) {
        mapped->array[i] = mapFn(this->array[i], i);
    }

    return mapped;
}

template <typename T> template <typename F> F Array<T>::reduce(std::function<F(F, T, int)> fn, F init) const {
    F accumulator = init;

    for (int i = 0; i < length; ++i) {
        accumulator = fn(accumulator, array[i], i);
    }

    return accumulator;
}
