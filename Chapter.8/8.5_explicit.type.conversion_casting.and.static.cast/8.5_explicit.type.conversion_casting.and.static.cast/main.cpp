//
//  main.cpp
//  8.5_explicit.type.conversion_casting.and.static.cast
//
//  Created by εκλεγμένοι εν Χριστώ on 2/11/23.
//

/*
 type casting operators or casts : used by the programmer to request that the compiler
 perform a type conversion
 
 casts : explicit requests, so it is explicit type conversion
 
 Type casting :
 cpp : supports 5 different type of casts
 -C-style casts
 -static casts
 -const casts
 -dynamic casts
 -reinterpret casts
 latter four are sometimes referred to as named casts
 
 warning:
 avoid const casts and reinterpret casts unless there is a very good reason to use them
 
 ––––––––––––––––––––
 C-style casts:
 In standard C programming : casts are done via the () operator, with name of the type to
 convert the value placed inside the parenthesis.

 C-style cast:
 can actually perform a variety of different conversions depending on context, this can
 include as static cast, const cast or a reinterpret cast.
 
 C-style casts:
 are at risk for being accidentally misused and not producing the expected behavior, which
 is easily avoidable by using C++ casts instead
 
 best practice:
 avoid using c-style casts
 
 ––––––––––––––––––––
 static_cast:
 static_cast: casting operator, can be used to convert value of one type to value of another
 type
 
 static_cast: operator takes an expression as input, return evaluated value converted to the
 type specified inside the angled brackets
 
 static_cast: is best used to convert one fundamental type into another
 
 static_cast: provides compile-time type checking, so harder to make an accidental error
 
 static_cast: also less powerful than c-style casts, so can't accidentally remove const or
 do other things which you may not have intended to do
 
 best practice:
 favor static_cast when there is a need to convert a value from one type to another type
 
 we can use static_cast to explicitly convert our integer to a char as below in main()
 when we do this, we explicitly telling the compiler that this conversion is intended, we
 accept the responsibility for the consequences(like overflow).
 */

#include <iostream>

int main()
{
    int x{20};
    int y{18};
    
    /// C-style cast below
    /// converting x to double, so we get floating point division
    double d{(double)x / y};
    std::cout << d << '\n';
    
    /// same as previous example, but casting with more function-call like syntax
    /// it has a benefit of parenthesizing the value being converted, this makes easier to tell what is being converted
    double d2{double(x) / y};
    std::cout << d2 << '\n';
    
    int x1{22};
    int y1{4};
    
    /// static cast : x to a double, so we get floating point division
    double d3{static_cast<double>(x1) / y1};
    std::cout << d3 << '\n';
    
    int x2{90};
    /// explicit conversion : from int to char, char is assigned to variable ch
    /// no warnings or errors because of static_cast
    /// because output of this static_cast is of type char
    char ch{static_cast<char>(x2)};
    std::cout << ch << '\n';
    
    int p{200};
    /// telling the compiler that we explicitly mean to do this
    p = static_cast<int>(p / 2.2);
    std::cout << p << '\n';
    
    return 0;
}
