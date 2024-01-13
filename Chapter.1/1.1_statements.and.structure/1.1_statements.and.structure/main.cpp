//
//  main.cpp
//  1.1_statements.and.structure
//
//  Created by Judah's Leon on 7/14/22.
//

/*
 Statements : is a type of instruction that causes the program to perform some action.
 if line ends with a semicolon then it's a statement
 
 There are many different kinds of statements in C++:

     Declaration statements
     Jump statements
     Expression statements
     Compound statements
     Selection statements (conditionals)
     Iteration statements (loops)
     Try blocks
 
 */


/*
 functions and the main function :
 statements are typically grouped into units called functions.

 A function is a collection of statements that executes
 sequentially (in order, from top to bottom).
 
 Rule

 Every C++ program must have a special function named main (all lower case letters). When the program is run, the statements inside of main are executed in sequential order.
 
 syntax : The rules that govern how sentences are constructed in a language is called syntax.
 */

#include <iostream> // preprocessor directive - to use iostream library for input/output

int main()
{                               // function body starts
    std::cout<<"Hello World!";  // using iostream library here - cout : character output
                                // << - operator that allow us to send letters and numbers
                                // to the console to be output
    return 0;                   // program sending value 0 to OS to indicate that program ran
                                // successfully without any problem
}                               // function body ends
