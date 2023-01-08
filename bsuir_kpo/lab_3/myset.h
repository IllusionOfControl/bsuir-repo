#include <iostream>

#define SET_SIZE 10


template <class T>
class Set {
private:
    int _capacity = 0;
    T _array[SET_SIZE];
public:
    Set() {}

    void Add(T value);
    void Delete(T value);
    int Find(T value);
    void Print();

    Set operator+=(T right);
    Set operator-=(T right);
};