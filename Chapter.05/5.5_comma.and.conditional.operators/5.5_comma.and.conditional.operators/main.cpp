//
//  main.cpp
//  5.5_comma.and.conditional.operators
//
//  Created by εκλεγμένοι εν Χριστώ on 10/19/22.
//

/*
 comma operator: evaluate multiple expressions wherever a single
 expression is allowed, it evaluates the left then right then returns
 the result of the right operand.
 
 +--------------------------------------------------------------------+
 OPERATOR       SYMBOL          FORM       OPERATION
 +--------------------------------------------------------------------+
 comma          ,               x,y        evaluate x then y, return y
 +--------------------------------------------------------------------+
 
 comma operator: avoid using the comma operator except within the for
 loops
 
 comma as a separator: often comma is used as a separator in function
 definition, function calls and this is valid to do
 never use comma to declare multiple variables.
 
 Conditional operator: also called arithmetic if operator, compacts the
 code without losing readability.
 conditional operator: also referred to as "the ternary operator".
 conditional operator: shorthand method for doing a particular type of
 if/else statement.
 
 syntax:    (condition) ? expression 1 : expression 2;
 expression 2: is not optional as this is in if/else statement.
 explanation:   if condition evaluates to true, expression 1 executes,
 if condition is false then expression 2 executes.
 
 +--------------------------------------------------------------------+
 OPERATOR       SYMBOL          FORM       OPERATION
 +--------------------------------------------------------------------+
 conditional    ?:              c?a:b       if c is true/nonzero,
                                            evaluate a otherwise
                                            evaluate b
 +--------------------------------------------------------------------+
 
 ?: - has a very low precedence, so it is better to wrap the whole ?:
 operator in parentheses.
 
 Best practice
 Always parenthesize the conditional part of the conditional operator,
 and consider parenthesizing the whole thing as well.
 
 conditional operator ?: - evaluates as an expression.
 ?: operands: are expressions rather than statements, so the ?: can
 be used where the if/else can not.
 
 ?: - in conditional operator, the type of the expressions must
 match or it must be convertible to same type.
 
 use of ?: operator: use this operator for simple conditionals
 where the result is used and also where the readability is
 enhanced by using it.
 */

#include <iostream>

int main()
{
    int a{1};
    int b{2};
    
    /// expression below evaluates to the right operand
    std::cout << (++a, ++b) << '\n';
    
    int c{(a, b)};
    /// (a, b) evaluated first to get the value of b, then assigned that value to c
    std::cout << c << '\n';
    
    c = a, b;
    /// evaluated as (c = a), b, a assigned to c and b evaluated then b discarded
    /// this makes comma operator somewhat dangerous to use, avoid using it
    std::cout << c << '\n';
    
    a = 20;
    b = 19;
    /// conditional operator's/ternary operator's use below
    int larger{(a > b) ? a : b};
    std::cout << larger << '\n';
    
    /// parenthesizing the whole conditional operator and the whole thing
    /// otherwise the result will be wrong
    std::cout << ((a > b) ? a : b) << '\n';
    
    /// using ?: where if/else cannot be used
    /// ?: - evaluates as an expression
    /// ?: operands are expressions rather than statements
    /// another way of doing this is to use a function that checks
    /// the condition and return the value to the
    /// variable as the initialization value
    constexpr bool in_big_classroom{false};
    constexpr int class_size{in_big_classroom ? 40 : 10};
    std::cout << class_size << '\n';
    
    constexpr int x{2};
    /// error: incompatible types of the operands, one is integer and another is
    /// C-style string literal
    /// the compiler here is unable to determine a common type for expressions of
    /// these types
    /// to make this compile, if/else can be used
//    std::cout << (x != 2 ? x : "x is 2") << '\n';
    if (x != 2)
        std::cout << x << '\n';
    else
        std::cout << "x is 2" << '\n';
    
    return 0;
}
