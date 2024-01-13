//
//  main.cpp
//  14.1_intro.to.operator.overloading
//
//  Created by Εκλεκτός εν Χριστώ on 7/19/23.
//

/*
 -------------------------------------------------------------------------------------------
 Function overloading: a mechanism to create and resolve function calls to multiple
 functions with the same name, so long as each function has a unique function prototype
 
 Operators in C++: are implemented as functions
 
 Function overloading: by using function overloading on operator functions, we can define
 own versions of the operators that work with different data types
 
 OPERATOR OVERLOADING: using the function overloading to overload operators
 
 -------------------------------------------------------------------------------------------
 OPERATORS AS FUNCTIONS:
 
        int x{ 10 };
        int y{ 20 };
 
        
        std::cout << x + y << '\n';
 
 -translate this inside the head to the function call operator+(x, y)
 -operator+ here is the name of the function
 
        double x{ 1.1 };
        double y{ 2.2 };
 
        std::cout << x + y << '\n';             /// operator+(x, y)
 
 function overloading is used to determine that the compiler should be calling the double
 version of this function instead of the integer version
 
 -------------------------------------------------------------------------------------------
 RESOLVING OVERLOADED OPERATORS:
 
 When resolving an expression that contains an operator, compiler uses the following rules:
 
 ---------Inbuilt data types:
 
 -if all the operands are fundamental data types, compiler will call a built-in routine if
 one exists
 
 -if one doesn't exist, compiler will produce an error
 
 ---------User-defined data types:
 
 -if any of the operands are program-defined types i.e. classes/enum etc, the compiler will
 use the function overload resolution algorithm to see if it can find an overloaded operator
 that is an unambiguous best match
 
 -this might involve implicit converting of one or more operands to match the parameter
 types of an overloaded operator
 
 -it may also involve implicit converting of program-defined types into fundamental types so
 that it can match a built in operator
 
 -if no match can be found or an ambiguous match is found, compiler will error
 
 -------------------------------------------------------------------------------------------
 LIMITATIONS ON OPERATOR OVERLOADING:
 
 Any existing operator in C++: can be overloaded, almost
 
 FIRST
 Exceptions: conditional(?:), sizeof, scope(::), member selector(.), pointer member selector
 (.*), typeid and casting operators
 
 SECOND
 New operators: can't be created
 Existing operators: can't be renamed but can be overloaded
 
 THIRD
 At least one of the operands in an overloaded operator must be a user-defined type
 
 Possible: operator+(int, user_defined_type), one operand is a user-defined type
 Not possible: operator+(int, double), both operands are fundamental types
 
 BEST PRACTICE:
 An overloaded operator should operate on at least one program-defined type, either as a
 parameter of the function or the implicit object
 
 FOURTH
 Not possible: to change the number of operands an operator supports
 
 FINALLY
 All operators: keep their default precedence and associativity, this can't be changed
 
 BEST PRACTICE:
 because of the precedence issues, it's best to keep the function of the operators as close
 to the original intent of the operators as possible
 
 Operators: don't have descriptive names, it's not always clear what they are intended to do
 
 BEST PRACTICE:
 If the meaning of the overloaded operator is unclear and unintuitive, use a named function
 instead
 
 Operators: that don't modify their operands, should generally return results by value
 
 Operators: that modify their leftmost operand, should generally return the leftmost operand
 by reference
 
 -------------------------------------------------------------------------------------------
 */

#include <iostream>

int main()
{
    
    
    return 0;
}
