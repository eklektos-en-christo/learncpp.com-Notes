//
//  main.cpp
//  1.9_introduction.to.literals.and.operators
//
//  Created by Judah's Leon on 8/25/22.
//

/*
 Literal/literal constant : a fixed value that has been inserted
 directly into the source code
 
 literals & variables : have a value + type
 value of literal : fixed, can't be changed, hence literal constant
 value of variable : can be changed
 
 operators : symbols or pair of symbols used to denote an operation between two
 operands
 
 2 + 2 = 4
 
 2, 2 : operands
 
 + : operator
 
 new, delete and throw : also called operators
 
 Arity : no. of operands than an operator can take as input
 arities : unary, binary, ternary
 
 unary operators : act on one operand, like -2, - will flips 2's sign to produce new
 output value -2
 
 binary operators : act on two operands, called left or right operands
 2 + 2 : left 2 and right 2 gives 4, + is binary operator
 << and >> : binary operators, << takes std::cout on the left side and on the right
 side user output, also same with >> operator which takes on its right side the input
 from the user
 
 ternary operators : act on three operands
 
 some operators : have more than one meaning depending upon how they used, example
 -5 will invert the 5's sign, 2 - 2 will subtract.
 
 
 
 chaining operators : taking output of one operator and using that output as input
 for another operator
 2 * 3 + 4 : * operates first on 2 and 3 and that ouput is used as input on the left
 of + operator.
 
 arithmetic operators : executes in the same order as they do in standard mathematics

 PEMDAS : parenthesis then exponents then multiplication and division then addition..
 and subtraction
 PEMDAS, PEDMAS, BEDMAS, BODMAS or BIDMAS : in some countries
 */

#include <iostream>

int main()
{
    // literals below : fixed values directly inserted into the source code
    std::cout<<"A string literal\n";
    int x{2};
}
