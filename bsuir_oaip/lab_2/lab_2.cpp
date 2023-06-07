#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>


struct Employee {
    std::string name;
    std::string faculty;
    std::string department;
    std::string position;
    int workload;
};


Employee* parseLine(const std::string line) {
    std::istringstream f(line);
    std::string text;
    std::vector<std::string> columns;

    // разбиваем строку по пробелам
    while (std::getline(f, text, ';')) {
        columns.push_back(text);
    }

    return new Employee{
        columns[0],
        columns[1],
        columns[2],
        columns[3],
        std::atoi(columns[4].c_str())
    };
}


std::vector<Employee*> getEmployeesFromFile(std::string filename) { 
    std::ifstream infile(filename);
    std::string line;
    std::vector<Employee*> employees;

    // считываем строки из файла
    while (std::getline(infile, line)) {
        employees.push_back(parseLine(line));
    }
    return employees;
}


// функция сортировки по рабочему времени
bool compareWorkload(Employee* e1, Employee* e2)
{
    return (e1->workload > e2->workload);
}

int main() {
    // Загружаем список работников
    std::vector<Employee*> employees = getEmployeesFromFile("employees.txt");;

    // создаём список департаментов
    std::set<std::string> departments;

    // заполняем список департаментов
    for (const auto& employee : employees) {
        departments.insert(employee->department);
    }

    // сортировка данных работников по рабочему времени
    std::sort(employees.begin(), employees.end(), compareWorkload);

    // выводим работников по департаменту
    for (const auto& department : departments) {
        std::cout << "Department: " << department << std::endl;

        for (const auto& employee : employees) {
            if (employee->department == department) {
                std::cout << "  " << employee->name << " (" << employee->position << ") - " << employee->workload << " hours" << std::endl;
            }
        }
    }

    // очистка списка работников
    for (const auto& employee : employees) {
        delete employee;
    }

    return 0;
}