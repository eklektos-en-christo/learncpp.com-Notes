//
//  main.cpp
//  2.5_intro.to.local.scope
//
//  Created by εκλεγμένοι εν Χριστώ on 9/3/22.
//

/*
 local variables: function parameters as well as variables
 defined inside the function body
 
 local variable: parameters created and initialized when
 function is entered, variable within the function created
 and initialized at the point of definition
 
 local variable destruction: they are destroyed at the end of
 the set of curly braces
 parameters: destroyed at the end of the function
 
 lifetime: time between creation and destruction
 lifetime: is a runtime property not compile time
 
 objects: must be created and initialized no later than the
 point of definition, destroyed no earlier than the end of
 the set of the curly braces in which they are defined, para
 meters destroyed at the end of the function
 
 in cpp, objects: may be created earlier and destroyed later
 for optimization purposes
 
 local scope: determines where the identifier can be accessed
 within the source code.
 In scope: when can be accessed
 out of scope: when can't be accessed
 scope: compile time property
 out of scope identifier use : error
 
 one function's local variable: not in scope in another
 functions that are called
 
 out of scope: term applies to identifier/variable
 going out of scope: term applies to object
 
 local variable lifetime: ends at the point where it goes out
 of scope, or destroyed
 
 not all variables: destroyed when they go out of scope
 
 variable inside one function are distinct from the variables
 in another function
 
 one function's variable: visible/usable inside that function
 only
 
 scopes: don't overlap
 
 Key insight
 Names used for function parameters or variables declared in a function body are only visible within the function that declares them. This means local variables within a function can be named without regard for the names of variables in other functions. This helps keep functions independent.
 
 Where to define local variables: should be defined as close
 to their first use, reasonable
 
 Best practice
 Define your local variables as close to their first use as reasonable.
 */

#include <iostream>

int test(int x, int y)  /// x and y created and initialized here
{
    return x + y;
}/// x and y destroyed here


/// x is not in scope in this function
void do_some()
{
    std::cout << "Hello" << '\n';
}

int main()
{
    /// x created, enters scope here, can be used now
    int x{};
    std::cout <<"x: " << x << '\n';
    
    do_some();
    
    return EXIT_SUCCESS;
}   /// x goes out of scope here, no longer can be used
