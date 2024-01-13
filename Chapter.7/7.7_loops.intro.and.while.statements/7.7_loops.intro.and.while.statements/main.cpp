//
//  main.cpp
//  7.7_loops.intro.and.while.statements
//
//  Created by εκλεγμένοι εν Χριστώ on 12/20/22.
//

/*
 Loops : control flow statements
 Loops : allow a piece of code to execute repeatedly until some condition is met
 Loops : add significant amount of flexibility into the programming toolkit
 
 Loop types in C++ : 3 types
 
 While statement : simplest of the three loop types
 Syntax :   while (condition)
                statement;
 
 When while statement executes, the condition is evaluated, if condition evaluates to
 true, the associated statement executes, once the statement has finished executing,
 control returns to the top of the while statement and the process is repeated, if
 condition evaluates to false at some point, the statement associated with the loop
 will be skipped, and at this point the loop is done
 
 While statement : keeps looping for as long as the condition evaluates to true
 
 While statements that evaluate to false initially :
 if the condition initially evaluates to false, the associated statement will not
 execute at all
 
 Infinite loops : if the expression always evaluates to true, the while loop will
 execute forever
 
 Intentional infinite loops : common in web server applications that run continuously
 and service web requests
 syntax :
            while (true)
            {
                // this loop executes forever
            }
 the only way to exit an infinite loop is through a return, break, exit, goto,
 an exception being thrown, or user manually killing the program.
 
 best practice : favor while(true) for intentional infinite loops
 
 Loop variable/counter : an integer used to count how many times a loop has executed
 
 Loop variables : often given simple names, like i,j or k.
 
 case : if there is a need to know about where in the program a loop variable is used,
 and to find that if we use the search function on i,j or k, the search function will
 return half of the lines in the program, some devs. prefer names like iii, jjj or kkk
 these names are unique, so search function will return all the lines of the program
 which contain unique loop variables
 
 better idea : is to use real variable names, like "count", "user_count" etc
 
 Loop variables : should be signed, unsigned integers can lead to unexpected issues
 
 best practice : loop variables should be of type (signed int), unsigned can lead to
 unexpected issues.
 
 Iteration : each time a loop executes it is called an iteration
 
 when we want to do something every 2nd, 3rd or 4th iteration, like printing a newline, this
 can easily be done by using the modulus operator on our counter: as below in the
 n_iterations() function definition
 
 Nested loops : it is possible to nest loops inside of other loops
 
 Nested loops : hard for new comers
 
 Nested loop : for each iteration of the outer loop, the body of the outer loop will execute
 once, because the outer loop body contains an inner loop, the inner loop is executed for
 each iteration of the outer loop
 
 declare the variables : in the smallest scope possible
 */

#include <iostream>

void a_z_ascii()
{
    /// Write a program that prints out the letters a through z along with their ASCII codes.
    /// Hint: To print characters as integers, you have to use a static_cast.
    
    char my_char{'a'};
    
    std::cout << "\nLetters : ASCII" << '\n';
    
    /// while loop will run continue until the condition becomes false
    while (my_char <= 'z')
    {
        /// using static_cast to print chars as integers
        std::cout << "'" << my_char << "'       " << static_cast<int>(my_char) << '\n';
        ++my_char;
    }
    std::cout << '\n';
}

/// nested loop
void nested_loops()
{
    int outer_count{1};

    /// outer while loop will execute 10 times with outer_count
    /// having values 1,2.... 10 successively
    while (outer_count <= 10)
    {
        /// on each iteration of the outer loop, the inner count will be
        /// reinitialized to 1
        int inner_count{1};
        
        /// inner while loop will continue to run on each outer loop iteration
        /// until the condition in the inner loop becomes false
        while (inner_count <= outer_count)
        {
            std::cout << "$@ ";
            ++inner_count;
        }
        
        /// printing newline after each outer loop iteration
        std::cout << "\n";
        ++outer_count;
    }
}

void nested_loop_inverted()
{
    int outer{10};
    
    while (outer >= 1)
    {
        int inner{outer};
        while (inner >= 1)
        {
            std::cout << "$@" << ' ';
            --inner;
        }
        std::cout << '\n';
        --outer;
    }
    
    std::cout << "------ END OF THE LOOP ------\n\n";
}

void another_nested_loop()
{
    int outer{1};
    
    while (outer <= 10)
    {
        int inner{10};
        
        while (inner >= 1)
        {
            if (inner <= outer)
                std::cout << "$ ";
            else
                std::cout << "X ";
            
            --inner;
        }
        std::cout << '\n';
        ++outer;
    }
    std::cout << "------ END OF THE LOOP ------\n\n";
}

/// doing something every N iterations
void n_iterations()
{
    /// loop counter
    int count{1};
    
    while (count <= 60)
    {
        /// padding numbers under 10 with a leading 0, formatting the output
        if (count < 10)
            std::cout << '0';
        
        std::cout << count << " ";
        
        /// printing the newline when the count variable is divisible by 10
        if (count % 10 == 0)
            std::cout << "\n";
        
        ++count;
    }
}

/// this is an infinite loop, unless the if condition stops the while loop from executing infinitely
void unsigned_loop_variable()
{
    /// count is unsigned, so it won't be negative ever, this will make the while loop run infinitely
    unsigned int count{10};
    
    while (count >= 0)
    {
        if (count == 4294967290)
        {
            std::cout << "Blastoff, can't execute while loop more!\n";
            /// breaking the while loop to stop the IDE from crashing
            break;
        }
        else
            std::cout << count << '\n';
        /// count wraps around back to 4294967295, 32 bit integer assumed here
        --count;
    }
    
    std::cout << "WHILE LOOP BROKEN\n";
}

void infinite_loop_while()
{
    /// count is never incremented, so it remains 1 forever and loop continues forever
    int count{1};
    while (count <= 10)
    {
        std::cout << "INFINITE LOOP\n";
    }
    
    std::cout << "PRINT STATEMENT WON'T EXECUTE, INFINITE LOOP GOING ON ABOVE\n";
}

void while_false_init()
{
    int count{20};
    /// the condition evaluates to false, no associated statement executes, the print statement after -
    /// the WHILE block executes only
    while (count <= 15)
    {
        std::cout << count << ' ';
        ++count;
    }
    /// this print statement executes, WHILE condition evaluates to false, that's why
    std::cout << "\nWhile condition is evaluated to false initially!\nNo associated statement executes at all!\n";
}

void infinite_loop_intentional()
{
    while (true)
    {
        std::cout << "Loop again? (y/n) : ";
        char c{};
        std::cin >> c;
        
        std::cout << "You selected : " << c << '\n';
        /// until user enters n as input, this loop will run continuously
        /// when IF statement evaluates to true, break will break the while loop
        /// and print statement after the while loop will be printed
        if (c == 'n')
            break;
    }
    
    std::cout << "Loop terminated!\n";
}

int main()
{
    int count{1};
    /// condition evaluates to true, associated block executes
    /// when condition evaluates to false, associated statement with loop will be skipped, loop will be done then
    while  (count <= 10)
    {
        std::cout << count << ' ';
        
        /// incrementing the count, at some point the count becomes greater than 100, loop terminates then
        ++count;
    }   /// control returns to the top of the while statement, condition check happens again
    
    while_false_init();
    
    /// this will execute forever because condition in the while loop is true forever
//    infinite_loop_while();
    
    /// this function continues to execute unless the user enters 'n' as input
    infinite_loop_intentional();
    
    /// unsigned counter variable leads to unexpected issues
    unsigned_loop_variable();
    
    std::cout << '\n';
    n_iterations();
    std::cout << '\n';
    
    nested_loops();
    
    a_z_ascii();
    
    nested_loop_inverted();
    
    another_nested_loop();
    
    return 0;
}
