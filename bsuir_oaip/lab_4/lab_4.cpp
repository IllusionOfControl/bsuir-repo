#include <iostream>
#include <random>
#include <ctime> 

std::mt19937 generator(time(0)); // �������������� ��������� ��������� �����
std::uniform_int_distribution<int> distribution(1, 200); // ������ �������� ��������

// ����������� ��������� �������� ������
struct Node {
    int data;        // ������ �������� ������
    Node* next;      // ��������� �� ��������� ������� ������
    Node* prev;      // ��������� �� ���������� ������� ������
};

// ������� ��� �������� ������ �������� ������
Node* createNode(int data) {
    Node* newNode = new Node;
    newNode->data = data;
    newNode->next = nullptr;
    newNode->prev = nullptr;
    return newNode;
}

// ������� ��� ���������� �������� � ������ ������
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

// ������� ��� ���������� �������� � ����� ������
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

// ������� ��� ��������� ������ � ������
void printListFromBeginning(Node* head) {
    std::cout << "List from beginning: ";
    while (head != nullptr) {
        std::cout << head->data << " ";
        head = head->next;
    }
    std::cout << std::endl;
}

// ������� ��� ��������� ������ � �����
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

// ������� ������� �����������
void printSeparator() {
    std::cout << "====================" << std::endl;
}

// ������� ������� ������� ��������
void printAvarage(int avarage) {
    std::cout << "Avarage value: " << avarage << std::endl;
}

// ��������� �������� ��������������� ��������� ������
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

// ������� ���������� ��������� ����� (-100, 100)
int getRandomNumber() {
    return distribution(generator) - 100;
}

// ������� ��� ������ ���� ������ ��������� ������ �� �������� ��������
void replaceEven(Node* head, int value) {
    Node* current = head;

    while (current != nullptr) {
        if (current->data % 2 == 0) {
            current->data = value;
        }
        current = current->next;
    }
}


// ������� ��������� ������
void doTask() {
    Node* head = nullptr;

    for (int i = 0; i < 10; i++) {
        addToEnd(head, getRandomNumber());
    }

    // ����� ������ �� ���������
    printListFromBeginning(head);

    // ���������� �������� ��������������� � ������ ���� ������ ���������
    int average = getAverage(head);
    printAvarage(average);
    replaceEven(head, average);

    // ����� ������ ����� ���������
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
