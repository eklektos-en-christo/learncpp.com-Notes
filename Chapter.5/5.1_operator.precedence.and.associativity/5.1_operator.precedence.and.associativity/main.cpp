//
//  main.cpp
//  5.1_operator.precedence.and.associativity
//
//  Created by εκλεγμένοι εν Χριστώ on 10/15/22.
//

/*
 compound expression: expression that has multiple operators
 
 operator's precedence: the order in which operators are evaluated
 in a compound expression is determined by their precedence
 
 precedence: operators with higher precedence are evaluated first
 
 operator associativity: if two operators in the same expression
 have the same precedence level and both are adjacent to each
 other, then it's associativity tells the compiler whether to
 evaluate the operators from left to right or from right to left,
 
 Table of operators:
 +---------------------------------------------------------------------------------------+
 precedence associativity   operator    description                 Pattern
 +---------------------------------------------------------------------------------------+
 1          L->R            ::          globalscope(unary)          ::name
                            ::          namespace scope(binary)     class::member
 +---------------------------------------------------------------------------------------+
 2          L->R            ()          parentheses                 (expression)
                            ()          function call               function()
                            ()          initialization              type name(expression)
                            {}          uniform initialization      type name(expression)
                            type()      functional cast             new_type(expression)
                            type{}      functional cast             new_type{expression}
                            []          array subscript             pointer[expression]
                            .           member access from object   object.member_name
                            ->          member access from obj. ptr obj_ptr->member_name
                            ++          post increment              lvalue++
                            --          post decrement              lvalue--
                            typeid      runtime type information    typeid(type)/
                                                                    typeid(expression)
                            const_cast  cast away const             const_cast<type>(exp.)
                            dynamic_cast
                                        runtime type-checked cast   dynamic_cast<type>(exp)
                            reinterpret_cast
                                        cast one type to another    reinterpret_cast<type>
                                                                    (expression)
                            static_cast compile-time type checked
                                        cast                        static_cast<type>(exp.)
                            sizeof...   get parameter pack size     sizeof...(expression)
                            noexcept    compile-time exception      noexcept(expression)
                                        check
                            alignof     get type alignment          alignof(type)
 +---------------------------------------------------------------------------------------+
 3          R->L            +           unary plus                  +expression
                            -           unary minus                 -expression
                            ++          pre increment               ++lvalue
                            ––          pre decrement               --lvalue
                            !           logical NOT                 !expression
                            ~           bitwise NOT                 ~expression
                            (type)      c-style cast                (new_type)expression
                            sizeof      size in bytes               sizeof(type)
                                                                    /sizeof(expression)
                            co_await    await asynchronous call     co_await expression
                            &           address of                  &lvalue
                            *           dereference                 *expression
                            new         dynamic memory allocation   new type
                            new[]       dynamic array allocation    new type[expression]
                            delete      dynamic memory deletion     delete pointer
                            delete[]    dynamic array deletion      delete[] pointer
 +---------------------------------------------------------------------------------------+
 4          L->R            ->*         member pointer selector     obj_pointer->*
                                                                    pointer_to_member
                            .*          member object selector      object.*
                                                                    pointer_to_member
 +---------------------------------------------------------------------------------------+
 5          L->R            *           multiplication              expression*expression
                            /           division                    expression/expression
                            %           modulus                     expression%expression
 +---------------------------------------------------------------------------------------+
 6          L->R            +           addition                    expression+expression
                            -           subtraction                 expression+expression
 +---------------------------------------------------------------------------------------+
 7          L->R            <<          bitwise shift left          expression<<expression
                            >>          bitwise shift right         expression>>expression
 +---------------------------------------------------------------------------------------+
 8          L->R            <=>         three way comparison        expression<=>exp.
 +---------------------------------------------------------------------------------------+
 9          L->R            <           less than                   expression<expression
                            <=          less than or equals         expression<=exp.
                            >           greater than                expression>expression
                            >=          greater than or equals      expression>=exp.
 +---------------------------------------------------------------------------------------+
 10         L->R            ==          equality                    expression==exp.
                            !=          inequality                  expression!=exp.
 +---------------------------------------------------------------------------------------+
 11         L->R            &           bitwise AND                 expression&expression
 +---------------------------------------------------------------------------------------+
 12         L->R            ^           bitwise XOR                 expression^expression
 +---------------------------------------------------------------------------------------+
 13         L->R            |           bitwise OR                  expression|expression
 +---------------------------------------------------------------------------------------+
 14         L->R            &&          logical AND                 expression && exp.
 +---------------------------------------------------------------------------------------+
 15         L->R            ||          logical OR                  expression || exp.
 +---------------------------------------------------------------------------------------+
 16         R->L            throw       throw expression            throw expression
                            co_yield    yield expression            co_yield expression
                            ?:          conditional                 exp. ? exp. : exp.
                            =           assignment                  lvalue = expression
                            *=          multiplication assignment   lvalue *= expression
                            /=          division assignment         lvalue /= expression
                            %=          modulus assignment          lvalue %= expression
                            +=          addition assignment         lvalue += expression
                            -=          subtraction assignment      lvalue -= expression
                            <<=         bitwise shift left          lvalue <<= expression
                                        assignment
                            >>=         bitwise shift right         lvalue >>= expression
                                        assignment
                            &=          bitwise AND assignment      lvalue &= expression
                            |=          bitwise OR assignment       lvalue |= expression
                            ^=          bitwise XOR assignment      lvalue ^= expression
 +---------------------------------------------------------------------------------------+
 17         L->R            ,           comma operator              expression, expression
 +---------------------------------------------------------------------------------------+
 
 
 Parenthesization : can change the order of application of operations, parentheses have
 one of the highest precedence levels, parentheses generally evaluate before whatever is
 inside them
 
 Best practice
 Use parentheses to make it clear how a non-trivial expression should evaluate (even if they are
 technically unnecessary).
 
 Best practice
 Expressions with a single assignment operator do not need to have the right operand of the
 assignment wrapped in parenthesis.
 
 Warning
 In many cases, the operands in a compound expression may evaluate in any order. This includes
 function calls and the arguments to those function calls.
 
 Best practice
 Outside of the operator precedence and associativity rules, assume that the parts of an
 expression could evaluate in any order. Ensure that the expressions you write are not
 dependent on the order of evaluation of those parts.
 */

#include <iostream>

int get_value()
{
    std::cout << "Enter the integer:";
    int x{};
    std::cin >> x;
    
    return x;
}

int main()
{
    /// instead of this
    int x = (2 + 2 + 2);
    /// it's okay to do this
    ///
    /// Best practice
    /// Expressions with a single assignment operator do not need to have the right operand
    /// of the assignment wrapped in parenthesis.
    x = 2 + 2 + 2;
    
    /// instead of this
    x = ((x || x) && x);
    /// it's okay to do this
    x = (x || x) && x;
    
    /// parenthesis are beneficial here because of multiple assignments
    x = (x *= 2);
    
    /// order of evaluation matters in the below expression, order depends upon the calls made to the get_value( )
    std::cout << get_value() + (get_value() * get_value()) << '\n';
    
    /// order of evaluation does't matter here
    int a{get_value()};
    int b{get_value()};
    int c{get_value()};
    std::cout << a + (b * c) << '\n';
    
    return 0;
}
