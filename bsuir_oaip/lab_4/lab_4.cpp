#include <iostream>
#include <random>
#include <ctime> 

std::mt19937 generator(time(0)); // инициализируем генератор случайных чисел
std::uniform_int_distribution<int> distribution(1, 200); // задаем диапазон значений

// Определение структуры элемента списка
struct Node {
    int data;        // Данные элемента списка
    Node* next;      // Указатель на следующий элемент списка
    Node* prev;      // Указатель на предыдущий элемент списка
};

// Функция для создания нового элемента списка
Node* createNode(int data) {
    Node* newNode = new Node;
    newNode->data = data;
    newNode->next = nullptr;
    newNode->prev = nullptr;
    return newNode;
}

// Функция для добавления элемента в начало списка
void addToBeginning(Node*& head, int data) {
    Node* newNode = createNode(data);

    if (head == nullptr) {
        head = newNode;
    }
    else {
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }
}

// Функция для добавления элемента в конец списка
void addToEnd(Node*& head, int data) {
    Node* newNode = createNode(data);

    if (head == nullptr) {
        head = newNode;
    }
    else {
        Node* last = head;
        while (last->next != nullptr) {
            last = last->next;
        }
        last->next = newNode;
        newNode->prev = last;
    }
}

// Функция для просмотра списка с начала
void printListFromBeginning(Node* head) {
    std::cout << "List from beginning: ";
    while (head != nullptr) {
        std::cout << head->data << " ";
        head = head->next;
    }
    std::cout << std::endl;
}

// Функция для просмотра списка с конца
void printListFromEnd(Node* head) {
    std::cout << "List from end: ";
    Node* last = head;
    while (last->next != nullptr) {
        last = last->next;
    }
    while (last != nullptr) {
        std::cout << last->data << " ";
        last = last->prev;
    }
    std::cout << std::endl;
}

// функция выводит разделитель
void printSeparator() {
    std::cout << "====================" << std::endl;
}

// функция выводит среднее значение
void printAvarage(int avarage) {
    std::cout << "Avarage value: " << avarage << std::endl;
}

// Получение среднего арифметического элементов списка
int getAverage(Node* head) {
    int sum = 0;
    int count = 0;
    Node* current = head;

    while (current != nullptr) {
        sum += current->data;
        count++;
        current = current->next;
    }

    if (count == 0) {
        return 0;
    }

    return sum / count;
}

// функция генерирует случайное число (-100, 100)
int getRandomNumber() {
    return distribution(generator) - 100;
}

// Функция для замены всех четных элементов списка на заданное значение
void replaceEven(Node* head, int value) {
    Node* current = head;

    while (current != nullptr) {
        if (current->data % 2 == 0) {
            current->data = value;
        }
        current = current->next;
    }
}


// функция реализует задачу
void doTask() {
    Node* head = nullptr;

    for (int i = 0; i < 10; i++) {
        addToEnd(head, getRandomNumber());
    }

    // Вывод списка до изменений
    printListFromBeginning(head);

    // Вычисление среднего арифметического и замена всех четных элементов
    int average = getAverage(head);
    printAvarage(average);
    replaceEven(head, average);

    // Вывод списка после изменений
    printListFromBeginning(head);
}

void doExample() {
    Node* head = nullptr;

    addToBeginning(head, 1);
    addToEnd(head, 2);
    addToEnd(head, 3);
    addToBeginning(head, 0);

    printListFromBeginning(head);
    printListFromEnd(head);
}

int main() {
    doExample();
    printSeparator();
    doTask();

    return 0;
}
