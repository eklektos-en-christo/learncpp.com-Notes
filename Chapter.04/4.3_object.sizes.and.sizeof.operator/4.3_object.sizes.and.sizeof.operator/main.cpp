//
//  main.cpp
//  4.3_object.sizes.and.sizeof.operator
//
//  Created by εκλεγμένοι εν Χριστώ on 9/11/22.
//

/*
 Object size: is based on its data type
 
 1 bit:  hold 2 possible values
 2 bits: hold 4 possible values
 3 bits: hold 8 possible values
 
 Object with n bits: can hold 2^n unique values, n - integer
 1 byte: 8 bits
 1 byte sized object: 2^8  different values - total 256
 2 byte sized object: 2^16 different values - total 65536
 
 Object size: puts a limit on the unique values it can store
 Object size: bigger the size, large number of unique values
 
 Key insight: focus on maintainable code, optimize only when
 and where the benefit will be substantive
 
 Size of given type: depends upon compiler and architecture
 
 In C++, each primitive type have a minimum size as below:
 bool                   1 byte
 char                   1 byte(always)
 wchar_t                1 byte
 char16_t               2 bytes
 char32_t               4 bytes
 int                    2 bytes
 short                  2 bytes
 long                   4 bytes
 long long              8 bytes
 float                  4 bytes
 double                 8 bytes
 long double            8 bytes
 
 int: more often 4 bytes
 actual variable size: depends upon compiler and architecture
 
 best practice
 for maximum compatibility, you shouldn't assume that
 variables are larger than the specified minimum size.
 
 Objects of fundamental data types: extremely fast
 
 sizeof: unary operator, takes either a type or a variable
 and returns it's size in bytes, used to determine the size of
 the data types on a machine
 
 sizeof: cannot be used on void type, void has no size
 
 not always true: types that use less memory would be faster
 than types that use more memory
 */

#include <iostream>

int main()
{
    std::cout << "bool:\t\t" << sizeof(bool) << '\n';
    std::cout << "char:\t\t" << sizeof(char) << '\n';
    std::cout << "wchar_t:\t" << sizeof(wchar_t) << '\n';
    std::cout << "char16_t:\t" << sizeof(char16_t) << '\n';
    std::cout << "char32_t:\t" << sizeof(char32_t) << '\n';
    std::cout << "short:\t\t" << sizeof(short) << '\n';
    std::cout << "int:\t\t" << sizeof(int) << '\n';
    std::cout << "long:\t\t" << sizeof(long) << '\n';
    std::cout << "long long:\t" << sizeof(long long) << '\n';
    std::cout << "float:\t\t" << sizeof(float) << '\n';
    std::cout << "double:\t\t" << sizeof(double) << '\n';
    std::cout << "long double:" << sizeof(long double) << '\n';
    
    int x{};
    std::cout << "x: " << sizeof(x) << '\n';
    
    return EXIT_SUCCESS;
}
