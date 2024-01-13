//
//  main.cpp
//  7.14_common.semantic.errors.in.cpp
//
//  Created by εκλεγμένοι εν Χριστώ on 1/18/23.
//

/*
 Semantic errors : occur when the code written does not do what it was intended to do
 
 Compilers: generally won't catch semantic errors, in some cases smart compilers may be able
 to generate a warning
 
 Undefined behavior : semantic errors can cause most of the same symptoms of undefined
 behavior, causing program to produce wrong results, causing unpredictable behavior,
 corrupting program data, causing the program to crash, or having no impact at all
 
 Almost inevitable : that programmer will make semantic errors
 
 Testing the program : can also help surface the semantic errors
 
 One another thing that can help : knowing the most common type of semantic errors
 
 Most common types of semantic errors : have to do with flow control in some way
 
 Conditional logic errors : when programmer incorrectly codes the logic of a conditional
 statement or loop condition
 
 Infinite loops : count increment/decrement problem
 
 Off by one errors : that occurs when a loop executes one too many one two few times
 
 Incorrect operator precedence : use explicit parenthesization to avoid these errors
 
 Precision issues with floating point types : lack of precision can cause the number to
 round slightly, operator== and operator!= can be problematic with floating point numbers
 due to small rounding errors
 
 Integer division : static_cast can be used to convert one of the integral operands to a
 floating point value to do floating point division
 
 Accidental null statements : statements that do nothing
 
 Not using a compound statement when one is required : not using {} where they are required
 */

#include <iostream>

/// conditional logic error in the below function:
void conditional_logic_error()
{
    std::cout << "Enter an integer: ";
    int x{};
    std::cin >> x;
    
    /// conditional logic error : used operator>= instead of operator>, x>=5 evaluates to true when user enters 5
    if (x >= 5)
        std::cout << x << " is greater than 5\n";
}

void conditional_logic_error_loop()
{
    std::cout << "Enter an integer: ";
    int x{};
    std::cin >> x;
    
    /// conditional logic error : used operator> instead of operator<, loop never iterates at all
    for (int count{1}; count > x; ++count)
        std::cout << count << ' ';
    std::cout << '\n';
}

void infinite_loop()
{
    int count{1};
    /// this condition will never be false, because we forgot to increment count variable
    /// the loop runs until the user shuts down the program
    while (count <= 10)
        std::cout << count << ' ';
    std::cout << '\n';
}

void quiz_question()
{
    /// count keeps decrementing when it is an unsigned integer
    for (unsigned int count{5}; count >= 0; --count)
    {
        if (count == 0)
            std::cout << "BLASTOFF! ";
        else
            std::cout << count << ' ';
    }
}

void off_by_one_error()
{
    /// wrong relational operator< used instead of operator<=
    /// so loop executes one fewer times than intended, printing 1,2,3,4,5
    for (unsigned int count{1}; count < 5; ++count)
        std::cout << count << ' ';
    std::cout << '\n';
}

void incorrect_operator_precedence()
{
    int x{2};
    int y{10};
    
    /// the conditional evaluates as if it is (!x > y), which isn't the intent of the programmer
    /// this can also happen when mixing the logical OR and logical AND in the same expression
    if (!x > y)
        std::cout << x << " is not greater than " << y << '\n';
    else
        std::cout << x << " is greater than " << y << '\n';
}

void floating_precision_problem()
{
    float f{0.123456789f};
    /// lack of precision, the number is rounded slightly
    std::cout << f << '\n';
    
    /// should be 1.0
    double d{0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 };
    
    /// the condition evaluates to false, because of small rounding error in d
    if (d == 1.0)
        std::cout << "EQUAL\n";
    else
        std::cout << "NOT EQUAL\n";
}

void integer_division()
{
    int a{21};
    int b{2};
    
    /// both operands are integers, so integer division has happened
    std::cout << a << '/' << b << ": " << a / b << '\n';
    /// both operands are integers, but static_cast used to perform the floating point division
    std::cout << a << '/' << b << ": " << static_cast<float>(a) / b << '\n';
}

void blow_up_world()
{
    std::cout << "Blow up the world again? Y/N: ";
    char c{};
    std::cin >> c;
    
    /// accidental null statement i.e. ';' after the IF() caused the world to blow up again
    if (c == 'Y');
    /// this print statement is not a part of the IF() statement
        std::cout << "BOOM!!!" << '\n';
}

void compound_statement_not_used()
{
    std::cout << "Blow up the world again? Y/N: ";
    char c{};
    std::cin >> c;
    
    if (c == 'y')
        std::cout << "Here we go...\n";
    /// this print should be inside the IF{} block
        std::cout << "BOOM!!!\n";
}

int main()
{
    conditional_logic_error();
    conditional_logic_error_loop();
//    infinite_loop();
//    quiz_question();
    off_by_one_error();
    incorrect_operator_precedence();
    floating_precision_problem();
    integer_division();
    blow_up_world();
    compound_statement_not_used();
    
    return 0;
}
