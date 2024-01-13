//
//  main.cpp
//  3.6_using.an.integrated.debugger_stepping
//
//  Created by εκλεγμένοι εν Χριστώ on 9/10/22.
//

/*
 Debugger: program, allows the programmer to control how
 another program executes, examine the program state while
 that program is running. helps immensely in tracking down
 semantic errors
 
 Tip
 Debugger keyboard shortcuts will only work if the
 IDE/integrated debugger is the active window.
 Tip
 Don’t neglect learning to use a debugger. As your programs
 get more complicated, the amount of time you spend
 learning to use the integrated debugger effectively
 will pale in comparison to amount of time you save
 finding and fixing issues.
 
 Stepping: set of related debugger features that lets
 execute code statement by statement
 
 Step into: command executes the next statement in the normal
 execution path of the program
 
 Step over: step into will enter function calls and execute
 them line by line, step over will execute an entire function
 without stopping and return control to you after the
 function has been executed. Step over provides a convenient
 way to skip functions when you are sure they already
 work or are not interested in debugging them right now.
 
 Step out: it executes all remaining code in the function
 currently being executed, then returns control to you when
 the function has returned. It is useful when you’ve
 accidentally stepped into a function that you don’t
 want to debug.
 
 Step back: rewind the last step, so you can return the
 program to a prior state.
 */

#include <iostream>

void print(int x)
{
    std::cout << x << '\n';
}

int main()
{
    print(2);
    return EXIT_SUCCESS;
}
