#include <iostream>
#include <string>
#include <stack>
#include <sstream>

// ������� ��� ��������, �������� �� ������ ����������
bool isOperator(char ch) {
    return ch == '+' || ch == '-' || ch == '*' || ch == '/';
}

bool isOperator(const std::string& s) {
    if (s.length() != 1) return false;
    return s == "+" || s == "-" || s == "*" || s == "/";
}


// ������� ��� ��������, �������� �� ����� ������
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

// ������� ��� ��������� ���������� ���������
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

// ������� ��� �������������� ���������� ��������� � ���
std::string infixToPostfix(std::string infix) {
    std::stack<char> opStack;
    std::string postfix = "";

    for (char ch : infix) {
        // ���� ������ �������� ������ ��� ������, ��������� ��� � ���
        if (isalnum(ch) || ch == '.') {
            postfix += ch;
        }
        // ���� ������ �������� ����������, ��������� ��� � ����
        else if (isOperator(ch)) {
            postfix += " ";
            // ������� �� ����� ��� ��������� � ����� ������� ��� ������ �����������
            while (!opStack.empty() && getPriority(opStack.top()) >= getPriority(ch)) {
                postfix += opStack.top();
                opStack.pop();
            }
            opStack.push(ch);
        }
        // ���� ������ �������� ����������� �������, ��������� ��� � ����
        else if (ch == '(') {
            opStack.push(ch);
        }
        // ���� ������ �������� ����������� �������, ������� �� ����� ��� ���������
        // �� ����������� ������ � ��������� �� � ���
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

    // ��������� ���������� ��������� �� ����� � ���
    while (!opStack.empty()) {
        postfix += " ";
        postfix += opStack.top();
        opStack.pop();
    }

    return postfix;
}

// ������� ��� ���������� �������� ���
double evaluatePostfix(std::string postfix) {
    std::stack<double> operandStack;
    std::istringstream f(postfix);
    std::string element;
    // ��������� ������ �� ��������
    while (std::getline(f, element, ' ')) {
        // ���� ������ �������� ������ ��� ������, ��������� ��� � ���� ���������
        if (isdigit(element)) {
            operandStack.push(std::atof(element.c_str()));
        }
        // ���� ������ �������� ����������, ��������� ��� � ���� ��������� ��������� �� �����
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

// ������� ��� �������� ����� ��������� � ������ ����������
void calculate() {
    setlocale(LC_ALL, "");
    std::string infix;
    std::cout << "������� ���������: ";
    std::getline(std::cin, infix);
    std::string postfix = infixToPostfix(infix);
    double result = evaluatePostfix(postfix);

    std::cout << "�������� �������� ������: " << postfix << std::endl;
    std::cout << "���������: " << result << std::endl;
}

int main() {
    calculate();
    return 0;
}
