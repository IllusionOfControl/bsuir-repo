#include <iostream>
#include <string>
#include "myset.h"

int main() {
    Set<char*> charSet;
    char str1[] = "abcd";
    char str2[] = "efgh";
    char str3[] = "jklm";
    char str4[] = "nopq";
    char str5[] = "abcd";
    char str6[] = "qwer";
    char str7[] = "qwer";

    // ����������
    charSet.Add(str1);
    charSet.Add(str2);
    charSet.Add(str3);
    charSet.Add(str4);
    charSet.Print();

    //���������� �� �����������
    charSet.Add(str5);
    charSet.Print();

    // ���������� ����� +=
    charSet += str6;
    charSet.Print();

    // �������� ����� -=
    // ���������� Set::Delete
    charSet -= str7;
    charSet.Print();
}