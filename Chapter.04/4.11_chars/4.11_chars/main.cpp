//
//  main.cpp
//  4.11_chars
//
//  Created by εκλεγμένοι εν Χριστώ on 9/16/22.
//

/*
 char: used to hold a character, can be a single character,
 letter, number, symbol or whitespace
 
 char: integral type
 
 char: integer stored by char are interpreted as ASCII
 characters.
 
 character literal: always placed between ''
 
 ASCII: 0-32 - unprintable, used for formatting and control
 printers. 32-127 - printable, represent letters, number
 characters, punctuation.
 
 ASCII code: number used to represent the character, example-
 97 is 'a'.
 
 Initialization: can initialize character variables with
 integers, but not preferred
 
 Warning:
 Be careful not to mix up character numbers with integer
 numbers.
 
 character numbers: represent numbers as text
 
 char range, size and default sign:
 size: 1byte
 by default: char may be signed or unsigned, usually is signed
 0-127 values: signed and unsigned chars can hold
 signed char can hold: number between -128 and 127
 unsigned char can hold: number between 0 and 255
 
 Escape sequences: characters in C++ that have special
 meaning
 Escape sequence: starts with backslash '\' character and then
 following letter or number
 
 Best practice
 Put stand-alone chars in single quotes
 
 wchar_t: should be avoided in all cases, deprecated
 
 char8_t, char16_t, or char32_t: for unicode compatibility
 
 Unicode characters can also be encoded using multiple 16-bit
 or 8-bit characters 
 */

#include <iostream>

int main()
{
    /// initializing character variable using character literal
    /// 'a' stored as 97
    char a{'a'};
    
    /// integer
    char b{98};
    
    /// code point for '2'
    char c{'2'};
    
    /// std::cout - prints the character variable an an ASCII character
    std::cout << a << '\n';
    std::cout << b << '\n';
    std::cout << 'c' << '\n';
    
    /// std::cin - lets enter multiple characters, char variable holds only
    /// one character, so std::cin will extract only first character from the input
    /// the rest will input is left in the input butter which std::cin uses
    /// and can be extracted with subsequent calls to std::cin
    std::cout << "Enter a character: ";
    char x{};
    std::cin >> x;
    std::cout << "You entered: " << x << '\n';
    std::cin >> x;
    std::cout << "You entered: " << x << '\n';
    std::cin >> x;
    std::cout << "You entered: " << x << '\n';
    
    /// escape sequence '\n' for new line
    std::cout << "Escape\nSequence\n";
    std::cout << "Horizontal\tTab" << '\n';
    std::cout << "Single \'Quote\'" << '\n';
    std::cout << "Double \"Quote\"" << '\n';
    std::cout << "Back\\Slash" << '\n';
    std::cout << "Hex \x6B" << '\n';
    
    return 0;
}
