//
//  main.cpp
//  5.6_relational.operators.and.floating.point.comparisons
//
//  Created by εκλεγμένοι εν Χριστώ on 10/20/22.
//

/*
 relational operators: used to compare the two values, they evaluate to true
 or false.
 
 6 relational operators:
 +-----------------------------------------------------------------------------+
 Operator       Symbol      Form        Operation
 +-----------------------------------------------------------------------------+
 greater than   >           x > y       true, if x is greater than y
 less than      <           x < y       true, if x is less than y
 greater than   >=          x >= y      true, if x is greater than or equal to y
 or equal
 less than      <=          x <= y      true, if x is less than or equal to y
 or equal
 equality       ==          x == y      true, if x equals y
 inequality     !=          x != y      true, if x does not equal y
 +-----------------------------------------------------------------------------+
 
 Best practice
 Don’t add unnecessary == or != to conditions. It makes them harder to read
 without offering any additional value.
 
 example:
 instead of using this-
 if (x == true) /// this is redundant
 if (x == false)
 
 use this-
 if (x)         /// this is better
 if (!x)
 
 <, <=, >, and >= : when used with floating point values, they will usually
 produce the correct answer, the == and != use can be dangerous. because
 floating point values are not precise.
 
 != and == : should be avoided to use with floating value comparison
 
 Warning
 Avoid using operator== and operator!= to compare floating point values if
 there is any chance those values have been calculated.
 
 exception:
 It is okay to compare a low-precision (few significant digits) floating point
 literal to the same literal value of the same type.
 
 floating point comparison:------
 The most common method of doing floating point equality involves using a
 function that looks to see if two numbers are almost the same. If they are
 “close enough”, then we call them equal. The value used to represent
 “close enough” is traditionally called epsilon. Epsilon is generally defined
 as a small positive number (e.g. 0.00000001, sometimes written 1e-8).
 
 std::abs() - return the absolute value of its argument, so
 (std::abs(a - b) <= absEpsilon) checks if distance between a and b is less than
 or equal to the epsilon(close enough) value, then it returns true.
 
 it’s not great. An epsilon of 0.00001 is good for inputs around 1.0, too big
 for inputs around 0.0000001, and too small for inputs like 10,000.
 --------
 
 
 ------------------------------------------------------------------------------
 In this algorithm, we first check if a and b are close together in absolute terms, which handles the case where a and b are both close to zero. The absEpsilon parameter should be set to something very small (e.g. 1e-12). If that fails, then we fall back to Knuth’s algorithm, using the relative epsilon.

 Here’s our previous code testing both algorithms:

 #include <algorithm>
 #include <cmath>
 #include <iostream>

 // return true if the difference between a and b is within epsilon percent of the larger of a and b
 bool approximatelyEqualRel(double a, double b, double relEpsilon)
 {
     return (std::abs(a - b) <= (std::max(std::abs(a), std::abs(b)) * relEpsilon));
 }

 bool approximatelyEqualAbsRel(double a, double b, double absEpsilon, double relEpsilon)
 {
     // Check if the numbers are really close -- needed when comparing numbers near zero.
     double diff{ std::abs(a - b) };
     if (diff <= absEpsilon)
         return true;

     // Otherwise fall back to Knuth's algorithm
     return (diff <= (std::max(std::abs(a), std::abs(b)) * relEpsilon));
 }

 int main()
 {
     // a is really close to 1.0, but has rounding errors
     double a{ 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 };

     std::cout << approximatelyEqualRel(a, 1.0, 1e-8) << '\n';     // compare "almost 1.0" to 1.0
     std::cout << approximatelyEqualRel(a-1.0, 0.0, 1e-8) << '\n'; // compare "almost 0.0" to 0.0

     std::cout << approximatelyEqualAbsRel(a, 1.0, 1e-12, 1e-8) << '\n'; // compare "almost 1.0" to 1.0
     std::cout << approximatelyEqualAbsRel(a-1.0, 0.0, 1e-12, 1e-8) << '\n'; // compare "almost 0.0" to 0.0
 }
 ------------------------------------------------------------------------------
 */

#include <iostream>

double some_function()
{
    return 0.0;
}

int main()
{
    int x{2};
    int y{x};
    
    /// using relational operators
    if (x > y)
        std::cout << "x is greater!" << '\n';
    if (x < y)
        std::cout << "x is smaller!" << '\n';
    if (x >= y)
        std::cout << "x is greater/equal" << '\n';
    if (x <= y)
        std::cout << "x is smaller/equal" << '\n';
    if (x != y)
        std::cout << "x is not equal to y" << '\n';
    if (x == y)
        std::cout << "x equal y" << '\n';
    
    /// unexpected result with floating point comparison
    double d1{100.00 - 99.99};              /// 0.01
    double d2{10.0 - 9.99};                 /// 0.01
    
    if (d1 == d2)
        std::cout << "d1 == d2" << '\n';
    if (d1 > d2)
        std::cout << "d1 > d2" << '\n';
    if (d1 < d2)
        std::cout << "d1 < d2" << '\n';
    
    /// It is okay to compare a low-precision (few significant digits) floating point literal to the same
    /// literal value of the same type.
    /// this is valid to do, some_function( ) returns the same value as 0.0
    if (some_function() == 0.0)
        std::cout << "equal" << '\n';
        
    return 0;
}
