//
//  main.cpp
//  4.15_literals
//
//  Created by εκλεγμένοι εν Χριστώ on 9/27/22.
//

/*
 Literals: unnamed values inserted directly into the source
 code
 
 literal constants: same as literals, because their values
 can't be reassigned
 
 LITERAL TYPES: literals have a type
 type of a literal: deduced from it's value
 
 default literals below:
 +-----------------------------------------------------------+
 value          example             default literal type
 +-----------------------------------------------------------+
 integer        5,0,-2              int
 boolean        true, false         bool
 floating point 1.1, 0.001, 22.2    double(not float)
 character      'a', 'A', '\n'      char
 string(CStyle) "Hello, World"      const char[]
 +-----------------------------------------------------------+
 
 LITERAL SUFFIXES: can be used if the default literal is not
 what you desired. suffixes change the type of the literal
 
 suffixes: aren't case sensitive
 Best practice:
 Prefer literal suffix L (upper case) over l (lower case).
 
 +-----------------------------------------------------------+
 type           suffix              description
 +-----------------------------------------------------------+
 integral       u/U                 unsigned int
 integral       l/L                 long
 integral       ul/uL/Ul/UL/lu      unsigned long
                /lU/Lu/LU
 integral       ll/LL               long long
 integral       ull/uLL/Ull/ULL/    unsigned long long
                llu/llU/LLu/LLU
 integral       z/Z                 signed version of size_t
 integral       uz/UZ               unsigned size_t
 floating point f/F                 float
 floating point l/L                 long double
 string         s                   string
 string         sv                  std::string_view
 +-----------------------------------------------------------+
 
 integer literals:
 generally won’t need to use suffixes
 exception: the u (or ‘U’) suffix, which is used to denote an
 unsigned integer literal
 
 floating point literals:
 by default: they are of double type
 f/F: can be used to make them float type
 
 Magic number: a literal,  usually a number(can also be text
 or other types), it either has an
 unclear meaning or may need to be changed later.
 
 using magic numbers: considered a bad practice
 
 literals: that are unlikely to change are not considered as
 magic numbers. example, -1, 0, 0.0, and 1
 
 Best practice
 Avoid magic numbers in your code (use constexpr variables
 instead).
 */

#include <iostream>

int main()
{
    /// 2: integer literal, inserted directly into the source code, also it is unnamed
    std::cout << 2 << '\n';
    
    /// 3: int literal, no suffix, so it is int literal by default
    std::cout << 3 << '\n';
    
    /// 3L: integer long literal
    std::cout << 3L << '\n';
    
    /// exception: u/U is necessary to denote an unsigned integer literal
    /// 2u: unsigned integer literal
    std::cout << 2u << '\n';
    
    /// 4.4: by default is of double type
    std::cout << 4.4 << '\n';
    
    /// 4.4f: suffix f is used, so it is of type float
    std::cout << 4.4f << '\n';
    
    /// two ways to declare floating point literals:
    /// standard notation: below
    double pi{3.14159};
    /// scientific notation: below
    double avogadro{6.02e23};
    /// scientific notation: below, negative number
    double charge_on_electron{1.6e-19};
    
    constexpr int total_classes{12};
    
    /// 40: uncleared the use of 40 and it could be changed later
    constexpr int max_stu_per_school{total_classes * 40};
    
    /// 40: clear, it can be changed but only one place where it needs to be
    /// changed, this won't break the program even if there are multiple instances
    /// of the same value in the program which are not required to be changed
    constexpr int max_stu_per_class{40};
    constexpr int max_stu_in_school{total_classes * max_stu_per_class};
    
    ///  Avoid magic numbers in your code (use constexpr variables instead).
    
    return 0;
}
