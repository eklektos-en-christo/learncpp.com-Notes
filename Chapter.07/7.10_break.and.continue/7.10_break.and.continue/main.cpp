//
//  main.cpp
//  7.10_break.and.continue
//
//  Created by εκλεγμένοι εν Χριστώ on 1/11/23.
//

/*
 Break : causes a while loop, for loop, do while loop or switch
 statement to end, but execution continues with the next statement after the loop or
 switch statement
 
 Breaking a switch : in switch statement break is typically used to indicate that the case
 is finished, this prevents fall-through into subsequent cases
 
 Breaking a loop : break is used to end the loop early, but execution continues with the
 next statement after the end of the loop
 
 break : is also a common way to get out of an intentional infinite loop
 
 Break vs Return :
 break : terminates the switch/loop, execution continues at first statement beyond the loop
 return : terminates the entire function that the loop is within, execution continues at
 point where the function was called.
 
 Continue : provides a convenient way to end the current iteration of a loop without
 terminating the entire loop
 
 continue statements : cause the current point of execution to jump to the bottom of the
 current loop
 
 for loop : the end-statement of the loop still executes after a continue statement, because
 this happens after the end of the loop body
 
 continue with while/do-while loops : these loops typically change the value of the variable
 used in the condition inside the loop body and if the continue skip the lines where
 variable is incremented then the loop can become infinite
 so best is to use for loop if there is an obvious counter variable available
 
 debate over the use of break and continue:
 break and continue can help make loops more readable by keeping the number of nested blocks
 down and reducing the need for complicated looping logic
 
 Best practice
 Use break and continue when they simplify your loop logic.

 debate over the use of early returns:
 early returns : return statement that is not the last statement in the function
 
 Best practice
 Use early returns when they simplify your function’s logic.
 */

#include <iostream>

/// break is preventing here the fall-through into subsequent cases
void break_switch(int x, int y, char c)
{
    switch(c)
    {
        case '+':
            std::cout << x << '+' << y << ':' << x + y << '\n';
            break;
        case '-':
            std::cout << x << '-' << y << ':' << x - y << '\n';
            break;
        case '*':
            std::cout << x << '*' << y << ':' << x * y << '\n';
            break;
        case '/':
            std::cout << x << '/' << y << ':' << x / y << '\n';
            break;
    }
}

/// using break to terminate the for loop early if user enters 0
void break_loop()
{
    int sum{0};
    
    for (int count{0}; count < 10; ++count)
    {
        std::cout << "Enter a number to add, or 0 to exit: ";
        int num{};
        std::cin >> num;
        
        if (num == 0)
            break;
        sum += num;
    }
    
    std::cout << "Total sum: " << sum << '\n';
}

void break_intent_infinite_loop()
{
    while (true)
    {
        std::cout << "Enter 0 to exit or any other integer to continue: ";
        int num{};
        std::cin >> num;
        
        if (num == 0)
            break;
    }
    
    std::cout << "We're out of Infinite loop, finally!" << '\n';
}

int break_or_return()
{
    /// infinite while loop
    while (true)
    {
        std::cout << "Enter 'b' to break or 'r' to return: ";
        char ch{};
        std::cin >> ch;
        
        if (ch == 'b')
            break;
        
        /// return will cause function to immediately return to the caller, which is main( ) in this case
        if (ch == 'r')
        {
            std::cout << "'r' entered, function returns ";
            return 1;
        }
    }
    
    /// break will cause the execution to resume from here
    std::cout << "'b' entered, function returns ";
    return 0;
}

/// prints all the numbers from 0 to 9 that aren't divisible by 4
/// continue will skip the current iteration if the condition evaluates to true
void continue_stat()
{
    for (int count{0}; count < 10; ++count)
    {
        /// continue will cause the current point of execution to jump to the bottom of the for loop
        if ((count % 4) == 0)
            continue;
        std::cout << count << ' ';
        
        /// the continue statement jumps to here
    }
    
    std::cout << '\n';
}

void continue_with_while_dowhile()
{
    int count{0};
    
    while (count < 10)
    {
        /// continue will cause the current point of execution to jump to the bottom of the while loop
        if (count == 5)
            continue;
        std::cout << count << ' ';
        
        /// this won't be incremented ever
        ++count;
        /// the continue statement jumps to here
    }
    std::cout << '\n';
}

/// counts how many times the loop iterates
void injudicious_break_continue()
{
    int count{0};
    /// controls whether the loop ends or not
    bool keep_looping{true};
    
    while (keep_looping)
    {
        std::cout << "Enter 'e' to exit, any other character to continue: ";
        char c{};
        std::cin >> c;
        
        if (c == 'e')
            keep_looping = false;
        else
        {
            ++count;
            std::cout << "This loop iterated " << count << " times" << '\n';
        }
    }
    
    std::cout << '\n';
}

/// loops until user terminates
/// no use of boolean variable, else statement and a nested block
/// this improves code comprehensibility
void judicious_break_continue()
{
    int count{0};
    
    while (true)
    {
        std::cout << "Enter 'e' to exit, any other character to continue: ";
        char c{};
        std::cin >> c;
        
        if (c == 'e')
            break;
        
        ++count;
        std::cout << "This loop iterated " << count << " times" << '\n';
    }
    
    std::cout << '\n';
}

int main()
{
    break_switch(2, 2, '+');
    break_switch(22, 2, '-');
    break_switch(22, 2, '*');
    break_switch(223, 33, '/');
    
    break_loop();
    break_intent_infinite_loop();
    
    int return_val(break_or_return());
    std::cout << return_val << '\n';
    
    continue_stat();
    
//    continue_with_while_dowhile();
    
    injudicious_break_continue();
    judicious_break_continue();
    
    return 0;
}
