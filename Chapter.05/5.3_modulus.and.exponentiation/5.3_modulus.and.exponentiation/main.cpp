//
//  main.cpp
//  5.3_modulus.and.exponentiation
//
//  Created by εκλεγμένοι εν Χριστώ on 10/17/22.
//

/*
 modulus operator(remainder operator): returns the remainder after
 doing the integer division
 example: 7/4 - remainder is 3, so 7%4 - remainder is 3
 
 modulus: only works with integer operands.
 
 modulus: most useful for testing whether a number is evenly divisible
 by another number, means that after the division the remainder becomes
 zero or not
 example: if x % y evaluates to 0, this means x is evenly divisible
 by y.
 
 whenever the first number is smaller than the second number, then the
 second number will divide the first number 0 times, and the remainder
 will be the first number.
 example: 2 % 4 = 2, 4 times zero is 0 and remainder is 2 which is also
 the first number.
 
 modulus with negative numbers: x % y will always return the results
 with the sign of x, which means remainder will take the sign of the
 first operand
 
 ^ - perform the bitwise XOR operation in C++
 
 exponentiation in C++: can be done with pow() function which is inside
 the <cmath> header file
 
 integer exponentiation: it is better to use own functions to do so
 warning: in vast majority of cases, integer exponentiation will
 overflow the integral type, that's why there is no such function
 included in the STD.
 */

#include <cmath>
#include <iostream>
#include <cstdint>
#include <cassert>

std::int64_t pow_int(std::int64_t base, int exp)
{
    assert(exp >= 0 && "powint: exp param. has negative value");
    
    std::int64_t result{1};
    while (exp)
    {
        if (exp & 1)
            result *= base;
        exp >>= 1;
        base *= base;
    }
    
    return result;
}

bool is_even(int integer)
{
    /// making code simple here
    return integer % 2 == 0;
}

int main()
{
    std::cout << "Enter an integer: ";
    int x{};
    std::cin >> x;
    
    std::cout << "Enter another integer: ";
    int y{};
    std::cin >> y;
    
    std::cout << "Remainder is: " << x % y << '\n';
    
    if (x % y == 0)
        std::cout << x << " is evenly divisible by " << y << '\n';
    else
        std::cout << x << " isn't evenly divisible by " << y << '\n';
    
    /// due to the rounding errors in floating point point numbers, the result of pow( )
    /// may not be precise, even if the integers or whole number are passed to it
    std::cout << std::pow(3.0, 4.0) << '\n';
    
    std::cout << pow_int(7, 12) << '\n';
    
    /// -------------------------------------------- PROGRAM --------------------------------------
    std::cout << "Enter an integer: ";
    int input{};
    std::cin >> input;
    
    if (is_even(input))
        std::cout << "EVEN" << '\n';
    else
        std::cout << "ODD" << '\n';
    
    return 0;
}
