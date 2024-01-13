//
//  main.cpp
//  28.2_input.with.istream
//
//  Created by Εκλεκτός εν Χριστώ on 12/9/23.
//

/*
 -----------------------------------------------------------------------------------------------------------
 THE EXTRACTION OPERATOR(>>):used to read information from an input stream, C++ has predefined extraction
 operations for all of the built in data types
 
 It is a bad idea to make assumptions about how many characters the user will enter, the user may enter more
 than the characters are needed and it may overflow the buffer
 
 MANIPULATOR: an object that is used to modify a stream when applied with extraction(>>) or insertion(<<)
 operators
 
 std::endl - is also a manipulator, it prints a newline character and also flushes any buffered output
 residing in the buffer
 
 setw - lives in <iomanip>, can be used to limit the number of characters read in from a stream,
 
 To use setw: simply provide the max. number of characters to read as a parameter to setw() and insert it
 into the input statement
 
 -----------------------------------------------------------------------------------------------------------
 EXTRACTION AND WHITESPACE:
 
 >> operator - extraction operator skips any whitespaces, blanks, tabs and newlines
 
 istream - provides many functions that can be used to make the operator>> read the whitespaces also
 
 get() - simply gets a character from the input stream, it also has a string version that takes a maximum
 number of characters to read
 
 get() - doesn't read a newline character
 
 getline() - it works same as the get() but reads a newline also
 
 gcount() - tells how many characters were extracted by the last call of getline
 
 -----------------------------------------------------------------------------------------------------------
 A SPECIAL VERSION OF getline() FOR std::string - it lives outside the istream class, used for reading in
 variables of type std::string, it is included in <string> header
 
 -----------------------------------------------------------------------------------------------------------
 A FEW MORE USEFUL istream FUNCTIONS -
 
 ignore() - discards the first character in the stream
 
 ignore(int ncount) - discards the first n count characters
 
 peek() - to read a char from the stream without removing it from the stream
 
 unget() - Makes the most recently extracted character available again , so it can be read again by the
 next call, returns the last character read back into the stream
 
 putback(char ch) - allows you to put a char of your choice back into the stream to be read by the next call
 
 -----------------------------------------------------------------------------------------------------------
 */

#include <iostream>
#include <string>
#include <iomanip>      /// for setw

int main()
{
    char buffer[10];
    
    /// using the manipulator setw to limit the number of characters to read from the stream
    /// this will only read 9 characters from the stream, 1 character is for a terminator
    /// remaining characters will be left in the stream until the next extraction
    /*std::cin >> std::setw(10) >> buffer;*/
    
    char ch;
    
    /// extraction operator>> ignores whitespaces
    /*while (std::cin >> ch)
    {
        std::cout << ch;
    }*/
    
    /// a function from istream class
    /// it simply gets a character from the input stream
    /*while (std::cin.get(ch))
        std::cout << ch;*/
    
    char string_buffer[5];
    
    /// string version of get() function, takes the number of characters to read from the input stream
    /// it reads 4 characters, 1 character is for terminator, remaining characters were left in the input stream
    /*std::cin.get(string_buffer, 5);
    std::cout << string_buffer << '\n';*/
    
    /// remaining character from string_buffer is inputted in ch
    /*std::cin >> ch;
    std::cout << ch;*/
    
    char str_buf[11];
    
    /// this reads the newline character as well
    /// '.' - delimiter, stops the input if entered
    /*std::cin.getline(str_buf, 11, '.');
    std::cout << str_buf << '\n';
    
    /// tells the total characters extracted from the last call to getline
    std::cout << std::cin.gcount() << '\n';*/
    
    std::string my_string;
    
    /// reads in variables of type std::string, '.' is delimiter to stop the reading
    std::getline(std::cin, my_string, '.');
    std::cout << my_string << '\n';
    
    return 0;
}
