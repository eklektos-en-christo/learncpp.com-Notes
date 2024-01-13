//
//  main.cpp
//  3.7_using.an.integerated.debugger_running.and.breakpoints
//
//  Created by εκλεγμένοι εν Χριστώ on 9/11/22.
//

/*
 Run to cursor: command executes the program until execution
 reaches the statement selected by your cursor. It is an an
 efficient way to start debugging at a particular point in
 your code.
 
 Continue: simply continues running the program as per
 normal, either until the program terminates, or until
 something triggers control to return back to you again
 
 Start: performs the same action as continue, just starting
 from the beginning of the program.It can only be invoked
 when not already in a debug session.
 
 Breakpoints: special marker that tells the debugger to stop
 execution of the program at the breakpoint when running
 in debug mode.
 
 Set next statement: allows us to change the point of
 execution to some other statement (sometimes informally
 called jumping).
 
 Warning

 The set next statement command will change the point of execution, but will not otherwise change the program state. Your variables will retain whatever values they had before the jump. As a result, jumping may cause your program to produce different values, results, or behaviors than it would otherwise. Use this capability judiciously (especially jumping backwards).

 Warning

 You should not use set next statement to change the point of execution to a different function. This will result in undefined behavior, and likely a crash.


 */

#include <iostream>

void print(int n)
{
    std::cout << n << '\n';
}

int main()
{
    print(2);
    print(2);
    print(2);
    
    return EXIT_SUCCESS;
}
