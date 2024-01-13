//
//  main.cpp
//  8.1_implicit.type.conversion_coercion
//
//  Created by εκλεγμένοι εν Χριστώ on 2/8/23.
//

/*
 Value of an object : stored as a sequence of bits
 
 data type of the object : tells the compiler how to interpret those bits into meaningful
 values
 
 different data types : may represent the same number differently
 
 example : int 3 as     0000 0000 0000 0000 0000 0000 0000 0011 in binary
           float 3.0 as 0100 0000 0100 0000 0000 0000 0000 0000 in binary
 
 ______________________________________
 float f{3}; - initialize float with integer 3
 
 In this case, compiler can't just copy the bits representing the int value 3 into the
 memory allocated for float variable f
 instead, it needs to convert the integer value 3 to the equivalent floating point number
 which can then be stored in the memory allocated for float f.
 
 TYPE CONVERSION : process of converting a value from one data type to another
 
 type conversion : can be invoked in one of two ways
 -implicitly : as needed by the compiler
 -explicitly : when requested by the programmer
 
 IMPLICIT TYPE CONVERSION/(automatic type conversion)/COERCION:
 performed automatically by the compiler when one data type is required, but a different
 data type is supplied
 
 Vast majority of type conversion in CPP are : implicit
 
 WHAT HAPPENS WHEN A TYPE CONVERSION IS INVOKED?
 When type conversion is invoked(whether implicit or explicit), compiler will determine
 whether it can convert the value from the current type to the desired type, if a valid
 conversion can be found, then compiler will produce a new value of the desired type.
 
 type conversions : don't change the value or type of the value or object being converted
 
 compiler error : if compiler can't find an acceptable conversion
 
 type conversion failure reasons:
 -compiler might not know how to convert a value between the original type and desired type
 -statements may disallow certain type of conversions, example- brace initialization
 disallows conversions that result in data loss, even though compiler knows how to convert
 a double value to an int value, such conversions are disallowed when using brace
 initialization
 -there are also the cases where compiler may not be able to figure out which of the several
 possible type conversions is unambiguously the best to use
 
 The standard conversions:
 standard conversions : conversion rules in cpp language standard that defines how different
 fundamental types(some cases, compound types) can be converted to other types.
 
 STANDARD CONVERSIONS: 4 broad categories, each covering different types of conversions
 -numeric promotions
 -numeric conversions
 -arithmetic conversions
 -other conversions(includes various pointer and reference conversions)
 
 when a type conversion is needed, compiler will se if there are standard conversions that
 it can use to convert the value to the desired type, compiler may apply zero, one or more
 than one standard conversions in the conversion process
 
 type conversion with zero conversion : architectures where int and long are of same size
 and range, same sequence of bits is used to represent values of both types, so there is no
 need of actual conversion between those types, the value can simply be copied
 */

#include <iostream>

/// implicit type conversion : when the type of a return value is different from the function declared return type
float do_something()
{
    return 3.0;                 /// double 3.0 implicitly converted to type float
}

/// implicit type conversion : when an argument passed to the function is of different type than the function's parameter type
void do_something2(long l)
{
    /// call to this function is in the main( )
}

int main()
{
    /// implicit type conversion : when initializing/assigning a value to a variable of different data type
    double d{3};                /// int value : 3, implicit type conversion happening here
    d = 6;                      /// int value : 6, implicitly converted to type double
    
    /// implicit type conversion : when using certain binary operators with operands of different types
    double division{ 4.0 / 3 }; /// int value : 3, implicitly converted to type double
    
    /// implicit type conversion : when using a non-boolean value in an if statement
    if (2) {}                   /// int value : 2, implicitly converted to type bool
    
    do_something2(3);           /// int value : 3, implicitly converted to type long
    
    ///int x{2.2};                 /// brace-initialization disallows conversions that result in data loss
    
    return 0;
}
