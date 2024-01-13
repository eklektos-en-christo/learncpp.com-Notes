//
//  main.cpp
//  4.9_boolean.values
//
//  Created by εκλεγμένοι εν Χριστώ on 9/16/22.
//

/*
 Boolean variables: that can have only two possible values,
 true and false
 
 boolean values: stored as integers, true becomes 1 and false
 becomes 0.
 
 boolean evaluation: evaluate to 1 or 0 and not true or false
 
 boolean values: integral type
 
 std::boolalpha: using this the std::cout will print true as
 "true" and false as "false" and not 1 or 0
 
 Integer to Boolean conversion: can't initialize a boolean
 with an integer using uniform initialization
 
 Integer to Boolean conversion: the integer 0 is converted to
 false, and any other integer than 0 is converted to true
 
 Inputting Boolean values: std::cin only accepts two inputs
 for boolean value, 0 and 1, any other inputs will cause
 std::cin to silently fail
 
 failed input: will also zero out the variable, to allow
 std::cin to accept "false" and "true" as inputs, the std::
 boolalpha has to be enabled, when std::boolalpha is enabled,
 “0” and “1” will no longer be treated as booleans.
 
 boolean return values: booleans can be used as return values
 for functions, that check whether something is true or not
 */

#include <iostream>

/// used bool and return type, will return 1 or 0
bool is_equal(int x, int y)
{
    return x == y;
}

int main()
{
    /// boolean variable, initialized
    bool b1{true};
    bool b2{false};
    
    /// flipping a boolean value using ! logical not operator
    bool bf1{!true};        /// initialized with false
    bool bf2{!false};       /// initialized with true
    
    /// cout prints 0 for false and 1 for true
    std::cout << b1 << '\n';
    std::cout << b2 << '\n';
    std::cout << bf1 << '\n';
    std::cout << bf2 << '\n';
    
    /// std::boolalpha: prints true as true and false as false
    std::cout << std::boolalpha;
    std::cout << b1 << '\n';
    std::cout << b2 << '\n';
    
    /// std::noboolalpha: this turns off the std::boolalpha
    std::cout << std::noboolalpha;
    std::cout << bf1 << '\n';
    std::cout << bf2 << '\n';
    
    /// error: conversion disallowed
//    bool bint{2};
    
    /// any integer converted to true and 0 converted to false
    bool bint1 = 22;
    bool bint2 = 0;
    std::cout << std::boolalpha;
    std::cout << bint1 << '\n';
    std::cout << bint2 << '\n';
    
    std::cout << std::noboolalpha;
    
    /// std::boolalpha enabled allowing std::cin to accept
    /// "false" and "true" as inputs
    /// using std::boolalpha with cin as well as with cout
    /// 0 and 1 now no longer be treated treated as booleans
    std::cin >> std::boolalpha;
    bool my_bool{};
    std::cout << "Enter boolean value: ";
    std::cin >> my_bool;
    std::cout << std::boolalpha;
    std::cout << "You entered: " << my_bool << '\n';
    
    std::cin >> std::noboolalpha;
    std::cout << std::noboolalpha;
    
    /// will print either 1 or 0
    std::cout << "is equal: " << is_equal(2, 2) << '\n';
    
    return 0;
}
