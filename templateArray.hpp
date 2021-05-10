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
    const bool validateIndex;
public:
    const int length;

    Array(int length, bool validateIndex = false);
    ~Array();

    friend std::ostream& operator << <> (std::ostream &os, const Array<T> &array);
    const T& operator[] (int index) const;
    T& operator[] (int index);
    bool operator== (const Array<T> &b) const;

    void forEach(const std::function<void(T&, int)> fn) const;
    void mapSelf(const std::function<T(T&, int)> mapFn);
    Array<T> map(const std::function<T(T&, int)> mapFn) const;
    template <typename F> F reduce(const std::function<const F(F, const T&, int)> fn, F accumulator) const;
    bool some(const std::function<bool(const T&, int)> testFn) const;
    bool every(const std::function<bool(const T&, int)> testFn) const;
    bool includes(const T& element) const;
    int indexOf(const T& element) const;
    void fill(const T& value);
    void fill(const std::function<T(int)> fillFn);
    Array<T> copy() const;

    //Not yet fixed
    //void sortSelf(const std::function<bool(const T&, const T&)> sortFn);
    //Array<T> sort(const std::function<bool(const T&, const T&)> sortFn) const;
};

//------------ Constructor / Destructor

template <typename T> Array<T>::Array(int length, bool validateIndex) : length(length), validateIndex(validateIndex) {
    array = new T[length];
}

template <typename T> Array<T>::~Array() {
    delete[] array;
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

template <typename T> const T& Array<T>::operator[](int index) const {
    if (validateIndex) assert(index < length && index > -1);
    return array[index];
}

template <typename T> T& Array<T>::operator[](int index) {
    if (validateIndex) assert(index < length && index > -1);
    return array[index];
}

template <typename T> bool Array<T>::operator==(const Array<T> &b) const {
    if (b.length != length) return false;

    for (int i = 0; i < length; i++) {
        if (array[i] != b[i]) return false;
    }

    return true;
}

//------------ Methods

template <typename T> void Array<T>::forEach(const std::function<void(T&, int)> fn) const {
    for (int i = 0; i < length; ++i) {
        fn(array[i], i);
    }
}

template <typename T> void Array<T>::mapSelf(const std::function<T(T&, int)> mapFn) {
    for (int i = 0; i < length; ++i) {
        array[i] = mapFn(array[i], i);
    }
}

template <typename T> Array<T> Array<T>::map(const std::function<T(T&, int)> mapFn) const {
    Array<T> mapped(length);

    for (int i = 0; i < length; ++i) {
        mapped[i] = mapFn(array[i], i);
    }

    return mapped;
}

template <typename T> template <typename F> F Array<T>::reduce(const std::function<const F(F, const T&, int)> fn, F init) const {
    F accumulator = init;

    for (int i = 0; i < length; ++i) {
        accumulator = fn(accumulator, array[i], i);
    }

    return accumulator;
}

template <typename T> bool Array<T>::some(const std::function<bool(const T&, int)> testFn) const {
    for (int i = 0; i < length; i++) {
        if (testFn(array[i], i)) return true;
    }

    return false;
}

template <typename T> bool Array<T>::every(const std::function<bool(const T&, int)> testFn) const {
    bool passed = true;

    for (int i = 0; i < length; i++) {
        if (!testFn(array[i], i)) passed = false;
    }

    return passed;
}

template <typename T> bool Array<T>::includes(const T& element) const {
    for (int i = 0; i < length; i++) {
        if (array[i] == element) return true;
    }

    return false;
}

template <typename T> int Array<T>::indexOf(const T& element) const {
    for (int i = 0; i < length; i++) {
        if (array[i] == element) return i;
    }

    return -1;
}

template <typename T> void Array<T>::fill(const T& value) {
    for (int i = 0; i < length; i++) {
        array[i] = value;
    }
}

template<typename T> void Array<T>::fill(const std::function<T(int)> fillFn) {
    for (int i = 0; i < length; i++) {
        array[i] = fillFn(i);
    }
}

template<typename T> Array<T> Array<T>::copy() const {
    Array<T> out(length);

    for (int i = 0; i < length; i++) {
        out[i] = array[i];
    }

    return out;
}

/*template <typename T> void Array<T>::sortSelf(const std::function<bool(const T&, const T&)> sortFn) {
    //std::sort(std::begin(array), std::end(array), sortFn);
}

template <typename T> Array<T> Array<T>::sort(const std::function<bool(const T&, const T&)> sortFn) const {
    Array<T> out = copy();
    //std::sort(out[0], out[length - 1], sortFn);

    return out;
}*/