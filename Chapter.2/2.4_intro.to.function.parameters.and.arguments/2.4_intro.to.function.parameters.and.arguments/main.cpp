//
//  main.cpp
//  2.4_intro.to.function.parameters.and.arguments
//
//  Created by Judah's Leon on 8/30/22.
//

/*
 function parameter: variable used in a function
 
 function parameters: identical to variable defined inside the
 function, but the only difference is that they are always
 initialized with a value provided by the caller of the
 function.
 
 parameters : defined in the function declaration, placed in
 between the parenthesis after the function name
 multiple parameters: separated by the commas
 
 argument: value that is passed from the caller to the
 function call
 multiple arguments: separated by the commas
 argument: can be any valid expression
 
 pass by value: at function call, all of the function params
 are created as variables, value of arguments passed is copied
 into the matching parameter, this process is pass by value
 
 number of arguments must be equal to the number of parameters
 
 Conclusion
 Function parameters and return values are the key mechanisms by which functions can
 be written in a reusable way, as it allows us to write functions that can perform
 tasks and return calculated results back to the caller without knowing
 what the specific inputs or outputs are beforehand.
 */

#include <iostream>

/// function takes no parameters
void no_parameters()
{
    std::cout << "FUN: No parameters passed!" << '\n';
}

/// function with one parameter
void one_parameter(int x)
{
    std::cout << "FUN: " << x << " passed!" << '\n';
}

/// function with multiple parameters
/// parameters separated by the commas
void mul_parameter(int x, int y)
{
    std::cout << "FUN: " << x << ", " << y << " passed!"<<'\n';
}

void print_the_passed(int x, int y)
{
    std::cout << "x: " << x << '\n';
    std::cout << "y: " << y << '\n';
}

int get_from_user()
{
    std::cout << "Enter an integer: ";
    int input{};
    std::cin >> input;
    
    return input;
}

void print_the_double(int value)
{
    std::cout << "Double of " << value << " is " << value * 2 << '\n';
}

/// parameters and return together
int add(int x, int y)
{
    return x + y;
}

/// read an integer from the user
/// double it using a function
/// print the doubled value out to the console
void read_integer()
{
    std::cout << "Enter an integer: ";
    int input{};
    std::cin >> input;
    
    print_the_double(input);
}

int main()
{
    /// function with no parameters passed
    no_parameters();
    
    /// function with one argument passed
    one_parameter(2);
    
    /// function with multiple arguments passed
    /// arguments separated by the commas
    mul_parameter(22, 33);
    
    /// arguments can be any valid expression
    print_the_passed(10-2, 20);
    
    /// return value of get_from_user passed as an argument to the function
    print_the_double(get_from_user());
    
    std::cout << "Sum: " << add(2, 2) << '\n';
    
    /// passing return value of get_from_user into add function, add's return value printed directly
    std::cout << add(get_from_user(), get_from_user()) << '\n';
    
    read_integer();
    
    return EXIT_SUCCESS;
}
