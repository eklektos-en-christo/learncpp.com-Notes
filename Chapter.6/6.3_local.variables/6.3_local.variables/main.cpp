//
//  main.cpp
//  6.3_local.variables
//
//  Created by εκλεγμένοι εν Χριστώ on 11/2/22.
//

/*
 identifier in scope : when it can be accessed
 identifier not in scope : when it can't be accessed
 
 scope : compile time property
 
 local variables : have block scope, they remain in scope from the
 point of their definition to the end of the block they are defined
 within
 
 function parameters : part of the the scope of the function body block
 
 All variable names within a scope : must be unique
 
 local variables : have automatic storage duration
 
 storage duration : determines what rules govern when and how a variable
 will be created and destroyed
 
 storage duration : determines variable's lifetime
 
 automatic storage duration : means variables created at the point of
 definition and destroyed at the end of the block they are defined in.
 
 variables defined in the outer block : can be seen inside a nested
 block.
 
 linkage : identifier's property
 
 linkage : of an identifier determines whether other declarations of
 that identifier/name refer to the same object or not.
 
 local variables : have no linkage, each declaration refers to a
 unique object
 
 scope vs linkage : scope defines where a single declaration can be used
 linkage defines whether mutiple declarations refer to the same object
 or not.
 
 variables : should be defined in a most limited scope, must be defined
 where they are needed, reduces complexity of the program, reduces the
 no. of active variables in the memory.
 
 variable : defined within a block can be used within that block or
 nested blocks
 
 Best practice:
 Define variables in the most limited existing scope. Avoid creating
 new blocks whose only purpose is to limit the scope of variables.
 */

#include <iostream>

int add(int x, int y)
{
    /// variables within a scope must be unique
    /// compiler error because of name collision with function parameters
//    int x{};
//    int y{};
    
    return x + y;
}

void add_nested()
{
    int x{2};
    
    {
        int y{2};
        std::cout << "Nested: " << x + y << '\n';
    }
    
    /// y can't be used here because it is out of scope here
//    std::cout << "Nested: " << x + y << '\n';
}

void linkage()
{
    int a{20};
    std::cout << "outer: " << a << '\n';
    
    {
        /// outer a
        std::cout << "nested, linkage to outer: " << a << '\n';
        
        /// this a is different from outer a, it's unique
        int a{2};
        std::cout << "nested, no linkage to outer: " << a << '\n';
    }
}

void limited_scope()
{
    {
        /// x is used here, so defined here
        int x{2};
        std::cout << "nested, limited scope: " << x << '\n';
    }   /// x is destroyed here, limited scope, so no. of active variables is reduced, complexity reduced
    /// x can't be used here because it's not needed now
}

void quiz_ques()
{
    std::cout << "Enter an integer: ";
    int smaller{};
    std::cin >> smaller;
    
    std::cout << "Enter a larger integer: ";
    int larger{};
    std::cin >> larger;
    
    {
        if (larger < smaller)
        {
            std::cout << "Swapping the values" << '\n';
            
            int temp{larger};
            larger = smaller;
            smaller = temp;
        }
    }   /// temp dies here, limited the scope of temp
    
    std::cout << "Smaller value: " << smaller << '\n';
    std::cout << "Larger value: " << larger << '\n';
}

int main()
{
    /// x - local variable with automatic storage duration
    int x{2};                   /// x enters scope here, created
    std::cout << x << '\n';
    
    add_nested();
    linkage();
    limited_scope();
    quiz_ques();
    
    return 0;
}                               /// x goes out of scope here, destroyed
