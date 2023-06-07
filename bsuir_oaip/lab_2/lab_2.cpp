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

    // ��������� ������ �� ��������
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

    // ��������� ������ �� �����
    while (std::getline(infile, line)) {
        employees.push_back(parseLine(line));
    }
    return employees;
}


// ������� ���������� �� �������� �������
bool compareWorkload(Employee* e1, Employee* e2)
{
    return (e1->workload > e2->workload);
}

int main() {
    // ��������� ������ ����������
    std::vector<Employee*> employees = getEmployeesFromFile("employees.txt");;

    // ������ ������ �������������
    std::set<std::string> departments;

    // ��������� ������ �������������
    for (const auto& employee : employees) {
        departments.insert(employee->department);
    }

    // ���������� ������ ���������� �� �������� �������
    std::sort(employees.begin(), employees.end(), compareWorkload);

    // ������� ���������� �� ������������
    for (const auto& department : departments) {
        std::cout << "Department: " << department << std::endl;

        for (const auto& employee : employees) {
            if (employee->department == department) {
                std::cout << "  " << employee->name << " (" << employee->position << ") - " << employee->workload << " hours" << std::endl;
            }
        }
    }

    // ������� ������ ����������
    for (const auto& employee : employees) {
        delete employee;
    }

    return 0;
}