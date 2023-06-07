#include <iostream>
#include <random>
#include <ctime> 

std::mt19937 generator(time(0)); // �������������� ��������� ��������� �����
std::uniform_int_distribution<int> distribution(1, 200); // ������ �������� ��������

struct Node {
    int data;
    Node* next;
};

Node* createNode(int data) {
    Node* newNode = new Node;
    newNode->data = data;
    newNode->next = nullptr;
    return newNode;
}

void push(Node*& top, int data) {
    Node* newNode = createNode(data);
    newNode->next = top;
    top = newNode;
}

int pop(Node*& top) {
    if (top == nullptr) {
        throw std::runtime_error("Stack is empty");
    }
    int data = top->data;
    Node* temp = top;
    top = top->next;
    delete temp;
    return data;
}

void printList(Node* head) {
    Node* current = head;
    while (current != nullptr) {
        std::cout << current->data << " ";
        current = current->next;
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

bool isEmpty(Node* head) {
    return head == nullptr;
}

// ���������� ���������
void sortStack(Node*& head) {
    if (isEmpty(head)) {
        // ���� ����, ������ �� ������
        return;
    }

    bool swapped = true;

    while (swapped) {
        swapped = false;

        Node* current = head;
        while (current->next != nullptr) {
            if (current->data > current->next->data) {
                // ������ ������� �������� ���� �������� ���������
                int temp = current->data;
                current->data = current->next->data;
                current->next->data = temp;
                swapped = true;
            }
            current = current->next;
        }
    }
}

// ��������� �������� ��������������� ��������� ������
int getAverage(Node* head) {
    int sum = 0.0;
    int count = 0;
    Node* current = head;
    while (current != NULL) {
        sum += current->data;
        current = current->next;
        count++;
    }
    return sum / count;
}

// ������� ���������� ��������� ����� (-100, 100)
int getRandomNumber() {
    return distribution(generator) - 100;
}

// ������ ������ ��������� ������ �� ������� ��������������
void replaceEvenWithAverage(Node* head) {
    int average = getAverage(head);
    Node* current = head;
    while (current != NULL) {
        if (current->data % 2 == 0) {
            current->data = average;
        }
        current = current->next;
    }
}

void doExample() {
    Node* top = nullptr;

    // ���������� ��������� � ����
    push(top, 5);
    push(top, 3);
    push(top, 8);
    push(top, 1);
    push(top, 2);

    // ����� ��������� ����� �� ����������
    std::cout << "Stack before sorting: " << std::endl;
    printList(top);

    // ���������� �����
    sortStack(top);

    // ����� ��������� ����� ����� ����������
    std::cout << "Stack after sorting: " << std::endl;
    printList(top);

    // �������� ��������� �� �����
    std::cout << "Get first value: " << std::endl;
    int value = pop(top);
    std::cout << "Value: " << value << std::endl;
    std::cout << "Stack after popping: " << std::endl;
    printList(top);
}

void doTask() {
    Node* head = nullptr;

    for (int i = 0; i < 10; i++) {
        push(head, getRandomNumber());
    }

    // ����� ������ �� ���������
    printList(head);

    // ���������� �������� ��������������� � ������ ���� ������ ���������
    int average = getAverage(head);
    printAvarage(average);
    replaceEvenWithAverage(head);

    // ����� ������ ����� ���������
    printList(head);
}

int main() {
    doExample();
    printSeparator();
    doTask();

    return 0;
}
