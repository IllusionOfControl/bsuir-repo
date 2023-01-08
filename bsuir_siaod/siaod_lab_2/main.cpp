#include <iostream>
#include <string>
#include <vector>


// ���������� ��������� ��������
template <typename T>
struct Node {
    T* value;
    Node* next;
};


// ���������� ���������
template <typename T>
class Iterator {
public:
    virtual void First() = 0;
    virtual void Next() = 0;
    virtual bool IsDone() = 0;
    virtual T* CurrentValue() = 0;
};


//
template <typename T>
class List {
private:
    Node<T>* _root_node = { 0 };
public:
    // ���������� ��������
    void Add(T* item) {
        Node<T>* new_node = new Node<T>();
        new_node->value = item;

        // �������� � ���������� �������� � ����
        if (_root_node == nullptr) {
            _root_node = new_node;
            return;
        }

        Node<T>* end_node = _root_node;
        while (end_node->next != NULL) {
            end_node = end_node->next;
        }
        end_node->next = new_node;
    }

    // ��������� ��������� ��������
    Node<T>* First() {
        return _root_node;
    }
};


// �������� ������
template <typename T>
class ListIterator : public Iterator<T> {
private:
    List<T>* _list;
    Node<T>* current_node = {0};
public:
    ListIterator(List<T>* list) : _list(list) {}

    // ����� ���������
    void First() {
        current_node = _list->First();
    }

    // ��������� �������
    void Next() {
        if (current_node != NULL) {
            current_node = current_node->next;
        }
    }

    // �������� �����
    bool IsDone() {
        if (current_node != NULL) return false;
        else return true;
    }

    // ��������� �������� ��������
    T* CurrentValue() {
        return current_node->value;
    }
};


// ����� ������
void print_char_list(List<char>* list) {
    Iterator<char>* iterator = new ListIterator<char>(list);

    std::cout << "[ ";
    for (iterator->First(); !iterator->IsDone(); iterator->Next()) {
        std::cout << *iterator->CurrentValue() << " ";
    }
    std::cout << "]" << std::endl;
}


// ���� ������
void input_char_list(List<char>* list, int lenght) {
    for (int i = 0; i < lenght; i++) {
        char* letter = new char;
        std::cin >> letter;
        list->Add(letter);
    }
}


// ������� �������
void merge_char_lists(List<char>* target, List<char>* source) {
    Iterator<char>* iterator = new ListIterator<char>(source);

    for (iterator->First(); !iterator->IsDone(); iterator->Next()) {
        target->Add(iterator->CurrentValue());
    }
}


int main() {
    List<char>* letter_list_1 = new List<char>;
    List<char>* letter_list_2 = new List<char>;
    List<char>* letter_list_3 = new List<char>;
    List<char>* temp_list_1 = new List<char>;
    List<char>* temp_list_2 = new List<char>;

    int count_letters;

    std::cout << "Enter count of letters:" << std::endl;
    std::cin >> count_letters;

    std::cout << "Enter " << count_letters << " letters to char_list_1:" << std::endl;
    input_char_list(letter_list_1, count_letters);

    std::cout << "Enter " << count_letters << " letters to char_list_2:" << std::endl;
    input_char_list(letter_list_2, count_letters);

    // ���������� �� �������� � ���������
    Iterator<char>* iterator = new ListIterator<char>(letter_list_1);
    for (iterator->First(); !iterator->IsDone(); iterator->Next()) {
        int char_dec = (int) *(iterator->CurrentValue());
        if ((char_dec >= 97) && (char_dec <= 122)) {
            temp_list_1->Add(iterator->CurrentValue());
        }
        else {
            temp_list_2->Add(iterator->CurrentValue());
        }
    }

    iterator = new ListIterator<char>(letter_list_2);
    for (iterator->First(); !iterator->IsDone(); iterator->Next()) {
        int char_dec = (int)*(iterator->CurrentValue());
        if ((char_dec >= 97) && (char_dec <= 122)) {
            temp_list_1->Add(iterator->CurrentValue());
        }
        else {
            temp_list_2->Add(iterator->CurrentValue());
        }
    }

    std::cout << "Content of char_list_1:" << std::endl;
    print_char_list(letter_list_1);

    std::cout << "Content of char_list_2:" << std::endl;
    print_char_list(letter_list_2);

    merge_char_lists(letter_list_3, temp_list_1);
    merge_char_lists(letter_list_3, temp_list_2);
    std::cout << "Merged two lists to char_list_3:" << std::endl;
    print_char_list(letter_list_3);

    return 0;
}