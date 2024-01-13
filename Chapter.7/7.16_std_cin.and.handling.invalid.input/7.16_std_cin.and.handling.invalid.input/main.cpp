//
//  main.cpp
//  7.16_std_cin.and.handling.invalid.input
//
//  Created by εκλεγμένοι εν Χριστώ on 1/25/23.
//

/*
 A robust program : that handles error cases well
 
 operator>> : to get user input into a variable
 >> : called extraction operator
 
 buffer/data buffer : simply a piece of memory set aside for storing data temporarily  while
 it's moved from one place to another
 
 std::cin : user inputted data is placed in a buffer inside of std::cin
 
 buffer : used to hold user input while it's waiting to be extracted to variables
 
 When extraction operator is used:
 -data already in input buffer : that data is used for extraction
 
 -if input buffer contains no data : user is asked to input data for extraction(dominant
 case)
 
 -when user hits enter : '\n' character will be placed in the input buffer
 
 -operator>> : extracts as much data from input buffer as it can into the variable
 -operator>> : ignores leading whitespace characters, spaces, tabs or '\n
 
 -un-extracted data : left in the input buffer for next extraction
 
 -Extraction succeeds : if at least once character is extracted from the input buffer
 -Extraction fails    : if input data does not match the type of variable being extracted to
 ––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––
 Input validation : process of checking whether the input by the user conforms to what the
 program is expecting
 
 three basic ways to do input validation:
 -Inline(when user types):
 1. prevent the user from typing invalid input in the first place
 -Post-entry(when user typed already)
 2. let the use enter whatever they want into a string, validate then the string, if correct
 then convert the string to the final variable format
 3. let the user enter whatever they want, let std::cin and operator>> try to extract it,
 and handle the error cases
 
 Some GUIs : validate input as user enters it char. by char., this is done using a validation
 function, when user presses the key, the function return true/false, if false then inputted
 char. is discarded, if true then input is accepted
 Most often : std::cin and >> is used, fallouts are dealt
 
 std::cin : stops extracting at the first non-leading whitespace char.
 ––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––
 Types of invalid text input:
 input text errors, generally can be separated into four types:
 -input extraction succeeds but input is meaningless to the program, like 'a' as operator
 -input extraction succeeds but user enters additional input, like '/hello' as operator
 -input extraction fails, like trying to enter 'a' into numeric field
 -input extraction fails, like user overflows a numeric value
 
 std::cin : goes into 'failure mode'
 failed extraction due to invalid input : cause the variable to be zero-initialized
 ––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––
 Conclusion:
 For each point of text input, consider:

     Could extraction fail?
     Could the user enter more input than expected?
     Could the user enter meaningless input?
     Could the user overflow an input?
 
 The following code will clear any extraneous input:

 std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

 The following code will test for and fix failed extractions or overflow:

 if (!std::cin) // has a previous extraction failed or overflowed?
 {
     // yep, so let's handle the failure
     std::cin.clear(); // put us back in 'normal' operation mode
     std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // and remove the bad input
 }
 
 Finally, use loops to ask the user to re-enter input if the original input was invalid.
 ––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––
 */

#include <limits>
#include <iostream>

/// extraction will fail if user enters other than a number like 'a' or something
double get_double()
{
    std::cout << "Enter a double: ";
    double d{};
    std::cin >> d;
    return d;
}

/// extraction will be successful if user enters other than the operator + - * / like "hello" or something
/// but afterward the handling of that input isn't in our hands, the input buffer can also cause problems if
/// the left input is still in the buffer
char get_operator()
{
    std::cout << "Enter any one from +, -, *, /: ";
    char c{};
    std::cin >> c;
    return c;
}

void print_output(double x, char operation, double y)
{
    switch (operation)
    {
        case '+':
            std::cout << x << '+' << y << ": " << x + y << '\n';
            break;
        case '-':
            std::cout << x << '-' << y << ": " << x - y << '\n';
            break;
        case '*':
            std::cout << x << '*' << y << ": " << x * y << '\n';
            break;
        case '/':
            std::cout << x << '/' << y << ": " << x / y << '\n';
            break;
        default:
            std::cerr << "Something's wrong: Invalid operator passed!\n";
    }
}

/// Error case 1 : solution below
/// input validation:
/// checking whether the user's input was what is expected
/// if so return the value to caller
/// if not then tell the user to try again
char get_operator_error_case1()
{
    while (true)
    {
        std::cout << "Enter any one from +, -, *, /: ";
        char operation{};
        std::cin >> operation;
        
        switch (operation)
        {
            case '+':
            case '-':
            case '*':
            case '/':
                return operation;
            default:
                std::cerr << "Invalid input! Please try again.\n";
        }
    }
}

/// std::cin.ignore(100, '\n') : means clear up to 100 characters out of the buffer, or until a '\n' char is removed
/// but if user enters more than 100 characters then input will be messy again
/// std::numeric_limits<std::streamsize>::max() : returns the largest value that can be stored in a variable of
/// type std::streamsize
/// passing this value to std::cin.ignore() causes it to disable the count check
/// this function ignores everything up to and including '\n' character
///
void ignore_line()
{
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

/// Error case 2 : solution below
/// this will ignore any extraneous input
double get_double_error_case2()
{
    std::cout << "Enter a double: ";
    double d{};
    std::cin >> d;
    ignore_line();
    return d;
}

/// error case 3 : solution below
/// if extraction fails then this will solve the problem
double get_double_error_case3()
{
    while (true)
    {
        std::cout << "Enter a double: ";
        double d{};
        std::cin >> d;
        
        /// checks if previous extraction failed
        /// !std::cin : works same as std::cin.fail() - fail returns boolean value, checks if the previous extraction has failed
        if (!std::cin)
        {
            /// put us back in 'normal' operation mode
            std::cin.clear();
            /// remove bad input from buffer
            ignore_line();
            /// if failed then print a message
            std::cout << "Wrong input! Try again.\n";
        }
        else
        {
            /// if not failed then remove extraneous input and return the value to caller
            ignore_line();
            return d;
        }
    }
}

int main()
{
    double x{get_double_error_case3()};
    double y{get_double_error_case3()};
    char operation{get_operator_error_case1()};
    
    print_output(x, operation, y);
    
    /// –––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––
    /// error case 4 : extraction succeeds but user overflows a numeric value
    std::int16_t a{};
    std::cout << "Enter a no. between -32768 and 32767: ";
    std::cin >> a;
    
    /// solved : by putting cin to normal mode and removing the bad input from the buffer
    if (!std::cin)
    {
        std::cin.clear();
        ignore_line();
    }
    
    std::int16_t b{};
    std::cout << "Enter a no. between -32768 and 32767: ";
    std::cin >> b;
    
    if (!std::cin)
    {
        std::cin.clear();
        ignore_line();
    }
    
    std::cout << "Sum: " << a + b << '\n';
    /// –––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––
    
    return 0;
}
