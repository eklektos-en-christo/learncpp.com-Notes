//
//  main.cpp
//  5.4_increment.decrement.operators.and.side.effects
//
//  Created by εκλεγμένοι εν Χριστώ on 10/17/22.
//

/*
 +--------------------------------------------------------------------+
 operator           symbol          form            operation
 +--------------------------------------------------------------------+
 prefix increment   ++              ++x             increment x then return x
 prefix decrement   --              --x             decrement x then return x
 postfix increment  ++              x++             copy x, then increment x, then return
                                                    the copy
 postfix decrement  --              x--             copy x, then decrement x, then return
                                                    the copy
 +--------------------------------------------------------------------+
 
 postfix inc/decrement are trickier: first a copy is made, then the operand is incremented
 or decremented(not the copy), then the copy is evaluated.
 
 postfix version: takes a lot more steps, thus may not be performant as the prefix version
 
 Best practice
 strongly favor the prefix version of inc/dec operators, they are more performant, there
 are also less strange issues with them.
 
 Side effect: a function/expression which does anything that persists beyond the life of
 the function or expression itself.
 example: changing the value of objects, doing input/output, updating a GUI(enable/disable
 a button) etc.
 
 C++ standard: does not define the order in which function arguments are evaluated
 
 side effects: all be avoided by making sure that any variable that has a side effect
 applied is used no more than once in a given statement
 
 Warning
 C++ does not define the order of evaluation for function arguments or operator operands.
 
 Warning
 Don’t use a variable that has a side effect applied to it more than once in a given
 statement. If you do, the result may be undefined.
 */

#include <iostream>

int add(int x, int y)
{
    return x + y;
}

int main()
{
    int x{5};
    int y{++x};
    
    /// prefix: x is incremented first, becomes 6 and then x assigned to y, so both are six
    std::cout << x << ' ' << y << '\n';
    
    int a{4};
    int b{a++};
    
    /// postfix: a incremented to 5, copy of original a is evaluated to the value 4, then 4 is assigned to b
    /// explanation: first a copy of a is made, then the original a is incremented to 5, then the copy of a(4) is returned
    /// and assigned to b, then the temporary copy of a(4) is discarded
    std::cout << a << ' ' << b << '\n';
    
    /// some common examples of side effects
    /// the assignment operator changes the state of the object x
    x = 2;
    /// ++ modifies the state of the x
    ++x;
    /// << modifies the state of the console - cout
    std::cout << x << '\n';
    
    int j{2};
    /// ++j argument to function add( ) has a side effect applied
    /// the result depends upon the order of function arguments' evaluation
    /// Don’t use a variable that has a side effect applied to it more than once in a given statement.
    /// If you do, the result may be undefined.
    int value{add(j, ++j)};
    std::cout << value << '\n';
    
    return 0;
}
