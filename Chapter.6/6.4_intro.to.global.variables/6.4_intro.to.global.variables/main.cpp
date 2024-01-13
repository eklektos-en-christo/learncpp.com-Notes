//
//  main.cpp
//  6.4_intro.to.global.variables
//
//  Created by εκλεγμένοι εν Χριστώ on 11/7/22.
//

/*
 global variables : declared outside of function
 
 convention : global variables declared at the top of the file, below the includes,
 convention : global variable identifiers prefixed with g or g_ to differentiate them
 from local variables
 
 global variables : can be seen and used everywhere in the file
 
 Best practice
 Consider using a “g” or “g_” prefix for global variables to help differentiate
 them from local variables.
 
 global variables : have file/global/global namespace scope, visible from the point
 of declaration until the end of the file in which they are declared,
 
 global variables : considered to be part of the global namespace
 
 global variables : have static duration, created when program starts and destroyed
 when program ends.
 
 static duration : variables that are created when the program starts and destroyed
 when program ends
 
 local variables : uninitialized by default
 static duration variables : are zero-initialized by default
 
 constant global variables : must be initialized
 
 A word of caution about (non-constant) global variables :
 use of non-constant global variables should generally be avoided altogether! 
 */

#include <iostream>

/// global variable below, declared outside outside of any function, above the file and below the includes
/// global variable - zero-initialized by default
/// no explicit initializer, still it is zero initialized by default
int g_variable;

/// error : this global variable is a constant and must be initialized
//const int x;
/// error : this global variable is a constant and must be initialized
//constexpr int x;

/// constant global variable, initialized with a value, valid
const int global{2};
/// constexpr global variable, initialized with a constant expression, valid
constexpr int global_2{global * 2};

void print_g()
{
    /// global variable is zero-initialized by default
    std::cout << g_variable << '\n';
    
    g_variable = 22;
    std::cout << g_variable << '\n';
}

int main()
{
    print_g();
    
    g_variable = 20;
    std::cout << g_variable << '\n';
    
    /// constant global variables, seen and used everywhere in the file
    std::cout << global << '\n';
    std::cout << global_2 << '\n';
    
    return 0;
}

/// global variable is out of scope here, constant global variable goes out of scope here
