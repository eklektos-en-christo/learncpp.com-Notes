//
//  main.cpp
//  27.3_exceptions.functions.and.stack.unwinding
//
//  Created by Εκλεκτός εν Χριστώ on 11/27/23.
//

/*
 -----------------------------------------------------------------------------------------------------------
 If a statement inside a try block is a function all and the called function throws an exception, then the
 try block will detect an exception thrown by the function call that is called from within the try block
 
 Throw statements: don't have to be placed directly inside a try block, exceptions can be thrown from
 anywhere in a function and those exceptions can be caught by the try block of the caller or the caller's
 caller, when a exception is caught in this manner, execution jumps from the point where the exception is
 thrown to the catch block handling the exception
 
 KEY INSIGHT: try block catch exceptions not only from statements within the try block, but also from the
 functions that are called within the try block, this allows us to use the exception handling in a much more
 modular fashion
 
 -----------------------------------------------------------------------------------------------------------
 By passing the error out of the function, each application can handle the error from the function in a way
 that is the most appropriate for it, this makes the function more modular and error handling can be placed
 in the less-modular parts of the code
 
 -----------------------------------------------------------------------------------------------------------
 EXCEPTION HANDLING AND STACK UNWINDING:
 
 Working of exceptions when multiple functions are involved:
 
 When an exception is thrown, the programs first looks to see if the exception can be handled immediately
 inside the function i.e. the exception was thrown within a try block inside the function, if the current
 function can handle the exception, it does so
 
 if not, the program next checks whether the function's caller can handle the exception, for the caller to
 handle the exception, the call to the current function must be inside a try block and matching catch block
 must be associated, if no match is found then the caller's caller is checked, similarly for the caller's
 caller to handle the exception, the call to the caller must be inside a try block and a matching block must
 be associated
 
 this process continues until a matching handler is found
 
 if the matching handler is found, then execution jumps from the point where the exception is thrown to the
 top of the match catch block, this requires unwinding the stack(removing the current function from the
 stack) as many times as necessary to make the function handling the exception the top function on the call
 stack
 
 if no matching exception handler is found, the stack may not be unwound
 
 When the current function is removed from the call stack, all local variables are destroyed as usual but no
 value is returned
 
 KEY INSIGHT: unwinding the stack destroys the local variables in the functions that are unwound, it ensures
 their destructors execute
 
 INTERESTING PRINCIPLES:
 
 - the immediate caller of a function that throws an exception doesn't have to handle the exception if it
   doesn't want to
 
 - if a try block doesn't have a catch handler for the type of exception being thrown, stack unwinding
   occurs just as if there were no try block at all
 
 - if a function has a matching catch block but the call to the current function did not occur within the
   associated try block, that catch block isn't used
 
 - once an exception is handled, control flow proceeds as normal starting from the end of the matching catch
   block
 
 if a function does not want to handle an exception, then exception will propagate up the stack until it
 finds someone who can handle the exception, this allows us to decide where in the call stack is the most
 appropriate place to handle any errors that may occur
 
 -----------------------------------------------------------------------------------------------------------
 */

#include <iostream>
#include <cmath>

/// a modular function performing the square root
/// square_root can throw the exceptions but can't handle them by itself
/// it delegates the responsibility to its caller
double square_root(double x)
{
    /// if the user enters a -ve number, then throw an exception of type const char*
    /// there is no exception handler in this function
    if (x < 0.0)
        throw "can't take sqrt of a negative number\n";
    
    return std::sqrt(x);
}

/*--------------------------------------------------------------------------------------------------------*/
void D()
{
    /// no exception handler available in this function
    std::cout << "D starts\n";
    std::cout << "D throwing an int exception\n";
    
    throw -1;
    
    /// this statement will be skipped
    std::cout << "D ends\n";
}

void C()
{
    /// no exception handler available in this function
    std::cout << "C starts\n";
    D();
    std::cout << "C ends\n";
}

void B()
{
    std::cout << "B starts\n";
    
    try
    {
        C();
    }
    /// int exception doesn't match with the exception handler
    catch (double)
    {
        std::cerr << "B caught double exception\n";
    }
    
    try
    {
    }
    /// this exception handler is not used because exception was not thrown within this try block
    catch (int)
    {
        std::cerr << "B caught int exception\n";
    }
    
    std::cout << "B ends\n";
}

void A()
{
    std::cout << "A starts\n";
    
    try
    {
        B();
    }
    /// exception caught and handled here, type of the exception matches with the exception handler
    catch (int)
    {
        std::cerr << "A caught int exception\n";
    }
    
    /// after the handling of exception, execution will resume from here
    std::cout << "A ends\n";
}
/*--------------------------------------------------------------------------------------------------------*/

int main()
{
    /*std::cout << "Enter a number: ";
    double x{};
    std::cin >> x;
    
    /// look for exceptions that occur within try block and route them to attached catch blocks
    try
    {
        /// there is no exception handler in square_root function, but place where it is called(main()) has an
        /// exception handler that has a matching exception handling catch block
        /// execution jumps from the throw statement in square_root to the top of the catch block in main(), then resumes
        double d = square_root(x);
        std::cout << "The sqrt of " << x << " is: " << d << '\n';
    }
    catch(const char* exception)
    {
        std::cerr << "Error: " << exception << std::endl;
    }*/
    
    try
    {
        /// order of calls: A -> B -> C-> D
        /// D throws an int exception but doesn't have the exception handler
        /// C doesn't have the exception handler also to handle the exception from D
        /// B have the exception handler but it is of type double, second try block won't work because call to C was not made within that try block
        /// A have the int exception handler and call to B was made from A's try block, so exception will be handler by the A
        A();
    }
    /// exception handled by A(), so this block is not called
    catch (int)
    {
        std::cerr << "main() caught int exception\n";
    }
    
    return 0;
}
