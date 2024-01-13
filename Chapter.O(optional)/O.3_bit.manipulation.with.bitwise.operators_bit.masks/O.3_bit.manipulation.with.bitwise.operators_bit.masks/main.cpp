//
//  main.cpp
//  O.3_bit.manipulation.with.bitwise.operators_bit.masks
//
//  Created by εκλεγμένοι εν Χριστώ on 10/27/22.
//

/*
 bitwise operators : work with bit masks
 
 BIT MASKS : predefined set of bits used to select specific bits that
 will be modified by subsequent/following/successive operations
 
 simple example of masking :
 Consider a real-life case where you want to paint a window frame. If you’re not careful, you risk painting not only the window frame, but also the glass itself. You might buy some masking tape and apply it to the glass and any other parts you don’t want painted. Then when you paint, the masking tape blocks the paint from reaching anything you don’t want painted. In the end, only the non-masked parts (the parts you want painted) get painted.
 
 bit mask : blocks the bitwise operators from touching bits that aren't
 to be modified, bit mask helps to access the bits which requires
 modification
 
 defining bit masks : simplest set of bit masks is to define one bit
 mask for each bit position, 0s used for the bits that don't need
 modification, 1s used to denote the bits that need modification
 
 symbolic constants : often used to define bit masks, they also give
 the mask a meaningful name
 
 testing a bit to see if it is ON or OFF : to determine if a bit is ON
 or OFF, bitwise AND in conjunction with the bit mask for the
 appropriate bit.
 
 setting/turn on a bit : bitwise OR equals(|=) operator in conjunction with bit
 mask will turn the bit flag ON.
 
 Resetting a bit/turning the bit OFF : bitwise AND and bitwise NOT used
 together to set the bit OFF.
 
 Flipping a bit : to change/toggle the state of the bit, XOR can be used.
 XOR will return true only if both inputs are different, same inputs will give 0
 
 std::bitset vs bit masks - std::bitset functions allow to modify individual
 bits only, bitwise operator allow to modify multiple bits at once with the bit
 masks
 
 A best practice is to give your bit masks useful names as a way to document
 the meaning of your bit flags.
 
 std::bitset::any() : returns true if any of the bit is set/ON/true, returns
 false if all bits are OFF/zero/false
 
 using of bit flags : programs where there are tens of thousands or even
 millions of similar objects, using bit flags can reduce memory use
 substantially. It’s a useful optimization to have in your toolkit if you need
 it.
 
 
 */

#include <iostream>

int main()
{
    /// bit masks representing bit 0 to bit 7
    /// these symbolic constants represent each bit position
    ///
    /// hexadecimal literals can be used to define bit masks
    /// constexpr std::uint8_t mask0{ 0x01 }; // hex for 0000 0001
    ///
    /// left shift operator can be used to shift a single bit into proper location
    /// constexpr std::uint8_t mask0{ 1 << 1 }; // 0000 0010
    constexpr std::uint8_t mask0{0b00000001};
    constexpr std::uint8_t mask1{0b00000010};
    constexpr std::uint8_t mask2{0b00000100};
    constexpr std::uint8_t mask3{0b00001000};
    constexpr std::uint8_t mask4{0b00010000};
    constexpr std::uint8_t mask5{0b00100000};
    constexpr std::uint8_t mask6{0b01000000};
    constexpr std::uint8_t mask7{0b10000000};
    
    std::uint8_t bits{0b00000101};
    
    /// testing the ON/OFF state of the bits in a bit flag variable using AND operator
    /// bit flag variable & bit mask will give the state of the bit in bit flag variable
    /// so AND + bit flag will tell if the bit is on or off, AND returns true if both bits are true/ON/1
    /// so if the bit flag is ON and bit mask's ON bit, the AND operation between them will give 1
    std::cout << "bit 0 is: " << ((bits & mask0) ? "ON" : "OFF") << '\n';
    std::cout << "bit 1 is: " << ((bits & mask1) ? "ON" : "OFF") << '\n';
    std::cout << "bit 2 is: " << ((bits & mask2) ? "ON" : "OFF") << '\n';
    std::cout << "bit 3 is: " << ((bits & mask3) ? "ON" : "OFF") << '\n';
    std::cout << "bit 4 is: " << ((bits & mask4) ? "ON" : "OFF") << '\n';
    std::cout << "bit 5 is: " << ((bits & mask5) ? "ON" : "OFF") << '\n';
    std::cout << "bit 6 is: " << ((bits & mask6) ? "ON" : "OFF") << '\n';
    std::cout << "bit 7 is: " << ((bits & mask7) ? "ON" : "OFF") << '\n';
    
    std::cout << "before, bit 7 is: " << ((bits & mask7) ? "ON" : "OFF") << '\n';
    
    /// setting the bit, turning it on using |= operator in conjunction with bit mask
    /// because - in OR, if one of the bit is ON then result is true
    /// if both bits are ON, then also the result is true
    ///
    /// turning ON multiple bits is also possible
    /// flags |= (mask4 | mask5); // turn bits 4 and 5 on at the same time
    bits |= mask7;
    std::cout << "after, bit 7 is: " << ((bits & mask7) ? "ON" : "OFF") << '\n';
    
    std::cout << "before, bit 7 is: " << ((bits & mask7) ? "ON" : "OFF") << '\n';
    
    /// bitwise AND and bitwise NOT together to reset the bit
    /// explanation : NOT will flip all the bits in the mask
    /// in the below case the mask7, at position 7 contains an bit, the rest bits are zero
    /// NOT will flip all the zero bits to 1 and bit at 7 will become zero
    /// AND between mask7 and bits will make the result 0 because AND return true if both bits are true
    /// but because of NOT, we flipped the bit to 0 in the bit mask, so ANDing will not give the result as true
    ///
    ///We can turn off multiple bits at the same time:
    /// flags &= ~(mask4 | mask5); // turn bits 4 and 5 off at the same time
    bits &= ~mask7;
    std::cout << "after, bit 7 is: " << ((bits & mask7) ? "ON" : "OFF") << '\n';
    
    std::cout << "before, bit 7 is: " << ((bits & mask7) ? "ON" : "OFF") << '\n';
    
    /// flipping the bit using XOR
    /// bit 7 is ON currently
    /// to flip it XOR can help
    /// in mask7, the 7th bit is ON, in the bits at 7th position, the bit is OFF
    /// XOR between mask7 and bit at 7th position in the bits will result true
    /// because XOR will return true only if one of the bit is ON, if both are on then it returns false/0
    /// in this case, mask7 has ON bit, 7th bit in bits is OFF so XOR will flip that bit, result will be true
    ///
    /// flipping multiple bits at the same time
    /// flags ^= (mask4 | mask5); // flip bits 4 and 5 at the same time
    bits ^= mask7;
    std::cout << "after, bit 7 is: " << ((bits & mask7) ? "ON" : "OFF") << '\n';
    
    
    std::bitset<8> flags{0b00000101};
    
    std::cout << "before, bit 1: " << (flags.test(1) ? "ON" : "OFF") << '\n';
    std::cout << "before, bit 2: " << (flags.test(2) ? "ON" : "OFF") << '\n';
    
    /// flipping
    flags ^= (mask1 | mask2);
    
    std::cout << "after, bit 1: " << (flags.test(1) ? "ON" : "OFF") << '\n';
    std::cout << "after, bit 2: " << (flags.test(2) ? "ON" : "OFF") << '\n';
    
    /// turning ON
    flags |= (mask1 | mask2);
    
    std::cout << "ON, bit 1: " << (flags.test(1) ? "ON" : "OFF") << '\n';
    std::cout << "ON, bit 2: " << (flags.test(2) ? "ON" : "OFF") << '\n';
    
    /// turning OFF
    flags &= ~(mask1 | mask2);

    std::cout << "OFF, bit 1: " << (flags.test(1) ? "ON" : "OFF") << '\n';
    std::cout << "OFF, bit 2: " << (flags.test(2) ? "ON" : "OFF") << '\n';
    
    /// meaning names, a way to document the meaning of bit flags
    /// 1 << 0 - 1 represents 0001 in binary
    constexpr std::uint8_t is_hungry{1 << 0};
    constexpr std::uint8_t is_sad{1 << 1};
    constexpr std::uint8_t is_mad{1 << 2};
    constexpr std::uint8_t is_happy{1 << 3};
    constexpr std::uint8_t is_laughing{1 << 4};
    constexpr std::uint8_t is_asleep{1 << 5};
    constexpr std::uint8_t is_dead{1 << 6};
    constexpr std::uint8_t is_crying{1 << 7};
    
    /// 0 flags - all the flags are zero
    std::uint8_t me{};
    
    me |= (is_sad | is_crying);
    
    std::cout << "I'm sad: " << static_cast<bool>(me & is_sad) << '\n';
    std::cout << "I'm crying: " << static_cast<bool>(me & is_crying) << '\n';
    
    constexpr std::uint32_t red_bits{0xFF000000};
    constexpr std::uint32_t green_bits{0x00FF0000};
    constexpr std::uint32_t blue_bits{0x0000FF00};
    constexpr std::uint32_t alpha_bits{0x000000FF};
    
    std::cout << "Enter 32-bit RGBA color value in hex: ";
    std::uint32_t pixel{};
    std::cin >> std::hex >> pixel;
    
    std::uint8_t red{static_cast<uint8_t>((pixel & red_bits) >> 24)};
    std::uint8_t green{static_cast<uint8_t>((pixel & green_bits) >> 16)};
    std::uint8_t blue{static_cast<uint8_t>((pixel & blue_bits) >> 8)};
    std::uint8_t alpha{static_cast<uint8_t>(pixel & alpha_bits)};
    
    std::cout << "Color contains: ";
    
    std::cout << std::hex;
    std::cout << "red: " << static_cast<int>(red) << '\n';
    std::cout << "green: " << static_cast<int>(green) << '\n';
    std::cout << "blue: " << static_cast<int>(blue) << '\n';
    std::cout << "alpha: " << static_cast<int>(alpha) << '\n';
    
    return 0;
}
