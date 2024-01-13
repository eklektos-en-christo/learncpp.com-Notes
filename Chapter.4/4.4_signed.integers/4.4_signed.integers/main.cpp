//
//  main.cpp
//  4.4_signed.integers
//
//  Created by εκλεγμένοι εν Χριστώ on 9/12/22.
//

/*
 Integer: integral type, can represent +ve and -ve whole
 numbers. example - 0, -1,2,-22 etc
 
 fundamental integer types, minimum sizes:
 short int      16 bits
 int            32 bits
 long int       32 bits
 long long int  64 bits
 
 signed integers: attribute of being +ve, -ve or 0 is called
 number's sign
 
 integers: signed by default
 
 sign bit: used to store the number's sign
 
 signed integer: holds both +ve or -ve including 0
 
 Best practice

 Prefer the shorthand types that do not use the int suffix or
 signed prefix.
 
 signed integer ranges:
 n bits variable: 2^n possible values
 range: set of specific values that a datatype can hold
 
 range determination: size(n bits) + sign of the integer
 
 8 bit signed integer range: -128 to 127, can store integer
 value between -128 and 127(included) safely.
 
 8 bit integer: 256 possible values between -128 to 127(incl.)
 
 range of signed integers of different sizes:
 8 bit signed           -128 to 127
 16 bit signed          -32,768 to 32,767
 32 bit signed          -2,147,483,648 to 2,147,483,647
 64 bit signed          -9,223,372,036,854,775,808 to
                         9,223,372,036,854,775,807
 
 n bit signed variable's range: -(2^(n-1) to 2^(n-1) - 1
 range -ve to +ve: because integer has the sign
 
 integer overflow: storing a value that is outside the range
 of the type, cause data loss
 
 signed integer overflow: undefined behavior.
 
 Integer division:integers can’t hold fractional values, any
 fractional portion is simply dropped (not rounded!).
 When doing division with two integers (called integer
 division), C++ always produces an integer result
 */

#include <iostream>

int main()
{
    /// prefer the short names for these types (that do not use the int suffix)
    /// int suffix makes the type harder to distinguish from variables of type int
    short s;        /// prefer short instead of short int
    int i;
    long l;
    long long ll;
    
    /// optional keyword: signed, redundant because integers are signed
    /// by default
    signed short ss;
    signed int si;
    signed long sl;
    signed long long sll;
    
    std::cout << 10/2 << '\n';
    
    /// fractional result: fractional portion is simply dropped
    std::cout << 25/2 << '\n';
}
