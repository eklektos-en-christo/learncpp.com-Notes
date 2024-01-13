//
//  main.cpp
//  28.4_stream.classes.for.strings
//
//  Created by Εκλεκτός εν Χριστώ on 12/10/23.
//

/*
 -----------------------------------------------------------------------------------------------------------
 Stream classes for strings: allows us to use the << and >> to work with strings
 
 String streams: provide a buffer to hold data, they treat the strings as streams, these streams are not
 connected to an IO channel the way cin and cout are connected to keyboard, monitor etc. Primary uses of
 string streams is to buffer output for display at a later time or to process input line by line
 
 Six Stream classes for strings - istringstream, ostringstream, stringstream, all three used for reading and
 writing normal characters width strings
 
 wistringstream, wostringstream, wstringstream - used for reading and writing wide character strings
 
 To use the string streams - use the <sstream> header
 
 There are two ways to get the data into a string stream:
 - using the insertion << operator
 - using the str(string) function to set the value of the buffer
 
 Two ways to get data out of a stringstream:
 - using the str() function to retrieve the results of the buffer, it returns the whole value of the stream
 - using the extraction operator, it iterates through the string stream and returns the next extractable
   value in the stream
 
 -----------------------------------------------------------------------------------------------------------
 Conversion between strings and numbers: we can use insertion and extraction operators to convert strings
 to number and vice versa, << and >> know how to work with all of basic data types
 
 -----------------------------------------------------------------------------------------------------------
 Clearing the stringstream for reuse:
 
 several ways to empty a stringstream's buffer:
 - set the stringstream to empty string using str() with a blank c-style string
 - set the stringstream to empty string using str() with a blank std::string object
 
 When clearing out a stringstream: it is also a good idea to call the clear() function, clear resets any
 error flags that may have been set and returns the stream back to the OK state
 
 -----------------------------------------------------------------------------------------------------------
 */

#include <iostream>
#include <sstream>

int main()
{
    /// insert the data into stringstream using <<
    std::stringstream os;
    os << "hello12345\n";
    
    /// set the data to stringstream buffer using str()
    std::stringstream os_fun;
    os_fun.str("hello12345");
    
    /// using the str() to get the data out of a stringstream
    std::cout << os.str();
    
    std::stringstream num;
    num << "1234 1111 2222";
    
    /// >> extraction operator iterates through num variable and returns the next extractable value in the stream
    std::string value1;
    num >> value1;
    
    std::string value2;
    num >> value2;
    
    std::string value3;
    num >> value3;
    
    std::cout << value1 << '-' << value2 << '-' << value3 << '\n';
    /// str() returns the whole string, even if >> operator has already been used on the stream
    std::cout << num.str() << '\n';
    
    /*------------------------------------------------------*/
    /// converting the number into string
    /// creating a stringstream object
    std::stringstream my_os;
    /// preparing two number, one integer, another double
    int my_value{ 201234789 };
    double my_double{ 1111.11123 };
    
    /// insertion operator putting the values in stringstream,
    /// ' ' used for a space
    my_os << my_value << ' ' << my_double;
    
    /// create two strings
    std::string my_value1, my_value2;
    /// extract the both values separately in string variables
    /// ' ' helped to put the both values in separate variables
    my_os >> my_value1 >> my_value2;
    
    /// print the both strings
    std::cout << my_value1 << ' ' << my_value2 << '\n';
    /*------------------------------------------------------*/
    
    /// converting the string into numbers
    std::stringstream my_string;
    my_string << "12121 98.32";
    int my_int1;
    double my_double1;
    
    my_string >> my_int1 >> my_double1;
    
    std::cout << my_int1 << ' ' << my_double1 << '\n';
    /*------------------------------------------------------*/
    
    std::stringstream str_to_clear;
    str_to_clear << "data";
    
    /// clearing the stringstream buffer using empty c-style string, passed to str()
    str_to_clear.str("");
    str_to_clear << "changed";
    std::cout << str_to_clear.str() << '\n';
    
    /// clearing the stringstream buffer using empty std::string object, passed to str()
    str_to_clear.str(std::string{});
    str_to_clear << "changed again";
    /// clear resets any error flags that may have been set and returns the stream back to the OK state
    str_to_clear.clear();
    std::cout << str_to_clear.str() << '\n';
    
    return 0;
}
