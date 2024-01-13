//
//  main.cpp
//  4.13_const.variables.and.symbolic.constants
//
//  Created by εκλεγμένοι εν Χριστώ on 9/21/22.
//

/*
 constant: value that may not be changed.
 
 types of constants in C++: const variables, compile time
 constants, constant expressions, constexpr and literals
 
 Const variables: variable whose value cannot be changed
 
 const: keyword, to make a variable constant, place const
 before or after the type of the variable in declaration
 
 before the type: preferred
 after the type: called "east const", not preferred
 
 better: modifiers come before the object being modified
 
 best practice
 Place const before the type (because it is more idiomatic to
 do so).
 
 Const variables must be initialized
 
 function parameters: can be made const using const keyword
 
 const variables naming: intercapped names with k prefix
 e.g. kEarthGravity
 EARTH_GRAVITY also, C style
 
 Best practice
 Don’t use const when passing by value.
 
 Returning a const value can also impede certain kinds of
 compiler optimizations
 
 Best practice
 Don’t use const when returning by value.
 
 Symbolic constant: name that is given to a constant value
 const variables: one type of symbolic constants with name and
 a constant value
 
 syntax: #define identifier substitution_text
 
 object-like macros with substitution text are also symbolic
 constants, because object-like macros have a name and the
 substitution text is a constant value.
 
 for symbolic constants: prefer constant variables to object-
 like macros.
 reasons:
 -in debugging, the actual values aren't visible, only
 the name of symbolic constant is visible
 -can't add a watch in the debugger to see the values of
 symbolic constants
 -to know the value of symbolic constants, you'll have to find
 the definition of the symbolic constants, that definition
 could be in a different file
 --so it could make the debugging harder
 
 Best practice
 Prefer constant variables over object-like macros with
 substitution text.
 
 Using constant variables throughout a multi-file program:
 In many applications, a given symbolic constant needs to be
 used throughout your code (not just in one location).
 These can include physics or mathematical constants
 that don’t change (e.g. pi or Avogadro’s number), or
 application-specific “tuning” values (e.g. friction or
 gravity coefficients). Instead of redefining these
 every time they are needed, it’s better to declare them
 once in a central location and use them wherever
 needed. That way, if you ever need to change them, you
 only need to change them in one place.
 */

#include <iostream>

/// any further occurrences of MAX_STUDENTS_PER_CLASS is replaced by
/// the constant value 40
#define MAX_STUDENTS_PER_CLASS 40

/// const function parameter
/// parameter x is passed by value, so need to use a const
/// x is just a copy that will be destroyed at the end of the function
void print(const int x)
{
    std::cout << x << '\n';
}

/// const return value
/// return value is a copy, so no need to return the value as const
const int print_int()
{
    int x = 2;
    return x;
}

int main()
{
    /// const before the type name, preferred
    const double d{21.1};
    /// const after the type name
    double const d2{77.80};
    
    /// Const variables must be initialized on definition
    const int i{};
    /// error: const variable i cannot be changed
//    i = 2;
    
    int a = 99;
    /// const variable can be initialized using not const value
    const int a2{a};
    
    print(22);
    
    std::cout << print_int() << '\n';
    
    std::cout << "Max students per class: " <<
    MAX_STUDENTS_PER_CLASS << '\n';
    
    return 0;
}
