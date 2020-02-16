#include <iostream>

#include "Calculator.h"

int main()
{
    std::string command;
    int count = 10;
    std::cout << "Please, input the command in the following form, for example: ";
    std::cout << "2*15-35.5+7" << std::endl;
    while (count)
    {
        std::cout << "Enter command: ";
        std::cin >> command;
        double result = calculate(command);
        std::cout << "Result: " << result << std::endl;
        count--;
    }

    return 0;
}