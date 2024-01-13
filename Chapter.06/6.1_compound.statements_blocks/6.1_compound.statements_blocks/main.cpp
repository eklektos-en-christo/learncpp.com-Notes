//
//  main.cpp
//  6.1_compound.statements_blocks
//
//  Created by εκλεγμένοι εν Χριστώ on 10/31/22.
//

/*
 compound statement/block/block statement: group of zero or more
 statements that is treated by the compiler as if it is a single
 statement
 
 blocks: begin with a { and end with }, the statements are placed in
 between {}.
 
 blocks: can be used anywhere a single statement is allowed.
 
 blocks: no semicolon is needed at the end of the {} as in case of a
 single statement
 
 blocks inside other blocks/Nested blocks: blocks can be nested inside other blocks,
 the enclosing block is typically called the outer block and the
 enclosed block is called the inner block or nested block.
 
 by default: if statement executes only single statement, block of
 statements can be used instead of single statement to execute multiple
 statements
 
 nesting level/nesting depth : max. no. of nested blocks inside at any
 point in the function(including the outer block)
 
 C++ standard : compilers should support 256 levels of nesting
 
 best practice: Keep the nesting level of your functions to 3 or less.
 If your function has a need for more nested levels,
 consider refactoring your function into sub-functions.
 (with the most-nested blocks becoming separate functions).
 */

#include <iostream>

int add(int x, int y)
{   /// start block
    return x + y;
}   /// end block, no semicolon needed

/// there are four blocks in this function
/// nesting level is three
/// because at any point you can never be inside more than 3 blocks
void nest_function()
{
    std::cout << "block 1, nesting level 1" << '\n';
    
    if (2 > 0)
    {
        std::cout << "block 2, nesting level 2" << '\n';
        if (2 > 0)
        {
            std::cout << "block 3, nesting level 3" << '\n';
        }
        if (2 == 2)
        {
            std::cout << "block 4, nesting level 3" << '\n';
        }
    }
}

int main()
{   /// start block
    
    /// multiple statements inside the block of main( )
    int x{};
    x = add(2, 2);
    std::cout << x << '\n';
    
    {   /// outer block
        add(10, 2);
        
        {   /// nested/inner block
            add(2, 3);
        }   /// end of nested/inner block
        
    }   /// end of outer block
    
    std::cout << "Enter an integer: ";
    int value{};
    std::cin >> value;
    
    /// executing multiple statements in a block if condition evaluates to true
    if (value >= 0)
    {
        std::cout << "Number is positive" << '\n';
        std::cout << "Double of number is : " << value * 2 << '\n';
    }
    else    /// else block executes if the condition above is false
    {
        std::cout << "Number is negative" << '\n';
        std::cout << "Positive of number is : " << -value << '\n';
    }
    
    nest_function();
    
    return 0;
}   /// end block, no semicolon
