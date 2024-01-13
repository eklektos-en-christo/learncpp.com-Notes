//
//  main.cpp
//  7.2_if.statements.and.blocks
//
//  Created by εκλεγμένοι εν Χριστώ on 12/13/22.
//

/*
 Conditional statement : that specifies whether some associated
 statements should be executed or not
 
 two basic kind of conditionals supported by CPP : if statements and switch statements
 
 if statement:
 syntax -   if (condition)
                true_statement;
 or with an optional else statement
 
            if (condition)
                true_statement;
            else
                false_statement;
 
 if the condition evaluates to true, the true_statement executes, if condition
 evaluates to false and the else statement(optional) exists, then false_statement
 executes.
 
 blocks : are treated as a single statement
 
 best practice : consider putting single statements associated with an if or else in
 blocks.
 
 a middle ground alternative is to put single-lines on the same as the if or else
 e.g.   if (age>=21) purchase_beer();
 at some minor cost to readability.
 
 Implicit blocks : if the programmer does not declare a block in the statement portion
 of an if or else statement, the compiler will implicitly declare one, most of the
 time, this doesn't matter.
 
 e.g.
        if (condition)
            true_statement;
        else
            false_statement;
 
 is actually equivalent of -
        
        if (condition)
        {
            true_statement;
        }
        else
        {
            false_statement;
        }
 */

#include <iostream>

int main()
{
    std::cout << "Enter a number: ";
    int num{};
    std::cin >> num;
    
    /// using IF statement with else to execute the code if the condition is true
    /// if condition is false, then else
    /// executes
    if (num > 10)
        std::cout << num << " is greater than 10." << '\n';
    else
        std::cout << num << " is less than 10." << '\n';
    
    std::cout << "Enter your height(in cm): ";
    int height{};
    std::cin >> height;
    
    /// using else statement with multiple conditional statements
    /// both statements inside else executes as a single statement
    /// because of the block {} which is enclosing them both
    if (height > 140)
        std::cout << "You are tall enough to ride." << '\n';
    else
    {
        std::cout << "You are not tall enough to ride." << '\n';
        std::cout << "That's bad!" << '\n';
    }
    
    if (true)
        int x{2};   /// x is destroyed here, because implicitly IF is IF{ }, so x has block scope
    else
        int x{200}; /// y is destroyed here, because of the block, y also has block scope
    
    /// error : x is destroyed when the if or else block ends
    /// x is not in the scope here
    /// x doesn't exist here
//    std::cout << x << '\n';
    
    return 0;
}
