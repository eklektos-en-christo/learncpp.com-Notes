//
//  main.cpp
//  O.1_bit.flags_bit.manipulation.via_std_bitset
//
//  Created by εκλεγμένοι εν Χριστώ on 10/25/22.
//

/*
 smallest addressable unit of memory on modern architectures : 1 byte
 
 all objects : have unique memory addresses
 
 objects : must be at least one byte in size to have a unique address
 
 BIT MANIPULATION : modifying individual bits within an object, useful in
 encryption and compression algorithms
 
 BIT FLAGS : when individual bits of an object are used as boolean values
 those bits are called bit flags
 
 flag in computing : acts as a signal for some function/process
 
 to define a set of bit flags : use an unsigned integer of appropriate
 size
 
 Best practice
 Bit manipulation is one of the few times when you should unambiguously
 use unsigned integers (or std::bitset).
 
 bit numbering : bits are numbered from right to left, starting from 0
 +------------------------------------------------------+
 7      6       5       4       3       2       1       0   bit position
 +------------------------------------------------------+
 0      0       0       0       0       1       0       1   bit sequence
 +------------------------------------------------------+
 
 here - at position 0 and 2, the bits have value 1 and rest bits are zero
 
 std::bitset : provide key functions that are useful for doing bit
 manipulation, below -
 test() - allows to query whether a bit is 0 or 1
 set() - allows to turn a bit ON, will do nothing if bit is ON already
 reset() - allows to turn a bit OFF, will do nothing if bit is OFF already
 flip() - allows to flip a bit value from a 0 to a 1 and vice versa
 
 all these functions takes the position of the bit as their only argument, bit
 on which the operation is to be performed, this means all these functions
 work on a single bit.
 */

#include <bitset>
#include <iostream>

int main()
{
    /// 8 means space for 8 bit flags
    std::bitset<8> my_bitset{0b0101'0101};
    
    std::cout << "all the bits before operation: " << my_bitset << '\n';
        
    /// applying functions to operate on bits
    my_bitset.set(1);
    my_bitset.flip(2);
    my_bitset.reset(0);
    my_bitset.set(6);
        
    std::cout << "all the bits after operation: " << my_bitset << '\n';
    
    /// using test( ) to query the bit's state
    std::cout << "bit 0: " << my_bitset.test(0) << '\n';
    std::cout << "bit 1: " << my_bitset.test(1) << '\n';
    std::cout << "bit 2: " << my_bitset.test(2) << '\n';
    std::cout << "bit 3: " << my_bitset.test(3) << '\n';
    std::cout << "bit 4: " << my_bitset.test(4) << '\n';
    std::cout << "bit 5: " << my_bitset.test(5) << '\n';
    std::cout << "bit 6: " << my_bitset.test(6) << '\n';
    std::cout << "bit 7: " << my_bitset.test(7) << '\n';
    
    return 0;
}
