//
//  main.cpp
//  11.9_pointer.arithmetic.and.array.indexing
//
//  Created by Εκλεκτός εν Χριστώ on 3/31/23.
//

/*
 Pointer Arithmetic:
 
 C++ allows - to perform integer addition/subtraction operations on pointers
 
 if ptr points to an integer-
 ptr + 1 : is the next address of the next integer in memory after ptr
 ptr - 1 : is the address of the previous integer in memory before ptr
 
 ptr + 1 : does not return the memory address after ptr
 ptr + 1 : returns the memory address of the next object of the type that ptr points to
 
 Note: the integer to be added or subtracted to pointer is interpreted not as change of
 address but as number of elements to move.
 
 if ptr points to an integer of 4 bytes-
 ptr + 3 : means 3 integers after ptr, which is after 12 bytes
 
 if ptr points to a char, which is always 1 byte-
 ptr + 3 : means 3 chars after ptr, which is after 3 bytes
 
 Scaling - when calculating the result of a pointer arithmetic expression, compiler always
 multiplies the integer operand by the size of the object being pointed to
 
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Arrays - laid out sequentially in memory
 
 & operator - we can test by using operator& that arrays are laid out sequentially in memory
 i.e. element 0,1,2... are all adjacent to each other, in order.
 
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Magic behind the array indexing, pointer arithmetic and arrays:
 
 Arrays - laid out sequentially in memory
 fixed array - decay into pointer, that pointer points to the first element(0) of the array
 adding 1 to a pointer - returns the memory address of next object of that type in memory
 
 conclusion - adding 1 to an array should point to the second element of the array
 
 when compiler sees the subscript operator[] - it translates that into a pointer addition
 and indirection:
 array[n] = *(array+n)      here n is an integer
 that's the magic behind array indexing
 
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~-
 Using a pointer to iterate through an array:
 we can use a pointer and pointer arithmetic to loop through an array, not commonly used
 
 std::count_if - counts elements that fulfill a condition, resides in <algorithm> header
 
 std::begin - returns an iterator/pointer to the first element
 std::end   - returns an iterator to the element that would be one after the last element
 std::end   - iterator returned by std::end in only used as a marker, accessing it would
 cause undefined behavior because std::end doesn't point to a real element
 
 if array decayed to a pointer - we can calculate the begin and end manually
 
 std::count_if(name, name+length, isvowel); - length is no. of elements in the array
 Calculating begin and end of an array like this works for all algorithms that need a begin
 and end argument.
 
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~-
 std::find - finds the element in the given range
 */

#include <iostream>
#include <iterator>     /// for std::size, std::begin and std::end
#include <algorithm>    /// for std::count_if

bool is_vowel(char ch)
{
    switch (ch)
    {
        case 'A':
        case 'a':
        case 'E':
        case 'e':
        case 'I':
        case 'i':
        case 'O':
        case 'o':
        case 'U':
        case 'u':
            return true;
        default:
            return false;
    }
}

/// function takes pointer to the beginning and pointer to the end(1 element past the last element) and a value
/// function searches for a given value and return a pointer to the first element with that value
/// or the end pointer if no element was found
int* find_value(int* begin, int* end, int value)
{
    for (int* ptr{begin}; ptr != end; ++ptr)
        if (*ptr == value)
            return ptr;
    return end;
}

int main()
{
    int int_value{22};
    int* ptr{&int_value};
    
    /// at the run, each of these addresses - differs by 4, because int is 4 bytes on this machine
    std::cout << ptr << '\n';
    std::cout << ptr+1 << '\n';
    std::cout << ptr+2 << '\n';
    std::cout << ptr+3 << '\n';
    std::cout << ptr+4 << '\n';
    
    std::cout << '\n';
    
    short short_value{8};
    short* ptr_short{&short_value};
    
    /// at the run, each of these addresses - differs by 2, because short is 2 bytes on this machine
    std::cout << ptr_short << '\n';
    std::cout << ptr_short+1 << '\n';
    std::cout << ptr_short+2 << '\n';
    std::cout << ptr_short+3 << '\n';
    std::cout << ptr_short+4 << '\n';
    
    int array[]{1, 2, 3, 4, 5};
    
    /// each memory address is of 4 bytes, which is the size of an integer
    /// this proves that arrays are laid out sequentially in memory
    std::cout << "At 0: " << &array[0] << '\n';
    std::cout << "At 1: " << &array[1] << '\n';
    std::cout << "At 2: " << &array[2] << '\n';
    std::cout << "At 3: " << &array[3] << '\n';
    std::cout << "At 4: " << &array[4] << '\n';
    
    int array_one[]{1, 2, 3, 4, 5};
    
    /// address of first array element
    std::cout << &array_one[1] << '\n';
    /// address of 2nd array element, pointer returned the address, address incremented to 1
    std::cout << array+1 << '\n';
    
    /// 3rd array element
    std::cout << array_one[2] << '\n';
    /// 3rd array element
    /// pointer returned address, address incremented to 2 then final address dereferenced
    /// parentheses required here to ensure the operator precedence is correct
    /// * has higher precedence than +
    std::cout << *(array_one+2) << '\n';
    
    char name[]{"programming"};
    int length{static_cast<int>(std::size(name))};
    int num_vowels{0};
    
    /// pointer is used to step through each element in an array
    /// ptr initialized with name, will point to the first element of the array
    for (char* ptr{name}; ptr != (name + length); ++ptr)
        if (is_vowel(*ptr))
            ++num_vowels;
    
    std::cout << name << " has " << num_vowels << " vowels!\n";
    
    /// above for loop can be replaced with a call to std::count_if
    ///
    /// std::begin - returns an iterator/pointer to the first element
    /// std::end - returns an iterator to the element that would be one after the last element
    /// std::end - iterator returned by std::end in only used as a marker, accessing it would cause undefined behavior
    /// because std::end doesn't point to a real element
    ///
    /// std::begin and std::end - only work on arrays with a known size
    auto num_vowels2{std::count_if(std::begin(name), std::end(name), is_vowel)};
    
    std::cout << name << " has " << num_vowels2 << " vowels!\n";
    
    int* found{find_value(std::begin(array_one), std::end(array_one), 4)};
    
    if (found != std::end(array_one))
        std::cout << *found << '\n';
    
    return 0;
}
