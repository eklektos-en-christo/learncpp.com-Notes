//
//  main.cpp
//  7.4_switch.statement.basics
//
//  Created by εκλεγμένοι εν Χριστώ on 12/14/22.
//

/*
 It is possible to chain many if-else statements together, this is difficult to read
 and inefficient
 
 Switch statement : conditional statement, for testing a variable or expression for
 equality against a set of different values.
 
 Idea behind switch statement : an expression(condition) is evaluated to produce a
 value, if expression's value is equal to the value after any of the case labels,
 the statements after the matching case label are executed, if no matching value can
 be found and if default label exists, the statement after the default label are
 executed
 
 switch statement : has the advantage over the if statement of only evaluating the
 expression once(which means more efficiency)
 
 switch statement : also makes clearer that it is the same expression being tested for
 equality in each case.
 
 best practice : prefer switch statements over if-else chains when there is a choice
 
 Starting a switch :
 switch statement is started with switch keyword, followed by parentheses with
 conditional expression inside that we want to evaluate, expression inside often is
 just a single variable, it can be any valid expression
 
 the condition must evaluate to an integral type or an enumerated type or be
 convertible to one, expressions that evaluate to floating types, strings and most
 other non-integeral types may not be used here
 
 Why switch type only allow for integeral types?
 switch statements - designed to be highly optimized, historically, most common way
 for compilers to implement switch statements is via JUMP TABLES, jump tables only
 work with integral values
 
 following the conditional expression, we declare a block, inside the block, we use
 labels to define all the values we want to test for equality.
 
 two kinds of labels : case label & default label
 
 case labels : declared using case keyword, followed by a constant expression,
 contant expression must either match the type of the condition or must be convertible
 to that type, if value of conditional expression equals the expression after a case
 label, then execution begins at the first statement after the case label, then case
 label continues sequentially
 
 all case labels in switch : must be unique
 
 default label/default case : declared using the default keyword, if the conditional
 expression doesn't match any case label and if the default label exists, then
 the execution begins at the first statement after the default label
 
 default label :  there can only be one default label per switch
 
 default case : by default it is place last in the switch block
 
 best practice : place the default case last in the switch block
 
 taking a break :
 return statements in switch cases exits the entire function
 break statements : declared using the break keyword, tells the compiler that we are
 done executing statements within the switch block and execution should continue with
 the statement after the end of the switch block, this allows to exit a switch
 statement without exiting the function
 
 best practice:
 each set of statements underneath a label should end in a break or return statement
 this includes the statements underneath the last label in the switch
 */

#include <iostream>

/// testing a variable against a set of different value using switch statement, inefficient
void print_digit_name_ifelse(int x)
{
    if (x == 1)
        std::cout << "ONE" << '\n';
    else if (x == 2)
        std::cout << "TWO" << '\n';
    else if (x == 3)
        std::cout << "THREE" << '\n';
    else
        std::cout << "UNKNOWN" << '\n';
}

/// testing a variable against a set of different value using switch statement
/// when case matches with the condition, the statements inside the case executes sequentially
/// then we return to the caller
/// if conditional expression does not match any of the case labels, no cases are executed
void print_digit_name_switch(int x)
{
    switch (x)
    {
        case 1:
            std::cout << "ONE" << '\n';
            return;
        case 2:
            break;  /// this will break the switch statement and statement after the switch block executes
            std::cout << "TWO" << '\n';
            return;
        case 3:
            std::cout << "THREE" << '\n';
            return;
//        default:
//            std::cout << "UNKNOWN" << '\n';
//            break;
    }
    
    /// this will execute if not default case is provided and if there is no case label matching
    std::cout << "SWITCH BLOCK EXITED : NO DEFAULT CASE PROVIDED" << '\n';
}

int main()
{
    print_digit_name_ifelse(4);
    
    print_digit_name_switch(2);
    
    return 0;
}
