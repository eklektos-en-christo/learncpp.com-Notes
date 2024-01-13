//
//  main.cpp
//  4.2_void
//
//  Created by εκλεγμένοι εν Χριστώ on 9/11/22.
//

/*
 Void: void mean "no type"
 variables: can't be defined with void type
 
 void uses:
 functions that don't return a value
 
 Deprecated: Functions that do not take parameters, it is used
 in C, C++ deprecates this practice, in C++ empty function
 parameters is an implicit void
 
 Best practice
 Use an empty parameter list instead of void to indicate that
 a function has no parameters.
 */

#include <iostream>

/// this function doesn't return a value, so void return type
/// void inside ( ) - works but is considered deprecated in cpp
void test(void)
{
    std::cout << "test()" << '\n';
}

int main()
{
    /// error: can't define variable of type void
//    void test{};
}
