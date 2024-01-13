//
//  main.cpp
//  27.4_uncaught.exceptions.and.catch_all.handlers
//
//  Created by Εκλεκτός εν Χριστώ on 11/27/23.
//

/*
 -----------------------------------------------------------------------------------------------------------
 When no exception handler for a function is found, std::terminate() is called and the application is
 terminated, in such cases the call stack or may not be unwound, if the call stack is unwound, local
 variables will not be destroyed and any cleanup expected of those variables will not happen
 
 WARNING:
 the call stack may or may not be unwound if an exception is unhandled
 
 If the stack were unwound, then all of the debug information about the state that led up to the throwing of
 the unhandled exception would be lost, by not unwinding, we preserve that debug information, making it
 easier to determine how an unhandled exception was thrown and how it can be fixed
 
 When an exception is unhandled, the OS generally notifies about it by using some pop-up, error message,
 error dialog or simply a crash
 
 -----------------------------------------------------------------------------------------------------------
 CATCH-ALL HANDLERS:
 
 - functions can potentially throw exceptions of any data type, infinite number of possible exceptions types
 - if the exception is not caught, the program will terminate immediately, stack unwound may not happen
 - adding explicit catch handlers for every possible type is tedious,
 
 Catch-all handler: works just like normal catch block it uses the ellipsis(...) as the type of catch
 parameter instead of specific type to catch
 
 ellipsis catch handler: catch-all handler's another name because of ellipsis being used as a parameter
 
 ellipsis: can represent exceptions of any type in the case of exception handling, in general they allow the
 caller to pass arguments of any type to a function
 
 Catch-all handler: must be placed last in the catch block chain to ensure that the exception of specific
 types get handled by their matching exception handler catch block(if they exist), if they don't exist then
 catch-all block can handle the exception at last
 
 catch-all handler: is often left empty, this catches the unanticipated exceptions which ensures that stack
 unwinding occurs up to this point and prevents the program from terminating but does no specific error
 handling
 
 One common use of catch-all handler is to wrap the contents of main() - the problem with this is that if an
 unhandled exception does occur, stack unwinding will occur, which will make it harder to determine why the
 unhandled exception was thrown in the first place
 
 So catch-all handler is good to use in production applications and disabled in debug applications
 
 BEST PRACTICE:
 use catch-all handler in main for an orderly behaviour when an unhandled exception occurs
 disable the catch-all handler for debug builds by using the conditional compilation directives
 
 -----------------------------------------------------------------------------------------------------------
 */

#include <iostream>

void run_game()
{
    throw -1;
}

void save_game()
{
}

int main()
{
    try
    {
        /// exception being thrown in of type int
        throw 8;
    }
    /// this catch handler handles only char type
    catch(char c)
    {
        std::cout << "Exception of char type is raised with value: " << c << '\n';
    }
    /// catch-all handler below, it must be in the last of all catch handlers
    /// so this handler is used, it accepts all types of exceptions, because of the ellipsis(...) operator
    catch(...)
    {
        std::cout << "we caught an exception of an undetermined type\n";
    }
    
    /// wrapping up the main with catch-all handler
    try
    {
        /// if the function throws an error which is not handled by itself
        run_game();
    }
    /// catch-all handler will catch the exception, stack will be unwound in an orderly manner
    /// this also prevents the program from terminating immediately
    /// this gives us the chance to print the appropriate error and save the user's data before the program exits
    catch(...)
    {
        std::cerr << "Abnormal termination\n";
    }
    
    /// save the user's data
    save_game();
    
    return 0;
}
