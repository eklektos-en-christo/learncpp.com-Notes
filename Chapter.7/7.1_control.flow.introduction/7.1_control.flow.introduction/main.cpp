//
//  main.cpp
//  7.1_control.flow.introduction
//
//  Created by εκλεγμένοι εν Χριστώ on 12/12/22.
//

/*
 
 CPU : execute statements in sequential order by default
 
 CPU : begins execution at the top of main(), program terminates at the end of the
 main().
 
 Program's Execution path/path : the specific sequence of statements that the CPU
 executes
 
 straight line programs : take the same path(execute the same statements in the same
 order everytime they are run.
 
 control flow/flow control statements : that allow the programmer to change the normal
 path of execution through the program, the common example is the IF statement
 
 Branching : when a control flow statement causes point of execution to change to
 a non-sequential statement
 
 +-----------------------------------------------------------------------------------+
 Category                |   Meaning
 +-----------------------------------------------------------------------------------+
 conditional statements  |  cause a sequence of code to execute only if some condition
                         |  is met
                         |
 Jumps                   |  tell the CPU to start executing the statements at some
                         |  other location
                         |
 function calls          |  these are jumps to some other location and block
                         |
 loops                   |  tell the program to repeatedly execute some sequence of
                         |  code zero or more times, until some condition is met
                         |
 halts                   |  tell the program to quit running
                         |
 exceptions              |  special kind of flow control struture designed for error
                         |  handling
 +-----------------------------------------------------------------------------------+
 */

#include <iostream>

int main()
{
    /// example of a straight line program
    std::cout << "Enter an integer: ";
    
    int x{};
    std::cin >> x;
    
    std::cout << "You entered " << x << '\n';
    
    return 0;
}
