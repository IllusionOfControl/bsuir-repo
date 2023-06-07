#include <iostream>

void replaceOnes(int arr[], int size, int index) {
    // ���� ����� �� �������
    if (index == size) {
        return;
    }

    // ��������� ������� �������
    bool leftOne = false;
    bool rightOne = false;

    if (index > 0 && arr[index - 1] == 1) {
        leftOne = true;
    }

    if (index < size - 1 && arr[index + 1] == 1) {
        rightOne = true;
    }

    // �������� ������� ���� ���������
    if (leftOne || rightOne) {
        arr[index] = 0;
    }

    // ����������� ����� ���� �� ��������� ��������
    replaceOnes(arr, size, index + 1);
}

int main() {
    int arr[] = { 11, 1, 13, 21, 1, 23, 31, 32, 33 };
    // ��������� ������ ������� (������ ������� ����� �� 4 ����� (������ int))
    int size = sizeof(arr) / sizeof(arr[0]);

    // �������� �������
    replaceOnes(arr, size, 0);

    // ������� ������  �������
    for (int i = 0; i < size; i++) {
        std::cout << arr[i] << " ";
    }

    return 0;
}