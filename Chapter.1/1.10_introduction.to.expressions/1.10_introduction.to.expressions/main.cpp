//
//  main.cpp
//  1.10_introduction.to.expressions
//
//  Created by Judah's Leon on 8/25/22.
//

/*
 Expression : combination of literals, variables, operators
 and function calls that can be executed to produce a single
 value
 
 process of executing an expression called : evaluation
 
 produced single value : result
 
 
 literals : evaluates to their own values
 variables : evaluates to the value of variable
 function : evalute to
 operators : combines value to produce a new value
 
 expressions : do not end in a semicolon
 expressions : evaluated as a part of statements
 
 Key insight
 Wherever you can use a single value in C++, you can use an expression instead, and the expression will be evaluated to produce a single value.
 
 Rule
 Values calculated in an expression are discarded at the end of the expression.
 */

#include <iostream>

int two()
{
    return 2;
}

int main()
{
    int a{2};
    int b{2 * 2};
    int c{(2/2) - 3};
    int d{a};
    int e{two()};
    
    /// 2 + 2 : expression, int x{2+2}; : statement as whole with semicolon
    int x{2 + 2};
    
    
    /// expression evaluated and result discarded because of no use
    3 * 3;
    
    /// expression statement, << is binary operator, left is cout and right is x
    std::cout<<x;
    
    
    
    
    
    
    /// simple example
    std::cout<<'\n'<<22+2<<'\n';
    x = 6;
    int y{x-2};
    std::cout<<y<<'\n';
    
    int z{x};
    std::cout<<z-x<<'\n';
}
