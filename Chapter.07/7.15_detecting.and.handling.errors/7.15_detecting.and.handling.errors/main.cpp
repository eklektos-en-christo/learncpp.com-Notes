//
//  main.cpp
//  7.15_detecting.and.handling.errors
//
//  Created by εκλεγμένοι εν Χριστώ on 1/20/23.
//

/*
 Defensive programming : anticipating all of the ways software can be misused
 
 Handling errors in functions : 4 general strategies that can be used -
 -handle the error within the function
 -pass the error back to caller to deal with
 -halt the program
 -throw an exception
 
 –––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––
 Handling the error within the function : if possible, best strategy is to recover from the
 error in the same function in which the error occurred, two options here:
 -retry until successful
 -cancel the operation being executed
 if the calling function expects from the called function to produce a return value or some
 useful side-effect then ignoring the error may not be an option
 –––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––
 Passing the error back to the caller : in many cases the error can't reasonably be handled
 in the function that detects the error.
 
 if function returns a normal value : then things are little more complicated.
 In some cases : full range of return values isn't used, in such cases we can use a return
 value that wouldn't otherwise be possible to occur normally to indicate an error , example
 below: double reciprocal(double x);
 
 if full range of return values are needed : then return value to indicate an error will not
 be possible, the caller won't be able to tell whether the return is a valid value or an
 error value, in such case an out parameter might be a viable choice
 –––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––
 Fatal errors/non-recoverable errors : the error is so bad that the program can't continue
 to operate properly
 In such cases : best is to terminate the program
 if code is in main() : best is to let the main() return a non-zero status code
 
 if code is in deep nested sub function : it is not convenient/possible to propagate the
 error all the way back to main()
 in such case : halt statement can be used, such as std::exit()
 –––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––
 Exceptions : when an error occurs, an exception is "thrown"
 if current function does not "catch" the error : the caller has a chance to "catch"
 
 Up progression of error : error moves up the call stack until it is either caught and
 handled, or until main() fails to handle the error.
 */

#include <iostream>

/// alternate strategy is to ignore the error/or cancel the operation
void print_division(int x, int y)
{
    /// if user passed in an invalid value for y, we just ignore the request to print the result of the division
    /// print only if user enters valid input for y, otherwise ignore the error
    if (y != 0)
        std::cout << static_cast<double>(x)/y << '\n';
}

/// better than ignoring the error
void print_division_with_helpful_error_message(int x, int y)
{
    if (y != 0)
        std::cout << static_cast<double>(x)/y << '\n';
    else
        std::cerr << "Error: could not divide by zero!\n";
}

/// if y is 0, we can't skip the logic, because the function needs to return some value
double do_division(int x, int y)
{
    return static_cast<double>(x)/y;
}

/// if function has void return type, it can be changed to bool that indicates success or failure
/// now, the caller can check the return value to see if the function failed for some reason
bool print_division_with_message_and_return_indicator(int x, int y)
{
    if (y == 0)
    {
        std::cout << "Error: could not divide by zero!\n";
        return false;
    }
    
    std::cout << static_cast<double>(x)/y << '\n';
    
    return true;
}

/// reciprocal of x is 1/x
/// if the user pass reciprocal(0.0), we get a divide zero error and a program crash
/// but this function must return a double value
/// this function will never produce 0.0 as a legitimate result, so we can return 0.0 to indicate an error case
double reciprocal(double x)
{
    return 1.0/x;
}

/// reciprocal of x is 1/x, it returns 0.0 if x is passed as 0
/// returning 0.0 to indicate an error case
/// using a return value that wouldn’t otherwise be possible to occur normally to indicate an error
double reciprocal_indicate_an_error_case(double x)
{
    if (x == 0.0)
        return 0.0;
    
    return 1.0/x;
}

double do_division_fatal_error(int x, int y)
{
    /// fatal error : so terminating the program with status code 1 passed as argument to std::exit( )
    if (y == 0)
    {
        std::cerr << "Error: Couldn't divide by zero!\n";
        std::exit(1);
    }
    
    return static_cast<double>(x) / y;
}

int main()
{
    print_division(20, 9);
    print_division_with_helpful_error_message(20, 0);
    std::cout << do_division(20, 0) << '\n';
    
    /// caller is checking the return value to see if the function failed for some reason, the caller is main( ) in this case
    print_division_with_message_and_return_indicator(20, 0);
    
    /// if x = 0, then this will return 0.0
    std::cout << reciprocal_indicate_an_error_case(0) << '\n';
    
    return 0;
}
