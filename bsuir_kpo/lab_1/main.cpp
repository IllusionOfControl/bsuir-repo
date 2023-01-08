#include <iostream>
#include <cstdio>
#include <string>
#include <cassert>
#include <iomanip>


class Double {
private:
    double m_value;
public:
    explicit Double(double value = 0) {
        m_value = value;
    }

    explicit Double(int value = 0) {
        m_value = (double)value;
    }

    friend std::ostream& operator <<(std::ostream& os, const Double& d)
    {
        os << std::fixed << std::setprecision(3) << d.m_value;
        return os;
    }
};


class Integer {
private:
    int m_value;
public:
    Integer(int value = 0) {
        m_value = value;
    }

    int value() const {
        return m_value;
    }

    Integer& operator =(const Integer& right) {
        m_value = right.value();
        return *this;
    }

    Integer& operator =(const int right) {
        m_value = right;
        return *this;
    }

    int operator [](int index) {
        if (index >= sizeof(int) * 8) {
            std::cout << "Array index out of bound, exiting";
            exit(0);
        }
        return (m_value & (0b1 << index)) > 0;
    }

    Integer& operator ++() {
        m_value++;
    }

    Integer operator +(const Integer& right) {
        return Integer(m_value + right.value());
    }

    Integer operator +(const int right) {
        return Integer(m_value + right);
    }

    bool operator <(const Integer& right) {
        return m_value < right.value();
    }

    bool operator <(const int right) {
        return m_value < right;
    }

    friend Integer operator -(const Integer& left, const double& right) {
        Integer result = left.value() - int(right);
        return result;
    }

    friend Integer& operator --(Integer& i) {
        i.m_value--;
    }

    friend bool operator >(const Integer& left, const float& right) {
        return left.value() > right;
    }

    friend std::ostream& operator <<(std::ostream& os, const Integer& i)
    {
        os << i.value();
        return os;
    }

    operator double() const
    {
        return double(m_value);
    }
};


int main() {
    setlocale(LC_ALL, "Russian");

    std::cout << "" << std::endl;

    Integer i = 10;
    std::cout << "Создание переменной i = 10: \nResult: " << i << std::endl;
    assert(i.value() == 10);

    Integer res;
    res = i + 10;
    std::cout << "Сложение переменной i и 10: \nResult:" << res << std::endl;
    assert(res.value() == 20);

    res = i - 5.0;
    std::cout << "Вычитание 5.0 из переменной i: \nResult:" << res << std::endl;
    assert(res.value() == 5);

    std::cout << "Сравнение 7 и переменной i на <: \nResult:" << std::boolalpha << (7 < i) << std::endl;
    assert(!(7 < res.value()));

    std::cout << "Сравнение 7.0f и переменной i на >: \nResult:" << std::boolalpha << (7.0f > i) << std::endl;
    assert(7 > res.value());

    res = i[1];
    std::cout << "Получение 2го бита переменной i: \nResult:" << res << std::endl;
    assert((bool) i[1] == true);
    
    std::cout << "Перевод числа " << i << " в double: \nResult : " << double(i) << std::endl;

    Double d = (Double) i;
    std::cout << "Перевод числа " << i << " из Integer в Double: \nResult : " << d << std::endl;

    return 0;
}