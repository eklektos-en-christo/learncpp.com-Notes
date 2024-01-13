//
//  main.cpp
//  5.2_arithmetic.operators
//
//  Created by εκλεγμένοι εν Χριστώ on 10/16/22.
//

/*
 unary arithmetic operators: that take only operand
 unary arithmetic operators: plus(+) and minus(-)
 
 +------------------------------------------------------------+
 operator           symbol      form        operation
 +------------------------------------------------------------+
 unary plus         +           +x          value of x
 unary minus        -           -x          negation of x
 +------------------------------------------------------------+
 
 unary minus: returns the operand multiplied by -1
 example: x = 5, -x will be -5
 unary plus: return the value of the operand
 example: x = 5, +x will be 5 only
 
 both unary plus and minus: should be placed immediately preceding the
 operand without any space. like -x and not - x
 
 binary arithmetic operators: that take left and right operand
 5 binary arithmetic operators:
 +--------------------------------------------------------------------+
 operator           symbol      form        operation
 +--------------------------------------------------------------------+
 addition           +           x + y       x plus y
 subtraction        -           x - y       x minus y
 multiplication     *           x * y       x multiplied by y
 division           /           x / y       x divided by y
 modulus(remainder) %           x % y       remainder of x divided by y
 +--------------------------------------------------------------------+
 
 integer and floating point division-
 
 division operator have two different modes:
 1. if both or one operands are floating point values, then the
 division operator performs floating point division, floating point
 division returns a floating point value and fraction is kept. rounding
 errors may occur with floating point numbers.
 example:
 if one operand is floating point
 7.0/4 = 1.75
 if one operand is floating point
 7/4.0 = 1.75
 if both operands are floating point
 7.0/4.0 = 1.75
 
 2. if both the operands are integers, then division operator performs
 integer division, integer division drops the fractions and returns an
 integer value
 example:
 if both operands are integers, fraction dropped
 7/4 = 1
 if one operand is a negative integer, fraction is still dropped
 -7/4 = -1
 
 static cast: we can do floating point division with integers using
 static cast.
 
 dividing by zero: trying to divide by 0/0.0 will generally cause
 the program to crash, because the results are mathematically undefined
 
 arithmetic assignment operators: they perform arithmetic and
 assignment both operation together
 +--------------------------------------------------------------------+
 operator           symbol      form        operation
 +--------------------------------------------------------------------+
 assignment         =           x = y       assign value y to x
 addition assign.   +=          x += y      add y to x
 subtraction assign.-=          x -= y      subtract y from x
 multi. assignment  *=          x *= y      multiply x by y
 division assign.   /=          x /= y      divide x by y
 modulus assign.    %=          x %= y      put remainder of x/y in x
 +--------------------------------------------------------------------+
 */

#include <iostream>

int main()
{
    /// program crash: division by zero is undefined
//    std::cout << 12 / 0 << '\n';
    
    /// floating point division
    std::cout << 2.2 / 2 << '\n';
    std::cout << 2 / 2.2 << '\n';
    std::cout << 2.222 / 2.2 << '\n';
    
    /// integer division
    std::cout << 22 / 2 << '\n';
    std::cout << -22 / 2 << '\n';
    
    int x{11};
    int y{2};
    
    /// using static cast to do the floating point division instead of integer division
    /// this also shows that if one operand is a floating point number then the result will
    /// be a floating point division and not integer division
    std::cout << "int/int: " << x / y << '\n';
    std::cout << "double/int: " << static_cast<double>(x) / y << '\n';
    std::cout << "int/double: " << x / static_cast<double>(y) << '\n';
    std::cout << "double/double: " << static_cast<double>(x) / static_cast<double>(y) << '\n';
    
    int a = 2;
    /// old fashioned, clunky and outdated
    a = a + 2;
    /// C++ way of doing it
    /// this means add 2 to existing value of a
    /// it first adds 2 to a's value and then assigns that output to a
    a += 2;
    
    std::cout << a << '\n';
    
    return 0;
}
