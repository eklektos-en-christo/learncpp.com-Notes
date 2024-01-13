//
//  main.cpp
//  O.2_bitwise.operators
//
//  Created by εκλεγμένοι εν Χριστώ on 10/26/22.
//

/*
 C++'s 6 bitwise operators:
 +----------------------------------------------------------------------+
 OPERATOR           SYMBOL              FORM            OPERATION
 +----------------------------------------------------------------------+
 left shift         <<                  x << y          all bits in x
                                                        shifted left y
                                                        bits
 right shift        >>                  x >> y          all bits in x
                                                        shifted right y
                                                        bits
 bitwise NOT        ~                   ~x              all bits in x
                                                        flipped
 bitwise AND        &                   x & y           each bit in x
                                                        AND
                                                        each bit in y
 bitwise OR         |                   x | y           each bit in x
                                                        OR
                                                        each bit in y
 bitwise XOR        ^                   x ^ y           each bit in x
                                                        XOR
                                                        each bit in y
 +----------------------------------------------------------------------+
 
 Best practice
 To avoid surprises, use the bitwise operators with unsigned operands or
 std::bitset.
 
 In actual programs: the number of bits used is based on the size of the
 object
 
 bitwise operators : defined for integral type and std::bitset
 
 -------------------------------------------------
 bitwise left shift << - shift bits to left, left operand is the
 expression to shift the bits of and the right operand is an integer no.
 which specifies the number of bits to shift left by. new bits shifted in
 from the right side receive the value 0
 bits that are shifted off the end of the binary number are lost forever
 
 example : x << 1 - means "shift the bits in x left by 1 place"
 
 0011 << 1 will be 0110, bits shifted by 1 place, empty bits will receive
 the value 0, or the new bits shifted from right side will receive the
 value 0
 
 -------------------------------------------------
 bitwise right shift >> - shift bits to the right
 example : 1100 >> 1 will become 0110, the rest of the thing is same as
 left shift operator
 
 -------------------------------------------------
 bitwise NOT ~ : flips each bit from 0 to 1 or vice versa. result of
 bitwise ~ depends upon the size of the type
 example: ~0100 will become 1011
          ~0000 0100 will become 1111 1011
 
 -------------------------------------------------
 bitwise OR | : works like logical OR(||), but bitwise OR applies to each
 bit
 example: 0101 | 0110
 doing OR below
 0 1 0 1   OR, operation applied to each column of bits
 0 1 1 0
 -------
 0 1 1 1

 
 below in compound OR expression,
 if any of bits in a column are 1, then the result is 1
 
 0 1 1 1 OR
 0 0 1 1 OR
 0 0 0 1
 --------
 0 1 1 1
 
 
 -------------------------------------------------
 bitwise AND & - evaluates to true(1) if both bits in the column are true
 example:
 0 1 0 1 AND
 0 1 1 0
 --------
 0 1 0 0
 
 compound AND expression, if all bits are true in a column then the
 result will be 1(true)
 0 0 0 1 AND
 0 0 1 1 AND
 0 1 1 1
 --------
 0 0 0 1
 
 
 -------------------------------------------------
 bitwise XOR ^ - evaluates to true if only one of its operands is true,
 evaluates to false even if both operands are true/false
 example:
 0 1 1 0 XOR
 0 0 1 1
 -------
 0 1 0 1

 
 compound XOR expression : if there are even number of bits in a column
 then the result will be false, otherwise if odd then true
 0 0 0 1 XOR
 0 0 1 1 XOR
 0 1 1 1
 --------
 0 1 0 1

 
 bitwise assignment operators: similar to arithmetic assignment operators
 +----------------------------------------------------------------------+
 OPERATOR           SYMBOL              FORM            OPERATION
 +----------------------------------------------------------------------+
 left shift assign. <<=                 x <<= y         shift x left by y
 right shift ,,     >>=                 x >>= y         shift x right ,,
 bitwise OR  ,,     |=                  x |= y          assign x|y to x
 bitwise AND ,,     &=                  x &= y          assign x&y to x
 bitwise XOR ,,     ^=                  x ^= y          assign x^y to x
 +----------------------------------------------------------------------+
 
 
 summary:
 -When evaluating bitwise OR, if any bit in a column is 1, the result for
 that column is 1.
 -When evaluating bitwise AND, if all bits in a column are 1, the result
 for that column is 1.
 -When evaluating bitwise XOR, if there are an odd number of 1 bits in a
 column, the result for that column is 1.
 
 
 bitwise rotation: same as bit shift, but in rotation any bits shifted
 off one end are added back to the other end
 example:
 1001 << 1 would be 0011, 1 added again at the right side
 */

#include <bitset>
#include <iostream>

std::bitset<4> rotate_left(std::bitset<4> bits)
{
    const bool left_bit{bits.test(3)};
    bits <<= 1;
    
    if (left_bit)
        bits.set(0);
        
    return bits;
}

std::bitset<4> rotl(std::bitset<4> bits)
{
    /// bits << 1 for left shift
    /// bits >> 3 for rotation of the leftmost bit
    return (bits << 1) | (bits >> 3);
}

int main()
{
    std::bitset<4> a{0b1100};
    
    std::cout << "before shifting: " << a << '\n';
    /// shifting left by 1, parenthesization is required here to print correctly
    std::cout << "left shifting: " << (a << 1) << '\n';
    /// shifting right by 1
    std::cout << "right shifting: " << (a >> 1) << '\n';
    
    std::bitset<8> b{0b1100};
    /// 1100 in this case is 00001100, total space is 8 bits, rest are zeroes, they flipped to 1
    std::cout << "flipping the bits: " << ~b << '\n';
    
    std::bitset<4> c{0b0101};
    std::bitset<4> d{0b0110};
    std::bitset<4> e{0b0001};
    
    /// bitwise OR operation on two operands
    /// in compound OR expression below, if any of bits in a column are 1, the result of
    /// that column is 1
    std::cout << "bitwise OR: " << (c | d | e) << '\n';
    
    /// bitwise AND operation on two operands
    std::cout << "bitwise AND: " << (c & d & e) << '\n';
    
    /// bitwise XOR operation
    std::cout << "bitwise XOR: " << (c ^ d ^ e) << '\n';
    
    /// bitwise assignment operator use
    std::bitset<4> f{0b1111};
    /// instead of f = f>>1, the assignment can simplify it as below
    f >>= 1;
    std::cout << "bitwise right shift: " << f << '\n';
    
    std::bitset<4> g{0b1001};
    
    /// bitwise left rotation below
    std::cout << "rotate left: " << rotate_left(g) << '\n';
    
    std::cout << "rotate left: " << rotl(g) << '\n';
    
    return 0;
}
