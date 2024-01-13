//
//  main.cpp
//  4.6_fixed.width.integers.and.size_t
//
//  Created by εκλεγμένοι εν Χριστώ on 9/14/22.
//

/*
 Why isn’t the size of the integer variables fixed?
 so that the compiler implementers could pick a size for int
 that performs best on the target computer architecture.
 
 int:
 min. size: 2 bytes
 modern architecture: 4 bytes
 
 if you assume that int is 4 bytes, program will misbehave on
 architectures where the int is 2 bytes, which means storing
 the values that require 4 bytes in 2 bytes memory, this will
 cause overflow or undefined behavior.
 if you assume that int in 2 bytes to ensure the maximum
 compatibility, then on systems with 4 bytes int you're are
 wasting 2 extra bytes per integer and doubling the memory
 usage
 
 Fixed width integers: to address the above issue, this
 guarantees the same size on any architecture.
 <stdint.h> header in C where they are defined
 <cstdint> header in C++ where they are defined in std::
 
 std::int8_t    1byte   -128 to 127
 std::uint8_t   1byte   0 to 255
 std::int16_t   2       -32,768 to 32,767
 std::uint16_t  2       0 to 65,535
 std::int32_t   4       -2,147,483,648 to 2,147,483,647
 std::uint32_t  4       0 to 4,294,967,295
 std::int64_t   8       -9,223,372,036,854,775,808 to
                        9,223,372,036,854,775,807
 std::uint64_t  8       0 to 18,446,744,073,709,551,615
 
 int8_t and uint8_t: treated like signed and unsigned char on
 many systems.
 
 downsides of fixed width integers:
 First:
 not guaranteed to be defined on all architectures
 Second:
 it may be slower than a wider type on some architectures, its
 hard to know without actually measuring.
 
 Fast and least integers: to help address the above downsides.
 Fast:
 they provide the fastest signed/unsigned integer type with a
 width of at least 8,16,32,64 bits.
 Least:
 provide the smallest signed/unsigned integer type with a
 width of at least 8,16,32,64 bits.
 
 size of the fast/least integers can vary, it’s possible that
 your program may exhibit different behaviors on
 architectures where they resolve to different sizes.
 
 std::int8_t and std::uint8_t likely behave like chars
 instead of integers:
 most compilers treat std::int8_t and std::uint8_t (and the
 corresponding fast and least fixed-width types)
 identically to types signed char and unsigned char
 respectively.
 This means these 8-bit types may (or may not) behave
 differently than the rest of the fixed-width types,
 which can lead to errors. This behavior is
 system-dependent, so a program that behaves correctly
 on one architecture may not compile or behave correctly
 on another architecture.
 
 For consistency, it’s best to avoid std::int8_t and std::uint8_t (and the related fast and least types) altogether (use std::int16_t or std::uint16_t instead).
 Warning
 The 8-bit fixed-width integer types are often treated like chars instead of integer values (and this may vary per system). Prefer the 16-bit fixed integral types for most cases.
 
 
 Integral best practices:
    Prefer int when the size of the integer doesn’t matter
    Prefer std::int#_t when storing a quantity that needs a
    guaranteed range.
    Prefer std::uint#_t when doing bit manipulation or where
    well-defined wrap-around behavior is required.
 
 Avoid the following when possible:
    Unsigned types for holding quantities
    The 8-bit fixed-width integer types
    The fast and least fixed-width types
    Any compiler-specific fixed-width integers -- for example
    Visual Studio defines __int8, __int16, etc…
 
 
 size_t: unsigned integral type, used to represent the size
 or length of objects.
 size_t: unsigned, 16 bits at least
 size_t: on most systems will be equivalent to the address-
 width of the application.
 32bit applications: size_t is 32bit unsigned integer
 64bit applications: size_t is 64bit unsigned integer
 
 size_t: big enough to hold the size of the largest object
 creatable on the system and can't be larger than the object
 
 object: with size larger than the largest integral value
 size_t can hold is considered ill-formed. sizeof operator
 wouldn't be able to return the size without wrapping around.
 */

#include <cstdint>      /// included for fixed width integers
#include <cstddef>      /// std::size_t
#include <iostream>

int main()
{
    std::int8_t i{2};
    std::cout << sizeof(i) << '\n';
    
    std::cout << '\n';
    std::cout << sizeof(std::int_least8_t) << '\n';
    std::cout << sizeof(std::int_least16_t) << '\n';
    std::cout << sizeof(std::int_least32_t) << '\n';
    std::cout << sizeof(std::int_least64_t) << '\n';
    std::cout << '\n';
    std::cout << sizeof(std::int_fast8_t) << '\n';
    std::cout << sizeof(std::int_fast16_t) << '\n';
    std::cout << sizeof(std::int_fast32_t) << '\n';
    std::cout << sizeof(std::int_fast64_t) << '\n';
    
    std::cout << '\n';
    std::cout << sizeof(std::size_t) << '\n';
    
    return EXIT_SUCCESS;
}
