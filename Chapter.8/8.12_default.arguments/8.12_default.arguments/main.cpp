//
//  main.cpp
//  8.12_default.arguments
//
//  Created by εκλεγμένοι εν Χριστώ on 2/19/23.
//

/*
 Default arguments : default values provided for function parameters
 
 if the caller provides an argument, the value of the argument is the function call is used
 if the caller doesn't provide, the value of the default argument is used
 you must use equals sign to specify a default argument, parentheses() or brace
 initialization {} won't work
 
 When to use default arguments?
 excellent option : when function needs a value that has a reasonable default value, but for
 which you want to let the caller override if they wish
 
 optional parameter : parameter with a default value provided, avoid this term because it is
 also used to refer to several other types of parameters - parameters passed by address,
 parameters using std::optional
 
 Multiple default arguments : function can have multiple parameters with default arguments
 
 cpp as of cpp2020 : does not support function call syntax such as print(,,3) to provide an
 explicit value for z while using default arguments for x and y, this has two consequences:
 -default arguments can only be supplied for the rightmost parameters
 -if more than one default argument exists, left default argument should be the one most
 likely to be explicitly set by the user
 
 Rule
 Default arguments can only be provided for the rightmost parameters.
 
 Default arguments : cannot be redeclared in the same file, for a function with a forward
 declaration and a function definition - default argument can be declared in either the
 forward declaration or the function definition
 best practice : is to declare the default argument in the forward declaration, as the
 forward declaration is more likely to be seen by other files (if it's in a header file)
 
 best practice :
 if the function has the forward declaration in a header file, put the default argument
 there, otherwise put it in the definition of the function
 
 Default arguments and function overloading:
 functions with default arguments may be overloaded
 
 parameters with default values : will differentiate a function overload
 */

#include <iostream>
#include "default_argument.h"

void print(int x, int y=10)
{
    std::cout << x << ',' << y << '\n';
}

/// () and {} doesn't work
//void foo(int a(2));
//void goo(int a{2});

/// couple of prototypes for which default arguments might be commonly used
int roll_die(int sides=6);
void open_log_file(std::string filename="default.log");;

void print2(int x=10, int y=20, int z=30)
{
    std::cout << x << ' ' << y << ' ' << z << '\n';
}

/// default arguments can only be provided for rightmost parameters
/// function below won't work : error
//void rightmost(int x=1, int y=2, int z)
//{
//    std::cout << x << ' ' << y << ' ' << z << '\n';
//}

/// default argument declared
void redeclare(int x, int y=2);
/// default argument redeclared : error
void redeclare(int x, int y)
{
    std::cout << x << ' ' << y << '\n';
}

void default_argument_declaration(int x, int y)
{
    std::cout << x << ' ' << y << '\n';
}

/// default arguments and function overloading
void default_overloading(std::string string)
{
    std::cout << string << '\n';
}

/// default arguments and function overloading
void default_overloading(char ch=' ')
{
    std::cout << ch << '\n';
}

void print3(int x)
{
    std::cout << x << '\n';
}

void print3(int x, int y=10)
{
    std::cout << x << ' ' << y << '\n';
}

void print3(int x, double y=10.10)
{
    std::cout << x << ' ' << y << '\n';
}

int main()
{
    /// parameter y will use default argument
    print(4);
    /// parameter y will use 1 which the user supplied
    print(2, 1);
    
    print2();
    print2(1);
    print2(1, 2);
    print2(1, 2, 3);
    
    redeclare(0);
    
    /// default argument for this function is declared in header file
    /// in main() the definition of this function doesn't have the default argument
    default_argument_declaration(22);
    
    /// resolves to default_overloading(std::string string)
    default_overloading("HELLO!");
    
    /// resolved to default_overloading(char ch=' ')
    default_overloading('z');
    
    /// resolved to default_overloading(char ch=' ')
    /// this call acts as if user explicitly called default_overloading(char ch=' ')
    default_overloading();
    
    /// resolves to print3(int, int)
    print3(1, 2);
    /// resolves to print3(int, double)
    print3(1, 2.1);
    
    /// ambiguous function call
    /// compiler is unable to tell whether this call should resolve to print(int) or print(int, double) or print(int, int)
    /// both print(int, double) and print(int, int) has a default value specified to their second parameter
//    print3(2);
    
    return 0;
}
