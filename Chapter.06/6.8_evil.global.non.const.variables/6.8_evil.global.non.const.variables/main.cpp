//
//  main.cpp
//  6.8_evil.global.non.const.variables
//
//  Created by εκλεγμένοι εν Χριστώ on 11/13/22.
//

/*
 Non-const global variables: their values can be changed by any function that is
 called.
 
 perfectly modular function : that utilizes nothing but its parameters and has no side
 effects
 
 global variables : reduce modularity
 
 Best practice
 Use local variables instead of global variables whenever possible.
 
 Two phases of static variables' initialization:
 Happens as a part of program startup, before execution of main()
 
 phases below:
 static initialization: in this phase the global variables with constexpr initializers
 are initialized to those values, global variables without initialzers are zero
 initialized
 dynamic initialization: in this phase the global variables with non-constexpr
 initializers are initialized as below
 int init(){return 4};
 int g_something{init()};   // non-constexpr initialization
 
 Warning
 Dynamic initialization of global variables causes a lot of problems in C++. Avoid dynamic initialization whenever possible.
 
 order of initialization of global variables: across different files is not defined
 
 criteria for using global variable :
 1. there should only ever be one of the thing the variable represents in the program
 2. its use must be everywhere/ubiquitous throughout the program
 
 global variables rules:
 -prefix all non-namespaced global variables with g or g_ or put them in a namespace
 to reduce the chance of naming collisions
 
 -it is better to encapsulate the variable, make sure the variable is only be accessed
 from within the file it's declared in, e.g. by making the variable static or const,
 the provide external global "access functions" to work with the variable, in this way
 at the time of changing the implementation, you only have to change the access
 functions instead of every piece of code that used the global variable directly
 
 -when writing a standalone function that used the global variable, don't use the
 variable directly in the function body, pass it in an an argument instead, this way
 whenever the function needs to use a different value for some circumstance, then you
 can simply vary the argument, this maintains modularity
 */

#include <iostream>

/// global non-const variable, zero initiallized by default
int g_mode;

void do_stuff()
{
    /// global variable : changed its value from 0 to 100
    g_mode = 100;
}

int initx();
int inity();

int g_x{initx()};           /// g_x initialized first
int g_y{inity()};

int initx()
{
    return g_y;             /// g_y isn't initialized when this function is called
}

int inity()
{
    return 2;
}

/// clear : this is a global variable, constants namespace for global constants
namespace constants
{
    /// this has internal linkage by default, only accessible by this file
    /// gravity doesn't need to be static, global const variables have internal linkage by default
    constexpr double gravity{9.8};
}

/// access function, returning the global const variable - gravity
/// this can be exported to other files to access the global outside of this file
double get_gravity()
{
    /// logic can also be added here if needed later
    return constants::gravity;
}

/// this can calculate the instant velocity for any gravity value - more useful
double instant_velocity(int time, double gravity)
{
    return gravity * time;
}

int main()
{
    g_mode = 10;
    
    /// this function call changed value of g_mode from 10 to 100
    /// unexpected results
    do_stuff();
    
    if (g_mode == 10)
        std::cout << "No threats detected!" << '\n';
    else
        std::cout << "Launching nuclear missiles!" << '\n';
    
    std::cout << g_x << " & " << g_y << '\n';
    
    std::cout << get_gravity() << '\n';
    
    /// passing the constant gravity to function as parameter
    /// this will calculate the instant velocity based on the global gravity
    std::cout << instant_velocity(5, constants::gravity) << '\n';
    
    /// this will calculate the instant velocity for any gravity value - more useful
    std::cout << instant_velocity(5, 9.7) << '\n';
    
    return 0;
}
