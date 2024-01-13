//
//  main.cpp
//  8.9_intro.to.function.overloading
//
//  Created by εκλεγμένοι εν Χριστώ on 2/15/23.
//

/*
 Function overloading : allows to create multiple functions with the same name, so long as
 each identically named function has different parameter types
 
 Each function sharing a name : is an overloaded function or an overload for short
 
 to overload the function : simply declare another function with same name that takes
 different parameters
 
 compiler is able to differentiate between overloaded functions, treats them as separate
 functions that just happen to share a name
 
 key insight:
 functions can be overloaded, as long as each overloaded function can be distinguished by
 the compiler
 
 Operators in cpp : are just functions, they can also be overloaded
 
 Overload resolution : at the call to overloaded function, compiler will try to match the
 function call to the appropriate overload, based on the arguments used in the function call
 
 In order for a program using overloaded function to compile : two things have to be true
 -each overloaded function has to be differentiated from others
 -each call to overloaded function has to resolve to an overload function
 
 conclusion : function overloading reduces complexity of the program, reduces the number of
 function names need to remember, should be used liberally
 
 best practice : use function overloading to make program simpler
 */

#include <iostream>

int add(int x, int y)
{
    return x + y;
}

/// same name with different parameters
double add(double x, double y)
{
    return x + y;
}

int main()
{
    /// int arguments provided to the function call, compiler will determine that we're trying to call add(int, int)
    std::cout << add(2, 2) << '\n';
    /// double arguments provided to the function call, compiler will determine that we're trying to call add(double, double)
    std::cout << add(2.2, 2.2) << '\n';
    
    return 0;
}
