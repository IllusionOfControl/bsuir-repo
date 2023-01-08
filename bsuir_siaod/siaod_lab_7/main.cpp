#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>


struct Stack
{
    char data;
    struct Stack* next;
};


// получаем приоритет токена
int GetTokenPriority(char token) {
    switch (token) {
    case '^': return 4;
    case '*': return 3;
    case '/': return 3;
    case '-': return 2;
    case '+': return 2;
    case '(': return 1;
    default: return 0;
    }
}


// добавляем элемент в стек
struct Stack* AddElementToStack(struct Stack* p, char data)
{
    struct Stack* element;
    element = (struct Stack*)malloc(sizeof(struct Stack));
    element->data = data;
    element->next = p;
    return element;
}


// добавляем элемент в список
void AddElementToList(struct Stack* p, char data)
{
    struct Stack* element;
    element = (struct Stack*)malloc(sizeof(struct Stack));
    element->next = NULL;
    element->data = data;
    // Если элемент первый
    if ((p->data == '|') || (p->data == NULL)) {
        p->data = data;
        p->next = NULL;
    }
    else {
        // итерируемся до конца
        while (p->next != NULL) {
            p = p->next;
        }
        p->next = element;
    }
}


// вывод стека в консоль
void PrintStack(struct Stack* p)
{
    while (p != NULL) {
        if (p->data != '|') std::cout << p->data;
        p = p->next;
    }
    std::cout << std::endl;
}


// удалить элемент стека
struct Stack* DeleteStackElement(struct Stack* s)
{
    struct Stack* element;
    // Если конец списка
    if (s->next == NULL) {
        s->data = '|';
        return s;
    }
    else {
        element = s->next;
        free(s);
        return element;
    }
}


// получам постфикс форму
struct Stack* GetPostfixForm(std::string* expression)
{
    struct Stack* list = (struct Stack*)malloc(sizeof(struct Stack));
    list->data = '|';
    list->next = NULL;

    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->data = '|';
    stack->next = NULL;


    // Magic
    for (int i = 0; i < expression->size(); i++) {
        char token = expression->at(i);

        if (token >= 'a' && token <= 'z') {
            AddElementToList(list, token);
        }
        else if (GetTokenPriority(token) == 1) {
            stack = AddElementToStack(stack, token);
        }
        else if ((GetTokenPriority(token) != 0) && (GetTokenPriority(token) != 1)) {
            if ((GetTokenPriority(stack->data) < GetTokenPriority(token)) || (stack->next == NULL)) {
                stack = AddElementToStack(stack, token);
            }
            else {
                while ((GetTokenPriority(stack->data)) >= (GetTokenPriority(token))) {
                    AddElementToList(list, stack->data);
                    stack = DeleteStackElement(stack);
                }
                stack = AddElementToStack(stack, token);
            }
        }
        if (token == ')') {
            while (stack->data != '(')
            {
                AddElementToList(list, stack->data);
                stack = DeleteStackElement(stack);
            }
            stack = DeleteStackElement(stack);
        }
    }

    while (stack->next != NULL)
    {
        AddElementToList(list, stack->data);
        stack = DeleteStackElement(stack);
    }

    return list;
}


// получам префикс форму
struct Stack* GetPrefixForm(std::string* expression)
{
    struct Stack* list = (struct Stack*)malloc(sizeof(struct Stack));
    list->data = '|';
    list->next = NULL;

    struct Stack* s;
    s = (struct Stack*)malloc(sizeof(struct Stack));
    s->data = '|';
    s->next = NULL;

    std::string* reversed_expression = new std::string();

    // переворачиваем выражение
    for (int i = expression->size() - 1; i >= 0; i--) {
        char token = expression->at(i);
        if (token == '(')
            reversed_expression->push_back(')');
        else if (token == ')')
            reversed_expression->push_back('(');
        else reversed_expression->push_back(token);
    }

    
    list = GetPostfixForm(reversed_expression);

    while (list != NULL) {
        s = AddElementToStack(s, list->data);
        list = list->next;
    }

    return s;
}


int main() {
    struct Stack* head;

    std::string* expression = new std::string();
    std::cout << "Enter the expression:" << std::endl;
    std::cin >> *expression;

    std::cout << "Postfix form:" << std::endl;
    head = GetPostfixForm(expression);
    PrintStack(head);

    std::cout << "Prefix form:" << std::endl;
    head = GetPrefixForm(expression);

    PrintStack(head);

    return 0;
}
