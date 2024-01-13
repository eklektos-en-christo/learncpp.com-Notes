//
//  main.cpp
//  28.6_basic.file.IO
//
//  Created by Εκλεκτός εν Χριστώ on 12/13/23.
//

/*
 3 basic file IO classes in C++:
 - ifstream, derived from istream
 - ofstream, derived from ostream
 - fstream, derived from iostream
 
 To use file IO classes: include <fstream>
 
 File streams have to be explicitly set up by the programmer, simply instantiate an object of the
 appropriate file IO class, with the name of the file as a parameter, then use << or >> to write to or
 read data from the file, once done, explicitly call close() or just let the file IO variable go out of
 scope(destructor will close the file)
 
 -----------------------------------------------------------------------------------------------------------
 File output:
 
 it is also possible to use the put() function to write a single character to the file.
 
 -----------------------------------------------------------------------------------------------------------
 File Input: ifstream returns a 0 if we have reached the end of file, extraction operator breaks on
 whitespace, in order to read in entire lines, we use getline
 
 -----------------------------------------------------------------------------------------------------------
 Buffered output: anything that is output to a file stream may not be written to disk immediately
 
 Flushing the buffer: when a buffer is written to disk
 
 To manually flush the buffer: send ostream::flush() or std::flush to the output stream
 
 std::endl - also flushes the output stream
 
 Performance conscious program often use '\n' instead of std::endl to insert a newline into the output
 stream to avoid unnecessary flushing of the buffer
 
 -----------------------------------------------------------------------------------------------------------
 File modes: file is completely rewritten when the program is run again,
 
 File stream constructors take an optional second parameter that allows you to specify information about how
 the file should be opened, this parameter is called mode, and the valid flags that it accepts live in ios
 class
 
 app - opens the file in append mode
 ate - seeks to the end of the file before reading/writing
 binary - opens the file in binary mode instead of text mode
 in - opens the file in read mode, default for ifstream
 out - opens the file in write mode, default for ofstream
 trunc - erases the file if it already exists
 
 fstream defaults to read/write file mode, it is possible to specify multiple flags by bitwise ORing them
 together
 
 fstream may fail if std::ios::in is used and the file being opened doesn't exist, if you need to create a
 new file using fstream, use std::ios::out mode only
 
 -----------------------------------------------------------------------------------------------------------
 Explicitly opening the files using open() - it works like the file stream constructors, it takes a file
 name and an optional file mode
 
 -----------------------------------------------------------------------------------------------------------
 */

#include <iostream>
#include <fstream>
#include <string>

int main()
{
    /// ofstream - used for writing files
    std::ofstream out_to_file{ "output_file.txt" };
    
    /// if we couldn't open the output file stream for writing
    if (!out_to_file)
    {
        std::cout << "File could not be opened for writing\n";
        return 1;
    }
    
    /// writing to file using <<
    out_to_file << "Hello, World!\n";
    out_to_file << "What's up there? YOU\n";
    
    /// putting a single character
    out_to_file.put('a');
    out_to_file.put('\n');
    out_to_file.close();
    
    /// specify the file to read from using ifstream object
    std::ifstream input_file{ "output_file.txt" };
    
    /// if we couldn't open the input file stream for reading
    if(!input_file)
    {
        std::cerr << "File could not be opened for reading\n";
        return 1;
    }
    
    /// read while there is stuff left to read
    while (input_file)
    {
        std::string input_string;
        
        /*input_file >> input_string;*/
        
        /// put the stuff into a string and print it
        /// using the getline to read the whole line, extraction operation breaks at whitespace
        std::getline(input_file, input_string);
        std::cout << input_string << '\n';
    }
    
    out_to_file.close();
    
    /// writing to the existing file in append mode
    out_to_file.open("output_file.txt", std::ios::app);
    out_to_file << "hello there again\n";
    out_to_file << "hi\n";
    out_to_file << "hi\n";
    out_to_file.close();
    
    /// opening the file explicitly using open(), with append mode parameter
    out_to_file.open("output_file.txt", std::ios::app);
    out_to_file << "New data\n";
    
    return 0;
}   /// ofstream's destructor closes the file here
