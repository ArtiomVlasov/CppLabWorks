#include "hashMap.hpp"
#include <iostream>

int main()
{
    HashMap student;
    student["first_name"] = "Ivan";
    student["last_name"] = "Petrov";
    student["university"] = "NSU";
    student["department"] = "FIT";
    student["group"] = "23205";
    std::cout << "name" << student["first_name"] << std::endl;
    return 0;
}
