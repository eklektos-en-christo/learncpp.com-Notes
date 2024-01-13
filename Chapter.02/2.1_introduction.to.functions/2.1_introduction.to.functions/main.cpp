//
//  main.cpp
//  2.1_introduction.to.functions
//
//  Created by Judah's Leon on 8/25/22.
//

/*
 function : reusable sequence of statements designed to do a particular job
 
 main function : putting all code inside main becomes hard to manage
 
 functions : provide a way to split the program into small chunks that are easier to
 organize, test and use
 
 user-defined functions : written by the user
 
 function call : expression that tells the CPU to interrupt the current function and
 execute another function.
 
 caller : function which initiates the function call
 callee/called : the function being called
 
 Warning
 Don’t forget to include parentheses () after the function’s name when making a
 function call.
 
 nested function are not supported : functions inside functions
 
 metasyntactic variables : placeholder names for variables and functions, three letter
 words end in "oo"
 example : bar, baz, goo, foo, moo, boo etc
 */

#include <iostream>

/// function header below : void user_defined_function( ) - tells compiler we are defining a function
/// ( ) - tells the compiler that it is a function
/// user_defined_function : identifier or name of the function
/// void - return type of the function
/// { } - called function body, in it the sequence of statements resides that performs the work
/// defined a function below
void user_defined_function()
{
    std::cout<<"User defined function() called!"<<'\n';
}

void five()
{
    std::cout<<"From five(), ";
    user_defined_function();
}

/// main : the caller function
int main()
{
    /// main starts
    std::cout<<"main() starts!"<<'\n';
    
    /// calling the function - the called/callee function
    /// ( ) is necessary to call a function otherwise it is an error
    user_defined_function();
    
    /// function called again
    user_defined_function();
    
    /// functions calling functions calling functions
    five();
    
    /// main ends
    std::cout<<"main() ends!"<<'\n';
}
