//
//  main.cpp
//  7.3_common.if.statement.problems
//
//  Created by εκλεγμένοι εν Χριστώ on 12/13/22.
//

/*
 less nested code : is less error prone
 
 Nested if statements can often be flattened by either restructuring the logic or by
 using logical operators
 
 Null statements : an expression statement that consists of just a semicolon.
 example : if (x > 10)
                ; - this is a null statement, consists of just a semicolon
 
 null statements : do nothing
 null statements : typically used when the language requires a statement to exist but
 the programmer doesn't need one.
 null statements : typically placed on their own lines for readability
 
 null statements : can unintentionally cause problems for new programmers as in the
 below example,
 e.g. if (nuclear_codes_activated());
            blow_up_the_world();
 
 an accidental semicolon on the end of if statement, the blow_up_the_world() always
 executes because if statement is terminated with semicolon already
 
 warning : careful not to terminate the if statement with a semicolon, otherwise
 conditional statements will execute unconditionally(even if they are inside a block)
 
 operator== vs operator= inside the conditional:
 inside the conditional operator== is used for equality and not operator=(this is
 assignment operator)
 */

#include <iostream>

int main()
{
    std::cout << "Enter a number: ";
    int num{};
    std::cin >> num;
    
    /// nested if statements
    if (num >= 0)
        if (num <= 20)
            std::cout << num << " is between 0 and 20." << '\n';
    /// dangling else, which if statement does this else belong to?
    else
        std::cout << num << " is negative." << '\n';
    
    /// solution to dangling else:
    /// it is a good idea to enclose the inner if statement within a block
    /// this allows to attach an else to either if statement without ambiguity
    if (num >= 0)
    {
        if (num <= 20)
            std::cout << num << " is between 0 and 20." << '\n';
        else    /// attached to inner if statement
            std::cout << num << " is greater than 20." << '\n';
    }
    else        /// attached to outer if statement because of the { } block
        std::cout << num << " is negative." << '\n';
    
    /// flattening nested if statement
    if (num < 0)
        std::cout << num << " is negative." << '\n';
    else if (num <= 20)
        std::cout << num << " is between 0 and 20." << '\n';
    else
        std::cout << num << " is greater than 20." << '\n';
    
    /// using logical operators to check multiple conditions within a single if statement and else if statement
    if (num >= 0 && num <= 20)
        std::cout << num << " is between 0 and 20" << '\n';
    else if (num < 0 || num > 20)
        std::cout << num << " is negative or greater than 20." << '\n';
    
    std::cout << "Enter 0 or 1: ";
    int y{};
    std::cin >> y;
    
    /// error: wrong output
    /// this evaluates to 0 and 0 is boolean false, so else statement will always execute
    if (y = 0)
        std::cout << "You entered 0" << '\n';
    else
        std::cout << "You entered 1" << '\n';
    
    return 0;
}
