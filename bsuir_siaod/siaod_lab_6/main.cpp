#include <iostream>
#include <string>
#include <vector>


struct Node {
    char* value;
    int priority;
    Node* next;

    Node(char* _value, int _priority) : value(_value), priority(_priority), next(nullptr) {}
};


class Queue {
    Node* _root_node;

public:
    Queue() : _root_node(nullptr) {}

    // получение предыдущего элемента
    Node* GetPrevious(struct Node* node) {
        while (node) {
            if (node == _root_node) return nullptr;
            if (node->next == _root_node) return node;
            node = node->next;
        }
        return node;
    }

    // получение приоритета изходя из значения char
    int GetPriority(char* value) {
        return *value - 97;
    }

    // добавление элемента
    void AddElement(char* value) {
        // если пустой корень, то создаём
        if (_root_node == nullptr) {
            _root_node = new Node(value, GetPriority(value));
        }
        else {
            // создаём новый элемент
            Node* new_node = new Node(value, GetPriority(value));
            Node* head = _root_node;
            while (_root_node != NULL) {
                // сравнение приоритетов
                if (GetPriority(value) <= _root_node->priority) {
                    if (GetPrevious(head) != nullptr) {
                        new_node->next = _root_node;
                        GetPrevious(head)->next = new_node;
                    }
                    else {
                        new_node->next = _root_node;
                        head = new_node;
                    }
                    break;
                }
                // иначе в конец
                if (_root_node->next == nullptr) {
                    _root_node->next = new_node;
                    new_node->next = nullptr;
                    break;
                }
                _root_node = _root_node->next;
            }
            _root_node = head;
        }
    }

    // удаление элемента
    void RemoveElement(char* value) {
        Node* nodeCurrent = _root_node;
        Node* nodePrev = nullptr;
        // итерируемся по списку
        while (nodeCurrent != nullptr) {
            // сравниваем значения
            if (strcmp(nodeCurrent->value, value) == 0) {
                // если истина, заменяем указатели
                if (nodePrev != nullptr) {
                    nodePrev->next = nodeCurrent->next;
                }
                else {
                    _root_node = nodeCurrent->next;
                }
                break;
            }
            nodePrev = nodeCurrent;
            nodeCurrent = nodeCurrent->next;
        }
    }
    
    // проверка на существование
    bool IsExists(char* value) {
        Node* nodeCurrent = _root_node;
        // итерация
        while (nodeCurrent != nullptr) {
            // сраавнение значений
            if (strcmp(nodeCurrent->value, value) == 0) {
                return true;
            }
            nodeCurrent = nodeCurrent->next;
        }
        return false;
    }

    // вывод в консоль
    void PrintQueue() {
        Node* newNode = _root_node;
        while (newNode != nullptr) {
            std::cout << newNode->value << " ";
            newNode = newNode->next;
        }
        std::cout << std::endl;
    }

};


int main() {
    Queue queue;

    char value_1[] = "b";
    char value_2[] = "d";
    char value_3[] = "a";
    char value_4[] = "f";
    char value_5[] = "h";
    char value_6[] = "s";

    // добавляем элементы
    queue.AddElement(value_1);
    queue.AddElement(value_2);
    queue.AddElement(value_3);
    queue.AddElement(value_4);
    queue.AddElement(value_5);
    queue.AddElement(value_6);

    // выводим элементы
    queue.PrintQueue();

    // удаляем элемент
    queue.RemoveElement(value_5);
    queue.PrintQueue();

    // поиск элемента "a"
    std::cout << std::boolalpha << queue.IsExists(value_3) << std::endl;
    return 0;
}
