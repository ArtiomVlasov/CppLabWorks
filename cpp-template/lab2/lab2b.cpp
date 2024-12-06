#include "hashMap.hpp"
#include <iostream>

int main()
{
    HashMap<std::string, std::string> student;

    student["first_name"] = "Ivan";
    student["last_name"] = "Petrov";
    student["university"] = "NSU";
    student["department"] = "FIT";
    student["group"] = "23205";

    // std::cout << "Name: " << student["first_name"] << " " << student["last_name"] << std::endl;
    // std::cout << "University: " << student["university"] << std::endl;
    // std::cout << "Department: " << student["department"] << std::endl;
    // std::cout << "Group: " << student["group"] << std::endl;

    // выводит все пары в мэпе student в формате "ключ: значение"
    for (auto it = student.begin(); it != student.end(); ++it)
    {
        std::cout << it->key << ": " << it->value << "\n";
    }
    return 0;
}
