//
//  main.cpp
//  5.7_logical.operators
//
//  Created by εκλεγμένοι εν Χριστώ on 10/22/22.
//

/*
 relational operators/comparison operators : test only one condition at at time
 
 logical operators : allow to test multiple conditions
 
 3 logical operators
 +-----------------------------------------------------------------------------+
 Operator           Symbol         Form         Operation
 +-----------------------------------------------------------------------------+
 logical NOT        !              !x           true if x is false or vice versa
 logical AND        &&             x&&y         true if both x and y are true
 logical OR         ||             x||y         true if either x or y are true
 +-----------------------------------------------------------------------------+
 
 logical NOT: flips a boolean value from true to false and vice-versa, it also
 has a high level of precedence
 
 Best practice:
 If logical NOT is intended to operate on the result of other operators,
 the other operators and their operands need to be enclosed in parentheses.
 
 Simple uses of logical NOT, such as if (!value) do not need parentheses
 because precedence does not come into play.
 
 logical OR: is used to test whether either of two conditions is true, if left
 operands evaluates to true of right operand evaluates to true, or even both
 evaluates to true, then the logical OR return true, otherwise it returns false
 
 +----------------------------------------------+
 left operand       right operand       result
 +----------------------------------------------+
 false              false               false
 false              true                true
 true               false               true
 true               true                true
 +----------------------------------------------+
 
 logical AND: used to test whether both operands are true, if both are true,
 then it return true otherwise it returns false
 
 +----------------------------------------------+
 left operand       right operand       result
 +----------------------------------------------+
 false              false               false
 false              true                false
 true               false               false
 true               true                true
 +----------------------------------------------+
 
 Short circuit evaluation: In order for logical AND to return true, both
 operands must evaluate to true. If the first operand evaluates to false,
 logical AND knows it must return false regardless of whether the second
 operand evaluates to true or false. In this case, the logical AND operator
 will go ahead and return false immediately without even evaluating the second
 operand! This is known as short circuit evaluation, and it is done primarily
 for optimization purposes.
 
 warning:
 Short circuit evaluation may cause Logical OR and Logical AND to not evaluate
 one operand. Avoid using expressions with side effects in conjunction with
 these operators.
 
 Only the built-in versions of these operators perform short-circuit evaluation,
 overloaded operators will not perform short-circuit evaluation.
 
 mixing AND and OR:
 When mixing logical AND and logical OR in a single expression, explicitly
 parenthesize each operation to ensure they evaluate how you intend.
 
 De Morgan's law : !(x && y) is not same as !x && !y
 !(x && y) is equivalent to !x || !y
 !(x || y) is equivalent to !x && !y
 this means, when the logical NOT is distributed, the logical AND and logical OR
 need to be flipped and vice versa, this makes the complex expressions easier
 to read.
 
 truth table: de Morgan's law first part, !(x && y) == !x || !y
 +-----------------------------------------------------------------------------+
 x          y           !x          !y          !(x&&y)             !x || !y
 +-----------------------------------------------------------------------------+
 false      false       true        true        true                true
 false      true        true        false       true                true
 true       false       false       true        true                true
 true       true        false       false       false               false
 
 HENCE PROVED THAT !(x && y) == !x || !y
 +-----------------------------------------------------------------------------+
 
 truth table: de Morgan's law first part, !(x || y) == !x && !y
 +-----------------------------------------------------------------------------+
 x          y           !x          !y          !(x||y)             !x && !y
 +-----------------------------------------------------------------------------+
 false      false       true        true        true                true
 false      true        true        false       false               false
 true       false       false       true        false               false
 true       true        false       false       false               false
 
 HENCE PROVED THAT !(x || y) == !x && !y
 +-----------------------------------------------------------------------------+
 
 logical XOR/exclusive: can't be short circuited, logical XOR can be mimicked
 using the inequality operator(!=), != only works if operands are booleans,
 if they are not booleans then static_cast them to bool can help
 +-----------------------------------------------------------------------------+
 left operand           right operand               result
 +-----------------------------------------------------------------------------+
 false                  false                       false
 false                  true                        true
 true                   false                       true
 true                   true                        false
 +-----------------------------------------------------------------------------+
 
 Alternative operator representations:
 Operator name    Keyword alternate name
 &&               and
 ||               or
 !                not
 */

#include <iostream>

int main()
{
    int x{10};
    bool too_large{x < 100};
    
    /// logical NOT flips the result of boolean variable from true to false
    /// so else gets executed
    if (!too_large)
        std::cout << "large" << '\n';
    else
        std::cout << "small" << '\n';
    
    /// !20 evaluates to 0, because ! has higher precedence than <
    if (!20 > 10)
        std::cout << "not greater" << '\n';
    else
        std::cout << "greater" << '\n';
    
    /// using ( ) to evaluate 20 > 10 first and then !
    if (!(20 > 10))
        std::cout << "greater" << '\n';
    else
        std::cout << "not greater" << '\n';
    
    /// using OR operator below
    std::cout << "Enter value: ";
    int value{};
    std::cin >> value;
    
    /// stringing together many logical OR statements
    if (value == 0 || value == 1 || value == 2)
        std::cout << "You've entered 0, 1 or 2." << '\n';
    
    std::cout << "Enter value: ";
    std::cin >> value;
    
    /// stringing together many logical AND statements
    if (value > 10 && value < 20 && value != 15)
        std::cout << "Yes, it is in between 10 and 20" << '\n';
    else
        std::cout << "No!" << '\n';
    
    /// using != operator as XOR operator below
    bool a{true};
    bool b{false};

    bool res{a != b};
    std::cout << "XOR: " << res << '\n';
    
    /// alternative operator representations
    /// && - and, || - or, ! - not
    std::cout << "AND: " << (a and b) << '\n';
    std::cout << "OR: " << (a or b) << '\n';
    std::cout << "NOT: " << (not a) << '\n';
    
    return 0;
}
