//
//  main.cpp
//  6.5_variable.shadowing_name.hiding
//
//  Created by εκλεγμένοι εν Χριστώ on 11/9/22.
//

/*
 name hiding/shadowing : when we have a variable inside a nested block that has the
 same name as a variable in an outer block, the nested variable hides the outer
 variables in areas where they are both in scope
 
 When inside the nested block, there’s no way to directly access the shadowed
 variable from the outer block.
 
 shadowing of global variables:
 local variables with same name as a global variable will shadow the global variable
 wherever the local variable is in scope
 
 best practice : avoid variable shadowing, trivially avoidable if all global
 variables use a g_ prefix
 */

#include <iostream>

/// global variable
int x{20};

void g_x()
{
    /// this x refers to the global variable x, because value is not shadowed here
    std::cout << "Global variable decremented: " << x << '\n';
}

int main()
{   /// outer block mangoes
    int mangoes{10};
    
    /// this x refers to the global variable x = 20, no shadowing here, that's why
    std::cout << x << '\n';
    
    /// local variable x, local to main( )
    int x{40};
    
    /// local x incremented here not the global x
    ++x;
    /// this x refers to the local x, local x hides the global x until the end of the main( ) block
    std::cout << "Local variable incremented: " << x << '\n';
    
    /// decrementing the global x using :: operator
    --(::x);
    
    g_x();
    
    {   /// nested block mangoes
        std::cout << mangoes << '\n';
        
        int mangoes{};
        
        /// this mangoes refers to the inner/nested mangoes variable
        /// outer mangoes is hidden here
        std::cout << mangoes << '\n';
    }   /// nested mangoes destroyed here
    
    /// this mangoes refers to the outer block mangoes and not to the nested mangoes
    /// nested mangoes is destroyed by now
    std::cout << mangoes << '\n';
    
    return 0;
}   /// outer block mangoes destroyed here, local x destroyed here
