//
//  main.cpp
//  7.11_halts_exiting.your.program.early
//
//  Created by εκλεγμένοι εν Χριστώ on 1/12/23.
//

/*
 Halt : flow control statement
 Halt : terminates the program
 Halts in CPP : implemented as functions, rather than keywords
 Halt statements : are function calls
 
 how a program exits?
 main() : function returns, by reaching the end of the function, via a return statement
 leaving the function : local variables, function parameters are destroyed
 
 special function : std::exit() is called with the return value from main(), status code
 passed in as an argument
 
 std::exit() function :
 -causes the program to terminate normally
 -Normal termination : program has exited in an expected way
 -Normal termination : doesn't imply anything about whether the program was successful
 -std::exit() : performs a number of cleanup functions
 -first : objects with static duration are destroyed
 -then : some other misc. file cleanup is done, if any files were used
 -finally : control is returned back to the OS with argument passed to exit(), used as a
 -status code.
 
 Calling std::exit() explicitly : std::exit() called implicitly when main() ends,
 std::exit() can be called explicitly to halt the program before its normal termination,
 cstdlib : should be included to used std::exit()
 
 std::exit() : can be called from any function to terminate the program at that point
 std::exit() : does not clean up any local variables in current function or in functions up
 the call stack
 
 Warning :
 The std::exit() function does not clean up local variables in the current function or up
 the call stack.
 
 exit() terminates program immediately,
 manual cleanup : like closing database/network connections, deallocating memory, logging to
 a log file etc.
 
 std::atexit() : C++ offers this function, allows to specify a function that will be called
 automatically on program termination via std::exit(), the function that will do the cleanup
 is passed as an argument to the atexit() function
 
 std::exit() : called implicitly when main() terminates, this will invoke any functions
 registered by std::atexit() if program exits that way
 
 std::atexit() : the function being registered must take no parameters and have no return
 value
 
 std::atexit() : multiple cleanup functions can be registered using std::atexit()
 
 reverse order of registration : registered functions will be called in reverse order, the
 last one registered will be called first and first one registered will be called last
 
 std::quick_exit() : terminates the program normally, but does not clean up static objects,
 may not do other types of cleanup
 
 std::at_quick_exit() : same role as atexit() for programs terminated with std::quick_exit()
 
 std::exit() and std::atexit()
 std::quick_exit() and std::at_quick_exit()
 
 other halt related functions : std::abort() and std::terminate()
 
 std::abort() : causes the program to terminate abnormally
 abnormal termination : means the program has some kind of unusual runtime error and it
 couldn't continue to run. example : trying to divide by 0
 std::abort() : does not do any cleanup
 
 std::terminate() : typically used in conjunction with exceptions
 std::terminate() : can be called explicitly, more often called implicitly
 std::terminate() : often called implicitly when exception is not handled
 std::terminate() : by default, it calls std::abort()
 
 When should halt be used?
 answer : never
 none of the halt functions : clean up local variables
 exceptions : better and safer mechanisms for handling error cases
 
 best practice : only use halt if there is no safe way to return normally from the main()
 exceptions : prefer exceptions if they aren't turned off to handle the errors safely
 */

#include <cstdlib>
#include <iostream>

void cleanup()
{
    std::cout << "CLEANUP!" << '\n';
    /// calling std::exit( ) in this function, will terminate the program also
//    std::exit(2);
}

void cleanup_atexit()
{
    std::cout << "DOING SOME CLEANUP BEFORE EXITING!" << '\n';
}

void cleanup_atexit2()
{
    std::cout << "DOING CLEANUP AGAIN 1!" << '\n';
}

void cleanup_atexit3()
{
    std::cout << "DOING CLEANUP AGAIN 2!" << '\n';
}

int main()
{
    cleanup();
    
    /// cleanup_atexit is called automatically when std::exit() is called
    /// used cleanup_atexit rather than cleanup_atexit(), because there is no function call to cleanup_atexit()
    /// reverse order of registration : last one registered will be called first
    ///
    /// this will be called last, it was registered at first : reverse order
    std::atexit(cleanup_atexit);
    std::atexit(cleanup_atexit2);
    /// this will be called first, it was registered at last
    std::atexit(cleanup_atexit3);
    
    /// terminates the program abnormally
//    std::abort();
    
    /// terminating and returning status code 0 to OS : explicit call to std::exit( )
    std::exit(0);
    
    /// this won't execute ever
//    std::cout << "Hello man!" << '\n';
    
    return 0;
}
