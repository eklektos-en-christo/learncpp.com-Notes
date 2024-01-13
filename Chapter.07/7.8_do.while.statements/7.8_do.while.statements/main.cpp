//
//  main.cpp
//  7.8_do.while.statements
//
//  Created by εκλεγμένοι εν Χριστώ on 12/31/22.
//

/*
 while loop : evaluates the condition upfront
 
 do while statements :
 
 syntax :   do
                statement; // single or a compound statement
            while (condition);
 
 do while : looping construct, works just like a while loop except the statement always
 executes at least once
 
 do while : checks the condition after the statement has been executed, if it evaluates
 to true the path of execution jumps back to the top of the do while loop and executes it
 again.
 
 best practice : favor while loop over do-while loop when given an equal choice
 */

#include <iostream>

void do_while_loop()
{
    int selection{};
    
    do
    {
        std::cout << "1. ADD\n2. SUB\n3. MUL\n4. DIV\n\n";
        std::cout << "Make a selection: ";
        std::cin >> selection;
    }
    while (selection != 1 && selection != 2 && selection != 3 && selection != 4);
    
    std::cout << "\nYou selected: " << selection << '\n';
}

int main()
{
    do_while_loop();
    
    return 0;
}
