//
//  main.cpp
//  1.5_intro.to.iostream.cout.cin.endl
//
//  Created by Judah's Leon on 7/14/22.
//

/*
 the input/output library :
 io library : part of standard library
 deals with basic input output
 header needed to use iostream library
 
 std::cout : predefined variable, allow to send data to console
 cout : character output
 
 std::cin : predefined variable in iostream lib.
 cin : character input
 variable needed to store the input
 */

#include <iostream>

int main()
{
    // << : insertion operator to send text to console
    std::cout<<"Hello\n";
    
    // cout : can also print numbers
    std::cout<<22<<"\n";
    
    // cout : can also print value of variables
    int x{2};
    // << << to concatenate multiple pieces of output together
    std::cout<<"x = "<<x<<"\n";
    
    // endl for new line, endl : end line - ends the current line
    std::cout<<"Hello!"<<std::endl;
    std::cout<<"World!"<<std::endl;
    
    /*Best practice

    Output a newline whenever a line of output is complete.*/
    
    // endl vs '\n'
    // endl : moves cursor to next line + flushes the output
    // \n : moves cursor to next line only + doesn't flush the output
    std::cout<<"newline"<<'\n';
    
    /*
     Best practice
     
     Prefer ‘\n’ over std::endl when outputting text to the console.
     */
    
    // std::cin : variable needed to store the input
    // >> extraction operator to extract the
    // input from the keyboard to variable
    
    // zero-initialization
    int number{};
    std::cout<<"Enter a number: ";
    
    // \n not needed : user will press enter and
    // the cursor will move to next line
    std::cin>>number;
    
    std::cout<<"You entered: "<<number<<'\n';
    
    // multiple inputs in single line
    int number2{};
    std::cout<<"Enter two numbers, separated by space: ";
    std::cin>>number>>number2;
    std::cout<<"You entered: "<<number<<" and "<<number2<<'\n';
    
    /*
     best practice is to initialize the variable first. maybe zero initialize it
     */
}
