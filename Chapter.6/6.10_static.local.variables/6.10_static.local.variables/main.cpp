//
//  main.cpp
//  6.10_static.local.variables
//
//  Created by εκλεγμένοι εν Χριστώ on 11/21/22.
//

/*
 Use of static keyword when applied to a local variable
 
 local variables : have automatic duration by default, created at the point of
 definition and destroyed when the block is exited.
 
 static keyword : changes the automatic duration to static duration, this means the
 static variable will retain its value even after it goes out of scope, this means the
 variable is now created at the start of the program and destroyed at the end of the
 program
 
 Just like we use “g_” to prefix global variables, it’s common to use “s_” to prefix static (static duration) local variables.
 
 static local variables that are not explicitly initialized will be zero-initialized by default.
 
 Static local variables with non-constexpr initializers are initialized the first time the variable definition is encountered (the definition is skipped on subsequent calls, so no reinitialization happens).
 
 Most common use for static duration local variables : unique ID generators
 
 Best practice
 Initialize your static local variables. Static local variables are only initialized the first time the code is executed, not on subsequent calls.
 
 Static local constants

 Static local variables can be made const (or constexpr). One good use for a const static local variable is when you have a function that needs to use a const value, but creating or initializing the object is expensive (e.g. you need to read the value from a database). If you used a normal local variable, the variable would be created and initialized every time the function was executed. With a const/constexpr static local variable, you can create and initialize the expensive object once, and then reuse it whenever the function is called.
 
 Don’t use static local variables to alter flow:
 
 static local variables : should only be used if in the entire program and in the forseeable future,
 the variable is unique and it wouldn't make sense to reset the variable
 
 Best practice:
 avoid static local variables unless the variable never needs to be reset
 
 static local variables : used to count the number of times a function is called.
 */

#include <iostream>

void inc_print()
{
    /// local variable with auto. duration by default
    int value{1};
    ++value;
    std::cout << "auto:" << value << '\n';
}

void static_inc_print()
{
    /// this initializer in only executed once
    static int s_value{1};
    ++s_value;
    std::cout << "static:" << s_value << '\n';
    /// this s_value is not destroyed here, it is inaccessible because it goes out of scope
}

int generate_ID()
{
    static int s_ID{0};
    return s_ID++;
}

int get_integer()
{
    static bool s_is_first_call{true};
    
    /// Don't use static local variables to alter the flow
    if (s_is_first_call)
    {
        std::cout << "Enter an Integer: ";
        s_is_first_call = false;
    }
    else
    {
        std::cout << "Enter another Integer: ";
    }
    
    int i{};
    std::cin >> i;
    return i;
}

int main()
{
    inc_print();
    inc_print();
    inc_print();
    
    static_inc_print();
    static_inc_print();
    static_inc_print();
    
    std::cout << "obj " << generate_ID() << " created."<< '\n';
    std::cout << "obj " << generate_ID() << " created."<< '\n';
    std::cout << "obj " << generate_ID() << " created."<< '\n';
    std::cout << "obj " << generate_ID() << " created."<< '\n';
    std::cout << "obj " << generate_ID() << " created."<< '\n';
    
    int a{get_integer()};
    int b{get_integer()};
    
    std::cout << "Add: " << a + b << '\n';
    
    /// Don’t use static local variables to alter flow
    /// unexpected result
    /// "Enter another Integer" instead of "Enter an Integer", in the below two calls
    int c{get_integer()};
    int d{get_integer()};
    
    std::cout << "Sub: " << c - d << '\n';
    
    return 0;
}
