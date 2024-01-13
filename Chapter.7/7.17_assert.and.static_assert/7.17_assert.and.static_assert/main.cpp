//
//  main.cpp
//  7.17_assert.and.static_assert
//
//  Created by εκλεγμένοι εν Χριστώ on 1/27/23.
//

/*
 Preconditions : any condition that must always be true prior to the execution of component
 of code, like check of y is a precondition that ensures y has a valid value and not the
 zero value(in case of divide function below).
 
 Invariant : condition that must be true while some component of code is executing
 
 Postcondition : that must be true after the execution of some component of code
 
 Assertions : using a conditional statement to detect an invalid parameter/or to validate
 some other kind of assumption, along with printing an error message and terminating the
 program, this is a common response to problems, there is shortcut method that C++ provides
 
 Assertion : an expression that will be true unless there is a bug in the program,
 if expression evaluates to true, assertion statement does nothing, if it is false, an error
 message is displayed and program is terminated via std::abort
 error message : contains the expression that failed as text, along with the name of the
 code file and line no. of the assertion, this makes easy to tell what the problem was and
 also where in the code the problem occurred. this also helps in debugging efforts
 
 runtime assertions : implemented via assert preprocessor macro, which lives in <cassert>
 header file
 
 asserts : can be used anywhere to validate if something is true
 
 best practice:
 asserts : few preprocessor macros that are acceptable to use, use assert statements
 liberally throughout the code
 
 string literal : always evaluates to true
 
 Making assert statements more descriptive: simply add a string literal joined by a logical
 AND, string literal is always true.
 
 Asserts vs Error handling:
 Assertion : goal is to catch programming errors by documenting something that should never
 happen, if error happens then it can be identified and fixed, assertions don't allow
 recovery from errors, and program will not produce a friendly error message.
 Error handling : designed to gracefully handle cases that could happen, these may or may
 not be recoverable, but it should always be assumed that user of the program may encounter
 them
 
 best practice : use assertions to document cases that should be logically impossible
 
 Assertions : also used to document cases that were not implemented because they were not
 needed at the time the programmer wrote the code, this way the future user of the code
 does encounter a situation where this case is needed, the code runs but with a useful error
 message, then the programmer can determine how to implement that case
 
 Assert macro : comes with a small performance cost that is incurred each time the assert
 condition is checked.
 
 asserts : should never be encountered in production code, because code should already be
 thoroughly tested
 
 Way to turn off asserts in production code : C++ comes with a way to turn off asserts in
 production code.
 NDEBUG : if this macro is defined, the assert macro gets disabled
 
 Assert limitations and warnings :
 -assert itself can be improperly written: if so, if will report an error where none exists,
 or fail to report a bug where one does exist
 -asserts should have no side effects : program should run the same with and without assert,
 otherwise, testing in a debug configuration will not be same as in a release configuration
 (assuming if shipping with NDEBUG)
 
 abort() : terminates program immediately, without a chance to do further cleanup,
 
 asserts : should be used only in cases where corruption isn't likely to occur if the
 program terminates unexpectedly
 
 assert : evaluated at runtime
 static_assert : assertion that is checked at compile time, rather than at runtime,
 failing static_assert : cause a compile error
 assert : declared in cassert header
 static_assert : keyword, so no header needed to use it
 
 static assert form:
 static_assert(condition, diagnostic message)   - if the condition is false, diagnostic
 message is printed
 
 static_assert : evaluated by the compiler
 static_assert : can be placed anywhere in the code file, even in global namespace
 
 before c++17 : second parameter(diagnostic message) to static_assert is must
 since c++17 : diagnostic message is optional
 */

#define NDEBUG          /// disabling the asserts using NDEBUG macro
#include <cassert>      /// for assert()
#include <cmath>        /// for std::sqrt()
#include <iostream>

/// ensuring that types have a certain size
/// second assert evaluates to false by the compiler and compilation stops
static_assert(sizeof(long) == 8, "long must be of 8 bytes");
//static_assert(sizeof(int) == 8, "int should be of 8 bytes");

/// this function doesn't have any post conditions
void print_division(int x, int y)
{
    /// precondition, invariant
    if (y == 0)
    {
        std::cout << "Error: Can't divide by zero!\n";
        return;
    }
    else
        std::cout << static_cast<double>(x)/y << '\n';
}

double cal_time_until_obj_hit_ground(double init_height, double gravity)
{
    /// condition becomes false when gravity is passed as negative or even zero
    /// when condition become false, assert executes, printing the error message as text
    assert(gravity > 0.0);
    
    if (init_height <= 0.0)
        return 0.0;
    
    return std::sqrt((2.0 * init_height) / gravity);
}

void descriptive_assert_statement(bool value)
{
    /// when this assert executes, as it becomes false, it will print only "value", function name, file name, line no.
    /// but to make it more descriptive, we can add a message with it
    /// otherwise we have to go look at the code to determine what went wrong
//    assert(value);
    
    /// adding a string literal joined by a logical AND makes this assert more descriptive
    /// string literal : always evaluates to true
    /// even string literal is true, logical ANDing won't impact the evaluation of the assert
    /// in the message : the additional message will be included, that will tell what went wrong
    assert(value && "Car could not be found in database!");
}

int main()
{
    print_division(2, 0);
    std::cout << cal_time_until_obj_hit_ground(20, 0.0) << '\n';
    std::cout << cal_time_until_obj_hit_ground(20, 5.1) << '\n';
    
    descriptive_assert_statement(false);
    descriptive_assert_statement(true);
    
    return 0;
}
