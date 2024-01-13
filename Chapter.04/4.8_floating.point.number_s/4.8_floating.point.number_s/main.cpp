//
//  main.cpp
//  4.8_floating.point.number_s
//
//  Created by εκλεγμένοι εν Χριστώ on 9/14/22.
//

/*
 floating point type: that can hold a real number, like
 22320.0, -2.214 or 0.00343
 
 floating: means that decimal point can float, it can
 support a variable number of digits before and after the
 decimal point
 
 floating point types: float, double and long double
 
 floating point: guarantee minimum sizes
 
 floating point: follows IEEE 754 binary format
 
 In IEEE 754 binary format: float:4bytes, double:8bytes
 long double:8bytes, 12bytes or 16bytes
 
 floating point: always signed
 
 When using floating point literals, always include at least one decimal place (even if the decimal is 0). This helps the compiler understand that the number is a floating point number and not an integer.
 
 +---------------------------------------------+
 type           min.size    typical size
 +---------------------------------------------+
 float          4bytes      4bytes
 double         8bytes      8bytes
 long double    8bytes      8, 12, or 16 bytes
 +---------------------------------------------+
 
 best practice:
 type of literals must match the type of variable they're
 being assigned to or used to initialize, otherwise
 unnecessary conversion will result, possibly with a loss of
 precision.
 
 warning:
 don’t use integer literals where floating point literals
 should be used.
 
 floating point range:
 +-----------------------------------------------------------+
 size           range                           precision
 +-----------------------------------------------------------+
 4bytes         ±1.18 x 10-38 to ±3.4 x 1038    6-9                                                     significant                                             digits,                                                 typically 7
 +-----------------------------------------------------------+
 8 bytes        ±2.23 x 10-308 to ±1.80 x 10308 15-18                                                   significant                                             digits,                                                 typically 16
 +-----------------------------------------------------------+
 80-bits        ±3.36 x 10-4932                 18-21                   to ±1.18 x 104932               significant                                             digits
 (typically
 uses 12 or
 16 bytes)
 +-----------------------------------------------------------+
 16 bytes    ±3.36 x 10-4932 to ±1.18 x 104932  33-36                                                    significant                                             digits
 +-----------------------------------------------------------+
 
 80-bit floating point type: historical anomaly, typically
 implemented using 12 or 16 bytes.
 
 80-bit floating point type has the same range as the 16-byte
 floating point type,
 
 precision: defines how many significant digits it can
 represent without information loss.
 
 no. of digits of precision: depends upon the size and the
 particular value being stored
 
 float values: 6-9 precision, 7 significant digits at least
 
 double values: 15-18 precision, 16 significant digits '' ''
 
 long double: 15, 18 or 33 significant digits, depending upon
 the bytes it occupies
 
 output manipulator: function named std::setprecision(), can
 override the default precision that std::cout shows, it alter
 how data is output.
 
 output manipulators: iomanip header
 
 rounding error: when precision is lost because a number
 can't be stored precisely
 
 Best practice:
 Favor double over float unless space is at a premium,
 as the lack of precision in a float will often lead to
 inaccuracies.
 
 Rounding errors make floating point comparisons tricky:
 1/10
 in decimal: 0.1    1 significant digit
 in binary: 0.00011001100110011.... infinite sequence
 
 Rounding errors: may make a number either slightly smaller
 or slightly larger, depending upon the truncation
 
 key insight:
 Rounding errors occur when a number can’t be stored precisely. This can happen even with simple numbers, like 0.1. Therefore, rounding errors can, and do, happen all the time. Rounding errors aren’t the exception -- they’re the rule. Never assume your floating point numbers are exact.
 A corollary of this rule is: be wary of using floating point numbers for financial or currency data.
 
 mathematical operations (such as addition and multiplication)
 tend to make rounding errors grow.
 
 
 Floating point number categories:
 inf: infinity, +ve or -ve
 NaN: Not a number
 
 Best practice:
 Avoid division by 0 altogether, even if your compiler
 supports it.
 
 Summary:
 * floating point numbers: useful for storing very large or
 very small numbers including numbers with fractional
 components.
 * often have small rounding errors, even when the number has
 fewer significant digits than the precision.
 * numbers are truncated for output, many times rounding error
 go unnoticed because they are so small.
 * comparisons of floating point numbers may not give the
 expected results
 * mathematical operations on these values will cause the
 rounding errors to grow larger.
 */

#include <iomanip>
#include <iostream>

int main()
{
    int a{2};           /// integer
    
    /// floating point, .0f to specify a float, f suffix is used to denote a literal
    /// of type float
    float b{2.0f};
    
    /// double, no f, floating point literals default to type double
    double c{2.2};
    
    /// if fractional part is 0, cout won't print it(default), so output is 2
    std::cout << (2.0) << '\n';
    
    /// if fractional part is 0, cout won't print it
    std::cout << (2.02f) << '\n';
    
    /// scientific notation
    std::cout << (9876543.21) << '\n' << '\n';
    
    /// std::cout, default precision of 6, so truncating
    std::cout << 9.87654321f << '\n';
    std::cout << 987.654321f << '\n';
    std::cout << 987654.321f << '\n';
    std::cout << 9876543.21f << '\n';
    
    ///minimum number of exponent digits displayed is compiler-specific
    std::cout << 0.0000987654321f << '\n';

    std::cout << std::setprecision(16);
    std::cout << 3.33333333333333333333333333333333333333f << '\n';
    std::cout << 3.33333333333333333333333333333333333333 << '\n';
    
    double d{0.1};
    std::cout << d << '\n';
    std::cout << std::setprecision(17);
    std::cout << d << '\n';
    
    /// floating point numbers tend to be inexact
    /// d1 and d2 should be equal, but they are not
    std::cout << std::setprecision(17);
    double d1{1.0};
    std::cout << d1 << '\n';
    double d2{0.1+0.1+0.1+0.1+0.1+0.1+0.1+0.1+0.1+0.1};
    /// rounding error
    std::cout << d2 << '\n';
    
    double zero{0.0};
    /// infinity: positive
    double positive_infinity{5.0/zero};
    /// infinity: negative
    double negative_infinity{-5.0/zero};
    /// NaN: not a number
    double not_a_number{zero/zero};
    
    std::cout << positive_infinity << '\n';
    std::cout << negative_infinity << '\n';
    std::cout << not_a_number << '\n';
    
    return 0;
}
