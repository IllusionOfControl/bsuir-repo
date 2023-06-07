#include <iostream>

void replaceOnes(int arr[], int size, int index) {
    // если конец то возврат
    if (index == size) {
        return;
    }

    // проверяем наличие соседей
    bool leftOne = false;
    bool rightOne = false;

    if (index > 0 && arr[index - 1] == 1) {
        leftOne = true;
    }

    if (index < size - 1 && arr[index + 1] == 1) {
        rightOne = true;
    }

    // заменяем элемент если требуется
    if (leftOne || rightOne) {
        arr[index] = 0;
    }

    // рекурсивный вызов себя со следующим индексом
    replaceOnes(arr, size, index + 1);
}

int main() {
    int arr[] = { 11, 1, 13, 21, 1, 23, 31, 32, 33 };
    // вычисляем размер массива (размер массива делим на 4 байта (размер int))
    int size = sizeof(arr) / sizeof(arr[0]);

    // заменяем элемент
    replaceOnes(arr, size, 0);

    // выводим массив  консоль
    for (int i = 0; i < size; i++) {
        std::cout << arr[i] << " ";
    }

    return 0;
}