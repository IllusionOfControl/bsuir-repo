#include <iostream>
#include <string>
#include <stack>
#include <sstream>

// функция для проверки, является ли символ оператором
bool isOperator(char ch) {
    return ch == '+' || ch == '-' || ch == '*' || ch == '/';
}

bool isOperator(const std::string& s) {
    if (s.length() != 1) return false;
    return s == "+" || s == "-" || s == "*" || s == "/";
}


// функция для проверки, является ли срока числом
bool isdigit(const std::string& s)
{
    try
    {
        std::stod(s);
    }
    catch (...)
    {
        return false;
    }
    return true;
}

// функция для получения приоритета оператора
int getPriority(char op) {
    if (op == '+' || op == '-') {
        return 1;
    }
    else if (op == '*' || op == '/') {
        return 2;
    }
    else {
        return 0;
    }
}

// функция для преобразования инфиксного выражения в ОПЗ
std::string infixToPostfix(std::string infix) {
    std::stack<char> opStack;
    std::string postfix = "";

    for (char ch : infix) {
        // если символ является цифрой или буквой, добавляем его в ОПЗ
        if (isalnum(ch) || ch == '.') {
            postfix += ch;
        }
        // если символ является оператором, добавляем его в стек
        else if (isOperator(ch)) {
            postfix += " ";
            // удаляем из стека все операторы с более высоким или равным приоритетом
            while (!opStack.empty() && getPriority(opStack.top()) >= getPriority(ch)) {
                postfix += opStack.top();
                opStack.pop();
            }
            opStack.push(ch);
        }
        // если символ является открывающей скобкой, добавляем его в стек
        else if (ch == '(') {
            opStack.push(ch);
        }
        // если символ является закрывающей скобкой, удаляем из стека все операторы
        // до открывающей скобки и добавляем их в ОПЗ
        else if (ch == ')') {
            while (!opStack.empty() && opStack.top() != '(') {
                postfix += " ";
                postfix += opStack.top();
                opStack.pop();
            }
            if (!opStack.empty() && opStack.top() == '(') {
                opStack.pop();
            }
        }
    }

    // добавляем оставшиеся операторы из стека в ОПЗ
    while (!opStack.empty()) {
        postfix += " ";
        postfix += opStack.top();
        opStack.pop();
    }

    return postfix;
}

// функция для вычисления значения ОПЗ
double evaluatePostfix(std::string postfix) {
    std::stack<double> operandStack;
    std::istringstream f(postfix);
    std::string element;
    // разбиваем строку по пробелам
    while (std::getline(f, element, ' ')) {
        // если символ является цифрой или буквой, добавляем его в стек операндов
        if (isdigit(element)) {
            operandStack.push(std::atof(element.c_str()));
        }
        // если символ является оператором, применяем его к двум последним операндам из стека
        else if (isOperator(element)) {
            double operand2 = operandStack.top();
            operandStack.pop();
            double operand1 = operandStack.top();
            operandStack.pop();

            switch (element[0]) {
            case '+':
                operandStack.push(operand1 + operand2);
                break;
            case '-':
                operandStack.push(operand1 - operand2);
                break;
            case '*':
                operandStack.push(operand1 * operand2);
                break;
            case '/':
                operandStack.push(operand1 / operand2);
                break;
            }
        }
    }

    return operandStack.top();
}

// функция для удобного ввода выражения и вывода результата
void calculate() {
    setlocale(LC_ALL, "");
    std::string infix;
    std::cout << "Введите выражение: ";
    std::getline(std::cin, infix);
    std::string postfix = infixToPostfix(infix);
    double result = evaluatePostfix(postfix);

    std::cout << "Обратная Польская Запись: " << postfix << std::endl;
    std::cout << "Результат: " << result << std::endl;
}

int main() {
    calculate();
    return 0;
}
