//
//  main.cpp
//  11.10_c.style.string.symbolic.constants
//
//  Created by Εκλεκτός εν Χριστώ on 4/3/23.
//

/*
 C++ - supports a way to create c-style string constants using pointers
 
 C++ dealing with the memory allocation:
 string literals can’t be changed, so the string must be const
 For optimization purposes, multiple string literals may be consolidated into a single
 value. For example:
 const char* name1{ "Alex" };
 const char* name2{ "Alex" };
 
 These are two different string literals with the same value, these both are constants, the
 compiler may opt to save memory by combining these into a single shared string literal
 with both name1 and name2 pointed at the same address
 
 string literals being stored in a fixed location in memory - string literals have static
 duration rather than automatic duration, they die at the end of the program
 
 when we use string literals - we don't have to worry about scoping issues
 
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 std::cout and char pointers
 
 std::cout - handles pointers of different types differently
 
 if you pass it a non-char pointer - it simply prints the contents of that pointer, address
 if you pass it the object of type char* or const char* - it will assume you're intending to
 print a string
 */

#include <iostream>

int main()
{
    /// c-style array
    /// memory allocated for a fixed array of length 7
    /// initialized that memory with the string "edward\0"
    /// contents of the array are free to be altered
    /// array itself is a normal local variable
    /// when array goes out of scope, memory is freed used by the array
    char my_name[]{"edward"};
    std::cout << my_name << '\n';
    
    /// c-style string symbolic constant using pointer
    /// pointer to a string literal
    /// compiler places the string "edward\0" into read-only memory somewhere
    /// then sets the pointer to point to it
    /// string literals can't be changed, so string must be const
    const char* my_name_again{"edward"};
    std::cout << my_name_again << '\n';
    
    int int_array[5]{1, 2, 3, 4, 5};
    char char_array[]{"hello"};
    const char* name{"leon"};
    
    /// int array print an address
    std::cout << int_array << '\n';
    /// std::cout will assume you're intending to print a string
    std::cout << char_array << '\n';
    /// std::cout will assume you're intending to print a string
    std::cout << name << '\n';
    
    char c{'A'};
    /// std::cout - assumed &c which has type char* was a string
    /// it printed 'A' and then kept going, next is memory was a bunch of garbage
    /// it stopped at memory holding a 0 value, which acted as a null terminator
    std::cout << &c << '\n';
    
    return 0;
}
