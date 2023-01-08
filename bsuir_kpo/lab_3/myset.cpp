#include "myset.h"


template<class T>
void Set<T>::Add(T value) {}

template<class T>
void Set<T>::Delete(T value) {}

template<class T>
int Set<T>::Find(T value) {}

template<class T>
void Set<T>::Print() {}


template<class T>
Set<T> Set<T>::operator+=(T right) {
    this->Add(right);
    return *this;
}

template<class T>
Set<T> Set<T>::operator-=(T right) {
    this->Delete(right);
    return *this;
}


template<>
void Set<char*>::Add(char* value) {
    if (_capacity == SET_SIZE) return;

    for (int i = 0; i < _capacity; i++) {
        if (strcmp(value, _array[i]) == 0) {
            return;
        }
    }

    _array[_capacity] = value;
    _capacity++;
}


void Set<char*>::Delete(char* value) {
    int pos = -1;

    for (int i = 0; i < _capacity; i++) {
        if (strcmp(value, _array[i]) == 0) {
            pos = i;
            break;
        }
    }
    if (pos == -1) return;
    for (int i = pos; i < _capacity - 1; i++) {
        _array[i] = _array[i + 1];
    }
    _capacity--;
}


int Set<char*>::Find(char* value) {
    for (int i = 0; i < _capacity; i++) {
        if (strcmp(value, _array[i]) == 0) return i;
    }
    return -1;
}


void Set<char*>::Print() {
    for (int i = 0; i < _capacity; i++) {
        std::cout << _array[i] << std::endl;
    }

    std::cout << "=================\n" << std::endl;
}


Set<char*> Set<char*>::operator+=(char* right) {
    this->Add(right);
    return *this;
}

Set<char*> Set<char*>::operator-=(char* right) {
    this->Delete(right);
    return *this;
}