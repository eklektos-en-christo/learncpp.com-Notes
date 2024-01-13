//
//  main.cpp
//  3.9_using.an.integerated.debugger_the.call.stack
//
//  Created by εκλεγμένοι εν Χριστώ on 9/11/22.
//

/*
 call stack: list of all the active functions that have been
 called to get to the current point of execution
 includes an entry for each function called, as well as which
 line of code will be returned to when the function
 returns. Whenever a new function is called, that
 function is added to the top of the call stack. When
 the current function returns to the caller, it is
 removed from the top of the call stack, and control
 returns to the function just below it.
 
 call stack window: debugger window that shows the current
 call stack
 Tip

 The line numbers after the function names show the next line to be executed in each function.

 Since the top entry on the call stack represents the currently executing function, the line number here shows the next line that will execute when execution resumes. The remaining entries in the call stack represent functions that will be returned to at some point, so the line number for these represent the next statement that will execute after the function is returned to.
 */

#include <iostream>

void a()
{

}

void b()
{
    a();
}

int main()
{
    a();
    b();
    return EXIT_SUCCESS;
}
