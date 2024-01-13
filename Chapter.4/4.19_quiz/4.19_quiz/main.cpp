//
//  main.cpp
//  4.19_quiz
//
//  Created by εκλεγμένοι εν Χριστώ on 10/11/22.
//

#include <iostream>

double user_input()
{
    std::cout << "Enter a double value: ";
    double input{};
    std::cin >> input;
    
    return input;
}

char symbol()
{
    std::cout << "Enter one of the following: +, -, *, or /: ";
    char symbol{};
    std::cin >> symbol;
    
    return symbol;
}

void calculate_print(double num1, double num2, char symbol)
{
    if (symbol == '+')
    {
        std::cout << num1 << " + " << num2 << " is " << num1 + num2 << '\n';
    }
    else if (symbol == '-')
    {
        std::cout << num1 << " - " << num2 << " is " << num1 - num2 << '\n';
    }
    else if (symbol == '*')
    {
        std::cout << num1 << " * " << num2 << " is " << num1 * num2 << '\n';
    }
    else if (symbol == '/')
    {
        std::cout << num1 << " / " << num2 << " is " << num1 / num2 << '\n';
    }
}

int main()
{
    double number1{user_input()};
    double number2{user_input()};
    
    char operation{symbol()};
    
    calculate_print(number1, number2, operation);
    
    return 0;
}
