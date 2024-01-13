//
//  main.cpp
//  1.11_developing.your.first.program
//
//  Created by Judah's Leon on 8/25/22.
//

/*
 better strategy : add one piece at a time, compile and test
 it then move on to the next piece
 */

#include <iostream>

int main()
{
    std::cout<<"Enter an integer: ";
    
    int x{};
    std::cin>>x;
    
    /// not good solution
//    x = x * 2;
//    std::cout<<"Double that number is: "<<x<<'\n';
    
    /// mostly good solution
//    int double_x{x * 2};
//    std::cout<<"Double that number is: "<<double_x<<'\n';
    
    /// preferred solution
    std::cout<<"Double that number is: "<<x*2<<'\n';
    
    /// triple
    std::cout<<"Triple that number is: "<<x*3<<'\n';
    
    
    
    
    /// question: Write a program that asks the user to enter a number, and then enter a second number. The
    /// program should tell the user what the result of adding and subtracting the two numbers is.
    std::cout<<"Enter a number: ";
    int p{};
    std::cin>>p;
    
    std::cout<<"Enter another number: ";
    int q{};
    std::cin>>q;
    
    std::cout<<p<<" + "<<q<<" is "<<p+q<<'\n';
    std::cout<<p<<" - "<<q<<" is "<<p-q<<'\n';
    
    return 0;
}


/*
summary :
statement : instruction that causes program to perform some action, and are terminated
by semicolon
function : collection of statement that execute sequentially, main function is must
have function in a cpp program
syntax : rules that governs how element of language are constructed
comments : allow the programmer to leave the notes in the code. 
data : any sequence of symbols that can be interpreted to mean something
value : a single piece of data stored somewhere in the memory
variable : a piece of memory used to store the data
identifier : a variable's name in the source code
definition statement : used to create a variable
instantiation : assignation of memory address
data type : tells the compiler how to interpret a piece of data into a meaningful value
copy assignment(=) : used to assign an already create variable a value
initialization : used to give variable a value at the point of creation

types of initialization:
copy initialization
direct initialization : parenthesis initialization
brace initialization : uniform or list initialization(preferred over other initializations)

initialization preferred over assignment(using =)

std::cout<< : to output an expression to the console
std::cin>> : to input a value from the keyboard
std::endl : outputs a new line character

uninitialized variable : that has not been given a value, accessing it causes undefined behavior
keywords : reserved words of the language, can't be used as variable names
literal constant : fixed value, inserted directly into the source code, like "hello" or 22
operation : mathematical calculation involving zero or more input values(operands)
operator : operation between two operands in specified using an operator, like + , - etc.
unary : operators that take one operand as input
binary : takes two
ternary : takes three
expression : combination of literals, variables, operators and function calls, evaluates to a single
value
evaluation : process of of calculation of an expression
result : output of evaluation
expression statement : expression that has been turned into a statement by placing a semicolon at the
end of the expression

*/
