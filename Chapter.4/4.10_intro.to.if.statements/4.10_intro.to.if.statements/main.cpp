//
//  main.cpp
//  4.10_intro.to.if.statements
//
//  Created by εκλεγμένοι εν Χριστώ on 9/16/22.
//

/*
 if statement: allows to execute one or more lines of code
 is certain condition is true
 
 syntax:    if (condition) true_statement;
 
 condition: also called conditional expression, evaluated to
 a boolean value
 
 if else statement: if condition evaluated to true the if
 block executes and if false then else block executes
 
 Chaining if statements: to check if several things are true
 or false in sequence
 
 conditional expression: can be a functional call that returns
 a boolean value
 
 Non-Boolean conditionals: non zero values get converted to
 true and 0 converted to false
 */

#include <iostream>

bool is_equal(int a, int b)
{
    return a == b;
}

int main()
{
    std::cout << "Enter an integer: ";
    int integer{};
    std::cin >> integer;
    
    /// if statement
    if (integer == 0)
        std::cout << "The value is zero!" << '\n';
    
    /// if else statement
    if (integer == 0)
        std::cout << "The value is zero!" << '\n';
    else
        std::cout << "The value is non zero!" << '\n';
    
    std::cout << "Enter an integer: ";
    std::cin >> integer;
    
    /// chaining if statements
    if (integer < 0)
        std::cout << "Negative!" << '\n';
    else if (integer > 0)
        std::cout << "Positive!" << '\n';
    else
        std::cout << "Zero!" << '\n';
    
    /// conditional expression as a functional call
    if (is_equal(2, 2))
        std::cout << "Equal!" << '\n';
    else
        std::cout << "Not equal!" << '\n';
    
    /// non boolean conditional: non zero will be converted to boolean true
    /// and zero will be converted to boolean false
    /// conditional below is true, so "hi" will execute
    if (2)
        std::cout << "hi" << '\n';
    else
        std::cout << "bye" << '\n';
    
    return 0;
}
