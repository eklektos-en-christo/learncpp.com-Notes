//
//  main.cpp
//  7.9_for.statements
//
//  Created by εκλεγμένοι εν Χριστώ on 1/2/23.
//

/*
 most utilized loop statement in CPP : for statement/loop
 
 for statement/loop : preferred when we have an obvious loop variable, it lets us
 easily and concisely define, initialize, test and change the value of loop variables
 
 two different kinds of for loops :
 -classic for statement
 -range based for statement
 
 syntax :       for (init-statement; condition; end-expression)
                    statement;
 
 easiest way to understand for statement is to convert it into an equivalent while
 statement - the above syntax can be converted to while statement as below :
 
            {
                init-statement;     // loop variable, used in the loop
                while (condition)
                {
                    statement;
                    end-expression; // loop variable modifying, prior to the re-check
                                    // of the condition
                }
            }   // variable inside the loop goes out of scope here
 
 
 evaluation of for statements : for statement is evaluated in 3 parts,
 
 PART 1:
 init-statement : executed first, happens only when loop starts
 init-statement : typically used for variable definition and initialization
 these variables: have loop scope which is a form of block scope
 these variables: exist from the point of definition through end of the loop statement
 
 PART 2:
 for each loop iteration : the condition is evaluated
 condition : if this evaluates to true, the statement is executed
 condition : if evaluated to false, the loop terminates and execution continues with
 the next statement beyond the loop
 
 PART 3:
 statement : after it is executed, the end-expression is evaluated
 end-expression : used to increment/decrement the loop variables defined in the init-
 statement
 end-expression : after it's evaluation, execution returns to the (PART 2) and
 condition is evaluated again
 
 loop variables in for loop : can be decremented also
 
 value of the loop variable : we can change the value of our loop variable by more than 1
 with each iteration
 
 perils of != operator in for loop : avoid operator!= when doing numeric comparisons in
 the for loop condition
 
 Off by one errors : when the loop iterates one too many or one two few times to produce the
 desired result
 
 common cause of off by one errors : wrong relational operator used,
 pre-increment/decrement used instead of post increment/decrement or vice versa
 
 Omitted expressions : it is possible to write the For loops that omit any/all of the
 statements/expressions
 
 cases : there are cases where a loop variable's declaration and increment is not desired,
 may because it is incrementing in some other way, or initialized already in some other
 way
 
 C++ standard : explicitly defines that an omitted condition-expression in a for loop
 should be treated as true
 
 for loop : typically iterate over only one variable
 
 for loops with multiple counters : programmer can define multiple variables in init
 statement and can make use of the comma operator to change the value of multiple variables
 in the end expression, this is the only place where defining multiple variables in the
 same statement and use of comma operator is considered an acceptable practice.
 
 best practice : defining multiple variables in init-statement and using comma operator in
 the end-expression is acceptable inside a for statement
 
 Nested for loops : for loops inside the for loop, for loops can be nested inside other
 loops
 
 Best practice
 Prefer for loops over while loops when there is an obvious loop variable.
 Prefer while loops over for loops when there is no obvious loop variable.
 */

#include <iostream>

void sample_for_loop()
{
    std::cout << "FOR-----LOOP\n";
    std::cout << "How many times you want the loop to run?\nEnter here : ";
    int times{};
    std::cin >> times;
    
    for (int count{1}; count <= times; ++count)
    {
        std::cout << "ITERATION : " << count << '\n';
    }
    
    std::cout << '\n';
    
    /// explanation:
    /// STEP 1 - initialization
    /// loop variable count initialized to 1
    /// STEP 2 - condition checking/evaluation
    /// count less than equal to times is evaluated, count is 1, so it evaluates to true
    /// std::cout statement inside the loop executes
    /// STEP 3 - end-expression's evaluation
    /// ++count is evaluated then, it increment to 2
    /// again the loop goes back to STEP 2
    ///
    /// the loop continues until the condition in STEP 2 evaluates to false and loop exits
}

void for_loop_to_while_converted()
{
    std::cout << "WHILE-----LOOP\n";
    std::cout << "How many times you want the loop to run?\nEnter here : ";
    int times{};
    std::cin >> times;
    
    {
        int count{1};
        while (count <= times)
        {
            std::cout << "ITERATION : " << count << '\n';
            ++count;
        }
    }
    
    std::cout << '\n';
}

/// for loop example
/// this function returns the base ^ exponent
std::int64_t power(int base, int exponent)
{
    std::int64_t total{1};
    
    for (int count{0}; count < exponent; ++count)
        total *= base;
    
    return total;
}

void loop_variable_decremented()
{
    for (int count{10}; count >= 1; --count)
        std::cout << count << ' ';
    
    std::cout << '\n';
}

void loop_var_value_change()
{
    int n{1};
    const int five{5};
    
    std::cout << "\n--5's Table--\n";
    
    for (int count{5}; count <= 50; ++n, count += 5)
    {
        std::cout << five << "  x  " << n;
        std::cout << (n == 10 ? " =" : "  =");
        std::cout << (count == 5 ? " 0" : " ") << count << '\n';
    }
    
    std::cout << '\n';
}

void off_by_one_error()
{
    std::cout << '\n';
    
    /// used the wrong relational operator here,
    /// so program is printing undesired output
    /// <= needed here to print the desired output
    for (int count{1}; count < 5; ++count)
        std::cout << count << ' ';
    
    std::cout << '\n';
}

void omitted_expressions()
{
    /// we did the initialization of loop counter manually
    int count{1};
    
    /// no init-statement and expression : omitted
    for (; count <= 10;)
    {
        std::cout << count << ' ';
        /// incrementing manually
        ++count;
    }
    std::cout << '\n';
}

/// this produces an infinite loop
void infinite_for_loop()
{
    for (;;)
        std::cout << "INFINITE FOR LOOP!" << '\n';
}

/// this produces infinite loop also
/// avoid infinite for loop above and prefer while infinite loop
void infinite_while_loop()
{
    while (true)
        std::cout << "INFINITE WHILE LOOP!" << '\n';
}

void multiple_counters()
{
    /// explanation:
    /// definition & initialization : two variables x and y
    /// condition : iterates x over the range 0 to 9
    /// end expression : x increments and y decrements
    std::cout << "+-----------+\n";
    
    for (int x{0}, y{9}; x < 10; ++x, --y)
    {
        std::cout << "| " << x << " | " << y << " | ";
        std::cout << x << " |" << '\n';
        std::cout << "+-----------+\n";
    }
}

void nested_for_loop()
{
    for (char c{'a'}; c <= 'e'; ++c)
    {
        std::cout << c;
        
        for (int i{0}; i < 5; ++i)
        {
            std::cout << i;
        }
            std::cout << '\n';
    }
    std::cout << '\n';
}

int main()
{
    sample_for_loop();

    for_loop_to_while_converted();

    std::cout << power(10, 2) << '\n';

    loop_variable_decremented();

    loop_var_value_change();
    
    /// this loop terminates even when i becomes 11 because of the
    /// less than operator in condition checking
    for (int i{0}; i<10; ++i)
    {
        std::cout << i << ' ';
        if (i == 9)
            ++i;
    }
    
    /// this became an infinite loop, because of != operator in condition checking
    for (int i{0}; i!=10; ++i)
    {
        std::cout << i << ' ';
        if (i == 9)
//            ++i;
            ;
    }
    
    off_by_one_error();
    
    omitted_expressions();
    
//    infinite_for_loop();
    
//    infinite_while_loop();
    
    multiple_counters();
    
    nested_for_loop();
    
    return 0;
}
