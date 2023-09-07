#ifndef ARRAY_LIST_H_
#define ARRAY_LIST_H_

#include <cstdio>

template <typename T>
class ArrayList {
private:
    int _length;
    T* _array;
    int _size;

    void expand();

public:
    ArrayList(int n = 1);

    void add(T t);
    void insert(int index, T t);

    T get(int index) const;
    void set(int index, T t);

    int size() const {
        return _size;
    }
    int length() const {
        return _length;
    }

    T pop();
};

template <typename T>
ArrayList<T>::ArrayList(int n) {
    _length = n;
    _size = 0;
    _array = new T[n];
}

template <typename T>
void ArrayList<T>::add(T t) {
    if (_size >= _length) {
        expand();
    }
    _array[_size++] = t;
}

template <typename T>
void ArrayList<T>::insert(int index, T t) {
    add(T{});
    for (int i = _size; i > index; i--) {
        _array[i] = _array[i - 1];
    }
    _array[index] = t;
}

template <typename T>
void ArrayList<T>::expand() {
    T* new_array = new T[_length << 1];
    for (int i = 0; i < _length; i++) {
        new_array[i] = _array[i];
    }
    delete[] _array;
    _array = new_array;
    _length <<= 1;
}

template <typename T>
T ArrayList<T>::get(int index) const {
    return _array[index];
}

template <typename T>
void ArrayList<T>::set(int index, T t) {
    if (_size <= index) {
        _size = index + 1;
    }
    while (_size > _length) {
        expand();
    }
    _array[index] = t;
}

template <typename T>
T ArrayList<T>::pop() {
    return _array[--_size];
}

#endif  // ARRAY_LIST_H_
