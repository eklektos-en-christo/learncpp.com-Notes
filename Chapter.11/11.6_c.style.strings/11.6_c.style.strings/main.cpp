//
//  main.cpp
//  11.6_c.style.strings
//
//  Created by Εκλεκτός εν Χριστώ on 3/23/23.
//

/*
 String - a collection of sequential characters
 
 Strings - primary way in which we work with text in C++
 
 std::string - makes working with strings in C++ easy
 
 Modern C++ supports two different types of strings:
 1. std::string - part of the std library
 2. c-style strings - natively as inherited from the C language
 
 std::string - implemented using c-style strings
 
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 C style string - simply an array of characters that uses a null terminator
 
 Null terminator - special character, '\0', 0 in ASCII, used to indicate the end of the
 string
 
 C-style string - more generically called a null-terminated string
 
 to define a c style string - simply declare a char array and initialize it with a string
 literal
 
 C++ automatically adds a null terminator to the end of the string for us
 
 when declaring strings in this manner - good idea to use empty [] and let compiler
 calculate the length of the array, if you want to change the string later, you won't have
 to adjust the array length manually
 
 C style strings - follow all the same rules as arrays, means you can initialize the string
 upon creation but can't assign values to it using assignment operator after the
 initialization
 
 C style strings - are arrays, which means we can use [] to change individual characters
 
 when printing the c style string - std::cout prints all characters until it encounters the
 null terminator
 
 if accidentally overwrite the null terminator in a string - std::cout will just keep
 printing everything in adjacent memory slots until it happens to hit a 0
 
 it's fine - if the array is larger than the string it contains, cout will print until it
 encounters null terminator, rest array characters are ignored
 
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 C style string and std::cin -
 many cases where we don't know in advance how long our string is going to be
 
 example- a program where we need to ask the user to enter their name, how long is their
 name? we don't know until they enter it, in this case we can declare an array larger than
 we need
 
 if we’ve allocated an array of 255 characters to name, guessing that the user will not enter this many characters. Although this is commonly seen in C/C++ programming, it is poor programming practice, because nothing is stopping the user from entering more than 254 characters (either unintentionally, or maliciously).
 
 recommended way of reading a c style string using std::cin - using cin.getline(), this will
 read up to 254 chars into variable, leaving room for null terminator, any excess chars
 will be discarded, in this way we guarantee that we will not overflow the array
 
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Manipulating C-style strings:
 <cstring> : header, contains functions to manipulate C-style strings
 
 strcpy() - allows to copy a string to another string, commonly this is used to assign a
 value to a string
 
 strcpy() - can easily cause array overflows
 
 strncpy() - same as strcpy but allows to specify the size of the buffer and ensures
 overflow doesn't occur, but it doesn't ensure that strings are null terminated, so leaves
 a plenty of room for array overflow
 
 strcpy_s() - preferred in C++11, it adds a new parameter to define the size of the
 destination, not all compilers support this function, to use it, you have to define
 STDC_WANT_LIB_EXT1 with integer value 1, strlcpy() is a popular alternative, no universal
 solution recommended if you need to a copy a c-style string
 
 strlen() - returns the length of the c-style string without the null terminator
 std::size - returns the size of the entire array, regardless of what is in it
 
 other useful functions:
 strcat() - appends one string to another, dangerous
 strncat() - appends one string to another but with buffer length check
 strcmp() - compare two strings, returns 0 if equal
 strncmp() - compare two strings up to a specific number of characters, return 0 is equal
 
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Don't use c-style strings:
 use std::string in the <string> header
 std::string - easier, safer, more flexible
 
 for memory-limited devices - use 3rd party string library designed for the purpose or
 std::string_view
 
 RULE:
 use std::string or std::string_view instead of c-style strings
 
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

#define __STDC_WANT_LIB_EXT1__ 1
#include <iostream>
#include <iterator>     /// for std::size
#include <cstring>

int main()
{
    /// "string" - has 6 letters
    /// a null terminator \0 is added to the end of the "string" for us automatically
    /// "string" - actually is of length 7
    char my_string[]{"string"};
    const int length{static_cast<int>(std::size(my_string))};
    
    std::cout << "Length before loop: " << length << '\n';
    
    /// in the output - 0 printed at last of all characters, which is null terminator appended to the end of the string
    for (int index{0}; index < length; ++index)
        std::cout << static_cast<int>(my_string[index]) << ' ';
    
    std::cout << '\n';
    
    /// can't use the assignment after the initialization
//    my_string = "string changed";
    
    std::cout << my_string << '\n';
    /// can use [ ] to change the individual characters in the string
    my_string[1] = 'p';
    std::cout << my_string << '\n';
    
    /// 5 characters total - it's okay to have bigger array than the string
    char larger_array[20]{"leon"};
    /// cout will stop at null terminator, rest of characters in array are ignored
    std::cout << larger_array << '\n';
    
    /// 254 chars + null terminator
    /// it's a poor programming practice, nothing is stopping the user from entering more than 254 chars
    /// either unintentionally or maliciously
//    char name[255]{};
//    std::cout << "Enter your name: ";
//    std::cin >> name;
//    std::cout << "You entered: " << name << '\n';
    
    /// recommended way of reading a c style string using std::cin
    /// using cin.getline() function
    /// getline - will read up to 254 characters, leaving room for null terminator
    /// any excess chars will be discarded
    /// so in this way, we guarantee that we will not overflow the array
    char name1[255]{};
    std::cout << "Enter your name: ";
    std::cin.getline(name1, std::size(name1));
    std::cout << "You entered: " << name1 << '\n';
    
    char src[]{"copy this!"};
    char dest[50];
    /// strcpy function - to copy src into dest string
    std::strcpy(dest, src);
    std::cout << dest << '\n';
    
    char source[]{"copy this!"};
    /// length is only 3 characters
    char destination[3];
    /// array overflow, destination isn't big enough to hold the entire string
    std::strcpy(destination, source);
    std::cout << destination << '\n';
    
    char src1[]{"copy this!"};
    /// length of dest1 is only 5 chars
    char dest1[5];
    /// runtime error will occur in debug mode
//    strcpy_s(dest1, 5, src1);
    
    /// only using 5 chars - 4 letters + 1 null terminator
    char name2[20]{"leon"};
    /// strlen - prints the number of chars before the null terminator
    std::cout << "name has " << strlen(name2) << " characters!" << '\n';
    /// std::size - returns the size of entire array, regardless of what is in it
    std::cout << "name has " << std::size(name2) << " chars in the array!" << '\n';
    
    /// asking the user to enter a string
    char buffer[255]{};
    std::cout << "Enter a string: ";
    std::cin.getline(buffer, std::size(buffer));
    
    int spaces_found{0};
    /// strlen outside the loop, so length is calculated only once
    int buffer_length{static_cast<int>(std::strlen(buffer))};
    
    /// looping through all the characters user entered
    for (int index{0}; index < buffer_length; ++index)
        /// if current char is a space, count it
        if (buffer[index] == ' ')
            ++spaces_found;
    
    std::cout << "You typed " << spaces_found << " spaces!" << '\n';
    
    return 0;
}
