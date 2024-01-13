//
//  main.cpp
//  8.2_floating.point.and.integral.promotion
//
//  Created by εκλεγμένοι εν Χριστώ on 2/8/23.
//

/*
 C++ : has minimum size guarantees for each fundamental types
 
 actual size of these types : can vary based on the compiler and architecture
 
 variability : was allowed so that the int and double types could be set to the size that
 maximizes performance on a given architecture.
 
 example-
 32 bit computer : typically be able to process 32-bits of data at at time, so int would
 likely be set to a width of 32 bits, since this is "natural" size of the data that cpu
 operates on and likely to be the most performant
 
 width : number of bits a data types uses
 
 wider data type : uses more bits
 
 narrower data type : uses less bits
 
 What happens when we want 32 bit CPU to modify an 8 bit value or a 16 bit value?
 some 32 bit processors(such as x86 series) : can manipulate 8 or 16 bit values directly, it
 is often slower than manipulating 32 bit values
 other 32 bit CPUs(like powerPC) : can operate on 32 bit values only, additional tricks must
 be employed to manipulate narrower values
 
 ------------------------------NUMERIC PROMOTION------------------------------
 numeric promotion : type conversion of a narrower numeric type(like char) to a wider
 numeric type(typically int or double) that an be processed efficiently and is less likely
 to have a result that overflows
 
 All numeric promotions : are value preserving, means all values in original type are
 representable without loss of data or precision in the new type
 
 numeric promotions : are safer, the compiler will freely use these promotions without
 issuing any warning when doing so
 
 numeric promotion : reduces redundancy(un-usefulness)
 
 NUMERIC PROMOTION CATEGORIES: 2
 -integral promotions
 -floating point promotions
 
 Using floating point promotion rules:
 a value of type float can be converted to a value of type double
 
 Using Integral promotion rules, following conversions can be made:
 -signed char, signed short                              >   int
 
 -unsigned char, unsigned short, char8_t                 >   int(if int can hold the entire
 range of the type, or unsigned int otherwise)
 
 -if char is signed by default                           >   it follows the signed char
 conversion rules above
 
 -if char is unsigned by default                         >   it follows the unsigned char
 conversion rules above
 
 -bool                                                   >   int(true becomes 1 and false 0)
 
 while numeric promotion is value preserving : it does not necessarily preserve the
 signed-ness of the type
 
 Not all value preserving conversions are numeric promotions:
 some value preserving type conversions below-
 char   > short
 int    > long
 int    > double
 these are not considered numeric promotions in CPP, they are numeric conversions, because
 such conversions do not assist in the goal of converting smaller types to larger types that
 can be processed more efficiently
 
 in certain cases : compiler will favor numeric promotions over numeric conversions
 */

#include <iostream>

/// this functions reduces redundancy: how?
/// if we want to also be able to print a value of type short, char
/// if type conversions didn't exist?
/// we'd have to write another function for short and another one for char
/// also for another versions : unsigned char, signed char, unsigned short, wchar_t, char8_t, char16_t, char32_t
/// so this becomes unmanageable
///
/// numeric promotions solves this issue of redundancy by :
/// we can write functions that have int and/or double parameters(as the print_integer below).
/// this same function can be called with arguments of types that can be numerically promoted to match the types of the
/// function parameters
///
/// this function taking an int parameter, then we are using it with a variety of other integral types in main( )
void print_integer(int x)
{
    std::cout << x << '\n';
}

/// floating point promotion:
/// we can use this function that takes a double and then call it with either a double or a float value
void print_double(double d)
{
    std::cout << d << '\n';
}

int main()
{
    short s{12};
    
    /// numeric promotion
    /// implicit type conversion : from char to int
    print_integer('a');
    
    /// no numeric promotion
    print_integer(2);
    
    /// numeric promotion : short to int
    /// no short literal suffix, so using a short variable
    print_integer(s);
    
    /// numeric promotion : bool to int
    print_integer(true);
    
    /// no necessary conversion is needed
    print_double(2.2);
    /// numeric promotion of float to double
    /// float literal 2.2f : is promoted into a double
    /// so that the type of the argument matches the type of the function parameter
    print_double(2.2f);
    
    
    
    return 0;
}
