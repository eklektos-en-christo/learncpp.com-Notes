//
//  main.cpp
//  27.2_basic.exception.handling
//
//  Created by Εκλεκτός εν Χριστώ on 11/27/23.
//

/*
 EXCEPTIONS in C++: are implemented using three keywords that work in conjunction with each other
 
 Keywords: throw, try & catch
 
 -----------------------------------------------------------------------------------------------------------
 THROWING EXCEPTIONS: 1st part of the exception handling process
 
 Throw statement: is used to signal that an exception/error case has occurred
 
 Raising an exception: signaling that an exception has occurred
 
 To use a throw statement: simply use the throw keyword, followed by a value of any data type you wish to
 signal that an error has occurred, typically this value will be an error code, a description of the problem
 or a custom exception class
 
 examples: each of the statements below acts as a signal that some kind of problem that needs to be handled
 has occurred
 
 throw -1;                                  // throw a literal int value
 throw ENUM_INVALID_INDEX;                  // throw an enum value
 throw "Can't take sqrt of -ve number";     // a C-style string literal
 throw dX;                                  // a double variable that was previously defined
 throw MyException("Fatal error");          // an object of a class MyException
 
 -----------------------------------------------------------------------------------------------------------
 LOOKING FOR EXCEPTIONS: another part of the exception handling
 
 try keyword: is used to define a block of statements(try block), try block acts as an observer, looking for
 any exceptions that are thrown by any of the statements within the try block
 
 try block: doesn't define how we're going to handle the exception, it merely tells the program that if any
 of the statements inside the try block throws an exception, then grab it.
 
 example:
 
 try
 {
    // statements that may throw exceptions you may want to handle go here
    throw -1;               // a trivial throw statement
 }
 
 -----------------------------------------------------------------------------------------------------------
 HANDLING EXCEPTIONS: this is the job of the catch block(s)
 
 catch keyword: is used to define a block of code that handles exceptions for a single data type
 
 example:
 
 catch(int x)
 {
    std::cerr << "We caught an int exception with value " << x << '\n';
 }
 
 Try and catch block work together - a try block detects any exceptions that are thrown by statements within
 the try block and routes them to a catch block with a matching type for handling
 
 A try block must have at least one catch block immediately following it, but may have multiple catch blocks
 listed in sequence
 
 One an exception has been caught by the try block and routed to a catch block for handling, the exception
 is considered handled and execution will resume as normal after the catch block
 
 Catch parameters: work just like the function parameters, parameters being available within the subsequent
 catch block
 
 Exceptions of fundamental types: can be caught by value, but exceptions of non-fundamental types should be
 caught by const reference to avoid making an unnecessary copy and to prevent slicing in some cases
 
 If the catch parameter is not going to be used in the catch block, then its identifier can be omitted as
 shown below:
 
 catch(double)
 {
    std::cerr << "We caught an exception of type double" << '\n';
 }
 
 No type conversion is done for exceptions, so an exception will not be converted to match a catch block
 with a double parameter
 
 -----------------------------------------------------------------------------------------------------------
 an exception is raised using throw keyword, the compiler looks in the nearest enclosing try block to see if
 any of the catch handlers attached to the try block can handle that type of exception, if so, then
 execution jumps to the top of the catch block, the exception is considered handled then
 
 if no appropriate catch handlers exist in the nearest enclosing try block, then compiler continues to look
 at subsequent try blocks for a catch handler, if no appropriate catch handlers can be found before the end
 of the program, the program will fail with an exception error
 
 compiler will not perform implicit conversions or promotions when matching exceptions with catch blocks,
 a char exception will not match with an int block, an int exception will not match a float catch block,
 however, the casts from a derived class to one its parent classes will be performed
 
 -----------------------------------------------------------------------------------------------------------
 if an exception is routed to a catch block, it is considered "handled", even if the catch block is empty,
 
 some common things which the catch blocks do when they catch an exception:
 
 - they may print an error, either to the console or a log file and then allow the function to proceed
 
 - they may return a value or error code back to the caller
 
 - catch block may throw another exception, the newly thrown exception then is not handled by the preceding
   try block, it is handled by the next enclosing try block
 
 - a catch block in main may be used to catch the fatal errors and terminate the program in a clean way
 
 -----------------------------------------------------------------------------------------------------------
 */

#include <iostream>
#include <string>
#include <cmath>

int main()
{
    try
    {
        /// statements that may throw exceptions should go here
        /// throw statement is used to raise an exception with value -1, which is an int
        /// try block will catch this exception and route it to the appropriate catch block that handles the int exceptions
        throw -1;
    }
    /// any int exceptions thrown by the above try block will be sent in this catch block
    catch(int x)
    {
        std::cerr << "We caught an int exception with value: " << x << '\n';
    }
    /// this block handles the double exceptions, variable name is omitted in parameter because of not being used inside the catch block
    catch(double)
    {
        std::cerr << "We caught a double exception" << '\n';
    }
    /// this block handles the std::string exceptions, variable name omitted in parameter
    catch(const std::string&)
    {
        std::cerr << "We caught a std::string exception" << '\n';
    }
    
    std::cout << "Continuing now\n";
    
    try
    {
        throw 2.22;
        /// this line of code never executes, which means that exceptions are handled immediately
        /// the exception caused the execution path to jump immediately to the exception handler for doubles
        std::cout << "a print statement inside try block\n";
    }
    /// this catch block handles the double exceptions, so it will be executed
    catch(double x)
    {
        std::cout << "An exception has been caught of type double with value: " << x << '\n';
    }
    
    /*----------------------------------------------------------------------------------------------------*/
    std::cout << "Enter a number: ";
    double x{};
    std::cin >> x;
    
    try
    {
        /// if the user entered a negative number, then throw an exception of type const char*
        if (x < 0.0)
            throw "Can't take sqrt of negative number\n";
        
        /// if the input is right, then print the square root of that number, the catch block never executes in this case
        std::cout << "The sqrt of " << x << " is: " << std::sqrt(x) << '\n';
    }
    /// exception of type const char* is handled inside this catch block
    catch(const char* exception)
    {
        /// printing the error on the console
        std::cerr << "Error: " << exception << '\n';
        
        /// returning the error code to the caller, which is main() in this case
        return 99;
    }
    /*----------------------------------------------------------------------------------------------------*/
    
    return 0;
}
