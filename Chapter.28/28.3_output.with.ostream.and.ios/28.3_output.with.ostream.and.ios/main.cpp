//
//  main.cpp
//  28.3_output.with.ostream.and.ios
//
//  Created by Εκλεκτός εν Χριστώ on 12/9/23.
//

/*
 -----------------------------------------------------------------------------------------------------------
 Insertion operator(<<) - used to put information into an output stream, C++ has predefined insertion
 operations for all built-in data types
 
 ios & ios_base - one use of them is to control the formatting options for output
 
 -----------------------------------------------------------------------------------------------------------
 FORMATTING:
 
 Two ways to change the formatting options:
 - flags - boolean variables that can be turned on or off
 - manipulators - objects placed in a stream that affect the way things are input and output
 
 To switch a flag ON - use the setf() function with the appropriate flag as a parameter, it is also possible
 to turn on multiple ios flags at once using bitwise OR(|) operator
 
 To turn a flog OFF - use the unsetf() function
 
 Many flags belong to groups, called format groups
 
 Format group - a group of flags that perform similar(sometimes mutually exclusive) formatting options
 
 basefield - is a format group, contains the flags oct, hex and dec, they control the base of integral
 values, dec is the default flag set
 
 setf and unsetf are awkward, there is another way to set flags, that is to use manipulators, manipulators
 also are smart enough to turn off and on the appropriate flags
 
 -----------------------------------------------------------------------------------------------------------
 Useful formatters:
 
 Flags - live in the std::ios class
 Manipulators - live in std namespace
 Member Functions - live in std::ostream class
 
 std::ios::boolalpha - a flag, prints the boolean 0 or 1 to false or true
 
 std::boolalpha - a manipulator, works the same as std::ios::boolalpha flag
 std::noboolalpha -  manipulator, prints the true as 1 and false as 0
 
 std::ios::showpos - if this flag is set, the it prefixes the positive number with a + sign
 
 std::showpos - manipulator, works the same as std::ios::showpos
 std::noshowpos - turns off the std::showpos
 
 std::ios::uppercase - if this flag is set, uses uppercase letters
 
 std::uppercase  - manipulator, prints uppercase letters
 std::nouppercase - manipulator, turns off the std::uppercase
 
 std::ios::basefield - format group, contains flags
 
 std::ios::dec, std::ios::hex, std::ios::oct - all are flags of std::ios::basefield format group, dec prints
 the value decimal, hex prints in hexadecimal, oct prints in octal
 
 std::ios::basefield - is no flag, prints the value according to leading characters of value
 
 std::dec, std::oct, std::hex - manipulators, works the same as std::ios::basefield flags
 
 Sometimes the manipulators are not available, so flags can be used and vice versa
 
 -----------------------------------------------------------------------------------------------------------
 Precision, notation and decimal points:
 
 it is possible to change the precision and format with which the floating point numbers are displayed
 
 /// flags
 std::ios::fixed - uses decimal notation for float
 std::ios::scientific - uses scientific notation for float
 std::ios::showpoint - always show a decimal point and trailing 0's for float
 std::ios::floatfield - format group, uses fixed for numbers with few digits, scientific otherwise
 
 /// manipulators
 std::fixed - uses decimal notation for values
 std::scientific - uses scientific notation for values
 std::showpoint - show a decimal point and trailing 0's for float values
 std::noshowpoint - turns off the std::showpoint
 std::setprecision(int) - sets the precision of float, lives in <iomanip>
 
 /// member functions
 std::ios_base::precision() - returns the current precision of float
 std::ios_base::precision(int) - sets the precision of float and returns old precision
 
 if fixed or scientific notation is used: precision determines how many decimal places in the fraction is
 displayed, if the precision is less than the number of significant digits, the number will be rounded
 
 -----------------------------------------------------------------------------------------------------------
 Width, fill characters and justification: the numbers are printed without any regard to the space around
 them, it is possible to left or right justify the printing of numbers, to do this we need to define a field
 width, this defines the number of output spaces a value will have, if the actual number printed is smaller
 than the field with, it will be left or right justified as specified, if the actual number is larger than
 the field width, it will not be truncated, it will overflow the field
 
 std::ios::internal - left justifies the sign of the number and right justifies the value
 std::ios::left - left justifies the sign and value
 std::ios::right - right justifies the sign and value
 
 std::internal - left justifies the sign of the number and right justifies the value
 std::left - left justifies the sign and value
 std::right - right justifies the sign and value
 std::setfill(char) - sets the parameter as the fill characters, lives in <iomanip>
 std::setw(int) - sets the field width for input and output to the parameter, lives in <iomanip>
 
 std::basic_ostream::fill() - returns the current fill character
 std::basic_ostream::fill(char) - sets the fill character and returns the old fill character
 std::ios_base::width() - returns the current field width
 std::ios_base::width(int) - sets the current field width and returns old field width
 
 width(int), setw(int) - are used to set the field width, default justification is "right", setw and width
 both affect the next output statement, they are not persistent like other flags and manipulators
 
 -----------------------------------------------------------------------------------------------------------
 */

#include <iostream>
#include <iomanip>

int main()
{
    /// setf() - used to turn on the showpos flag
    /// showpos flag passed as a parameter to setf()
    std::cout.setf(std::ios::showpos);
    std::cout << 345 << '\n';
    
    /// turning on multiple ios flags together using bitwise OR(|) operator
    /// E as exponent in capital letter in the output
    std::cout.setf(std::ios::uppercase | std::ios::showpos);
    std::cout << 2229860867.23f <<'\n';
    
    /// unsetting the multiple flags using unsetf()
    std::cout.unsetf(std::ios::uppercase | std::ios::showpos);
    std::cout << 2229860867.23f <<'\n';
    
    /// this doesn't work because setf() only turns flags on
    /// setf() is not smart enough to turn the mutually exclusive flags off
    std::cout.setf(std::ios::hex);
    std::cout << 9198982 << '\n';
    
    /// one solution is to set the dec flag OFF and then set the hex flag ON
    std::cout.unsetf(std::ios::dec);
    std::cout.setf(std::ios::hex);
    std::cout << 9198982 << '\n';
    
    std::cout.unsetf(std::ios::dec | std::ios::hex);
    /// another solution is to use a different form of setf() that takes two parameters
    /// the first parameter it takes is the flag that we want to set
    /// the second parameter is the format group to which the flag belongs to
    std::cout << 9198982 << '\n';
    /// hex - a flag        basefield - format group
    /// this turns all the flags OFF in the format group except the flag passed in to setf()
    std::cout.setf(std::ios::hex, std::ios::basefield);
    std::cout << 9198982 << '\n';
    
    /// another way of setting the flags - using manipulators
    std::cout << std::dec << 9198982 << '\n';
    std::cout << std::hex << 9198982 << '\n';
    std::cout << std::dec;
    
    /// by default the boolalpha flag is OFF
    std::cout << true << ' ' << false << '\n';
    /// setting the boolalpha flag through setf()
    std::cout.setf(std::ios::boolalpha);
    std::cout << true << ' ' << false << '\n';
    
    /// turning off the boolalpha flag through noboolalpha manipulator
    std::cout << std::noboolalpha;
    std::cout << true << ' ' << false << '\n';
    /// turning ON the boolalpha through boolalpha manipulator
    std::cout << std::boolalpha;
    std::cout << true << ' ' << false << '\n';
    
    /// turning ON the + prefix with ios flag showpos using setf()
    std::cout.setf(std::ios::showpos);
    std::cout << 99 << '\n';
    
    /// turning OFF the + prefix with manipulator noshowpos
    std::cout << std::noshowpos;
    std::cout << 99 << '\n';
    /// turning ON the + prefix with manipulator showpos
    std::cout << std::showpos;
    std::cout << 99 << '\n';
    std::cout << std::noshowpos;
    
    /// turning ON the uppercase using ios flag uppercase
    std::cout.setf(std::ios::uppercase);
    std::cout << 13872847208374.24388 << '\n';
    
    /// turning OFF the uppercase using manipulator
    std::cout << std::nouppercase;
    std::cout << 13872847208374.24388 << '\n';
    /// turning ON the uppercase using manipulator uppercase
    std::cout << std::uppercase;
    std::cout << 13872847208374.24388 << '\n';
    std::cout << std::nouppercase;
    
    /// setting the dec hex and oct flags using special form of setf
    std::cout << 2222 << '\n';
    std::cout.setf(std::ios::dec, std::ios::basefield);
    std::cout << 2222 << '\n';
    std::cout.setf(std::ios::hex, std::ios::basefield);
    std::cout << 2222 << '\n';
    std::cout.setf(std::ios::oct, std::ios::basefield);
    std::cout << 2222 << '\n';
    
    /// setting the dec, hex and oct using manipulators
    std::cout << std::hex << 9987708 << '\n';
    std::cout << std::oct << 9987708 << '\n';
    std::cout << std::dec << 9987708 << '\n';
    
    /// fixed is used
    std::cout << std::fixed;
    std::cout << std::setprecision(3) << 1234.56 << '\n';
    std::cout << std::setprecision(4) << 1234.56 << '\n';
    std::cout << std::setprecision(5) << 1234.56 << '\n';
    std::cout << std::setprecision(6) << 1234.56 << '\n';
    std::cout << std::setprecision(7) << 1234.56 << '\n';
    
    /// scientific is used
    std::cout << std::scientific;
    std::cout << std::setprecision(3) << 1234.56 << '\n';
    std::cout << std::setprecision(4) << 1234.56 << '\n';
    std::cout << std::setprecision(5) << 1234.56 << '\n';
    std::cout << std::setprecision(6) << 1234.56 << '\n';
    std::cout << std::setprecision(7) << 1234.56 << '\n';
    
    std::cout.unsetf(std::ios::scientific | std::ios::fixed);
    
    /// no fixed or scientific is used, precision determines how many significant digits should be displayed
    std::cout << std::setprecision(3) << 1234.56 << '\n';   /// rounded
    std::cout << std::setprecision(4) << 1234.56 << '\n';   /// rounded
    std::cout << std::setprecision(5) << 1234.56 << '\n';
    std::cout << std::setprecision(6) << 1234.56 << '\n';
    std::cout << std::setprecision(7) << 1234.56 << '\n';
    
    /// make the stream write a decimal point and trailing zeroes
    std::cout << std::showpoint;
    std::cout << std::setprecision(3) << 1234.56 << '\n';
    std::cout << std::setprecision(4) << 1234.56 << '\n';
    std::cout << std::setprecision(10) << 1234.56 << '\n';
    std::cout << std::setprecision(6) << 1234.56 << '\n';
    std::cout << std::setprecision(12) << 1234.56 << '\n';
    
    /// normal value with no field width
    std::cout << -12345 << '\n';
    /// setting the field width, right justified by default
    std::cout << std::setw(10) << -12345 << '\n';
    /// setting the justification to left
    std::cout << std::setw(10) << std::left << -12345 << '\n';
    std::cout << std::setw(10) << std::left << -12345 << '\n';
    std::cout << std::setw(10) << std::left << -12345 << '\n';
    /// setting the justification to right
    std::cout << std::setw(10) << std::right << -12345 << '\n';
    std::cout << std::setw(10) << std::right << -12345 << '\n';
    std::cout << std::setw(10) << std::right << -12345 << '\n';
    
    /// internal - sets the sign to left justified and value to right justified
    std::cout << std::setw(10) << std::internal << -12345 << '\n';
    
    /// setting the fill character
    std::cout.fill('-');
    std::cout << -12345 << '\n';
    std::cout << std::setw(10) << -12345 << '\n';
    std::cout.fill('<');
    std::cout << std::setw(10) << std::left << -12345 << '\n';
    std::cout.fill('|');
    std::cout << std::setw(10) << std::right << -12345 << '\n';
    std::cout.fill('*');
    std::cout << std::setw(10) << std::internal << -12345 << '\n';
    
    return 0;
}
