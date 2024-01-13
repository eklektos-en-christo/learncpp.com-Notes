//
//  main.cpp
//  4.5_unsigned.integers.and.why.to.avoid.them
//
//  Created by εκλεγμένοι εν Χριστώ on 9/13/22.
//

/*
 Unsigned integers: integers that can only hold non-negative
 whole numbers.
 
 Unsigned integer range:
 1 byte unsigned integer's range: 0 - 255, 256 distinct values
 
 1 byte unsigned        0 - 255
 2 byte unsigned        0 - 65,535
 4 byte unsigned        0 - 4,294,967,295
 8 byte unsigned        0 - 18,446,744,073,709,551,615
 
 n-bit unsigned variable's range: 0 to 2^(n) - 1
 
 unsigned integers: well suited for networking, systems with
 little memory
 
 unsigned integer overflow: unsigned value out of range
 fix: modulo wrapping/wraps around
 
 modulo wrapping: unsigned value/largest number of the type+1,
 remainder is kept
 
 example: 260 is too big to fit in 1byte range of 0-255
 largest number of the type: 255
 1+largest number of the type: 256
 modulo wrapping: 260/256 = 4(remainder) - stored
 
 Best practice

 Favor signed numbers over unsigned numbers for holding quantities (even quantities that should be non-negative) and mathematical operations. Avoid mixing signed and unsigned numbers.
 
 So when should you use unsigned numbers?
 preferred when dealing with bit manipulation
 when well-defined wrap-around behavior is required
 (useful in some algorithms like encryption and random number generation).

 if you’re developing for an embedded system (e.g. an Arduino) or some other processor/memory limited context, use of unsigned numbers is more common and accepted (and in some cases, unavoidable) for performance reasons.

 */

#include <iostream>

int main()
{
    /// defining unsigned integer using unsigned keyword
    unsigned short us;
    unsigned int ui;
    unsigned long ul;
    unsigned long long ull;
    
    std::cout << "short\t\t" << sizeof(us) << '\n';
    std::cout << "int\t\t\t" << sizeof(ui) << '\n';
    std::cout << "long\t\t" << sizeof(ul) << '\n';
    std::cout << "long long\t" << sizeof(ull) << '\n';
    
    /// largest 16 bit unsigned value possible
    unsigned short a{65535};
    std::cout << '\n' << "a before: " << a << '\n';
    
    /// out of range, so wrap around, remainder 0 saved in a
    a = 65536;
    std::cout << "a after: " << a << '\n';
    
    /// out of range, so wrap around, remainder 0 saved in a
    a = 65537;
    std::cout << "a after: " << a << '\n';
    
    /// smallest 16 bit unsigned value possible
    unsigned short b{0};
    std::cout << "b before: " << b << '\n';
    
    /// out of range, so wrap around to the top of the range
    b = -1;
    std::cout << "b after: " << b << '\n';
    
    /// out of range, so wrap around to the top of the range
    b = -2;
    std::cout << "b after: " << b << '\n';
    
    /// largest 32 bit unsigned  value possible
    unsigned int c{4294967295};
    std::cout << "c before: " << c << '\n';
    
    /// out of range, so wrap around to the top of the range
    c = -1;
    std::cout << "c after: " << c << '\n';
    
    /// out of range, so wrap around to the top of the range
    c = -2;
    std::cout << "c after: " << c << '\n';
}
