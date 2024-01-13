//
//  main.cpp
//  O.4_converting.between.binary.and.decimal
//
//  Created by εκλεγμένοι εν Χριστώ on 10/30/22.
//

/*
 binary digits: 0 and 1
 
 Because there are 10 decimal numbers, the value of each subsequent
 digit to the left increases by a factor of 10.
 Binary numbers work the same way, except because there are only 2
 binary digits (0 and 1), the value of each digit increases by a
 factor of 2.
 
 converting binary to decimal:
 8 bit binary number:
 01011110 = (0 * 128) + (1 * 64) + (0 * 32) + (1 * 16) + (1 * 8) +
 (1 * 4) + (1 * 2) + (0 * 1)
 
 64 + 16 + 8 + 4 + 2 = 94.

 -----------------------------------------------------------------------
 converting decimal to binary: method 1
 continually divide the decimal number by 2 and writing down remainders,
 the binary number is constructed at the end from the remainders, from
 the bottom up
 148 from decimal to binary(using r to denote a remainder)
 148 / 2 = 74 r0
 74 / 2 = 37 r0
 37 / 2 = 18 r1
 18 / 2 = 9 r0
 9 / 2 = 4 r1
 4 / 2 = 2 r0
 2 / 2 = 1 r0
 1 / 2 = 0 r1
 
 Writing all of the remainders from the bottom up: 1001 0100

 148 decimal = 1001 0100 binary.
 
 verifying by converting the binary back to decimal:
 (1 * 128) + (0 * 64) + (0 * 32) + (1 * 16) + (0 * 8) + (1 * 4) +
 (0 * 2) + (0 * 1) = 148
 -----------------------------------------------------------------------
 converting decimal to binary: method 2
 The second method involves working backwards to figure out what each of the bits must be. This method can be easier with small binary numbers.

 Consider the decimal number 148 again. What’s the largest power of 2 that’s smaller than 148? 128, so we’ll start there.

 Is 148 >= 128? Yes, so the 128 bit must be 1. 148 - 128 = 20, which means we need to find bits worth 20 more.
 Is 20 >= 64? No, so the 64 bit must be 0.
 Is 20 >= 32? No, so the 32 bit must be 0.
 Is 20 >= 16? Yes, so the 16 bit must be 1. 20 - 16 = 4, which means we need to find bits worth 4 more.

 Is 4 >= 8? No, so the 8 bit must be 0.
 Is 4 >= 4? Yes, so the 4 bit must be 1. 4 - 4 = 0, which means all the rest of the bits must be 0.

 148 = (1 * 128) + (0 * 64) + (0 * 32) + (1 * 16) + (0 * 8) + (1 * 4) + (0 * 2) + (0 * 1) = 1001 0100
 -----------------------------------------------------------------------
 
 adding in binary:
 because a binary digit can only be a 0 or a 1, there are only 4
 possibilities:
 
 0 + 0 = 0
 0 + 1 = 1
 1 + 0 = 1
 1 + 1 = 0, carry a 1 over to the next column
 
 0110   +
 0111
 ----
 1101
 
 Now, how do we add 1 to any given binary number (such as 1011 0011)? The same as above, only the bottom number is binary 1.

        1  (carry column)
 1011 0011 (original binary number)
 0000 0001 (1 in binary)
 ---------
 1011 0100

 -----------------------------------------------------------------------
 Signed numbers and two’s complement:
 signed integers: stored using 2's complement,
 In two’s complement: the leftmost (most significant) bit is used as
 the sign bit
 A 0 sign bit means the number is positive, and a 1 sign bit means the
 number is negative.
 
 Positive signed numbers are represented in binary just like positive unsigned numbers (with the sign bit set to 0).
 
 Negative signed numbers are represented in binary as the bitwise inverse of the positive number, plus 1.
 
 Converting decimal to binary (two’s complement):
 5 :  0000 0101
 converting to -5 using 2's complement
 bitwise inverse of 5 : 11111010
 add 1 to inverse of 5 :
 11111010   +
 00000001
 --------
 11111011 is -5 in decimal
 
 -----------------------------------------------------------------------
 Converting binary (two’s complement) to decimal:
 
 To convert a two’s complement binary number back into decimal, first look at the sign bit.

 If the sign bit is 0, just convert the number as shown for unsigned numbers above.

 If the sign bit is 1, then we invert the bits, add 1, then convert to decimal, then make that decimal number negative (because the sign bit was originally negative).

 For example, to convert 1001 1110 from two’s complement into a decimal number:
 Given: 1001 1110
 Invert the bits: 0110 0001
 Add 1: 0110 0010
 Convert to decimal: (0 * 128) + (1 * 64) + (1 * 32) + (0 * 16) + (0 * 8) + (0 * 4) + (1 * 2) + (0 * 1) = 64 + 32 + 2 = 98
 Since the original sign bit was negative, the final value is -98.
 
 -----------------------------------------------------------------------
 
 Why types matter

 Consider the binary value 1011 0100. What value does this represent? You’d probably say 180, and if this were a standard unsigned binary number, you’d be right.

 However, if this value was stored using two’s complement, it would be -76.

 And if the value were encoded some other way, it could be something else entirely.

 So how does C++ know whether to print a variable containing binary 1011 0100 as 180 or -76?

 In case the section title didn’t give it away, this is where types come into play. The type of the variable determines both how a variable’s value is encoded into binary, and decoded back into a value. So if the variable type was an unsigned integer, it would know that 1011 0100 was standard binary, and should be printed as 180. If the variable was a signed integer, it would know that 1011 0100 was encoded using two’s complement (now guaranteed as of C++20), and should be printed as -76.
 
 -----------------------------------------------------------------------
 
 */

#include <iostream>

int printAndDecrementOne(int x, int pow)
{
    std::cout << '1';
    return (x - pow);
}

// x is our number to test
// pow is a power of 2 (e.g. 128, 64, 32, etc...)
int printAndDecrementBit(int x, int pow)
{
    // Test whether our x is greater than some power of 2 and print the bit
    if (x >= pow)
        return printAndDecrementOne(x, pow); // If x is greater than our power of 2, subtract the power of 2

    // x is less than pow
    std::cout << '0';
    return x;
}

int main()
{
    std::cout << "Enter an integer between 0 and 255: ";
    int x{};
    std::cin >> x;

    x = printAndDecrementBit(x, 128);
    x = printAndDecrementBit(x, 64);
    x = printAndDecrementBit(x, 32);
    x = printAndDecrementBit(x, 16);

    std::cout << ' ';

    x = printAndDecrementBit(x, 8);
    x = printAndDecrementBit(x, 4);
    x = printAndDecrementBit(x, 2);
    x = printAndDecrementBit(x, 1);

    std::cout << '\n';

    return 0;
}
