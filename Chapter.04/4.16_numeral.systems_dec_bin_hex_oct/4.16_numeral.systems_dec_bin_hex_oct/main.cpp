//
//  main.cpp
//  4.16_numeral.systems_dec_bin_hex_oct
//
//  Created by εκλεγμένοι εν Χριστώ on 10/3/22.
//

/*
 by default: numbers in C++ are assumed to be decimal
 
 Decimal    : 0 1 2 3 4 5 6 7 8 9
 Binary     : 0 1
 Octal      : 0 1 2 3 4 5 6 7
 Hexadecimal: 0 1 2 3 4 5 6 7 8 9 A B C D E F
 
 Octal and hexadecimal literals:
 In octal, counting goes like this:
 0, 1, 2, 3, 4, 5, 6, 7, 10, 11, 12.. - no 8 and 9, so we skip
 from 7 to 10
 octal: hardly used, so better to avoid it
 
 In hexadecimal, counting goes like this:
 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, A, B, C, D, E, F, 10, 11, 12...
 
 hexadecimal:
 16 different values: for a hexadecimal digit
 single hexadecimal digit: takes four bits
 pair of hexadecimal digits: takes 8 bits - 1 full byte
 
 hexadecimal values: often used to represent the memory
 addresses or raw data in memory(whose type is not known),
 hexadecimal values are more concise. example -
 0011 1010 0111 1111 1001 1000 0010 0110 = 3A7F 9826
 
 binary literals: before the C++14, no support for binary
 literals, the solution is to use hexadecimal literals
 digit separator: long literals can be hard to read, C++14
 also adds the ability to use a quotation mark (‘) as a
 digit separator, the separator can not occur before the
 first digit of the value
 
 I/O manipulators: change the output format C++ output values
 std::dec, std::oct, std::hex
 
 Outputting values in binary: std::cout doesn't come with this
 capability, solution is to use std::bitset type
 
 std::bitset - a type, <bitset> header, stores the number of
 bits.
 std::bitset - a variable can be defined to use this type
 number of bits used - must be a compile-time constant
 std::bitset - can be initialized with with an unsigned
 integral value in any format including dec, oct hex and
 binary.
 
 */

#include <bitset>
#include <iostream>

int main()
{
    /// octal literal with prefix 0 - 012: 10 in decimal
    /// 0 before the number means it is octal
    int octal{012};
    std::cout << "Oct: " << octal << '\n';
    
    /// hexadecimal literal with prefix 0x - C: 12 in decimal
    /// 0x before the number means it is hexadecimal
    int hexadecimal{0xC};
    std::cout << "hex: " << hexadecimal << '\n';
    
    /// hexadecimal literals provide a useful workaround for binary literals
    /// below assumed int as 16bit
    int binary{};
    binary = 0x0020;
    std::cout << "bin: " << binary << '\n';
    
    /// binary literal with prefix 0b - 240 in decimal
    /// assign binary 0000 0000 1111 0000 to the variable bin
    int bin{0b11110000};
    std::cout << "bin: " << bin << '\n';
    
    /// using quotation mark ' as a digit separator
    bin = 0b1011'0010;
    std::cout << "bin: " << bin << '\n';
    
    /// digit separator ' : made the literal easier to read
    long value{1'000'000'000};
    std::cout << "long: " << value << '\n';
    
    /// I/O manipulators: std::hex, std::oct and std::dec
    /// I/O manipulator remains set until it is changed again
    int decimal{12};
    std::cout << "default: " << decimal << '\n';
    std::cout << "hex: " << std::hex << decimal << '\n';
    /// manipulator is still in function, so decimal will be printed in hexadecimal
    /// as below
    std::cout << "hex: " << decimal << '\n';
    std::cout << "hex: " << decimal << '\n';
    std::cout << "hex: " << decimal << '\n';
    /// manipulator changed to std::oct
    std::cout << "oct: " << std::oct << decimal << '\n';
    std::cout << "bin: " << std::dec << decimal << '\n';
    
    /// bitset type to output values in binary
    /// <8>, <4>: are the number of bits specified that we want to store
    /// bin literal below
    std::bitset<8> binary1{0b10110010};
    /// hex literal
    std::bitset<8> binary2{0xC5};
    
    std::cout << binary1 << '\n';
    std::cout << binary2 << '\n';
    
    /// a temporary unnamed bitset object with 4 bits and printing, after printing
    /// the temporary object will be discarded
    std::cout << std::bitset<4>{0b1011} << '\n';
    
    return 0;
}
